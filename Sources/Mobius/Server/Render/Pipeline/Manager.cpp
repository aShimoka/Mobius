//
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Manager.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 06/05/2019.
 */

#include <Mobius/Server/Render/Pipeline/Manager.hpp>
#include <Mobius/Server/Render/Pipeline/Exceptions.hpp>

#include <Mobius/Server/Render/Window/Exceptions.hpp>
#include <Mobius/Server/Render/Window/Manager.hpp>

#include <Mobius/Server/Render/Buffer/Descriptor.hpp>

#include <Mobius/Platforms/Apple/Bridge/Swift/Pipeline.h>

namespace Mobius {
namespace Render {
namespace Pipeline {

Descriptor Manager::createPipeline(std::string window, Descriptor descriptor) {
    try {
        // Load the window descriptor.
        descriptor.window = Window::Manager::getWindowIdentifier(window);
        
        // Call the bridged pipeline creator.
        Descriptor info = sMB_RNDR_PIP_create(descriptor);
        
        // Return the info descriptor.
        return info;
    } catch (Window::InvalidIDException& invalidID) {
        // Throw an other InvalidIDException.
        throw InvalidIDException("Tried to create pipeline for non-existent window");
    }
}

Descriptor Manager::queryPipeline(std::string window) {
    try {
        // Load the window descriptor.
        unsigned int windowIdentifier = Window::Manager::getWindowIdentifier(window);
        
        // Call the bridged pipeline query.
        Descriptor info = sMB_RNDR_PIP_query(windowIdentifier);
        
        // Return the info descriptor.
        return info;
    } catch (Window::InvalidIDException& invalidID) {
        // Throw an other InvalidIDException.
        throw InvalidIDException("Tried to query pipeline for non-existent window");
    }
}

Descriptor Manager::updatePipeline(std::string window, Descriptor descriptor) {
    try {
        // Load the window descriptor.
        unsigned int windowIdentifier = Window::Manager::getWindowIdentifier(window);
        
        // Call the bridged pipeline update.
        Descriptor info = sMB_RNDR_PIP_update(windowIdentifier, descriptor);
        
        // Return the info descriptor.
        return info;
    } catch (Window::InvalidIDException& invalidID) {
        // Throw an other InvalidIDException.
        throw InvalidIDException("Tried to query pipeline for non-existent window");
    }
}

void Manager::closePipeline(std::string window) {
    try {
        // Load the window descriptor.
        unsigned int windowIdentifier = Window::Manager::getWindowIdentifier(window);
        
        // Call the bridged pipeline close.
        sMB_RNDR_PIP_close(windowIdentifier);
    } catch (Window::InvalidIDException& invalidID) {
        // Throw an other InvalidIDException.
        throw InvalidIDException("Tried to query pipeline for non-existent window");
    }
}

void Manager::parseConfig(ConfigNode::WeakReference configRoot) {
    // Prepare the result descriptor.
    Descriptor result;
    
    // Check if a window was specified.
    std::string windowStrIdentifier = ""; configRoot->getAttribute("window", &windowStrIdentifier);
    if (windowStrIdentifier != "") {
        // Seek the vertex shader.
        ConfigNode::WeakReference vertexNode = configRoot->getChildElementByName("Vertex");
        if (vertexNode.isValid()) {
            // Get the vertex function.
            std::string vertex = vertexNode->getText();
            result.vertex = vertex.c_str();
            
            // Seek the fragment shader.
            ConfigNode::WeakReference fragmentNode = configRoot->getChildElementByName("Fragment");
            if (fragmentNode.isValid()) {
                // Get the fragment function.
                std::string fragment = fragmentNode->getText();
                result.fragment = fragment.c_str();
                
                // Try to get the clear color.
                ConfigNode::WeakReference clearColorNode = configRoot->getChildElementByName("ClearColor");
                if (clearColorNode.isValid()) {
                    // Load the clear color values.
                    clearColorNode->getAttribute("r", &(result.clearColor[0]));
                    clearColorNode->getAttribute("g", &(result.clearColor[1]));
                    clearColorNode->getAttribute("b", &(result.clearColor[2]));
                    clearColorNode->getAttribute("a", &(result.clearColor[3]));
                }
                
                // Check for shared buffer manager.
                std::string sharedBufferManager;
                configRoot->getAttribute("shared", &sharedBufferManager);
                if (sharedBufferManager != "") {
                    result.bufferManager = cMB_RNDR_BUF_SharedManager;
                }
                
                // Check for culling mode.
                std::string cullingMode = "front";
                configRoot->getAttribute("culling", &cullingMode);
                
                // Parse the culling mode.
                if (cullingMode == "back") {
                    result.culling = cMB_RNDR_PIP_BackfaceCulling;
                } else {
                    result.culling = cMB_RNDR_PIP_FrontfaceCulling;
                }
                
                // Create the pipeline.
                createPipeline(windowStrIdentifier, result);
            } else {
                // Throw a ParsingException.
                throw ParsingException("Pipeline had no <Fragment> element.");
            }
        } else {
            // Throw a ParsingException.
            throw ParsingException("Pipeline had no <Vertex> element.");
        }
    } else {
        // Throw an InvalidIDException.
        throw InvalidIDException("No window specified in the <Pipeline> element.");
    }
}

//static RenderPass createRenderPass(std::string window) {}


}
}
}
