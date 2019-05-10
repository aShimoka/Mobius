
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Pipeline.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 06/05/2019.
 */

// TODO : Abstract pipeline away.
import AppKit
import Metal

class Mobius_PipelineManager {
    // ---  Methods ---
        // -- Public Methods --
            /**
             * Creates a new Pipeline object.
             * Uses the given descriptor to prepare the object.
             *
             * @param descriptor The descriptor parsed to create the pipeline.
             * @return An up-to-date descriptor made from the built object.
             */
            static func createPipeline(descriptor: cMB_RNDR_PIP_Descriptor) -> cMB_RNDR_PIP_Descriptor? {
                // Create the pipeline object.
                do {
                    // Create the pipeline.
                    let pipeline = try Mobius_Pipeline(identifier: descriptor.window);
                    
                    // Parse the descriptor.
                    try pipeline.parseDescriptor(descriptor: descriptor);
                    
                    // Return the results of the query.
                    return queryPipeline(identifier: descriptor.window);
                    
                } catch Mobius_PipelineError.invalidWindowIdentifier {
                    print("Pipeline creation error : Wrong window identifier.");
                } catch Mobius_PipelineError.invalidFragmentFunction {
                    print("Pipeline creation error : Wrong fragment function.");
                } catch Mobius_PipelineError.invalidVertexFunction {
                    print("Pipeline creation error : Wrong vertex function.");
                } catch {
                    print("Unexcpected error: \(error)");
                }

                return nil;
            }
    
            /**
             * Queries for a pipeline descriptor.
             *
             * @param identifier The identifier of the pipeline's window.
             * @return An up-to-date descriptor made from the pipeline object.
             */
            static func queryPipeline(identifier: CUnsignedInt) -> cMB_RNDR_PIP_Descriptor? {
                // Get the window delegate corresponding to the given index.
                guard let delegate = Mobius_WindowManager.getWindowDelegate(index: identifier) else {
                    return nil;
                }
                
                // Parse the pipeline state.
                return delegate._pipeline!._descriptor!;
            }
    
            /**
             * Updates a pipeline object.
             * Uses the given pipeline descriptor to update the pipeline object.
             *
             * @param identifier The identifier of the pipeline's window.
             * @param descriptor The descriptor parsed to update the pipeline.
             * @return An up-to-date descriptor made from the updated object.
             */
            static func updatePipeline(identifier: CUnsignedInt, descriptor: cMB_RNDR_PIP_Descriptor) -> cMB_RNDR_PIP_Descriptor? {
                return nil;
            }
    
            /**
             * Closes the given pipeline descriptor.
             *
             * @param identifier The identifier of the pipeline's window.
             */
            static func closePipeline(identifier: CUnsignedInt) {
                return;
            }
    
            static func getPipeline(identifier: CUnsignedInt) -> Mobius_Pipeline? {
                guard let delegate = Mobius_WindowManager.getWindowDelegate(index: identifier) else {
                    return nil;
                }
                
                return delegate._pipeline;
            }
    // --- /Methods ---

    // ---  Attributes ---
        // -- Private Attributes --
    // --- /Attributes ---
}

/**
 * C API Bridge.
 * All these functions are described in the Pipeline bridging header.
 */

let invalidPipelineDescriptor = cMB_RNDR_PIP_Descriptor(
    window: 0, fragment: nil, vertex: nil, clearColor: (0, 0, 0, 1), bufferManager: 0, culling: cMB_RNDR_PIP_FrontfaceCulling);

@_cdecl("sMB_RNDR_PIP_create")
func sMB_RNDR_PIP_create(descriptor: cMB_RNDR_PIP_Descriptor) -> cMB_RNDR_PIP_Descriptor {
    // Call the manager's creation method.
    guard let descriptor = Mobius_PipelineManager.createPipeline(descriptor: descriptor) else {
        // If the creation failed, return the invalid descriptor.
        return invalidPipelineDescriptor;
    }
    
    // Return the created window's descriptor.
    return descriptor;
}

@_cdecl("sMB_RNDR_PIP_query")
func sMB_RNDR_PIP_query(identifier: CUnsignedInt) -> cMB_RNDR_PIP_Descriptor {
    // Call the manager's query method.
    guard let descriptor = Mobius_PipelineManager.queryPipeline(identifier: identifier) else {
        // If the query failed, return the invalid descriptor.
        return invalidPipelineDescriptor;
    }
    
    // Return the created window's descriptor.
    return descriptor;
}

@_cdecl("sMB_RNDR_PIP_update")
func sMB_RNDR_PIP_update(identifier: CUnsignedInt, descriptor: cMB_RNDR_PIP_Descriptor) -> cMB_RNDR_PIP_Descriptor {
    // Call the manager's query method.
    guard let descriptor = Mobius_PipelineManager.updatePipeline(identifier: identifier, descriptor: descriptor) else {
        // If the update failed, return the invalid descriptor.
        return invalidPipelineDescriptor;
    }
    
    // Return the created window's descriptor.
    return descriptor;
}

@_cdecl("sMB_RNDR_PIP_close")
func sMB_RNDR_PIP_close(identifier: CUnsignedInt) {
    // Call the manager's close method.
    Mobius_PipelineManager.closePipeline(identifier: identifier);
}

