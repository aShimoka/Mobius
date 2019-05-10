
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file WindowBase.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 04/05/2019.
 */

import AppKit

/**
 * Base class for the window manager.
 * Implements macOS-specific behaviour.
 */
class Mobius_WindowManagerBase {
    // ---  Sub-Objects ---
        /**
         * Main delegate of NSWindows.
         * Stores the references to the window objects.
         * Handles window events and reports them to the manager.
         */
        class Mobius_WindowDelegate : NSObject, NSWindowDelegate {
            // ---  Methods ---
                // -- Events --
                    /**
                     * Event called by the system when the window is being closed.
                     */
                    internal func windowWillClose(_ notification: Notification) {
                        // Set the closing flag.
                        _bIsClosing = true;
                        
                        // Ask the engine to close the given window.
                        Mobius_WindowManager.closeWindow(identifier: _identifier);
                    }
                // -- Private Methods --
                    /**
                     * File-Private constructor.
                     * Ensures that ONLY the WindowManagerBase can isntantiate the object.
                     * Defines the window object and its identifier in the Manager.
                     *
                     * @param window The NSWindow object that the instance will delegate.
                     * @param id The id of the NSWindow in the Manager.
                     */
                    fileprivate init(window: NSWindow, id: CUnsignedInt) {
                        // Set the attributes.
                        _window = window; _identifier = id; _bIsClosing = false;
                        
                        // Create the content view.
                        _window!.contentView = NSView(frame: _window!.frame);
                        
                        // Get the default metal device.
                        _mtl_Device = MTLCreateSystemDefaultDevice()
                
                        // Create the metal layer.
                        _mtl_Layer = CAMetalLayer();
                            // Set the layer's device.
                            _mtl_Layer.device = _mtl_Device;
                            // Enable vsync.
                            _mtl_Layer.displaySyncEnabled = true;
                            // Enforce texture for framebuffers only.
                            _mtl_Layer.framebufferOnly = true;
                            // Set the layer bounds.
                            _mtl_Layer.frame = window.contentView!.frame;
                            // Set the pixel format.
                            _mtl_Layer.pixelFormat = .bgra8Unorm;
                        // Set the layer.
                        _window!.contentView!.layer = _mtl_Layer;
                        
                        // Move the window to the front of the application.
                        _window?.orderFrontRegardless();
                    }
            
                    internal func windowWillResize(_ sender: NSWindow, to frameSize: NSSize) -> NSSize {
                        _mtl_Layer.frame.size = frameSize;
                        _mtl_Layer.drawableSize = frameSize;
                        return frameSize;
                    }
            // --- /Methods ---
            
            // ---  Attributes ---
                // -- Internal Attributes --
                    /** NSWindow object that this instance delegates. */
                    internal var _window : NSWindow?;
            
                    /** Metal device handling this window. */
                    internal var _mtl_Device : MTLDevice!
            
                    /** Metal layer in which rendering occurs. */
                    internal var _mtl_Layer : CAMetalLayer!
            
                    /** Identifier of the window in the Manager class. */
                    internal var _identifier : CUnsignedInt;
            
                    /** Flag that allows the Manager to check the state of the underlying window. */
                    internal var _bIsClosing : Bool;
            
                    /** Rendering pipeline for the window. Explicitly created by the PipelineManager. */
                    internal var _pipeline : Mobius_Pipeline?
            // --- /Attributes ---
        }
    // --- /Sub-Objects ---
    
    // ---  Methods ---
        // -- Public Methods --
            /**
             * Create a new window object.
             * Uses the given parameters to create the window.
             *
             * @param descriptor The cWindowDescriptor for the new window.
             * @return A cWindowDescriptor filled with the valid information.
             */
            public static func createWindow(descriptor: cMB_RNDR_WIN_Descriptor) -> cMB_RNDR_WIN_Descriptor? {
                // Get the NSWindow.StyleMask value.
                let styleMask = parseWindowFlags(flags: descriptor.flags);
                // Get the rect for the window.
                let frame = mobiusToNSRect(rect: descriptor.frame);
                // Get the requested screen.
                let screen = screenByIndex(index: descriptor.screen);
                
                // Create the new window object.
                let newWin = NSWindow(contentRect: frame, styleMask: styleMask, backing: .buffered, defer: true, screen: screen);
                
                // Set the window's title.
                if (descriptor.title != nil) {
                    newWin.title = String(cString: descriptor.title);
                }
                
                // Increment the window counter.
                instance._windowCounter += 1;
                
                // Create the window delegate.
                let delegate = Mobius_WindowDelegate(window: newWin, id: instance._windowCounter);
                
                // Add the window to the array.
                instance._windowDict[instance._windowCounter] = delegate;
                
                // Return the queried descriptor.
                return queryWindow(index: instance._windowCounter);
            }
    
            /**
             * Queries a window's parameters and returns a cWindowDescriptor.
             *
             * @param index The index of the window to query.
             * @return The cWindowDescriptor of the window.
             */
            public static func queryWindow(index: CUnsignedInt) -> cMB_RNDR_WIN_Descriptor? {
                // Get the window from the descriptor.
                guard let delegate = instance._windowDict[index] else { return nil; }
                
                // Prepare the descriptor.
                var descriptor = cMB_RNDR_WIN_Descriptor();
                
                // Set the id.
                descriptor.identifier = index;
                // Parse the style mask.
                descriptor.flags = parseWindowStyle(window: delegate._window);
                // TODO : Parse the title of the window.
                // Get the frame of the window.
                descriptor.frame = nsToMobiusRect(rect: delegate._window?.frame ?? NSMakeRect(0, 0, 0, 0));
                // Get the current screen of the window.
                descriptor.screen = indexFromScreen(screen: delegate._window?.screen);
                
                // Return the descriptor.
                return descriptor;
            }
    
            /**
             * Update the state of the given window object.
             * Returns the actual status of the window after the change.
             *
             * @param identifier The identifier of the window to update.
             * @param descriptor The new state to put the window into.
             * @return An up-to-date descriptor of the window object.
             */
            public static func updateWindow(index: CUnsignedInt, descriptor: cMB_RNDR_WIN_Descriptor) -> cMB_RNDR_WIN_Descriptor? {
                // Try to load the window from the given index.
                guard let delegate = instance._windowDict[index] else { return nil; }
                // Get the delegate's window.
                let window = delegate._window!
                
                // Update the style mask of the window.
                window.styleMask = parseWindowFlags(flags: descriptor.flags);
                // Update the title of the window.
                window.title = String(cString: descriptor.title);
                
                // Parse the descriptor's frame.
                let newRect = mobiusToNSRect(rect: descriptor.frame)
                // Update the size of the window.
                window.setContentSize(newRect.size);
                
                // Compute the requested screen's origin.
                var screenOrigin = NSPoint(x: 0, y: 0);
                // Get the requested screen.
                let screen = screenByIndex(index: descriptor.screen);
                // If the screen is valid.
                if (screen != nil) {
                    // Get the origin of the screen.
                    screenOrigin = screen!.frame.origin
                }
                
                // Compute the origin of the window.
                let origin = NSPoint(x: screenOrigin.x + newRect.origin.x, y: screenOrigin.y + newRect.origin.y)
                // Update the position of the window.
                window.setFrameOrigin(origin);
                
                // Return the queried descriptor.
                return queryWindow(index: instance._windowCounter);
            }
    
            /**
             * Closes the given window in the back-end.
             * Causes all aueries and updates to fail on this window object.
             *
             * @param identifier The identifier of the window to close.
             */
            public static func closeWindow(identifier: CUnsignedInt) {
                // Try to get the delegate from the given identifier.
                guard let delegate = instance._windowDict[identifier] else { return; }
                
                // Terminate the window object.
                delegate._window!.close();
                
                // Free the delegate.
                instance._windowDict.removeValue(forKey: identifier);
            }
    
        // -- Internal Methods --
            /**
             * Grabs the Window Delegate object from a given index.
             *
             * @param index The index of the window to get.
             * @return The window delegate object.
             */
            internal static func getWindowDelegate(index: CUnsignedInt) -> Mobius_WindowDelegate? {
                // Try to get the window object.
                guard let delegate = instance._windowDict[index] else {
                    return nil;
                }
                
                // Return the window delegate.
                return delegate;
            }
    
        // -- Private Methods --
            /**
             * Private class constructor.
             * Initializes all the required variables.
             */
            private init() { _windowDict = [CUnsignedInt: Mobius_WindowDelegate](); _windowCounter = 0; }
    
            /**
             * Parses the given flags and returns the corresponding NSWindow.StyleMask value.
             *
             * @param flags The WindowFlags to be parsed.
             * @return The resulting NSWindow.StyleMask value.
             */
            private static func parseWindowFlags(flags: CUnsignedInt) -> NSWindow.StyleMask {
                // Check each flag value.
                var mask : UInt = 0;
                if ((flags & cMB_RNDR_WIN_Flags_Closable.rawValue)       > 0) { mask |= NSWindow.StyleMask.closable.rawValue; }
                if ((flags & cMB_RNDR_WIN_Flags_Resizable.rawValue)      > 0) { mask |= NSWindow.StyleMask.resizable.rawValue; }
                if ((flags & cMB_RNDR_WIN_Flags_Miniaturizable.rawValue) > 0) { mask |= NSWindow.StyleMask.miniaturizable.rawValue; }
                if ((flags & cMB_RNDR_WIN_Flags_Fullscreen.rawValue)     > 0) { mask |= NSWindow.StyleMask.fullScreen.rawValue; }
                else {
                    if ((flags & cMB_RNDR_WIN_Flags_Borderless.rawValue) > 0) { mask |= NSWindow.StyleMask.borderless.rawValue; }
                    else                                                      { mask |= NSWindow.StyleMask.titled.rawValue; }
                }
                
                // Return the style.
                return NSWindow.StyleMask(rawValue: mask);
            }
    
            /**
             * Parses the NSWindow and returns the corresponding WindowFlags value.
             *
             * @param window The window to parse.
             * @return The calculated WindowFlags value.
             */
            private static func parseWindowStyle(window: NSWindow?) -> CUnsignedInt {
                // Unwrap the window object.
                guard let unwrappedWindow = window else { return 0; }
            
                // Prepare the output variable.
                var mask : CUnsignedInt = 0;
                
                // Parse the window state.
                if ((unwrappedWindow.styleMask.rawValue & NSWindow.StyleMask.closable.rawValue)       > 0) { mask |= cMB_RNDR_WIN_Flags_Closable.rawValue; }
                if ((unwrappedWindow.styleMask.rawValue & NSWindow.StyleMask.resizable.rawValue)      > 0) { mask |= cMB_RNDR_WIN_Flags_Resizable.rawValue; }
                if ((unwrappedWindow.styleMask.rawValue & NSWindow.StyleMask.borderless.rawValue)     > 0) { mask |= cMB_RNDR_WIN_Flags_Borderless.rawValue; }
                if ((unwrappedWindow.styleMask.rawValue & NSWindow.StyleMask.fullScreen.rawValue)     > 0) { mask |= cMB_RNDR_WIN_Flags_Fullscreen.rawValue; }
                if ((unwrappedWindow.styleMask.rawValue & NSWindow.StyleMask.miniaturizable.rawValue) > 0) { mask |= cMB_RNDR_WIN_Flags_Miniaturizable.rawValue; }
                
                // Return the style.
                return mask;
            }
    
            /**
             * Simple NSRect to Rect2f converter method.
             *
             * @param rect The NSRect to convert.
             * @return The corresponding Rect2f.
             */
            private static func nsToMobiusRect(rect : NSRect) -> cMB_MATH_Rect2f {
                return cMB_MATH_Rect2f(x: Float(rect.origin.x), y: Float(rect.origin.y), w: Float(rect.width), h: Float(rect.height));
            }
    
            /**
             * Simple Rect2f to NSRect converter method.
             *
             * @param rect The Rect2f to convert.
             * @return The corresponding NSRect.
             */
            private static func mobiusToNSRect(rect : cMB_MATH_Rect2f) -> NSRect {
                return NSMakeRect(CGFloat(rect.x), CGFloat(rect.y), CGFloat(rect.w), CGFloat(rect.h));
            }
    
            /**
             * Returns the NSScreen with the given index.
             *
             * @param index The requested screen's index.
             * @return The screen object.
             */
            private static func screenByIndex(index: CUnsignedInt) -> NSScreen? {
                // Cast the index to a swift Int.
                let idx = Int(index);
                
                // Check the bounds of the array.
                if (idx >= 0 && idx < NSScreen.screens.count) {
                    // Return the requested screen.
                    return NSScreen.screens[idx];
                } else {
                    return nil;
                }
            }
    
            /**
             * Returns the index from the given NSScreen.
             *
             * @param screen The requested screen.
             * @return The index of the screen.
             */
            private static func indexFromScreen(screen: NSScreen?) -> CUnsignedInt {
                // Unwrap the screen.
                guard let unwrappedScreen = screen else { return 0; }
                
                // Get the index of the screen.
                return CUnsignedInt(NSScreen.screens.firstIndex(of: unwrappedScreen)!);
            }
    // --- /Methods ---
    
    // ---  Attributes ---
        // -- Private Attributes --
            /** Singleton class instance. */
            private static var instance = Mobius_WindowManagerBase();
    
            /** Map of all the existing windows. */
            private var _windowDict : [CUnsignedInt: Mobius_WindowDelegate];
    
            /** Counter for the window identifiers. */
            private var _windowCounter : CUnsignedInt;
    // --- /Attributes ---
}
