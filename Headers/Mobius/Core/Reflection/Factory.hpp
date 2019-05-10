
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Factory.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 02/05/2019.
 */

#ifndef _ProjectMobius_hppFactory
#define _ProjectMobius_hppFactory

#include <Mobius/Core/Memory/StrongPointer.hpp>
#include <Mobius/Core/Memory/WeakPointer.hpp>
#include <Mobius/Core/Reflection/Prototype.hpp>
#include <Mobius/Core/Reflection/Object.hpp>

#include <string>

namespace Mobius {

// Type alias for the prototype map.
typedef StrongPointer<std::map<const std::string, PrototypeReference>> PrototypeMap;

/**
 * Singleton class in charge of handling the reflection in the game engine.
 * All prototypes are excpected to self-register through static instantiation.
 * This allows the user to get class info at runtime.
 */
class Factory {
    // ---  Methods ---
        // -- Public Methods --
        public:
            /**
             * Register a new prototype in the ObjectFactory class.
             * Should be called by the Prototype subclass.
             *
             * @param referedClassName  The name of the new class to hold in memory.
             * @param prototype  A PrototypeReference to the class's descriptor.
             */
            static void registerPrototype(PrototypeReference prototype, const std::string referedClassName);
    
            /**
             * Check if a given prototype exists within the factory.
             *
             * @param className  The name of the desired class.
             * @return  True if the class exists in the factory.
             */
            static bool classExists(const std::string className);
    
            /**
             * Returns the requested prototype object.
             * If the prototype does not exist, an invalidated pointer is returned.
             *
             * @param className  The name of the desired class.
             * @return  The requested prototype, or an invalid pointer.
             */
            static PrototypeReference getPrototype(const std::string className);
    
            /**
             * Use the given prototype to create a new class instance.
             *
             * @param prototype  The prototype reference for the object to create.
             * @return  A strong pointer to the constructed object.
             */
            static Object::Reference makeObject(PrototypeReference prototype);
    
            /**
             * Create a new object from a given class name.
             *
             * @param className  The name of the desired class.
             * @return  A strong pointer to the constructed object. If the class name is invalid, this pointer will be invalidated.
             */
            static Object::Reference makeObject(const std::string className);
    
            /**
             * Make a new object based on a given type.
             *
             * @return A reference to the newly created object.
             */
            template <class T, typename ... Args >
            static Object::Reference makeObject(Args& ... params) { return new T(params ...); }
    
        // -- Private Methods --
        private:
            /**
             * Private class empty constructor.
             * Used to create the prototype map.
             * Privatized to ensure Singleton structure.
             */
            Factory();
    
            /**
             * Returns a pointer to the singleton instance.
             *
             * @return A weak pointer to the singleton instance.
             */
            static WeakPointer<Factory> getInstance();
    // --- /Methods ---
    
    // --- /Attributes ---
        // -- Private Attributes --
        private:
            /**
             * HashMap of all the prototype.
             * Holds a cross-reference class name / PrototypeReference of all declared prototypes.
             */
            PrototypeMap _pPrototypeMap;
    // ---  Attributes ---
};

}

#endif /* _ProjectMobius_hppFactory */
