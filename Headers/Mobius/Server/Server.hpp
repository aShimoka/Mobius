
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Server.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 04/05/2019.
 */

#ifndef _ProjectMobius_hppServer
#define _ProjectMobius_hppServer

#include <Mobius/Core/Reflection/Object.hpp>
#include <Mobius/Core/Serializer/ConfigNode.hpp>

namespace Mobius {

/**
 * Base class for all the server instances.
 * Used by the engine to enable specific settings of the application.
 */
class Server : public Object {
    MOBJECT_ABSTRACT_BODY(Mobius::Server, Mobius::Object)
    
    // ---  Methods ---
        // -- Public Methods --
            /**
             * Class constructor.
             */
            Server();
    
            /**
             * Class destructor.
             */
            virtual ~Server();
    
            /**
             * Main setup method.
             * Handles the given ConfigNode object and parses it for configuration info.
             *
             * @param configRoot The root ConfigNode to set this server up.
             */
            virtual void setupServer(ConfigNode::WeakReference configRoot) = 0;
    
            /**
             * Server closing method.
             * Triggered when the application shuts down.
             */
            virtual void serverQuit() = 0;
    // --- /Methods ---
    
    // ---  Attributes ---
    // --- /Attributes ---
};

}

#endif /* _ProjectMobius_hppServer */
