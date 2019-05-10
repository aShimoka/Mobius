
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file WindowManager.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 04/05/2019.
 */

/**
 * Window manager class.
 * Derives from the WindowManagerBase which implements platform-specific behaviour.
 * Bridged at the bottom with the C API.
 */
class Mobius_WindowManager : Mobius_WindowManagerBase {}


/**
 * C API Bridge.
 * All these functions are described in the Window bridging header.
 */

let invalidWindowDescriptor = cMB_RNDR_WIN_Descriptor(identifier: 0, frame: cMB_MATH_Rect2f(x: 0, y: 0, w: 0, h: 0), flags: cMB_RNDR_WIN_Flags_Invalid.rawValue, screen: 0, title: nil );

@_cdecl("sMB_RNDR_WIN_create")
func sMobius_Window_create(descriptor: cMB_RNDR_WIN_Descriptor) -> cMB_RNDR_WIN_Descriptor {
    // Call the manager's creation method.
    guard let descriptor = Mobius_WindowManager.createWindow(descriptor: descriptor) else {
        // If the creation failed, return the invalid descriptor.
        return invalidWindowDescriptor;
    }
    
    // Return the created window's descriptor.
    return descriptor;
}

@_cdecl("sMB_RNDR_WIN_query")
func sMobius_Window_query(id: CUnsignedInt) -> cMB_RNDR_WIN_Descriptor {
    // Call the manager's query method.
    guard let descriptor = Mobius_WindowManager.queryWindow(index: id) else {
        // If the query failed, return the invalid descriptor.
        return invalidWindowDescriptor;
    }
    
    // Return the queried descriptor.
    return descriptor;
}

@_cdecl("sMB_RNDR_WIN_update")
func sMobius_Window_update(id: CUnsignedInt, descriptor: cMB_RNDR_WIN_Descriptor) -> cMB_RNDR_WIN_Descriptor {
    // Call the manager's update method.
    guard let descriptor = Mobius_WindowManager.updateWindow(index: id, descriptor: descriptor) else {
        // If the query failed, return the invalid descriptor.
        return invalidWindowDescriptor;
    }
    
    // Return the queried descriptor.
    return descriptor;
}

@_cdecl("sMB_RNDR_WIN_close")
func sMobius_Window_close(id: CUnsignedInt) {
    // Call the manager's close method.
    Mobius_WindowManager.closeWindow(identifier: id);
}
