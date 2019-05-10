//
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Descriptor.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 06/05/2019.
 */

#include <Mobius/Server/Render/Buffer/Descriptor.hpp>

#include <limits.h>

const unsigned int cMB_RNDR_BUF_InvalidManager = 0;
const unsigned int cMB_RNDR_BUF_SharedManager = UINT_MAX;

const unsigned int cMB_RNDR_BUF_Invalid = 0;
const unsigned int cMB_RNDR_BUF_Immutable = 1;
const unsigned int cMB_RNDR_BUF_Mutable = 2;

namespace Mobius {
namespace Render {
namespace Buffer {

Descriptor::Descriptor(unsigned int manager, unsigned int identifier, unsigned int objectCount, unsigned int objectSize, unsigned int type) {
    this->manager = manager; this->identifier = identifier; this->objectCount = objectCount; this->objectSize = objectSize; this->type = type;
}

Descriptor::Descriptor() :
    Descriptor(0, 0, 0, 0, cMB_RNDR_BUF_Invalid)
{}

Descriptor::Descriptor(const cMB_RNDR_BUF_Descriptor& copy) :
    Descriptor(copy.manager, copy.identifier, copy.objectCount, copy.objectSize, copy.type)
{}

}
}
}

