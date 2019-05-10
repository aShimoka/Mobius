//
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Descriptor.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 06/05/2019.
 */

#include <Mobius/Server/Render/Pipeline/Descriptor.hpp>
#include <Mobius/Server/Render/Buffer/Descriptor.hpp>
#include <Mobius/Core/Reflection/Factory.hpp>

MOBJECT_DECLARE(Mobius::Render::Pipeline::Descriptor)

namespace Mobius {
namespace Render {
namespace Pipeline {

Descriptor::Descriptor(unsigned int window, const char * fragment, const char * vertex, const float * clearColor, unsigned int bufferManager, unsigned int culling) {
    this->window = window; this->fragment = fragment; this->vertex = vertex; this->bufferManager = bufferManager; this->culling = culling;
    this->clearColor[0] = clearColor[0]; this->clearColor[1] = clearColor[1]; this->clearColor[2] = clearColor[2]; this->clearColor[3] = clearColor[3];
}

Descriptor::Descriptor() :
    Descriptor(0, nullptr, nullptr, (float[4]){ 0.f, 0.f, 0.f, 1.f }, cMB_RNDR_BUF_Invalid, cMB_RNDR_PIP_FrontfaceCulling)
{}

Descriptor::Descriptor(const cMB_RNDR_PIP_Descriptor& copy) :
    Descriptor(copy.window, copy.fragment, copy.vertex, copy.clearColor, copy.bufferManager, copy.culling)
{}

}
}
}
