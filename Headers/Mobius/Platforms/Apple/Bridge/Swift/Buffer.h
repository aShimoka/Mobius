
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Buffer.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 04/05/2019.
 */

#ifndef _ProjectMobius_hBuffer
#define _ProjectMobius_hBuffer

#include <Mobius/Server/Render/Buffer/Descriptor.hpp>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Allocate a new buffer object.
 * Uses the given descriptor to create the buffer.
 * If the buffer is immutable, the data is copied into it.
 *
 * @param descriptor The descriptor used to build the buffer.
 * @param data The data to copy into the buffer.
 * @return A complete buffer descriptor for later use.
 */
cMB_RNDR_BUF_Descriptor sMB_RNDR_BUF_allocate(cMB_RNDR_BUF_Descriptor descriptor, void * data);

/**
 * Assigns the given data to the buffer.
 * The descriptor's identifier then gets updated internally.
 *
 * @param descriptor A pointer to the descriptor of the data to assign.
 * @param data The data to copy into the buffer.
 */
void sMB_RNDR_BUF_assign(cMB_RNDR_BUF_Descriptor * descriptor, void * data);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* _ProjectMobius_hppBuffer */
