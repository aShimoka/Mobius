
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file WindowManager.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 04/05/2019.
 */

#ifndef _ProjectMobius_hpp_RenderServer_Window_Manager
#define _ProjectMobius_hpp_RenderServer_Window_Manager

#include <Mobius/Core/Memory/StrongPointer.hpp>
#include <Mobius/Core/Serializer/ConfigNode.hpp>

#include <Mobius/Server/Render/Window/Descriptor.hpp>
#include <Mobius/Server/Render/Window/Exceptions.hpp>

namespace Mobius {
namespace Render {
namespace Window {

/**
 * Manager responsible for all the windows created by the application.
 * Allows the creation, query and update of all the windows.
 * Uses the Platform/ wrappers for each platform.
 * NOTE : For now, only macOs is supported.
 */
class Manager {
    // Type alias for the window identifier map.
    typedef StrongPointer<std::map<std::string, unsigned int>> __WindowIdentifierMap;
    
    // ---  Methods ---
        // -- Public Methods --
        public:
            /**
             * Creates a new window object.
             * Uses the given WindowDescriptor object to prepare the window.
             *
             * @param id The identifier of the new window.
             * @param descriptor The WindowDescriptor object for the new window.
             * @return A WindowDescriptor object filled with the window's valid info.
             * @throws InvalidWindowIDException If the window id is already assigned.
             */
            static Descriptor createWindow(std::string id, Descriptor descriptor);
    
            /**
             * Queries information about the given window.
             *
             * @param id The identifier of the requested window.
             * @return A filled WindowDescriptor object.
             * @throws InvalidWindowIDException If the window does not exist.
             */
            static Descriptor queryWindow(std::string id);
    
            /**
             * Updates a given window object.
             * Sets its parameters to the given descriptor.
             *
             * @param id The identifier of the window to update.
             * @param descriptor The new descriptor for the window.
             * @return A WindowDescriptor filled with the window's new info.
             * @throws InvalidWindowIDException If the window does not exist.
             */
            static Descriptor updateWindow(std::string id, Descriptor descriptor);
    
            /**
             * Closes the given window.
             *
             * @param id The identifier of the window to close.
             * @throws InvalidWindowIDException If the window does not exist.
             */
            static void closeWindow(std::string id);
    
            /**
             * Parses the given config node and creates the underlying windows.
             *
             * @param configNode The configNode to parse.
             */
            static void parseConfig(ConfigNode::WeakReference configNode);
    
            /**
             * Returns the identifier of a window, given a string identifier.
             *
             * @param identifier The string identifier of the window.
             * @return The unsigned int identifier of the window.
             */
            static unsigned int getWindowIdentifier(std::string identifier);
    
        // -- Private Methods --
        private:
            /**
             * Class constructor.
             * Made private to enforce ingleton pattern.
             */
            Manager();
    
            /**
             * Class desctructor.
             * Made private to enforce singleton pattern.
             */
            ~Manager();
    
            /**
             * Singleton accessor.
             * Private since it should NEVER exit the class's context.
             */
            static WeakPointer<Manager> instance();
    // --- /Methods ---
    
    // ---  Attributes ---
        // -- Private Attributes --
        private:
            /** Map of all the windows, sorted by identifier. */
            __WindowIdentifierMap _windowIdMap;
    // --- /Attributes ---
};

}
}
}

#endif /* _ProjectMobius_hpp_RenderServer_Window_Manager */
