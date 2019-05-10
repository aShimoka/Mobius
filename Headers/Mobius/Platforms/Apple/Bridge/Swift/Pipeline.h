
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Render.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 04/05/2019.
 */

#ifndef _ProjectMobius_hPipeline
#define _ProjectMobius_hPipeline

#include <Mobius/Server/Render/Pipeline/Descriptor.hpp>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Creates a new render pipeline with the supplied descriptor.
 * Returns a descriptor populated with the data of the created pipeline.
 *
 * @param descriptor The pipeline descriptor used as a base for the new pipeline.
 * @return The created pipeline's actual, full descriptor.
 */
cMB_RNDR_PIP_Descriptor sMB_RNDR_PIP_create(cMB_RNDR_PIP_Descriptor descriptor);

/**
 * Queries a rendering pipeline.
 * Returns a descriptor populated with the data of the pipeline.
 *
 * @param identifier The identifier of the window holding the pipeline.
 * @return The pipeline's descriptor.
 */
cMB_RNDR_PIP_Descriptor sMB_RNDR_PIP_query(unsigned int identifier);

/**
 * Updates the given pipeline with the given descriptor.
 * Returns a descriptor populated with the data of the updated pipeline.
 *
 * @param identifier The identifier of the window holding the pipeline.
 * @param descriptor The pipeline descriptor used to update the pipeline.
 * @return The created pipeline's actual, full descriptor.
 */
cMB_RNDR_PIP_Descriptor sMB_RNDR_PIP_update(unsigned int identifier, cMB_RNDR_PIP_Descriptor descriptor);

/**
 * Closes the given pipeline.
 *
 * @param identifier The identifier of the window holding the pipeline.
 */
void sMB_RNDR_PIP_close(unsigned int identifier);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* _ProjectMobius_hPipeline */
