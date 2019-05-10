
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Prototype.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 02/05/2019.
 */

#ifndef _ProjectMobius_hppPrototype
#define _ProjectMobius_hppPrototype

#include <Mobius/Core/Memory/WeakPointer.hpp>

namespace Mobius {

/**
 * Base abstract prototype class.
 * Used to reflect upon the objects of the Mobius engine.
 */
class PrototypeBase {
    // ---  Methods ---
        // -- Public Methods --
        public:
            /**
             * Class constructor.
             * Creates a new Prototype instance and registers it in the factory.
             */
            PrototypeBase();
    
            /**
             * Virtual class name accessor.
             * This method must be overriden by each child prototype object.
             */
            virtual const char * getClassName() const = 0;
    
            /**
             * Class parent accessor.
             */
            virtual const WeakPointer<const PrototypeBase> getParent() const = 0;

    
        // -- Private Methods --
        private:
    // --- /Methods ---
    
    // ---  Attributes ---
        // -- Private Attributes --
        private:
            /** Const pointer to the name of the refered class. */
            const char * _pReferedName;
    // --- /Attributes ---
};

}


#endif /* _ProjectMobius_hppPrototype */
