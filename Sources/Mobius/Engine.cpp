/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Engine.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 03/05/2019.
 */

#include <Mobius/Engine.hpp>
#include <Mobius/Core/Serializer/ConfigManager.hpp>
#include <Mobius/Core/Reflection/Factory.hpp>
#include <Mobius/Server/Render/RenderPass.hpp>
#include <Mobius/Math/Matrix.hpp>

#include <stdio.h>

MOBJECT_DECLARE(Mobius::Manager)

Mobius::Manager::~Manager() {}

bool Mobius::Engine::onSetup() {
    try {
        // Configure the application.
        bool state = instance()->loadEngineConfiguration();
        
        // Load the Main Manager.
        instance()->_main = Factory::makeObject("MainManager");
        state &= instance()->_main->start();
        
        return state;
    } catch (std::exception& exception) {
        // Print the error.
        fprintf(stderr, "Error thrown during engine setup: %s\n", exception.what());
        return false;
    }
}

bool Mobius::Engine::onLoop(double deltaTime) {
    return instance()->_main->loop(deltaTime);
}

void Mobius::Engine::onClose() {
    instance()->_main->close();
    
    // Close each server.
    for (auto it = instance()->_serverList->begin(); it != instance()->_serverList->end(); it++) {
        it->second->serverQuit();
    }
}
Mobius::Engine::Engine() :
    _main(nullptr),
    _serverList(ServerList::create())
{}

Mobius::Engine::~Engine() {
    _serverList->clear();
}

Mobius::WeakPointer<Mobius::Engine> Mobius::Engine::instance() {
    static Mobius::Engine instance;
    return &instance;
}

bool Mobius::Engine::loadEngineConfiguration() {
    // Get the configuration node.
    ConfigNode::WeakReference configRoot = ConfigManager::loadConfig("Config/EngineConfig.xml");
    
    // If the configuration is valid.
    if (configRoot.isValid()) {
        // Get all the server elements.
        auto server = configRoot->getChildElementsByName("Server");
        
        // Loop through them.
        for (auto it = server.begin(); it != server.end(); it++) {
            ConfigNode::WeakReference node = *it;
            
            // Validate the identifier.
            if (node->hasAttribute("id")) {
                // Initialize the server.
                if (Factory::classExists(node->getAttribute("id"))) {
                
                    // Create the server.
                    Server::Reference srv = Factory::makeObject(node->getAttribute("id"));
                    
                    // Get the server config node.
                    ConfigNode::WeakReference serverConfig;
                    if ((*it)->hasAttribute("config")) {
                        serverConfig = ConfigManager::loadConfig(std::string("Config/") + node->getAttribute("config") + std::string(".xml"));
                    } else {
                        serverConfig = ConfigManager::loadConfig(std::string("Config/") + node->getAttribute("id") + std::string("Config.xml"));
                    }
                    
                    // Set the server up.
                    srv->setupServer(serverConfig);
                    
                    // Store the server.
                    _serverList->insert(std::make_pair(node->getAttribute("id"), srv));
                    
                } else {
                    // Print the error.
                    printf("No such server : %s\n", node->getAttribute("id").c_str());
                    return false;
                }
            } else {
                // Print the error.
                printf("A server node ha no id field !\n");
                return false;
            }
        }
        
        // Return a success.
        return true;
        
    } else {
        // Print the error and return a false.
        printf("Could not load engine configuration file.\n");
        return false;
    }
}
