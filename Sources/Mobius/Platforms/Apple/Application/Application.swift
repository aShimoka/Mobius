/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Application.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 03/05/2019.
 */

class Mobius_ApplicationDelegate : Mobius_ApplicationDelegateBase {
    // ---  Methods ---
        // -- Public Methods --
            // - Overrides -
                /**
                 * Event triggered on the beginning of the application.
                 * Calls the Mobius setup method.
                 */
                override internal func onStart() -> Bool {
                    return cMobius_Engine_onSetup() > 0;
                }

                /**
                 * Event triggered on each run loop.
                 * Calls the Mobius loop method.
                 *
                 * @return A false closes the entire application.
                 */
                override internal func onLoop(deltaTime: Double) -> Bool {
                    return cMobius_Engine_onLoop(deltaTime) > 0;
                }

                /**
                 * Event triggered when the system required a closing.
                 * Calls the Mobius closing method.
                 */
                override internal func onClose() {
                    cMobius_Engine_onClose();
                }
    // --- /Methods ---
}
