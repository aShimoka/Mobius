
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Render.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 04/05/2019.
 */

#ifndef _ProjectMobius_hppRender
#define _ProjectMobius_hppRender

#include <Mobius/Server/Server.hpp>
#include <Mobius/Server/Render/Pipeline/Descriptor.hpp>

#include <map>

namespace Mobius {
namespace Render {

/**
 * Main redering server.
 * This server allocates and is responsible for everything rendering related :
 * Creating and closing windows, prepareing the rendering context, rendering vertices ...
 */
class RenderServer : public Server {
    MOBJECT_BODY(Mobius::Render::RenderServer, Mobius::Server)
    // ---  Methods ---
        // -- Public Methods --
        public:
            /**
             * Class constructor.
             */
            RenderServer();
    
            /**
             * Class destructor.
             */
            ~RenderServer();
    
            /**
             * Main setup method.
             * Handles the given ConfigNode object and parses it for configuration info.
             *
             * @param configRoot The root ConfigNode to set this server up.
             */
            virtual void setupServer(ConfigNode::WeakReference configRoot) override;
    
            /**
             * Server closing method.
             * Triggered when the application shuts down.
             */
            virtual void serverQuit() override;
    
        // -- Private Methods --
        private:
            /**
             * Returns the Render server static instance.
             *
             * @return The singleton render instance.
             */
            static RenderServer::WeakReference instance();
    
            /**
             * Parses the pipeline configuration.
             * Creates all the required rendering pipelines.
             *
             * @param configRoot The root node of the pipeline that needs to be configured.
             */
            void parsePipelineNode(ConfigNode::WeakReference configRoot);
    // --- /Methods ---
};

}
}

#endif /* _ProjectMobius_hppRender */
