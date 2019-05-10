//
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file ReferenceCounter.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 02/05/2019.
 */

#include <Mobius/Core/Memory/ReferenceCounter.hpp>
#include <Mobius/Core/Memory/WeakPointer.hpp>

namespace Mobius {

void ReferenceCounter::increment(const void * pointer) {
    // Return for a nullptr value.
    if (pointer == nullptr) return;
    
    // Get the reference counter object.
    WeakPointer<ReferenceCounter> refCounter = ReferenceCounter::getSingleton();
    
    // Check if the pointer exists in the map.
    auto ptrIdx = refCounter->_pPointerMap->find(pointer);
    if (ptrIdx != refCounter->_pPointerMap->end()) {
        // Increment the counter.
        ++(ptrIdx->second);
    } else {
        // Insert the pointer into the map.
        refCounter->_pPointerMap->insert(std::make_pair(pointer, 1));
    }
}

int ReferenceCounter::decrement(const void * pointer) {
    // Return -1 for a nullptr value.
    if (pointer == nullptr) return -1;
    
    // Get the reference counter object.
    WeakPointer<ReferenceCounter> refCounter = ReferenceCounter::getSingleton();
    
    // Check if the pointer exists in the map.
    auto ptrIdx = refCounter->_pPointerMap->find(pointer);
    if (ptrIdx != refCounter->_pPointerMap->end()) {
        // Decrement the counter.
        int counter = --(ptrIdx->second);
        
        // If the counter reached zero.
        if (!counter) {
            // Remove it from the tree.
            refCounter->_pPointerMap->erase(ptrIdx);
        }
        
        // Return the counter.
        return counter;
    } else {
        throw new InvalidPointerDecrementException();
    }
}

const bool ReferenceCounter::isValid(const void * pointer) {
    // Return false for a nullptr value.
    if (pointer == nullptr) return false;
    
    // Return true if the count is greater than 0.
    return ReferenceCounter::getCount(pointer) > 0;
}

const int ReferenceCounter::getCount(const void * pointer) {
    // Return 0 for a nullptr value.
    if (pointer == nullptr) return 0;
    
    // Get the reference counter object.
    WeakPointer<ReferenceCounter> refCounter = ReferenceCounter::getSingleton();
    
    // Check if the pointer exists in the map.
    auto ptrIdx = refCounter->_pPointerMap->find(pointer);
    if (ptrIdx != refCounter->_pPointerMap->end()) {
        // Return the value of the map.
        return ptrIdx->second;
    } else {
        // Return a 0;
        return 0;
    }
}

ReferenceCounter::ReferenceCounter() {
    // Create the map object.
    this->_pPointerMap = new PointerMap();
}

ReferenceCounter::~ReferenceCounter() {
    // Clear the map object.
    delete this->_pPointerMap;
}

WeakPointer<ReferenceCounter> ReferenceCounter::getSingleton() {
    // Store the instance statically in this method.
    static ReferenceCounter refCounter;
    
    // Return the weak reference.
    return WeakPointer<ReferenceCounter>(&refCounter);
}

}
