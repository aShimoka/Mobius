
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Engine.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 03/05/2019.
 */

#ifndef _ProjectMobius_hppEngine
#define _ProjectMobius_hppEngine

#include <Mobius/Server/Server.hpp>
#include <Mobius/Core/Memory/StrongPointer.hpp>
#include <Mobius/Core/Memory/WeakPointer.hpp>

#include <map>
#include <string>


namespace Mobius {

class Manager : public Object {
    MOBJECT_ABSTRACT_BODY(Mobius::Manager, Mobius::Object)
    // ---  Methods ---
        // -- Public Methods --
        public:
            virtual bool start() = 0;
            virtual bool loop(double deltaTime) = 0;
            virtual void close() = 0;
            virtual ~Manager();
    // --- /Methods ---
};

/**
 * Main engine class.
 * Static class that does not do much by itself.
 *
 * It starts by loading the EngineConfig.xml file and parsing it.
 * It resolves all the servers that should boot up,
 * TODO : Resolve game manager and/or levels.
 */
class Engine {
    // Type alias for the server list.
    typedef StrongPointer<std::map<std::string, Server::Reference>> ServerList;
    
    // ---  Methods ---
        // -- Public Methods --
        public:
            /**
             * Main setup event.
             * Triggered by the application on its startup.
             * This is were the settings are parsed.
             */
            static bool onSetup();
    
            /**
             * Main loop event.
             * Triggered by the application's run loop.
             * Its exection should be executed about 60 times a second.
             * If it returns true, the application will start to shutdowm.
             *
             * @param deltaTime The time elapsed since the last call to onLoop.
             * @return If true, the the application will close down.
             */
            static bool onLoop(double deltaTime);
    
            /**
             * Main close event.
             * Triggered by the application on its closure.
             * Here all resources allocated will be freed.
             */
            static void onClose();
    
        // -- Private Methods --
        private:
            /**
             * Class constructor.
             */
            Engine();
    
            /**
             * Class destructor.
             */
            virtual ~Engine();
    
            /**
             * Singleton instance getter.
             */
            static WeakPointer<Engine> instance();
    
            /**
             * Loads and parses the engine's configuration file.
             * It is expected to be found within the Config/ folder.
             */
            bool loadEngineConfiguration();
    // --- /Methods ---
    
    // ---  Attributes ---
        // -- Private Attributes --
            /** List of all the instantiated servers. */
            ServerList _serverList;
    
            /** Main application manager. */
            Manager::Reference _main;
    // --- /Attributes ---
};

}

#endif /* _ProjectMobius_hppEngine */
