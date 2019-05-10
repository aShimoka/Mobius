//
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Descriptor.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 05/05/2019.
 */

#ifndef _ProjectMobius_hpp_RenderServer_Window_Descriptor
#define _ProjectMobius_hpp_RenderServer_Window_Descriptor

#include <Mobius/Math/Rect.hpp>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * List of flags available to the window descriptor.
 */
typedef enum cMB_RNDR_WIN_Flags : unsigned int {
    cMB_RNDR_WIN_Flags_Resizable      = 0b00001,
    cMB_RNDR_WIN_Flags_Closable       = 0b00010,
    cMB_RNDR_WIN_Flags_Miniaturizable = 0b00100,
    cMB_RNDR_WIN_Flags_Fullscreen     = 0b01000,
    cMB_RNDR_WIN_Flags_Borderless     = 0b10000,
    cMB_RNDR_WIN_Flags_Default        = 0b00111,
    cMB_RNDR_WIN_Flags_Invalid        = 0b00000,
} cMB_RNDR_WIN_Flags;

/**
 * Descriptor object for the Windows.
 * Simplifies the transactions with the back-end.
 */
typedef struct cMB_RNDR_WIN_Descriptor {
    // ---  Attributes ---
        // -- Public Attributes --
            /** Back-end identifier of the window object. */
            unsigned int identifier;
    
            /** Frame that the window will be drawn into. */
            cMB_MATH_Rect2f frame;
    
            /** Flags that determine the appearence of the window. */
            unsigned int flags;
    
            /** Index of the screen containing this window. */
            unsigned int screen;
    
            /** Title of the window. */
            const char * title;
    // --- /Attributes ---
} cMB_RNDR_WIN_Descriptor;

#ifdef __cplusplus
} // extern "C"

namespace Mobius {
namespace Render {
namespace Window {

class Descriptor : public cMB_RNDR_WIN_Descriptor {
    // ---  Methods ---
        // -- Public Methods --
        public:
            /**
             * Simple constructor.
             * Defines all the elements of the window descriptor.
             *
             * @param identifier The unique identifier for the window.
             * @param frame The rectangle formed by this window.
             * @param flags The window's flags.
             * @param screen The index of the screen that holds the window.
             * @param title The name of the screen object.
             */
            Descriptor(unsigned int identifier, Math::Rect2f frame, unsigned int flags, unsigned int screen, const char * title);
    
            /**
             * Empty constructor.
             * Creates the invalid window descriptor.
             */
            Descriptor();
    
            /**
             * Copy constructor.
             * Creates a new WindowDescriptor from a cMB_RNDR_WIN_Descriptor.
             */
            Descriptor(const cMB_RNDR_WIN_Descriptor& copy);
    
            /**
             * Parses the given flag and adds it to the list.
             *
             * @param flag The flag to parse.
             */
            void parseFlag(const char * flag);
    // --- /Methods ---
};

}
}
}
#endif

#endif /* _ProjectMobius_hpp_RenderServer_Window_Descriptor */
