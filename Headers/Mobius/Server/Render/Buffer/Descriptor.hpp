
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Descriptor.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 06/05/2019.
 */

#ifndef _ProjectMobius_hpp_RenderServer_Buffer_Descriptor
#define _ProjectMobius_hpp_RenderServer_Buffer_Descriptor

#ifdef __cplusplus
extern "C" {
#endif

extern const unsigned int cMB_RNDR_BUF_InvalidManager;
extern const unsigned int cMB_RNDR_BUF_SharedManager;

extern const unsigned int cMB_RNDR_BUF_Invalid;
extern const unsigned int cMB_RNDR_BUF_Immutable;
extern const unsigned int cMB_RNDR_BUF_Mutable;

/**
 * Buffer descriptor structure.
 * Holds all relevant info fur a rendering buffer.
 */
typedef struct cMB_RNDR_BUF_Descriptor {
    // ---  Attributes ---
        // -- Public Attributes --
            /** Identifier of the manager handling this buffer. */
            unsigned int manager;
    
            /** Identifier dedicated to the buffer object. */
            unsigned int identifier;
    
            /** Number of objects found inside the buffer. */
            unsigned int objectCount;
    
            /** Size, in bytes, of a single object. */
            unsigned int objectSize;
    
            /** Type of buffer. Aka. mutalbe or not. */
            unsigned int type;
    // --- /Attributes ---
} cMB_RNDR_BUF_Descriptor;

#ifdef __cplusplus
}

namespace Mobius {
namespace Render {
namespace Buffer{

class Descriptor : public cMB_RNDR_BUF_Descriptor {
    // ---  Methods ---
        // -- Public Methods --
        public:
            /**
             * Create a new buffer object.
             * Defines all of its components.
             *
             * @param manager The identifier of the manager handling this buffer.
             * @param identifier Unique identifier of the buffer in its manager.
             * @param objectCount The number of objects found within the buffer.
             * @param objectSize The size of a single object within the buffer.
             * @param type The type of this buffer.
             */
            Descriptor(unsigned int manager, unsigned int identifier, unsigned int objectCount, unsigned int objectSize, unsigned int type);
    
            /**
             * Creates the default, invalid buffer.
             */
            Descriptor();
    
            /**
             * Copies a cMB_RNDR_BUF_Descriptor into a Descriptor instance.
             *
             * @param copy The descriptor to copy.
             */
            Descriptor(const cMB_RNDR_BUF_Descriptor& copy);
    // --- /Methods ---
};

}
}
}

#endif

#endif /* _ProjectMobius_hpp_RenderServer_Buffer_Descriptor */
