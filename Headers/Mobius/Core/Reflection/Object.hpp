/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Object.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 02/05/2019.
 */

#ifndef _ProjectMobius_hppObject
#define _ProjectMobius_hppObject

#include <Mobius/Core/Reflection/Macros.hpp>
#include <Mobius/Core/Reflection/Prototype.hpp>
#include <Mobius/Core/Memory/StrongPointer.hpp>

namespace Mobius {

/**
 * Base class for all reflected Mobius objects.
 *
 */
class Object {
    MOBJECT_BASE_BODY()
public:
    virtual const ::Mobius::WeakPointer<const ::Mobius::PrototypeBase> getPrototype();
    Object();
};
typedef const WeakPointer<const Object::Prototype> PrototypeReference;

}

#endif /* _ProjectMobius_hppObject */
