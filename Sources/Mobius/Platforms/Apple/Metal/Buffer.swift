
/**
 * Copyright © 2019 CAILLAUD Jean-Baptiste. All rights reserved.
 * Mobius Project file Buffer.
 * Created in Mobius by Jean-Baptiste CAILLAUD on 04/05/2019.
 */

import Metal

class Mobius_BufferManager {
    // ---  Sub-Objects ---
        private class Mobius_BufferPool {
            // ---  Methods ---
                // -- Public Methods --
                    /**
                     * Class constructor.
                     * Builds a new BufferPool object.
                     * Allocates the pool's buffers and prepares the semaphore object.
                     */
                    internal init(objectSize : CUnsignedInt, objectCount : CUnsignedInt, poolSize: Int, device: MTLDevice) {
                        // Store the buffer info data.
                        self.objectSize = objectSize; self.objectCount = objectCount;
                        self.poolSize = 0; self.semaphore = DispatchSemaphore(value: 0);
                        self.nextBuffer = 0;
                        
                        // Create the pool.
                        pool = [MTLBuffer]();
                        
                        // Allocate the buffer pool.
                        allocatePools(poolSize, device: device);
                    }
            
                    /**
                     * Allocates all the buffers in the pool.
                     *
                     * @param newPoolSize The new size of the pool.
                     */
                    internal func allocatePools(_ newPoolSize: Int, device: MTLDevice) {
                        // Create the semaphore dispatch.
                        semaphore = DispatchSemaphore(value: newPoolSize);
                        
                        // Allocate all the buffers.
                        for _ in 0...newPoolSize {
                            pool.append(device.makeBuffer(length: Int(objectCount * objectSize), options: [.storageModeManaged])!);
                        }
                        
                        // Store the new pool size.
                        self.poolSize = newPoolSize;
                    }
            
                    /**
                     * Returns the next available buffer in the list.
                     * Fills it with the given data and locks it in the semaphore.
                     */
                    internal func getNextBuffer(data : UnsafeRawPointer) -> Int {
                        // Lock the semaphore.
                        _ = semaphore.wait(timeout: .distantFuture)
                        
                        // Get the next buffer object.
                        let buffer = pool[nextBuffer];
                        
                        // Increment the next buffer.
                        let index = nextBuffer;
                        nextBuffer = (nextBuffer + 1) % poolSize;
                        
                        // Assign the data to the buffer.
                        let size = Int(objectCount * objectSize);
                        buffer.contents().copyMemory(from: data, byteCount: size);
                        // Update the buffer in the GPU's memory.
                        buffer.didModifyRange(0..<size);
                        
                        // Return the identifier.
                        return index + 1;
                    }
            
                    /**
                     * Returns a read-only buffer object.
                     */
                    internal func getBuffer(_ index: Int) -> MTLBuffer? {
                        if (index > 0 && index <= poolSize) {
                            return pool[index - 1];
                        } else {
                            return nil;
                        }
                    }
            
                    /**
                     * Liberates the buffer.
                     * Allows it to be written to again.
                     */
                    internal func freeBuffer() {
                        semaphore.signal();
                    }
            
                    /**
                     * Returns a hash of the buffer pool.
                     */
                    internal static func hash(size: CUnsignedInt, count: CUnsignedInt) -> Int {
                        // TODO : True hashing.
                        return Int(size * count);
                    }
            
            // --- /Methods ---
            
            // ---  Attributes ---
                // -- Private Attributes --
                    // - Buffer info -
                        /** Size of an object in the buffer pool. */
                        private var objectSize : CUnsignedInt;
            
                        /** Number of objects in the buffer pool. */
                        private var objectCount : CUnsignedInt;
            
                        /** Number of buffers in the pool. */
                        private var poolSize : Int;
            
                    // - Pool Data -
                        /** Actual buffer array. */
                        private var pool : [MTLBuffer]
            
                        /** Index of the next pool buffer. */
                        private var nextBuffer : Int;
            
                        /** Buffer access semaphore object. */
                        private var semaphore : DispatchSemaphore
            // --- /Attributes ---
        }
    // --- /Sub-Objects ---
    
    // ---  Methods ---
        // -- Public Methods --
            /**
             * Allocates the given buffer object.
             *
             * @param descriptor The descriptor of the immutable buffer that needs allocation.
             * @return A filled descriptor object with the valid configuration.
             */
            public func allocateBuffer(data: UnsafeRawPointer, descriptor : cMB_RNDR_BUF_Descriptor) -> cMB_RNDR_BUF_Descriptor {
                // Copy the descriptor.
                var out = descriptor;
                
                // If the buffer is immutable.
                if (descriptor.type == cMB_RNDR_BUF_Immutable) {
                    // Create the new buffer.
                    let buffer = mtl_Device.makeBuffer(bytes: data, length: Int(descriptor.objectCount * descriptor.objectSize), options: [.storageModeManaged])!;
                    buffer.didModifyRange(0..<Int(descriptor.objectCount * descriptor.objectSize));
                    
                    // Add the buffer to the immutable buffer list.
                    immutableBuffers.append(buffer);
                    
                    // Set the descriptor's identifier.
                    out.identifier = CUnsignedInt(immutableBuffers.count);
                } else {
                    // If the buffer pool does not exist.
                    let hash = Mobius_BufferPool.hash(size: descriptor.objectSize, count: descriptor.objectCount);
                    let poolIndex = bufferPools.index(forKey: hash);
                    if (poolIndex == nil) {
                        // Create the buffer pool.
                        bufferPools[hash] = Mobius_BufferPool(objectSize: descriptor.objectSize, objectCount: descriptor.objectCount, poolSize: 25, device: mtl_Device);
                    }
                }
                
                // Return the descriptor.
                return out;
            }
    
            /**
             * Returns a mutable MTLBuffer object based on a descriptor.
             *
             * @param descriptor The descriptor of the requested buffer.
             * @return The MTLBuffer object.
             */
            public static func getImmutableBuffer(descriptor: cMB_RNDR_BUF_Descriptor) -> MTLBuffer? {
                // Get the buffer manager.
                guard let manager = bufferManagers[descriptor.manager] else {
                    return nil;
                }
                
                // Return the buffer.
                if (descriptor.identifier > 0 && descriptor.identifier <= manager.immutableBuffers.count) {
                    return manager.immutableBuffers[Int(descriptor.identifier) - 1];
                } else {
                    return nil;
                }
            }
    
            /**
             * Returns a mutable MTLBuffer object based on a descriptor.
             *
             * @param descriptor The descriptor of the requested buffer.
             * @return The MTLBuffer object.
             */
            public static func getMutableBuffer(descriptor: cMB_RNDR_BUF_Descriptor) -> MTLBuffer? {
                // Get the buffer manager.
                guard let manager = bufferManagers[descriptor.manager] else {
                    return nil;
                }
                
                // Get the buffer pool object.
                guard let pool = manager.bufferPools[Mobius_BufferPool.hash(size: descriptor.objectSize, count: descriptor.objectCount)] else {
                    // The pool was not allocated.
                    return nil;
                }
                
                // Get the specified buffer.
                return pool.getBuffer(Int(descriptor.identifier));
            }
    
            /**
             * Assigns data to a buffer and returns its index.
             *
             * @param descriptor The descriptor of the requested buffer.
             * @param data The data to copy in the buffer.
             * @return The MTLBuffer object.
             */
            public static func assignMutableBuffer(descriptor: cMB_RNDR_BUF_Descriptor, data: UnsafeRawPointer) -> Int {
                // Get the buffer manager.
                guard let manager = bufferManagers[descriptor.manager] else {
                    return 0;
                }
                
                // Get the buffer pool object.
                guard let pool = manager.bufferPools[Mobius_BufferPool.hash(size: descriptor.objectSize, count: descriptor.objectCount)] else {
                    // The pool was not allocated.
                    return 0;
                }
                
                // Get the specified buffer.
                return pool.getNextBuffer(data: data);
            }
    
            /**
             * Frees the buffer in the given pool.
             *
             * @param descriptor The descriptor to the object to free.
             */
            public static func freeBufferInPool(descriptor: cMB_RNDR_BUF_Descriptor) {
                // Get the buffer manager.
                guard let manager = bufferManagers[descriptor.manager] else {
                    return;
                }
                
                // Get the buffer pool object.
                guard let pool = manager.bufferPools[Mobius_BufferPool.hash(size: descriptor.objectSize, count: descriptor.objectCount)] else {
                    // The pool was not allocated.
                    return;
                }
                
                // Free the buffer.
                pool.freeBuffer();
            }
    
        // -- Internal Methods --
            /**
             * Class constructor.
             * Creates the buffer management and assigns the metal device.
             *
             * @param device The Metal device dedicated to this manager.
             */
            internal init(device: MTLDevice, identifier: CUnsignedInt) {
                // Store the device.
                mtl_Device = device;
                
                // Create the buffer list.
                immutableBuffers = [MTLBuffer]();
                bufferPools = [Int: Mobius_BufferPool]();
                
                // Store the buffer in the array.
                Mobius_BufferManager.bufferManagers[identifier] = self;
            }
    
            /**
             * Loads the buffer manager based on the given window index.
             *
             * @param index The index of the window that holds this buffer manager.
             * @return The BufferManager attached to the given window.
             */
            static internal func getBufferManager(index: CUnsignedInt) -> Mobius_BufferManager? {
                // If the shared manager is requested.
                if (index == cMB_RNDR_BUF_SharedManager) {
                    return makeShared(device: nil);
                } else {
                    // Get the pipeline.
                    guard let pipeline = Mobius_PipelineManager.queryPipeline(identifier: index) else {
                        return nil;
                    }
                    
                    // Return the pipeline's buffer manager.
                    guard let manager = bufferManagers[pipeline.bufferManager] else {
                        return nil;
                    }
                    
                    return manager;
                }
                
            }
    
            /**
             * Creates the shared manager.
             *
             * @param device The device dedicated to the metal buffer.
             */
            static public func makeShared(device: MTLDevice?) -> Mobius_BufferManager {
                // Create the shared manager if it does not exist.
                if (sharedManager == nil) {
                    sharedManager = Mobius_BufferManager(device: device!, identifier: cMB_RNDR_BUF_SharedManager);
                }
                
                // Return it,
                return sharedManager!;
            }
    // --- /Methods ---
    
    // ---  Attributes ---
        // -- Private Attributes --
            /** Metal device used to allocate the buffers. */
            private var mtl_Device : MTLDevice!
    
            /** List of all the immutable buffers. */
            private var immutableBuffers : [MTLBuffer]!
    
            /** List of all the buffer pools. */
            private var bufferPools : [Int: Mobius_BufferPool]!
    
            /** List of all the allocated buffers. */
            private static var bufferManagers = [CUnsignedInt: Mobius_BufferManager]();
    
            /** Shared buffer manager. */
            private static var sharedManager : Mobius_BufferManager? = nil;
    // --- /Attributes ---
}

/**
 * C API Bridge.
 * All these functions are described in the Buffer bridging header.
 */

@_cdecl("sMB_RNDR_BUF_allocate")
func sMB_RNDR_BUF_allocate(descriptor: cMB_RNDR_BUF_Descriptor, data: UnsafeRawPointer) -> cMB_RNDR_BUF_Descriptor {
    // Wrap the buffer manager's allocator.
    guard let descriptor = Mobius_BufferManager.getBufferManager(index: descriptor.manager)?.allocateBuffer(data: data, descriptor: descriptor) else {
        return cMB_RNDR_BUF_Descriptor(manager: 0, identifier: 0, objectCount: 0, objectSize: 0, type: cMB_RNDR_BUF_Invalid);
    }
    
    return descriptor;
}

@_cdecl("sMB_RNDR_BUF_assign")
func sMB_RNDR_BUF_assign(buffer: UnsafeMutablePointer<cMB_RNDR_BUF_Descriptor>, data: UnsafeRawPointer) {
    // Check if the buffer is mutable.
    if (buffer.pointee.type != cMB_RNDR_BUF_Mutable) { return; }
    
    // Get the buffer from the manager.
    let mtlBuffer = Mobius_BufferManager.assignMutableBuffer(descriptor: buffer.pointee, data: data);
    
    // Update the descriptor.
    buffer.pointee.identifier = CUnsignedInt(mtlBuffer);
}
