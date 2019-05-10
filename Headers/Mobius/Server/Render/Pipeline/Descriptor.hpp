
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Descriptor.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 05/05/2019.
 */

#ifndef _ProjectMobius_hpp_RenderServer_Pipeline_Descriptor
#define _ProjectMobius_hpp_RenderServer_Pipeline_Descriptor

#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

const unsigned int cMB_RNDR_PIP_BackfaceCulling = 1;
const unsigned int cMB_RNDR_PIP_FrontfaceCulling = 2;

/**
 * Descriptor object for the Pipelines.
 * Simplifies the transactions with the back-end.
 */
typedef struct cMB_RNDR_PIP_Descriptor {
    // ---  Attributes ---
        // -- Public Attributes --
            /** Identifier of the window that this pipeline belongs to. */
            unsigned int window;
    
            /** Name of the fragment function used in the pipeline. */
            const char * fragment;
    
            /** Name of the vertex function used in the pipeline. */
            const char * vertex;
    
            /** Clear color for the pipeline's texture. */
            float clearColor[4];
    
            /** Identifier of the buffer manager assigned to this pipeline. */
            unsigned int bufferManager;
    
            /** Culling mode of rendering. */
            unsigned int culling;
    // --- /Attributes ---
} cMB_RNDR_PIP_Descriptor;

#ifdef __cplusplus
}

#include <Mobius/Core/Reflection/Object.hpp>

namespace Mobius {
namespace Render {
namespace Pipeline {

class Descriptor : public cMB_RNDR_PIP_Descriptor, public Mobius::Object {
    MOBJECT_BODY(Mobius::Render::Pipeline::Descriptor, Mobius::Object)
    
    // ---  Methods ---
        // -- Public Methods --
            /**
             * Creates a new rendering pipeline.
             * Fills the members with the given attributes.
             *
             * @param window The identifier of the window that this pipeline renders into.
             * @param fragment The name of the fragment shader used in this pipeline.
             * @param vertex The name of the vertex shader used in this pipeline.
             * @param clearColor RGBA color used to clear the framebuffer before rendering.
             * @param bufferManager The identifier of the bufferManager assigned to this pipeline.
             * @param culling One of cMB_RNDR_PIP_BackfaceCulling or cMB_RNDR_PIP_FrontfaceCulling.
             */
            Descriptor(unsigned int window, const char * fragment, const char * vertex, const float * clearColor, unsigned int bufferManager, unsigned int culling);
    
            /**
             * Creates a default rendering pipeline object.
             * It will be set in an invalid state.
             */
            Descriptor();
    
            /**
             * Copy constructor.
             * Creates a new Descriptor from a cMB_RNDR_PIP_Descriptor object.
             *
             * @param copy The descriptor to copy the values from.
             */
            Descriptor(const cMB_RNDR_PIP_Descriptor& copy);
    // --- /Methods ---
};

}
}
}

#endif

#endif /* _ProjectMobius_hpp_RenderServer_Pipeline_Descriptor */
