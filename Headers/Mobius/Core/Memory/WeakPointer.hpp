/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file WeakPointer.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 02/05/2019.
 */

#ifndef _ProjectMobius_hppWeakPointer
#define _ProjectMobius_hppWeakPointer

#include <Mobius/Core/Memory/ReferenceCounter.hpp>

namespace Mobius {

/**
 * WeakPointer generic class.
 * Safely accesses underlying data using the ReferenceCounter class.
 * Does not increment the pointer counters, allowing the avoidance of circular references.
 */
template <typename T>
class WeakPointer {
    // ---  Methods ---
        // -- Public Methods --
        public:
            // - Operators -
                /**
                 * Deference operator.
                 *
                 * @return The underlying object.
                 */
                T operator *() const { return * _pData; }
    
                /**
                 * Member selection via pointer operator.
                 *
                 * @return The underlying pointer.
                 */
                T * operator ->() const { return _pData; }
    
                /**
                 * Assignement operator.
                 * Assigns a pointer to a WeakPointer object.
                 *
                 * @param data The new data to point to.
                 * @return The modified WeakPointer instance.
                 */
                WeakPointer<T>& operator =(const T * data) {
                    // Update the pointer reference.
                    this->_update(data);
                    
                    // Return the object.
                    return *this;
                }
    
                /**
                 * Assignement operator.
                 * Assigns a WeakPointer's contents to another WeakPointer object.
                 *
                 * @param pointer The WeakPointer this object is going to dopy the reference from.
                 * @return The modified WeakPointer instance.
                 */
                WeakPointer<T>& operator =(const WeakPointer<T> pointer) {
                    // Update the pointer reference.
                    this->_update(pointer._pData);
                    
                    // Return the object.
                    return *this;
                }
    
                /**
                 * Cast operator.
                 * Casts the weak pointer's data to a given base object.
                 * The cast is static, so the compiler will complain if the cast is invalid.
                 */
                template <class B>
                operator WeakPointer<B>() const { return WeakPointer<B>(static_cast<B *>(this->_pData)); }
    
            // - Constructors -
                /**
                 * Creates a new, empty WeakPointer.
                 */
                WeakPointer() : _pData(nullptr) {}
    
                /**
                 * Creates a new WeakPointer from the given pointer.
                 *
                 * @param data The data for this new StrongPointer.
                 */
                WeakPointer(T * data) : WeakPointer() { this->_update(data); }
    
                /**
                 * Copy constructor.
                 * Creates a new WeakPointer from the given WeakPointer.
                 *
                 * @param pointer The WeakPointer object to copy.
                 */
                WeakPointer(const WeakPointer<T>& pointer) : WeakPointer() { this->_update(pointer._pData); }
    
            // - Destructor -
                /**
                 * Does nothing.
                 */
                virtual ~WeakPointer() { }
    
            // - Methods -
                /**
                 * Allows the user to check wether this pointer is valid.
                 * Wraps the ReferenceCounter's isValid method.
                 *
                 * @return true if this WeakPointer's reference is valid. (aka. not deleted)
                 */
                const bool isValid() const { return isNull() ? false : ReferenceCounter::isValid(this->_pData); }
    
                /**
                 * Allows the user to check wether this pointer is a nullptr.
                 *
                 * @return true if this WeakPointer's reference is a nullptr.
                 */
                const bool isNull() const { return this->_pData == nullptr; }
    
        // -- Private Methods --
            /**
             * Updates the data pointer of this WeakPointer.
             *
             * @param pointer The new pointer to use for this WeakPointer.
             */
             void _update(T * pointer) {
                // Update the reference.
                this->_pData = pointer;
             }
    // --- /Methods ---
    
    // ---  Attributes ---
    private:
        /** Data held within the pointer. */
        T * _pData;
    // --- /Attributes ---
};

}

#endif /* _ProjectMobius_hppWeakPointer */
