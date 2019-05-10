//
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Factory.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 02/05/2019.
 */

#include <Mobius/Core/Reflection/Factory.hpp>

#include <Mobius/Core/Reflection/Prototype.hpp>

#include <stdio.h>

namespace Mobius {

void Factory::registerPrototype(PrototypeReference prototype, const std::string referedClassName) {
    // Get the map instance.
    PrototypeMap map = getInstance()->_pPrototypeMap;
    
    // Check if the class is not already defined.
    if (map->find(referedClassName) == map->end()) {
        // Add it to the map.
        map->insert(std::make_pair(referedClassName, prototype));
    } else {
        // TODO : Handle errors !
    }
}

bool Factory::classExists(const std::string className) {
    // Return wether or not the class exists in the map.
    PrototypeMap map = getInstance()->_pPrototypeMap;
    return getInstance()->_pPrototypeMap->find(className) != getInstance()->_pPrototypeMap->end();
}

PrototypeReference Factory::getPrototype(const std::string className) {
    // Get the map instance.
    PrototypeMap map = getInstance()->_pPrototypeMap;
    
    // Check if the class exists.
    auto iterator = map->find(className);
    if (iterator != map->end()) {
        // Return the prototype.
        return iterator->second;
    } else {
        // Return an invalid reference.
        return PrototypeReference();
    }
}

Object::Reference Factory::makeObject(PrototypeReference prototype) {
    // If the prototype is valid.
    if (prototype.isValid()) {
        // Return a new object instance.
        Object::Reference object = prototype->makeEmptyObject();
        
        // Return the object.
        return object;
    } else {
        // TODO : Proper error handling.
        printf("INVALID PROTOTYPE OBJECT !!!");
        throw "INVALID PROTOTYPE OBJECT !!!";
    }
}

Object::Reference Factory::makeObject(const std::string className) {
    // Get the prototype object.
    PrototypeReference prototype = getPrototype(className);
    
    // Wrap the prototype based method.
    return makeObject(prototype);
}

Factory::Factory() : _pPrototypeMap(nullptr) {
    // Create the map object.
    this->_pPrototypeMap = PrototypeMap::create();
}

WeakPointer<Factory> Factory::getInstance() {
    static Factory staticInstance;
    return &staticInstance;
}

}
