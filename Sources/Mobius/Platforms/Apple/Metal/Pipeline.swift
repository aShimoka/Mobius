
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Pipeline.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 06/05/2019.
 */

import Metal
import AppKit

/**
 * Errors thrown by the metal pipeline object.
 */
enum Mobius_PipelineError : Error {
    case invalidWindowIdentifier
    case invalidVertexFunction
    case invalidFragmentFunction
}

class Mobius_Pipeline : Mobius_PipelineBase {
    // ---  Methods ---
        // -- Public Methods --
            /**
             * Class constructor.
             * Creates a new pipeline object and sets it up.
             *
             * @param identifier The identifier of the window delegate that this pipeline will be attached to.
             */
            public init(identifier: CUnsignedInt) throws {
                // Call the parent constructor.
                super.init()
                
                // Try to load the window from the identifier.
                guard let delegate = Mobius_WindowManager.getWindowDelegate(index: identifier) else {
                    throw Mobius_PipelineError.invalidWindowIdentifier;
                }
                // Create the local descriptor.
                _descriptor = cMB_RNDR_PIP_Descriptor(window: 0, fragment: nil, vertex: nil, clearColor: (0,0,0,0), bufferManager: 0, culling: 0);
                
                // Store the window identifier.
                _descriptor.window = identifier;
                
                // Attach the pipeline to the delegate.
                delegate._pipeline = self
                
                // Create the metal device.
                mtl_Device = delegate._mtl_Device;
                
                // Create the metal library.
                mtl_Library = mtl_Device.makeDefaultLibrary()!
                
                // Get the metal layer reference.
                mtl_Layer = delegate._mtl_Layer;
                
                // Create the command queue.
                mtl_CommandQueue = mtl_Device.makeCommandQueue();
                
                // Nullify the render pass.
                renderPass = nil;
            }
    
            /**
             * Parses the given descriptor and parameters the pipeline accordingly.
             *
             * @param descriptor The descriptor to parse.
             */
            public func parseDescriptor(descriptor: cMB_RNDR_PIP_Descriptor) throws {
                // Load the fragment function.
                guard let frag = mtl_Library.makeFunction(name: String(cString: descriptor.fragment)) else { throw Mobius_PipelineError.invalidFragmentFunction; }
                // Load the vertex function.
                guard let vertex = mtl_Library.makeFunction(name: String(cString: descriptor.vertex)) else { throw Mobius_PipelineError.invalidVertexFunction; }
                
                // Parse the culling mode.
                if (descriptor.culling == cMB_RNDR_PIP_BackfaceCulling) {
                    mtl_CullingMode = .back;
                } else {
                    mtl_CullingMode = .front;
                }
                _descriptor.culling = descriptor.culling;
                
                // Store the clear color.
                mtl_ClearColor = MTLClearColor(
                    red:   Double(descriptor.clearColor.0),
                    green: Double(descriptor.clearColor.1),
                    blue:  Double(descriptor.clearColor.2),
                    alpha: Double(descriptor.clearColor.3)
                );
                _descriptor.clearColor = descriptor.clearColor;
                
                // Create the render pipeline descriptor.
                let pipelineDescriptor = MTLRenderPipelineDescriptor()
                    // Set the vertex and fragment functions.
                    pipelineDescriptor.fragmentFunction = frag;
                    pipelineDescriptor.vertexFunction = vertex;
                
                    pipelineDescriptor.depthAttachmentPixelFormat = .depth32Float_stencil8;
                    pipelineDescriptor.stencilAttachmentPixelFormat = .depth32Float_stencil8;
                
                let attachment = pipelineDescriptor.colorAttachments[0]!;
                    // Set the pixel format.
                    attachment.pixelFormat = .bgra8Unorm;
                
                    // Enable alpha blending.
                    attachment.isBlendingEnabled = true;
                    attachment.rgbBlendOperation = .add;
                    attachment.alphaBlendOperation = .add;
                    attachment.sourceRGBBlendFactor = .sourceAlpha;
                    attachment.sourceAlphaBlendFactor = .sourceAlpha;
                    attachment.destinationRGBBlendFactor = .oneMinusSourceAlpha;
                    attachment.destinationAlphaBlendFactor = .oneMinusSourceAlpha;
                
                // Create the depth texture.
                let depthTextureDescriptor = MTLTextureDescriptor()
                    // Defines the pixel format.
                    depthTextureDescriptor.pixelFormat = .depth32Float_stencil8;
                    // Get the size of the texture.
                    depthTextureDescriptor.width = Int(mtl_Layer!.frame.width);
                    depthTextureDescriptor.height = Int(mtl_Layer!.frame.height);
                    // Disable mipmapping.
                    depthTextureDescriptor.mipmapLevelCount = 1;
                    // The texture is reserved for use by the GPU only.
                    depthTextureDescriptor.storageMode = .private;
                    // The texture is used to render upon it.
                    depthTextureDescriptor.usage = .renderTarget;
                
                // Create the texture object.
                mtl_DepthTexture = mtl_Device.makeTexture(descriptor: depthTextureDescriptor)!;
                
                // Create the depth stencil.
                let depthStencilDescriptor = MTLDepthStencilDescriptor();
                    // Set the stencil compare function.
                    depthStencilDescriptor.depthCompareFunction = .less;
                    // Enable writing to the depth stencil.
                    depthStencilDescriptor.isDepthWriteEnabled = true;
                
                mtl_DepthStencil = mtl_Device.makeDepthStencilState(descriptor: depthStencilDescriptor)!;
                
                // Create the pipeline state.
                mtl_PipelineState = try! mtl_Device.makeRenderPipelineState(descriptor: pipelineDescriptor);
                
                // Load the buffer manager.
                _descriptor.bufferManager = descriptor.bufferManager;
                if (_descriptor.bufferManager == cMB_RNDR_BUF_SharedManager) {
                    _bufferManager = Mobius_BufferManager.makeShared(device: mtl_Device);
                } else {
                    _bufferManager = Mobius_BufferManager(device: mtl_Device, identifier: _descriptor.window);
                    _descriptor.bufferManager = _descriptor.window;
                }
            }
    
            /**
             * Creates a new render pass object, or returns the current one.
             *
             * @return A RenderPass object that can be used to render data on the window.
             */
            public func getRenderPass() -> Mobius_RenderPass {
                // If the render pass is not initialized.
                if (renderPass == nil) {
                    // Create the render pass.
                    renderPass = try! Mobius_RenderPass(
                        drawable: mtl_Layer?.nextDrawable(),
                        clearColor: mtl_ClearColor,
                        cmdBuffer: mtl_CommandQueue.makeCommandBuffer()!,
                        pipelineState: mtl_PipelineState,
                        cullMode: mtl_CullingMode,
                        depthStencil: mtl_DepthStencil,
                        depthTexture: mtl_DepthTexture
                    );
                }
                
                // Return the render pass.
                return renderPass!;
            }
    
            /**
             * Commits the render pass object.
             */
            public func commitRenderPass() {
                // If the render pass is initialized.
                if (renderPass != nil) {
                    // Commit the render pass.
                    renderPass!.commit();
                    // Clear the instance.
                    renderPass = nil;
                }
            }
    
        // -- Internal Methods --
            /**
             * Clears the render pass.
             * Called by the render pass object itself when it is commited to the render pipeline.
             */
            internal func clearRenderPass() { renderPass = nil; }
    // --- /Methods ---
    
    // ---  Attributes ---
        // -- Private Attributes --
            /** Updated descriptor of this pipeline. */
            internal var _descriptor : cMB_RNDR_PIP_Descriptor!
    
            /** Metal device resonsible for the rendering pipeline. */
            private var mtl_Device : MTLDevice!
    
            /** Library of all the functions  */
            private var mtl_Library : MTLLibrary!
    
            /** Weak reference to the window's metal layer. */
            private weak var mtl_Layer : CAMetalLayer?
    
            /** Command queue of the pipeline. */
            private var mtl_CommandQueue : MTLCommandQueue!
    
            /** Render culling mode. */
            private var mtl_CullingMode : MTLCullMode!
    
            /** Rendering clear color. */
            private var mtl_ClearColor : MTLClearColor!
    
            /** Depth stencil used for rendering. */
            private var mtl_DepthStencil : MTLDepthStencilState!
    
            /** Depth texture used by the stencil. */
            private var mtl_DepthTexture : MTLTexture!
    
            /** Rendering pipeline state. */
            private var mtl_PipelineState : MTLRenderPipelineState!
    
            /** Mobius buffer manager of this pipeline. */
            private var _bufferManager : Mobius_BufferManager!
    
            /** Render pass object. */
            private var renderPass : Mobius_RenderPass?
    // --- /Attributes ---
}

