
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file RenderPass.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 06/05/2019.
 */

#ifndef _ProjectMobius_hppRenderPass
#define _ProjectMobius_hppRenderPass

#include <Mobius/Server/Render/Pipeline/Manager.hpp>
#include <Mobius/Server/Render/Buffer/Manager.hpp>

namespace Mobius {
namespace Render {

/**
 * Simple helper class for the render passes.
 */
class RenderPass {
    // ---  Methods ---
        // -- Public Methods --
        public:
            /**
             * Creates a new RenderPass.
             *
             * @param window The name of the window for this render pass.
             */
            RenderPass(std::string window);
    
            /**
             * Class desctructor.
             * Commits the rendering if it had not been done previously.
             */
            ~RenderPass();
    
            /**
             * Sets the given vertex buffer at the given index.
             *
             * @param buffer The descriptor of the buffer to set.
             * @param index The index to set the buffer at.
             */
            void setVertexBufferAt(Buffer::Descriptor buffer, unsigned int index);
    
            /**
             * Sets the given fragment buffer at the given index.
             *
             * @param buffer The descriptor of the buffer to set.
             * @param index The index to set the buffer at.
             */
            void setFragmentBufferAt(Buffer::Descriptor buffer, unsigned int index);
    
            /**
             * Renders with the current buffer setup.
             */
            void render(unsigned int triangleCount, unsigned int firstTriangle = 0);
    
            /**
             * Commits all the changes to the window.
             */
            void commit();
    // --- /Methods ---
    
    // ---  Attributes ---
        // -- Private Attributes --
        private:
            /** Pipeline descriptor of the pass' parent. */
            Pipeline::Descriptor _descriptor;
    
            /** State of the pass. Aka. was it commited ? */
            bool _bIsCommited;
    // --- /Attributes ---
};

}
}

#endif /* _ProjectMobius_hppRenderPass */
