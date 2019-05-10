
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Application.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 03/05/2019.
 */

import AppKit

class Mobius_ApplicationDelegateBase : NSObject, NSApplicationDelegate {
    // ---  Methods ---
        // -- Public Methods --
            // - Constructor -
                /**
                 * Class constructor.
                 * Initializes the NSApplication object.
                 */
                override init() {
                    // Call the parent constructor.
                    super.init()
                    
                    // Create the shared NSApplication object.
                    _ = NSApplication.shared;
                    
                    // Set the application activation policy.
                    NSApp.setActivationPolicy(.regular);
                    
                    // Set the application delegate.
                    NSApp.delegate = self;
                    
                    // Start the app up.
                    NSApp.run();
                }
    
            // - Overrides -
                /**
                 * Called by the system whenever the NSApplication finished launching.
                 * Wraps to the onStart() method.
                 */
                func applicationDidFinishLaunching(_ notification: Notification) {
                    // Call the onStart event.
                    if (onStart()) {
                        // Schedule the loop method.
                        Timer.scheduledTimer(withTimeInterval: 1/60, repeats: true, block: self.timerDrivenLoop);
                    } else {
                        // Close the application.
                        NSApp.terminate(self);
                    }
                }
    
                /**
                 * Called by the system whenever the last window is closed.
                 * Always returns true.
                 */
                func applicationShouldTerminateAfterLastWindowClosed(_ sender: NSApplication) -> Bool { return true; }
    
                /**
                 * Called by the system before the application definitively terminates.
                 * Calls the onClose event.
                 */
                func applicationWillTerminate(_ notification: Notification) { onClose(); }

        // -- Protected Methods --
            /**
             * Event triggered on the beginning of the application.
             * All setup should happen in here.
             * It should at least call Mobius's setup method.
             * A false stops the application and closes it without launching the onLoop method.
             */
            internal func onStart() -> Bool { assert(true, "ApplicationDelegate did not override onStart method."); return false; }

            /**
             * Event triggered on each run loop.
             * Rendering should happen in here.
             *
             * @return A false closes the entire application.
             */
            internal func onLoop(deltaTime: Double) -> Bool { assert(true, "ApplicationDelegate did not override onLoop method."); return false; }

            /**
             * Event triggered when the system required a closing.
             * All closing code should happen in here.
             */
            internal func onClose() { assert(true, "ApplicationDelegate did not override onClose method."); }
    
        // -- Private Methods --
            /**
             * Timer-driven loop.
             * Used to call the onLoop event.
             * If the onLoop decided to stop the engine, invalidates the timer and terminates the application.
             */
            private func timerDrivenLoop(timer : Timer) {
                // Call the onLoop event.
                if (!onLoop(deltaTime: timer.timeInterval)) {
                    // Invalidate the timer.
                    timer.invalidate();
                    
                    // Stop the application.
                    NSApp.terminate(self);
                }
            }
    // --- /Methods ---
}
