//
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file RenderPass.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 06/05/2019.
 */

#include <Mobius/Server/Render/RenderPass.hpp>
#include <Mobius/Server/Render/Pipeline/Manager.hpp>
#include <Mobius/Platforms/Apple/Bridge/Swift/Render.h>

namespace Mobius {
namespace Render {

RenderPass::RenderPass(std::string window) {
    // Get the pipeline object.
    _descriptor = Pipeline::Manager::queryPipeline(window);
    
    // Unset the comit flag.
    _bIsCommited = false;
    
    // Create the render pass.
    sMB_RNDR_PASS_create(_descriptor);
}

RenderPass::~RenderPass() {
    // Call the commit method.
    commit();
}

void RenderPass::setVertexBufferAt(Buffer::Descriptor buffer, unsigned int index) {
    // Call the back-end method.
    sMB_RNDR_PASS_setVertexBufferAt(_descriptor, buffer, index);
}

void RenderPass::setFragmentBufferAt(Buffer::Descriptor buffer, unsigned int index) {
    // Call the back-end method.
    sMB_RNDR_PASS_setFragmentBufferAt(_descriptor, buffer, index);
}

void RenderPass::render(unsigned int triangleCount, unsigned int firstTriangle) {
    // Call the back-end method.
    sMB_RNDR_PASS_renderTriangles(_descriptor, triangleCount, firstTriangle);
}

void RenderPass::commit() {
    // If the pass was not commited yet.
    if (!_bIsCommited) {
        // Call the back-end commit.
        sMB_RNDR_PASS_commit(_descriptor);
    }
}

}
}
