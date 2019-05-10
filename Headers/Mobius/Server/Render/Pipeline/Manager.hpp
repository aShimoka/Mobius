
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Manager.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 05/05/2019.
 */

#ifndef _ProjectMobius_hpp_RenderServer_Pipeline_Manager
#define _ProjectMobius_hpp_RenderServer_Pipeline_Manager

#include <Mobius/Core/Serializer/ConfigNode.hpp>
#include <Mobius/Server/Render/Pipeline/Descriptor.hpp>

#include <string>

namespace Mobius {
namespace Render {
namespace Pipeline {

/**
 * Manager class responsible for all the pipelines.
 * Allows the creation, query, updqte and closure of pipelines.
 * Uses the Platform/ specific code.
 * NOTE : For now, only compatible with macOS.
 */
class Manager {
    // ---  Methods ---
        // -- Public Methods --
        public:
            /**
             * Creates a new rendering pipeline.
             * Uses the given Pipeline Descriptor to prepare the pipeline.
             *
             * @param window The identifier of the window in which the pipeline should be created.
             * @param descriptor The pipeline descriptor for the pipeline.
             * @return A descriptor filled with the info of the actually created pipeline.
             */
            static Descriptor createPipeline(std::string window, Descriptor descriptor);
    
            /**
             * Queries the back-end about a pipeline.
             * Fills a Descriptor and returns it.
             *
             * @param window The name of the window holding the queried pipeline.
             * @return The filled Descriptor object.
             */
            static Descriptor queryPipeline(std::string window);
    
            /**
             * Updates the parameters of the given pipeline.
             *
             * @param window The name of the window holding the updated pipeline.
             * @param descriptor The descriptor object holding the up-to-date values.
             * @return A descriptor filled with the info of the actually updated pipeline.
             */
            static Descriptor updatePipeline(std::string window, Descriptor descriptor);
    
            /**
             * Closes the pipeline and stops all rendering.
             *
             * @param window The name of the window holding the pipeline to close.
             */
            static void closePipeline(std::string window);
    
            /**
             * Parses the given configuration node for a pipeline descriptor.
             * Creates the descriptor if its configuration is correct.
             *
             * @param configRoot The root configuration node to parse.
             */
            static void parseConfig(ConfigNode::WeakReference configRoot);
    
            /**
             * Create a new render pass.
             * This can then be used to render to the window object.
             *
             * @param window The window that holds the pipeline into which rendering should happen.
             * @return The render pass object able to render on the pipeline.
             */
            //static RenderPass createRenderPass(std::string window);
    // --- /Methods ---
};

}
}
}

#endif /* _ProjectMobius_hpp_RenderServer_Pipeline_Manager */
