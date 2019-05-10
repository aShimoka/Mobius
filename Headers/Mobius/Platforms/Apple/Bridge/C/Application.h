
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Application.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 03/05/2019.
 */

#ifndef _ProjectMobius_hApplication
#define _ProjectMobius_hApplication

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Trigger the engine's setup event.
 * This allows the engine to prepare its context.
 */
int cMobius_Engine_onSetup(void);

/**
 * Regular loop event.
 * Used by the engine to update all its element and rendering them.
 */
int cMobius_Engine_onLoop(double deltaTime);

/**
 * Close event.
 * Allows the engine to free all resources and finish any code execution.
 */
void cMobius_Engine_onClose(void);

void cMB_NGIN_throw(void);

#ifdef __cplusplus
}
#endif

#endif /* _ProjectMobius_hppApplication */
