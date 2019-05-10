//
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Manager.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 04/05/2019.
 */

#include <Mobius/Server/Render/Window/Manager.hpp>

#include <Mobius/Platforms/Apple/Bridge/Swift/Window.h>

namespace Mobius {
namespace Render {
namespace Window {

void Manager::parseConfig(ConfigNode::WeakReference configNode) {
    // Prepare the output descriptor.
    Descriptor parsedDescriptor;

    // Check if the root node has an "identifier" attribute.
    if (configNode->hasAttribute("identifier")) {
        // Get the identifier of the root node.
        std::string identifier = configNode->getAttribute("identifier");
        
        // Load the <Rect> element of the window.
        ConfigNode::WeakReference windowRect = configNode->getChildElementByName("Rect");
        
        // Ensure that there is at least one rect.
        if (windowRect.isValid()) {
            // Fill the descriptor's frame element.
            windowRect->getAttribute("x", &parsedDescriptor.frame.x);
            windowRect->getAttribute("y", &parsedDescriptor.frame.y);
            windowRect->getAttribute("w", &parsedDescriptor.frame.w);
            windowRect->getAttribute("h", &parsedDescriptor.frame.h);
            
            // Get all the flags for the window.
            ConfigHelpers::FlagList::WeakReference windowFlagList = configNode->getChildElementByName("Flags");
            
            if (windowFlagList.isValid()) {
                // Parse each flag in the list.
                for (auto flagIt = windowFlagList->getFlagIterator(); flagIt != windowFlagList->getFlagIterator(true); flagIt++) {
                    parsedDescriptor.parseFlag(flagIt->c_str());
                }
            }
            
            // If no flags were parsed.
            if (parsedDescriptor.flags == cMB_RNDR_WIN_Flags_Invalid) {
                // Load the default flags.
                parsedDescriptor.flags = cMB_RNDR_WIN_Flags_Default;
            }
            
            // Get the name of the window.
            std::string windowName = "";
            configNode->getAttribute("name", &windowName);
            parsedDescriptor.title = windowName.c_str();
            
            // Get the requested screen.
            configNode->getAttribute("screen", &parsedDescriptor.screen);
            
            // Create the window.
            createWindow(identifier, parsedDescriptor);
        } else {
            // Throw a ParseException.
            throw ParsingException("Window had no <Rect> element.");
        }
    } else {
        // Throw a ParseException.
        throw ParsingException("Window had no identifier.");
    }
}

Descriptor Manager::createWindow(std::string id, Descriptor descriptor) {
    // Check if the id was not already assigned.
    unsigned int windowId = 0;
    try {
        windowId = getWindowIdentifier(id);
    } catch (InvalidIDException& exception) {}
    if (windowId != 0) throw InvalidIDException("A window with this identifier already exists.");
    
    // Call the back-end creation method.
    Descriptor info = sMB_RNDR_WIN_create(descriptor);

    // Check if the creation was successful.
    if (info.flags != cMB_RNDR_WIN_Flags_Invalid) {
        // Add the window to the list of windows.
        instance()->_windowIdMap->insert(std::make_pair(id, info.identifier));
        
        // Return the information
        return info;
    } else {
        // Throw a CreationException.
        throw CreationException("Back-End failure on window creation.");
    }
}

Descriptor Manager::queryWindow(std::string id) {
    // Check if the id was already assigned.
    unsigned int windowIdentifier = getWindowIdentifier(id);
    if (windowIdentifier != 0) {
        // Call the back-end method to get the window information.
        Descriptor info = sMB_RNDR_WIN_query(windowIdentifier);
        
        // Check if any error occured in the back end.
        if (info.flags != cMB_RNDR_WIN_Flags_Invalid) {
            // Return the info.
            return info;
        } else {
            // Throw a query error.
            throw QueryException("Back-End failure on window query.");
        }
        return info;
    } else {
        // Throw an InvalidIDException.
        throw InvalidIDException("Tried to query a non-existent window.");
    }
}

Descriptor Manager::updateWindow(std::string id, Descriptor descriptor) {
    // Check if the id was already assigned.
    unsigned int windowIdentifier = getWindowIdentifier(id);
    if (windowIdentifier != 0) {
        // Call the back-end method to update the window information.
        Descriptor info = sMB_RNDR_WIN_update(windowIdentifier, descriptor);
        
        // Check if any error occured in the back end.
        if (info.flags != cMB_RNDR_WIN_Flags_Invalid) {
            // Return the info.
            return info;
        } else {
            // Throw a query error.
            throw QueryException("Back-End failure on window update.");
        }
        return info;
    } else {
        // Throw an InvalidIDException.
        throw InvalidIDException("Tried to update a non-existent window.");
    }
}

void Manager::closeWindow(std::string id) {
    // Check if the id was already assigned.
    unsigned int windowIdentifier = getWindowIdentifier(id);
    if (windowIdentifier != 0) {
        // Call the back-end method to close the window.
        sMB_RNDR_WIN_close(windowIdentifier);
        
        // Remove the window from the list.
        instance()->_windowIdMap->erase(id);
    } else {
        // Throw an InvalidIDException.
        throw InvalidIDException("Tried to close a non-existent window.");
    }
}

unsigned int Manager::getWindowIdentifier(std::string identifier) {
    // Find the identifier in the map.
    auto iterator = instance()->_windowIdMap->find(identifier);
    
    // If the window was found, return its identifier.
    if (iterator != instance()->_windowIdMap->end()) {
        return iterator->second;
    } else {
        throw InvalidIDException("No window with specified id.");
    }
}

Manager::Manager() :
    _windowIdMap(__WindowIdentifierMap::create())
{}

Manager::~Manager() {
    _windowIdMap->clear();
}

WeakPointer<Manager> Manager::instance() {
    static Manager instance;
    return &instance;
}

}
}
}
