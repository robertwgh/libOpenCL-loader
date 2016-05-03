/******************************************************************************
* Copyright (c) 2015-2016 Robert (Guohui) Wang
*
* Project:    A Cross-platform OpenCL Dynamic Library Loader
* File:       testCLLoader.cpp
* E-mail:     robertwgh (at) gmail.com
* License:    Apache License Version 2.0.
*
* Revisions:  April 30 2016 -Initial version.
******************************************************************************/

#include "cl_loader.h"

//#define __NO_STD_VECTOR
#define __CL_ENABLE_EXCEPTIONS
// Note: if <CL/cl.h> is already included in libopencl_loader.h, therefore, 
// if we use cl.h, here we don't need to include any OpenCL header. Howerver, 
// if the cl.hpp header is used, we should include it after the 
// libopencl_loader.h.
 #if defined(__APPLE__) || defined(__MACOSX)
 #include <OpenCL/cl.hpp>
 #else
 #include <CL/cl.hpp>
 #endif

#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//using namespace cl;
 
int main() {
    
    int err = clLoaderInit();
    if(err)
    {
        cout << "Failed to init CL loader, err code: " << err << std::endl;
        return -1;
    }
    
    
    // Create the two input vectors
    const int LIST_SIZE = 1000;
    int * A = new int[LIST_SIZE]; 
    if(A == NULL) 
        return -1;
    int * B = new int[LIST_SIZE];
    if(B == NULL) 
    {
        delete [] A; 
        A = NULL;
        return -1;
    }
    
    for(int i = 0; i < LIST_SIZE; i++) {
        A[i] = i;
        B[i] = LIST_SIZE - i;
    }
 
   try { 
        // Get available platforms
        std::vector<cl::Platform> platforms;
        cl::Platform::get(&platforms);
 
        // Select the default platform and create a context using this platform and the GPU
        cl_context_properties cps[3] = { 
            CL_CONTEXT_PLATFORM, 
            (cl_context_properties)(platforms[0])(), 
            0 
        };
        cl::Context context( CL_DEVICE_TYPE_GPU, cps);
 
        // Get a list of devices on this platform
        std::vector<cl::Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();
 
        // Create a command queue and use the first device
        cl::CommandQueue queue = cl::CommandQueue(context, devices[0]);
 
        // Read source file
        cl::Program::Sources sources;
        std::string kernel_code = std::string("kernel void vector_add(global const int* a, global const int* b, global int* c){ \n")
            + "    uint global_id = get_global_id(0); \n"
            + "    c[global_id] = a[global_id] + b[global_id]; \n"
            "}";
        sources.push_back({kernel_code.c_str(), kernel_code.length()});
 
        // Make program of the source code in the context
        cl::Program program = cl::Program(context, sources);
 
        // Build program for these specific devices
        program.build(devices);
 
        // Make kernel
        cl::Kernel kernel(program, "vector_add");
 
        // Create memory buffers
        cl::Buffer bufferA = cl::Buffer(context, CL_MEM_READ_ONLY, LIST_SIZE * sizeof(int));
        cl::Buffer bufferB = cl::Buffer(context, CL_MEM_READ_ONLY, LIST_SIZE * sizeof(int));
        cl::Buffer bufferC = cl::Buffer(context, CL_MEM_WRITE_ONLY, LIST_SIZE * sizeof(int));
 
        // Copy lists A and B to the memory buffers
        queue.enqueueWriteBuffer(bufferA, CL_TRUE, 0, LIST_SIZE * sizeof(int), A);
        queue.enqueueWriteBuffer(bufferB, CL_TRUE, 0, LIST_SIZE * sizeof(int), B);
 
        // Set arguments to kernel
        kernel.setArg(0, bufferA);
        kernel.setArg(1, bufferB);
        kernel.setArg(2, bufferC);
 
        // Run the kernel on specific ND range
        cl::NDRange global(LIST_SIZE);
        cl::NDRange local(1);
        queue.enqueueNDRangeKernel(kernel, cl::NullRange, global, local);
 
        // Read buffer C into a local list
        int *C = new int[LIST_SIZE];
        if(C == NULL)
        {
            delete [] A;
            delete [] B;
            return -1;
        }
        queue.enqueueReadBuffer(bufferC, CL_TRUE, 0, LIST_SIZE * sizeof(int), C);
 
        bool bSuccess = true;
        for(int i = 0; i < 10; i++)
        {
            if(C[i] != A[i] + B[i])
            {
                bSuccess = false;
                break;
            };
        }
        std::cout << "Test " << (bSuccess ? "passed." : "failed.") << std::endl; 
        
    }catch(cl::Error error) {
       std::cout << error.what() << "(" << error.err() << ")" << std::endl;
    }
    
    delete [] A;
    delete [] B;
    return CL_SUCCESS;
}
