
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file ConfigHandler.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 02/05/2019.
 */

#ifndef _ProjectMobius_hppConfigManager
#define _ProjectMobius_hppConfigManager

#include <Mobius/Core/Memory/StrongPointer.hpp>
#include <Mobius/Core/Serializer/ConfigNode.hpp>

#include <TinyXML/TinyXML2.h>
#include <map>
#include <string>

namespace Mobius {

// Type alias for the map holding all the configuration files and their full system path.
typedef StrongPointer<std::map<std::string, ConfigNode::Reference>> RootConfigNodeMap;

/**
 * Singleton class responsible for the management
 * of engine configuration file.
 * Uses the TinyXML2 library to parse XML documents.
 */
class ConfigManager {
    // ---  Methods ---
        // -- Public Methods --
        public:
            /**
             * Loads the given config file.
             */
            static ConfigNode::WeakReference loadConfig(std::string configFile);
    
        // -- Private Methods --
        private:
            /**
             * Class constructor.
             */
            ConfigManager();
    
            /**
             * Class destructor.
             */
            ~ConfigManager();
    
            /**
             * Returns the singleton class instance.
             */
            static WeakPointer<ConfigManager> instance();
    
            /**
             * Recursive method.
             * Parses the given xml element and its children.
             *
             * @param element The XMLElement to parse.
             * @return The new created node.
             */
            ConfigNode::Reference recursiveParse(tinyxml2::XMLElement * element);
    
    // --- /Methods ---
    
    // ---  Attributes ---
        // -- Private Attributes --
        private:
            /** Map of all the ConfiNode roots. */
            RootConfigNodeMap _configHandlerMap;
    // --- /Attributes ---
};

}

#endif /* _ProjectMobius_hppConfigManager */
