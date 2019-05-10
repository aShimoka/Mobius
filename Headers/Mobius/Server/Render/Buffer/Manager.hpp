
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Manager.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 06/05/2019.
 */

#ifndef _ProjectMobius_hpp_RenderServer_Buffer_Manager
#define _ProjectMobius_hpp_RenderServer_Buffer_Manager

#include <Mobius/Server/Render/Buffer/Descriptor.hpp>

#include <string>

namespace Mobius {
namespace Render {
namespace Buffer {

/**
 * Buffer manager class.
 * Allows the creation and assigment of buffer objects.
 */
class Manager {
    // ---  Methods ---
        // -- Public Methods --
        public:
            /**
             * Allocates a new buffer object.
             * Uses the given descriptor to communicate the creation to the back end.
             * Returns a buffer descriptor that can be used later.
             *
             * @param window The identifier of the window for which the buffer should be created.
             * @param descriptor The descriptor object to represent the buffer.
             * @return The descriptor for the new buffer.
             */
            static Descriptor allocateBuffer(std::string window, void * data, Descriptor descriptor);
    
            /**
             * Allocates a new, immutable buffer.
             * This buffer cannot be altered later and stays fixed until it is cleared.
             * Returns a buffer descriptor that can be used later.
             *
             * @param window The identifier of the window for which the buffer should be created.
             * @param data The data to copy into the buffer.
             * @param objectCount The number of objects to allocate in the buffer.
             * @param objectSize The size of a single object.
             * @return The descriptor for the new buffer.
             */
            static Descriptor allocateImmutableBuffer(std::string window, void * data, unsigned int objectCount, unsigned int objectSize);
    
            /**
             * Allocates a new, mutable buffer.
             * This buffer can be altered later and will be pooled for increased efficiency.
             * Returns a buffer descriptor that can be used later.
             *
             * @param window The identifier of the window for which the buffer should be created.
             * @param objectCount The number of objects to allocate in the buffer.
             * @param objectSize The size of a single object.
             * @return The descriptor for the new buffer.
             */
            static Descriptor allocateMutableBuffer(std::string window, unsigned int objectCount, unsigned int objectSize);
    
            /**
             * Allocates a new, immutable buffer.
             * This buffer cannot be altered later and stays fixed until it is cleared.
             * The template computes the size of the object automatically.
             * Returns a buffer descriptor that can be used later.
             *
             * @param window The identifier of the window for which the buffer should be created.
             * @param data The data to copy into the buffer.
             * @param objectCount The number of objects to allocate in the buffer.
             * @return The descriptor for the new buffer.
             */
            template<typename T>
            static Descriptor allocateImmutableBuffer(std::string window, T * data, unsigned int objectCount) {
                return allocateImmutableBuffer(window, data, objectCount, sizeof(T));
            }
    
            /**
             * Allocates a new, mutable buffer.
             * This buffer can be altered later and will be pooled for increased efficiency.
             * The template computes the size of the object automatically.
             * Returns a buffer descriptor that can be used later.
             *
             * @param window The identifier of the window for which the buffer should be created.
             * @param objectCount The number of objects to allocate in the buffer.
             * @return The descriptor for the new buffer.
             */
            template<typename T>
            static Descriptor allocateMutableBuffer(std::string window, unsigned int objectCount) {
                return allocateMutableBuffer(window, objectCount, sizeof(T));
            }
    
            /**
             * Allocates a new buffer in the shared manager.
             * These buffers can be accessed by all pipelines using the shared manager.
             * Returns a buffer descriptor that can be used later.
             *
             * @param descriptor The descriptor of the buffer to allocate.
             * @return The descriptor of the buffer object.
             */
            static Descriptor allocateSharedBuffer(void * data, Descriptor descriptor);
    
            /**
             * Allocates a new, immutable buffer in the shared manager.
             * This buffer cannot be altered later and stays fixed until it is cleared.
             * Returns a buffer descriptor that can be used later.
             *
             * @param data The data to copy into the buffer.
             * @param objectCount The number of objects to allocate in the buffer.
             * @param objectSize The size of a single object.
             * @return The descriptor for the new buffer.
             */
            static Descriptor allocateSharedImmutableBuffer(void * data, unsigned int objectCount, unsigned int objectSize);
    
            /**
             * Allocates a new, mutable buffer in the shared manager.
             * This buffer can be altered later and will be pooled for increased efficiency.
             * Returns a buffer descriptor that can be used later.
             *
             * @param objectCount The number of objects to allocate in the buffer.
             * @param objectSize The size of a single object.
             * @return The descriptor for the new buffer.
             */
            static Descriptor allocateSharedMutableBuffer(unsigned int objectCount, unsigned int objectSize);
    
            /**
             * Allocates a new, immutable buffer in the shared manager.
             * This buffer cannot be altered later and stays fixed until it is cleared.
             * The template computes the size of the object automatically.
             * Returns a buffer descriptor that can be used later.
             *
             * @param data The data to copy into the buffer.
             * @param objectCount The number of objects to allocate in the buffer.
             * @return The descriptor for the new buffer.
             */
            template <typename T>
            static Descriptor allocateSharedImmutableBuffer(T * data, unsigned int objectCount) {
                return allocateSharedImmutableBuffer(data, objectCount, sizeof(T));
            }
    
            /**
             * Allocates a new, mutable buffer in the shared manager.
             * This buffer can be altered later and will be pooled for increased efficiency.
             * The template computes the size of the object automatically.
             * Returns a buffer descriptor that can be used later.
             *
             * @param objectCount The number of objects to allocate in the buffer.
             * @return The descriptor for the new buffer.
             */
            template<typename T>
            static Descriptor allocateSharedMutableBuffer(unsigned int objectCount) {
                return allocateSharedMutableBuffer(objectCount, sizeof(T));
            }
    
            /**
             * Assigns data to a mutable buffer.
             *
             * @param buffer A reference to the buffer to assign to.
             * @param data The data to write into the buffer.
             */
            static void assign(Buffer::Descriptor * buffer, void * data);
    // --- /Methods ---
};

}
}
}

#endif /* _ProjectMobius_hpp_RenderServer_Buffer_Manager */
