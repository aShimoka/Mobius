
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file RenderPass.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 06/05/2019.
 */

import Metal
import AppKit

enum RenderPassError : Error {
    case invalidDrawableError
}

class Mobius_RenderPass {
    // ---  Methods ---
        // -- Public Methods --
            /**
             * Class constructor.
             * Prepares the render pass and its members.
             *
             * @param drawable The drawable to render into.
             * @param clearColor The clear color of the render pass.
             * @param cmdBuffer The command buffer to use for this pass.
             * @param pipelineState The pipeline state used by this render pass.
             * @param cullMode The culling mode of the render encoder.
             * @param depthStencil The depth stencil handler.
             */
            public init(
                drawable: CAMetalDrawable?, clearColor: MTLClearColor,
                cmdBuffer : MTLCommandBuffer, pipelineState : MTLRenderPipelineState,
                cullMode : MTLCullMode, depthStencil : MTLDepthStencilState,
                depthTexture : MTLTexture
            ) throws {
                // Check if the drawable is no nil.
                guard let unwrappedDrawable = drawable else {
                    throw RenderPassError.invalidDrawableError;
                }
                
                // Set the commited flag.
                _bIsCommited = false;
                
                // Store the drawable.
                _drawable = unwrappedDrawable;
                
                // Create the render pass descriptor.
                let passDescriptor = MTLRenderPassDescriptor()
                    // Load the texture from the drawable.
                    passDescriptor.colorAttachments[0].texture = _drawable.texture
                    // Set the clear mode.
                    passDescriptor.colorAttachments[0].loadAction = .clear;
                    // Set the clear color.
                    passDescriptor.colorAttachments[0].clearColor = clearColor;
                    // Set the depth stencil's texture.
                    passDescriptor.depthAttachment.texture = depthTexture;
                    // Set the clear depth.
                    passDescriptor.depthAttachment.clearDepth = 1.0;
                    // Set the store action.
                    passDescriptor.depthAttachment.storeAction = .dontCare;
                    // Clear the texture on load.
                    passDescriptor.depthAttachment.loadAction = .clear;
                    // Set the stencil info.
                    passDescriptor.stencilAttachment.texture = depthTexture;
                    passDescriptor.stencilAttachment.storeAction = .store;
                    passDescriptor.stencilAttachment.loadAction = .clear;
                
                // Store the command buffer.
                _cmdBuffer = cmdBuffer;
                
                // Prepare the render encoder.
                _encoder = _cmdBuffer.makeRenderCommandEncoder(descriptor: passDescriptor);
                
                // Enable the stencil.
                _encoder.setDepthStencilState(depthStencil);
                // Set the pipeline state in the encoder.
                _encoder.setRenderPipelineState(pipelineState);
                // Set the culling mode.
                _encoder.setCullMode(cullMode);
            }
    
            /**
             * Commits the encoder to the rendering.
             */
            public func commit() {
                // End the render encoding.
                _encoder.endEncoding();
                
                // Present the drawable and commit the buffer.
                _cmdBuffer.present(_drawable);
                _cmdBuffer.commit();
                
                // Set the commited flag.
                _bIsCommited = true;
            }
    
            /**
             * Defines the MTLBuffer for the vertex shader at a given index.
             *
             * @param descriptor The buffer descriptor.
             * @param index The index to put the buffer at.
             */
            public func setVertexBufferAtIndex(descriptor: cMB_RNDR_BUF_Descriptor, index: CUnsignedInt) {
                // Prepare the buffer variable.
                var buffer : MTLBuffer? = nil;
                
                // Check the buffer type.
                if (descriptor.type == cMB_RNDR_BUF_Mutable) {
                    // Get the mutable buffer's contents.
                    buffer = Mobius_BufferManager.getMutableBuffer(descriptor: descriptor);
                    
                    // Add to the liberate action.
                    _cmdBuffer.addCompletedHandler { (_) in
                        Mobius_BufferManager.freeBufferInPool(descriptor: descriptor);
                    }
                } else if (descriptor.type == cMB_RNDR_BUF_Immutable) {
                    // Get the immutable buffer.
                    buffer = Mobius_BufferManager.getImmutableBuffer(descriptor: descriptor);
                }
            
                _encoder.setVertexBuffer(buffer, offset: 0, index: Int(index));
            }
    
            /**
             * Defines the MTLBuffer for the fragment shader at a given index.
             *
             * @param descriptor The buffer descriptor.
             * @param index The index to put the buffer at.
             */
            public func setFragmentBufferAtIndex(descriptor: cMB_RNDR_BUF_Descriptor, index: CUnsignedInt) {
                // Prepare the buffer variable.
                var buffer : MTLBuffer? = nil;
                
                // Check the buffer type.
                if (descriptor.type == cMB_RNDR_BUF_Mutable) {
                    // Get the mutable buffer's contents.
                    buffer = Mobius_BufferManager.getMutableBuffer(descriptor: descriptor);
                    
                    // Add to the liberate action.
                    _cmdBuffer.addCompletedHandler { (_) in
                        Mobius_BufferManager.freeBufferInPool(descriptor: descriptor);
                    }
                } else if (descriptor.type == cMB_RNDR_BUF_Immutable) {
                    // Get the immutable buffer.
                    buffer = Mobius_BufferManager.getImmutableBuffer(descriptor: descriptor);
                }
                
                _encoder.setFragmentBuffer(buffer, offset: 0, index: Int(index));
            }
    
            /**
             * Renders the given triangles.
             *
             * @param count The number of triangles to draw.
             * @param from The index to start drawing from.
             */
            public func renderTriangles(count: CUnsignedInt, from: CUnsignedInt) {
                _encoder.drawPrimitives(type: .triangle, vertexStart: Int(from), vertexCount: Int(count));
            }
    // --- /Methods ---
    
    // ---  Attributes ---
        // -- Private Attributes --
            /** Drawable on which the rendering occurs. */
            private var _drawable : CAMetalDrawable!
    
            /** Command buffer used by the render pass. */
            private var _cmdBuffer : MTLCommandBuffer!
    
            /** Render pass' encoder. */
            private var _encoder : MTLRenderCommandEncoder!
    
            /** Boolean storing wether or not the encoder was already commited. */
            private var _bIsCommited : Bool
    // --- /Attributes ---
}

/**
 * C API Bridge.
 * All these functions are described in the Render bridging header.
 */

@_cdecl("sMB_RNDR_PASS_create")
func sMB_RNDR_PASS_create(descriptor: cMB_RNDR_PIP_Descriptor) {
    // Get the pipeline object.
    guard let pipeline = Mobius_PipelineManager.getPipeline(identifier: descriptor.window) else {
        return;
    }
    
    // Create the render pass object.
    _ = pipeline.getRenderPass();
}

@_cdecl("sMB_RNDR_PASS_setVertexBufferAt")
func sMB_RNDR_PASS_setVertexBufferAt(pipeDescriptor: cMB_RNDR_PIP_Descriptor, buffDescriptor: cMB_RNDR_BUF_Descriptor, index: CUnsignedInt) {
    // Get the pipeline object.
    guard let pipeline = Mobius_PipelineManager.getPipeline(identifier: pipeDescriptor.window) else {
        return;
    }
    
    // Set the buffer object.
    pipeline.getRenderPass().setVertexBufferAtIndex(descriptor: buffDescriptor, index: index);
}

@_cdecl("sMB_RNDR_PASS_setFragmentBufferAt")
func sMB_RNDR_PASS_setFragmentBufferAt(pipeDescriptor: cMB_RNDR_PIP_Descriptor, buffDescriptor: cMB_RNDR_BUF_Descriptor, index: CUnsignedInt) {
    // Get the pipeline object.
    guard let pipeline = Mobius_PipelineManager.getPipeline(identifier: pipeDescriptor.window) else {
        return;
    }
    
    // Set the buffer object.
    pipeline.getRenderPass().setFragmentBufferAtIndex(descriptor: buffDescriptor, index: index);
}

@_cdecl("sMB_RNDR_PASS_renderTriangles")
func sMB_RNDR_PASS_renderTriangles(pipeDescriptor: cMB_RNDR_PIP_Descriptor, count : CUnsignedInt, from: CUnsignedInt) {
    // Get the pipeline object.
    guard let pipeline = Mobius_PipelineManager.getPipeline(identifier: pipeDescriptor.window) else {
        return;
    }
    
    // Call the rendering method.
    pipeline.getRenderPass().renderTriangles(count: count, from: from)
}

@_cdecl("sMB_RNDR_PASS_commit")
func sMB_RNDR_PASS_commit(pipeDescriptor: cMB_RNDR_PIP_Descriptor) {
    // Get the pipeline object.
    guard let pipeline = Mobius_PipelineManager.getPipeline(identifier: pipeDescriptor.window) else {
        return;
    }
    
    // Commit the render pass.
    pipeline.commitRenderPass();
}
