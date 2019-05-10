//
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file ConfigManager.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 03/05/2019.
 */

#include <Mobius/Core/Serializer/ConfigManager.hpp>
#include <Mobius/Core/Reflection/Factory.hpp>

#include <unistd.h>

namespace Mobius {

ConfigNode::Reference ConfigManager::recursiveParse(tinyxml2::XMLElement * element) {
    // Prepare the next config node.
    ConfigNode::Reference node = new ConfigNode();;
    
    // Check the type of the node.
    std::string nodeName = std::string(element->Name());
    if (nodeName == "Flags") {
        // Create the flags list.
        node = new ConfigHelpers::FlagList();
    } else if (Factory::classExists(nodeName)) {
        // Create the object.
        node = Factory::makeObject(nodeName);
    } 
    
    // Set the name of the node.
    node->setName(element->Name());
    // Set the text of the node.
    if (element->GetText()) node->setText(element->GetText());
    
    // Parse the attributes of the node.
    for (const tinyxml2::XMLAttribute * a = element->FirstAttribute(); a; a = a->Next()) {
        // Add the attribute to the object.
        node->addAttribute(a->Name(), a->Value());
    }
    
    // Parse the children of the node.
    for (tinyxml2::XMLElement * e = element->FirstChildElement(); e; e = e->NextSiblingElement()) {
        // Recursively parse the node.
        node->addChild(recursiveParse(e));
    }
    
    // Return the node.
    return node;
}

ConfigNode::WeakReference ConfigManager::loadConfig(std::string configFile) {
    // Get the instance.
    WeakPointer<ConfigManager> inst = ConfigManager::instance();
    
    // Resolve the absolute path if necessary.
    if (configFile[0] != '/') {
        char * cwd = getcwd(NULL, 0);
        configFile = std::string(cwd) + '/' + configFile;
        free(cwd);
    }
    
    // If the config file was already loaded.
    auto config = inst->_configHandlerMap->find(configFile);
    if (config == inst->_configHandlerMap->end()) {
        // Open the file.
        tinyxml2::XMLDocument doc;
        doc.LoadFile(configFile.c_str());
        if (!doc.Error()) {
            // Recursively parse the document.
            ConfigNode::Reference root = inst->recursiveParse(doc.FirstChildElement());
            inst->_configHandlerMap->insert(std::make_pair(configFile, root));
            
            // Return the reference.
            return root;
        } else {
            // Return a null pointer.
            fprintf(stderr, "XML Error: %s\n", doc.ErrorStr());
            return nullptr;
        }
    } else {
        return config->second;
    }
    
}

ConfigManager::ConfigManager() :
    _configHandlerMap(RootConfigNodeMap::create())
{}

ConfigManager::~ConfigManager() {
    _configHandlerMap->clear();
}

WeakPointer<ConfigManager> ConfigManager::instance() {
    static ConfigManager instance;
    return &instance;
}

}
