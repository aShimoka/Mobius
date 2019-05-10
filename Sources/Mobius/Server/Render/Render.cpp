/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Render.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 04/05/2019.
 */

#include <Mobius/Server/Render/Render.hpp>
#include <Mobius/Core/Reflection/Factory.hpp>
#include <Mobius/Server/Render/Window/Manager.hpp>
#include <Mobius/Server/Render/Pipeline/Manager.hpp>

MOBJECT_DECLARE(Mobius::Render::RenderServer)

namespace Mobius {
namespace Render {

RenderServer::RenderServer()
{}
RenderServer::~RenderServer() {
    
}

void RenderServer::setupServer(ConfigNode::WeakReference configRoot) {
    // Parse the configRoot object.
    if (configRoot.isValid()) {
        // Loop through the windows.
        ConfigNode::ChildrenList windows = configRoot->getChildElementsByName("Window");
        for (auto it = windows.begin(); it != windows.end(); it++) {
            // Create the window.
            Window::Manager::parseConfig(*it);
        }
        
        // Loop through the pipelines.
        ConfigNode::ChildrenList pipelines = configRoot->getChildElementsByName("Pipeline");
        for (auto it = pipelines.begin(); it != pipelines.end(); it++) {
            // Create the pipeline.
            parsePipelineNode(*it);
        }
    } else {
        printf("Inited Render server without config ???");
    }
}

void RenderServer::parsePipelineNode(ConfigNode::WeakReference configRoot) {
    // Create the pipeline.
    Pipeline::Manager::parseConfig(configRoot);
}

void RenderServer::serverQuit() {
    
}

RenderServer::WeakReference RenderServer::instance() {
    static RenderServer instance;
    return &instance;
}

}
}
