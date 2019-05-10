
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Window.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 04/05/2019.
 */

#ifndef _ProjectMobius_hWindow
#define _ProjectMobius_hWindow

#include <Mobius/Server/Render/Window/Descriptor.hpp>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Swift bridged method.
 * Creates a new window object based on the given parameters.
 * Returns a window descriptor filled with the actual window's state.
 */
cMB_RNDR_WIN_Descriptor sMB_RNDR_WIN_create(cMB_RNDR_WIN_Descriptor descriptor);

/**
 * Swift bridged method.
 * Queries information about the given window.
 * Returns a window descriptor filled with the actual window's state.
 */
cMB_RNDR_WIN_Descriptor sMB_RNDR_WIN_query(int id);

/**
 * Swift bridged method.
 * Updates the given window with the given descriptor.
 * Returns a window descriptor filled with the actual window's state.
 */
cMB_RNDR_WIN_Descriptor sMB_RNDR_WIN_update(int id, cMB_RNDR_WIN_Descriptor descriptor);

/**
 * Swift bridged method.
 * Closes the given window object.
 */
void sMB_RNDR_WIN_close(int id);


#ifdef __cplusplus
}
#endif

#endif /* _ProjectMobius_hppWindow */
