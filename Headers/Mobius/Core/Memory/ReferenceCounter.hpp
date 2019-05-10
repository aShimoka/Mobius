
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file RefrenceCounter.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 02/05/2019.
 */

#ifndef _ProjectMobius_hppReferenceCounter
#define _ProjectMobius_hppReferenceCounter

#include <map>
#include <exception>

namespace Mobius {

// Pointer map used by the reference counter class.
typedef std::map<const void *, int> PointerMap;

// Forward declaration of the generic pointer classes.
template <typename T>
class WeakPointer;
template <typename T>
class StrongPointer;

/**
 * Custom exception thrown by the ReferenceCounter class.
 * It is thrown whenever a pointer is decremented past its reference count (aka. tried to decrement a pointer counted as 0)
 * Or when a non-stored pointer is decremented. (aka. tried to decrement a pointer initialized outside of the ReferenceCounter)
 */
class InvalidPointerDecrementException : public std::exception {
public:
    InvalidPointerDecrementException() : std::exception() {}
};

/**
 * Reference counter class.
 * Static class that handles all reference counting in the Mobius game engine.
 * Used by String and Wak pointers objects to handle memory.
 */
class ReferenceCounter {
    // ---  Methods ---
        // -- Public Methods --
        public:
            /**
             * Increments the specified pointer's counter.
             * Adds it to the list if it didn't exist previously.
             *
             * @param pointer the pointer to increment the counter of, or add to the map.
             */
            static void increment(const void * pointer);
    
            /**
             * Decrements the given pointer's counter.
             *
             * @param pointer The pointer to decrement the value from.
             * @return the leftover number of pointers.
             */
            static int decrement(const void * pointer);
    
            /**
             * Check wether a given pointer is stored in the ReferenceCounter and has a count greater or equal to one.
             *
             * @param pointer The pointer to check the counter of.
             * @return True if the pointer is counted and has a counter greater or equal to one.
             */
            static const bool isValid(const void * pointer);
    
            /**
             * Returns the coutner of the specified pointer.
             *
             * @param pointer The pointer to get the counter of.
             * @return The number of references to the pointer, or 0 if the pointer does not exist in the ReferenceCounter.
             */
            static const int getCount(const void * pointer);
    
        // -- Private Methods --
        private:
            /**
             * Private constructor.
             * Avoids multiple instantiation and initialized the pointer map.
             */
            ReferenceCounter();
    
            /**
             * Private destructor.
             * Logs a major error if any pointer are left over at the end of execution.
             * Releases the pointer map.
             */
            ~ReferenceCounter();
    
            /**
             * Singleton accessor.
             *
             * @return A weak pointer to the ReferenceCounter singleton.
             */
            static WeakPointer<ReferenceCounter> getSingleton();
    // --- /Methods ---
    
    // ---  Attributes –––
    private:
            /** Pointer map obbject. */
            PointerMap * _pPointerMap;
    // --- /Attributes ---
};

}

#endif /* _ProjectMobius_hppReferenceCounter */
