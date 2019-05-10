/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file StrongPointer.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 02/05/2019.
 */

#ifndef _ProjectMobius_hppStrongPointer
#define _ProjectMobius_hppStrongPointer

#include <Mobius/Core/Memory/ReferenceCounter.hpp>
#include <Mobius/Core/Memory/WeakPointer.hpp>

namespace Mobius {

/**
 * StrongPointer generic class.
 * Implements Automatic Reference Counting (ARC) using the ReferenceCounter class.
 */
template <typename T>
class StrongPointer {
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
    
                operator void *() const { return _pData; }
    
                /**
                 * Address operator.
                 * Wraps the WeakPointer conversion oeprator.
                 *
                 * @return A WeakPointer pointing to the data.
                 */
                WeakPointer<T> operator&() const { return (WeakPointer<T>)(*this); }
    
                /**
                 * WeakPointer conversion operator.
                 *
                 * @return A WeakPointer to the underlying object.
                 */
                operator WeakPointer<T>() const { return WeakPointer<T>(this->_pData); }
    
                /**
                 * Assignement operator.
                 * Assigns a pointer to a StrongPointer object.
                 *
                 * @param data The new data to point to.
                 * @return The modified StrongPointer instance.
                 */
                StrongPointer<T>& operator =(T * data) {
                    // Update the pointer reference.
                    this->_update(data);
                    
                    // Return the object.
                    return *this;
                }
    
                /**
                 * Assignement operator.
                 * Assigns a StrongPointer's contents to another StrongPointer object.
                 *
                 * @param pointer The StrongPointer this object is going to dopy the reference from.
                 * @return The modified StrongPointer instance.
                 */
                StrongPointer<T>& operator =(const StrongPointer<T> pointer) {
                    // Update the pointer reference.
                    this->_update(pointer._pData);
                    
                    // Return the object.
                    return *this;
                }
    
                /**
                 * Cast operator.
                 * Casts the strong pointer's data to a given base object.
                 * The cast is static, so the compiler should complain if the cast is invalid.
                 */
                template <class B>
                operator StrongPointer<B>() const { return StrongPointer<B>(static_cast<B*>(this->_pData)); }
    
            // - Constructors -
                /**
                 * Creates a new StrongPointer from the given pointer.
                 *
                 * @param data The data for this new StrongPointer.
                 */
                StrongPointer(T * data) : _pData(nullptr) { this->_update(data); }
    
                /**
                 * Copy constructor.
                 * Creates a new StrongPointer from the given StrongPointer.
                 *
                 * @param pointer The StrongPointer object to copy.
                 */
                StrongPointer(const StrongPointer<T>& pointer) : _pData(nullptr) { this->_update(pointer._pData); }
    
            // - Destructor -
                /**
                 * Ensures proper decrementation of the underlying pointer.
                 */
                virtual ~StrongPointer() { this->_update(nullptr); }
    
            // - Static Methods –
                /**
                 * Object creation constructor.
                 * Creates a new instance of the underlying type and returns a strong pointer to it.
                 * All parameters are passed to the class constructor.
                 */
                template<typename ...Args>
                static StrongPointer<T> create(Args ... params) { T * instance = new T(params ...); return StrongPointer<T>(instance); }
    
        // -- Private Methods --
        private:
            /**
             * Updates the data pointer of this StrongPointer.
             *
             * @param pointer The new pointer to use for this StrongPointer.
             */
             void _update(T * pointer) {
                // Decrement the old value.
                if (!ReferenceCounter::decrement(this->_pData)) delete this->_pData;
                
                // Update the reference.
                this->_pData = pointer;
                
                // Increment the new value.
                ReferenceCounter::increment(this->_pData);
             }
    // --- /Methods ---
    
    // ---  Attributes ---
    protected:
        /** Data held within the pointer. */
        T * _pData;
    // --- /Attributes ---
};

}

#endif /* _ProjectMobius_hppStrongPointer */
