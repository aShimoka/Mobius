//
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Render.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 06/05/2019.
 */

#ifndef _ProjectMobius_hRender
#define _ProjectMobius_hRender

#include <Mobius/Server/Render/Pipeline/Descriptor.hpp>
#include <Mobius/Server/Render/Buffer/Descriptor.hpp>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Allows the creation of a new RenderPass object.
 *
 * @param descriptor The descriptor of the pipeline that should render objects.
 */
void sMB_RNDR_PASS_create(cMB_RNDR_PIP_Descriptor descriptor);

/**
 * Defines a buffer in a given vertex shader's index.
 *
 * @param pipeDescriptor The descriptor of the pipeline to get the pass from.
 * @param buffDescriptor The descriptor of the buffer to set in the pipeline.
 * @param index The vertex shader's buffer index.
 */
void sMB_RNDR_PASS_setVertexBufferAt(cMB_RNDR_PIP_Descriptor pipeDescriptor, cMB_RNDR_BUF_Descriptor buffDescriptor, unsigned int index);

/**
 * Defines a buffer in a given fragment shader's index.
 *
 * @param pipeDescriptor The descriptor of the pipeline to get the pass from.
 * @param buffDescriptor The descriptor of the buffer to set in the pipeline.
 * @param index The fragment shader's buffer index.
 */
void sMB_RNDR_PASS_setFragmentBufferAt(cMB_RNDR_PIP_Descriptor pipeDescriptor, cMB_RNDR_BUF_Descriptor buffDescriptor, unsigned int index);

/**
 * Renders the given triangles.
 *
 * @param pipeDescriptor The descriptor of the pipeline to render.
 * @param count The number of triangles to draw.
 * @param from The vertex to start from in the vertex array.
 */
void sMB_RNDR_PASS_renderTriangles(cMB_RNDR_PIP_Descriptor pipeDescriptor, unsigned int count, unsigned int from);

/**
 * Commit the rendered texture to the window.
 *
 * @param pipeDescriptor The descriptor of the pipeline to commit.
 */
void sMB_RNDR_PASS_commit(cMB_RNDR_PIP_Descriptor pipeDescriptor);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* _ProjectMobius_hRender */
