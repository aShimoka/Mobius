//
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Descriptor.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 04/05/2019.
 */

#include <Mobius/Server/Render/Window/Descriptor.hpp>

#include <cstring>

namespace Mobius {
namespace Render {
namespace Window {

Descriptor::Descriptor(unsigned int identifier, Math::Rect2f frame, unsigned int flags, unsigned int screen, const char * title)
{
    this->identifier = identifier; this->frame = frame; this->flags = flags; this->screen = screen; this->title = title;
}

Descriptor::Descriptor() :
    Descriptor(0, Math::Rect2f(), cMB_RNDR_WIN_Flags_Invalid, 0, nullptr)
{}

Descriptor::Descriptor(const cMB_RNDR_WIN_Descriptor& copy)
{
    this->identifier = copy.identifier; this->frame = copy.frame; this->flags = copy.flags; this->screen = copy.screen; this->title = copy.title;
}

void Descriptor::parseFlag(const char *flag) {
    // Compare the string.
    if(!strcmp(flag, "Closable"))       this->flags |= cMB_RNDR_WIN_Flags_Closable;
    if(!strcmp(flag, "Miniaturizable")) this->flags |= cMB_RNDR_WIN_Flags_Miniaturizable;
    if(!strcmp(flag, "Resizable"))      this->flags |= cMB_RNDR_WIN_Flags_Resizable;
    if(!strcmp(flag, "Borderless"))     this->flags |= cMB_RNDR_WIN_Flags_Borderless;
    if(!strcmp(flag, "Fullscreen"))     this->flags |= cMB_RNDR_WIN_Flags_Fullscreen;
}

}
}
}
