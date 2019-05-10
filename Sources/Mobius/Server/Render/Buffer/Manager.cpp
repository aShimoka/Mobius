//
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Manager.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 06/05/2019.
 */

#include <Mobius/Server/Render/Buffer/Manager.hpp>
#include <Mobius/Server/Render/Pipeline/Manager.hpp>
#include <Mobius/Platforms/Apple/Bridge/Swift/Buffer.h>

namespace Mobius {
namespace Render {
namespace Buffer {

Descriptor _allocateBuffer(Descriptor descriptor, void * data) {
    return sMB_RNDR_BUF_allocate(descriptor, data);
}

Descriptor Manager::allocateBuffer(std::string window, void * data, Descriptor descriptor) {
    // Get the buffer manager of the window.
    descriptor.manager = Pipeline::Manager::queryPipeline(window).bufferManager;
    
    // Call the back-end method.
    return _allocateBuffer(descriptor, data);
}

Descriptor Manager::allocateImmutableBuffer(std::string window, void * data, unsigned int objectCount, unsigned int objectSize) {
    // Create the descriptor.
    Descriptor descriptor;
    
    // Set the parameters of the descriptor.
    descriptor.objectCount = objectCount;
    descriptor.objectSize = objectSize;
    descriptor.type = cMB_RNDR_BUF_Immutable;
    
    // Call the allocateBuffer method.
    return allocateBuffer(window, data, descriptor);
}

Descriptor Manager::allocateMutableBuffer(std::string window, unsigned int objectCount, unsigned int objectSize) {
    // Create the descriptor.
    Descriptor descriptor;
    
    // Set the parameters of the descriptor.
    descriptor.objectCount = objectCount;
    descriptor.objectSize = objectSize;
    descriptor.type = cMB_RNDR_BUF_Mutable;
    
    // Call the allocateBuffer method.
    return allocateBuffer(window, nullptr, descriptor);
}

Descriptor Manager::allocateSharedBuffer(void * data, Descriptor descriptor) {
    // Set the shared manager.
    descriptor.manager = cMB_RNDR_BUF_SharedManager;
    
    // Call the _allocateBuffer method.
    return _allocateBuffer(descriptor, data);
}

Descriptor Manager::allocateSharedImmutableBuffer(void * data, unsigned int objectCount, unsigned int objectSize) {
    // Create the descriptor.
    Descriptor descriptor;
    
    // Set the parameters of the descriptor.
    descriptor.objectCount = objectCount;
    descriptor.objectSize = objectSize;
    descriptor.type = cMB_RNDR_BUF_Immutable;
    descriptor.manager = cMB_RNDR_BUF_SharedManager;
    
    // Call the allocateBuffer method.
    return _allocateBuffer(descriptor, data);
}

Descriptor Manager::allocateSharedMutableBuffer(unsigned int objectCount, unsigned int objectSize) {
    // Create the descriptor.
    Descriptor descriptor;
    
    // Set the parameters of the descriptor.
    descriptor.objectCount = objectCount;
    descriptor.objectSize = objectSize;
    descriptor.type = cMB_RNDR_BUF_Mutable;
    descriptor.manager = cMB_RNDR_BUF_SharedManager;
    
    // Call the allocateBuffer method.
    return _allocateBuffer(descriptor, nullptr);
}

void Manager::assign(Buffer::Descriptor *buffer, void *data) {
    // Call the back-end method.
    sMB_RNDR_BUF_assign(buffer, data);
}

}
}
}
