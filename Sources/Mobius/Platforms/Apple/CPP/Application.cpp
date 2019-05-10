/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Application.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 03/05/2019.
 */

#include <Mobius/Platforms/Apple/Bridge/C/Application.h>

#include <Mobius/Engine.hpp>

#include <exception>

int cMobius_Engine_onSetup() { return Mobius::Engine::onSetup(); }

int cMobius_Engine_onLoop(double deltaTime) { return Mobius::Engine::onLoop(deltaTime); }

void cMobius_Engine_onClose() { Mobius::Engine::onClose(); }

void cMB_NGIN_throw(void) { throw std::exception(); }
