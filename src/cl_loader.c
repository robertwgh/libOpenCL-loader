/******************************************************************************
* Copyright (c) 2015-2016 Robert (Guohui) Wang
*
* Project:    A Cross-platform OpenCL Dynamic Library Loader
* File:       libopencl_loader.c
* E-mail:     robertwgh (at) gmail.com
* License:    Apache License Version 2.0.
*
* Revisions:  April  7 2015 -first version.
*             April 30 2016 -revised for release on github.
******************************************************************************/

#if defined(_WIN32) || defined(_WIN64)
    #define WIN32_LEAN_AND_MEAN
    #define WIN64_LEAN_AND_MEAN
    #define VC_EXTRALEAN
    #include <windows.h>
    #define strdup _strdup
    typedef HMODULE CL_LOADER_DYNLIB_HANDLE;
    #define CL_LOADER_DLOPEN    LoadLibraryA
    #define CL_LOADER_CLCLOSE   FreeLibrary
    #define CL_LOADER_DLSYM     GetProcAddress
#else
    #include <dlfcn.h>
    typedef void *  CL_LOADER_DYNLIB_HANDLE;
    #define CL_LOADER_DLOPEN(LIB)  dlopen(LIB, RTLD_LAZY)
    #define CL_LOADER_CLCLOSE      dlclose
    #define CL_LOADER_DLSYM        dlsym
#endif

#include "cl_loader.h"
#include <string.h>

static CL_LOADER_DYNLIB_HANDLE handle = NULL;
static char * opened_lib = "Unknown location";
//static char * failed_sym = "Unknown";

#define CL_LOADER_DLSYM_HELPER(fn) \
{\
    *(void **)(&fn) = CL_LOADER_DLSYM(handle, #fn);\
    if(fn == 0)\
    {\
        LOGD("Can't get mapping for method:%s in shared libraey:%s\n", #fn, opened_lib);\
        return CL_LOADER_FAILED_MAP_SYMBOL;\
    } \
}

int clLoaderInit()
{
    int i;
    
#if defined(_WIN32)
    const char * opencl_lib_path[]={
        "C:\\Windows\\System32\\OpenCL.dll",
        "OpenCL.dll"
    };
    const int num_opencl_lib_path = 2;
#elif defined(_WIN64)
    const char * opencl_lib_path[]={
        "C:\\Windows\\SysWOW64\\OpenCL.dll",
        "OpenCL.dll"
    };
    const int num_opencl_lib_path = 2;
    
#elif defined(__APPLE__)
    const char * opencl_lib_path[] = {
        "/Library/Frameworks/OpenCL.framework/OpenCL"
        };
    const int num_opencl_lib_path = 1;
        
#elif defined(__ANDROID_API__)
    const char * opencl_lib_path[]={
        // Typical libOpenCL location
        "/system/lib/libOpenCL.so",
        "/system/lib/egl/libOpenCL.so",
        "/system/vendor/lib/libOpenCL.so",
        "/system/vendor/lib/egl/libOpenCL.so",
        "/system/lib64/libOpenCL.so",
        "/system/lib64/egl/libOpenCL.so",
        "/system/vendor/lib64/libOpenCL.so",
        "/system/vendor/lib64/egl/libOpenCL.so",
        // Qualcomm Adreno A3xx
        "/system/lib/libllvm-a3xx.so",
        // ARM Mali series
        "/system/lib/libGLES_mali.so",
        "/system/lib/egl/libGLES_mali.so",
        "/system/vendor/lib/libGLES_mali.so",
        "/system/vendor/lib/egl/libGLES_mali.so",
        "/system/lib64/libGLES_mali.so",
        "/system/lib64/egl/libGLES_mali.so",
        "/system/vendor/lib64/libGLES_mali.so",
        "/system/vendor/lib64/egl/libGLES_mali.so",
        // Imagination PowerVR Series
        "/system/lib/libPVROCL.so",
        "/system/lib/egl/libPVROCL.so",
        "/system/vendor/lib/libPVROCL.so",
        "/system/vendor/lib/egl/libPVROCL.so",
        "/system/lib64/libPVROCL.so",
        "/system/lib64/egl/libPVROCL.so",
        "/system/vendor/lib64/libPVROCL.so",
        "/system/vendor/lib64/egl/libPVROCL.so",
        // Last try
        "libOpenCL.so",
        "libGLES_mali.so",
        "libPVROCL.so"
    };
    const int num_opencl_lib_path = 28;

#else
    const char * opencl_lib_path[] = {"libOpenCL.so"};
    const int num_opencl_lib_path = 1;
#endif

    for(i = 0; i < num_opencl_lib_path; i ++)
    {
        if ((handle = CL_LOADER_DLOPEN(opencl_lib_path[i])))
        {
            LOGD("Index %d, using the Shared library:%s\n", i, opencl_lib_path[i]);
            opened_lib = strdup(opencl_lib_path[i]);
            LOGD("Loaded OpenCL library:%s\n", opened_lib);
            break;
        }
    }

    if(handle == NULL)
        return CL_LOADER_FAILED_LOCATE_LIB_OPENCL;
        
    // Register the cleanup function to atexit.
    if (atexit(clLoaderExit))
    {
        CL_LOADER_CLCLOSE(handle);
        handle = NULL;
        return CL_LOADER_FAILED_REG_ATEXIT;
    }

    CL_LOADER_DLSYM_HELPER(clGetPlatformIDs);
    CL_LOADER_DLSYM_HELPER(clGetPlatformInfo);
    CL_LOADER_DLSYM_HELPER(clGetDeviceIDs);
    CL_LOADER_DLSYM_HELPER(clGetDeviceInfo);
    CL_LOADER_DLSYM_HELPER(clCreateContext);
    CL_LOADER_DLSYM_HELPER(clCreateContextFromType);
    CL_LOADER_DLSYM_HELPER(clRetainContext);
    CL_LOADER_DLSYM_HELPER(clReleaseContext);
    CL_LOADER_DLSYM_HELPER(clGetContextInfo);
    CL_LOADER_DLSYM_HELPER(clCreateCommandQueue);
    CL_LOADER_DLSYM_HELPER(clRetainCommandQueue);
    CL_LOADER_DLSYM_HELPER(clReleaseCommandQueue);
    CL_LOADER_DLSYM_HELPER(clGetCommandQueueInfo);
    CL_LOADER_DLSYM_HELPER(clCreateBuffer);
    CL_LOADER_DLSYM_HELPER(clCreateSubBuffer);
    CL_LOADER_DLSYM_HELPER(clRetainMemObject);
    CL_LOADER_DLSYM_HELPER(clReleaseMemObject);
    CL_LOADER_DLSYM_HELPER(clGetSupportedImageFormats);
    CL_LOADER_DLSYM_HELPER(clGetMemObjectInfo);
    CL_LOADER_DLSYM_HELPER(clGetImageInfo);
    CL_LOADER_DLSYM_HELPER(clSetMemObjectDestructorCallback);
    CL_LOADER_DLSYM_HELPER(clCreateSampler);
    CL_LOADER_DLSYM_HELPER(clRetainSampler);
    CL_LOADER_DLSYM_HELPER(clReleaseSampler);
    CL_LOADER_DLSYM_HELPER(clGetSamplerInfo);
    CL_LOADER_DLSYM_HELPER(clCreateProgramWithSource);
    CL_LOADER_DLSYM_HELPER(clCreateProgramWithBinary);
    CL_LOADER_DLSYM_HELPER(clRetainProgram);
    CL_LOADER_DLSYM_HELPER(clReleaseProgram);
    CL_LOADER_DLSYM_HELPER(clBuildProgram);
    CL_LOADER_DLSYM_HELPER(clGetProgramInfo);
    CL_LOADER_DLSYM_HELPER(clGetProgramBuildInfo);
    CL_LOADER_DLSYM_HELPER(clCreateKernel);
    CL_LOADER_DLSYM_HELPER(clCreateKernelsInProgram);
    CL_LOADER_DLSYM_HELPER(clRetainKernel);
    CL_LOADER_DLSYM_HELPER(clReleaseKernel);
    CL_LOADER_DLSYM_HELPER(clSetKernelArg);
    CL_LOADER_DLSYM_HELPER(clGetKernelInfo);
    CL_LOADER_DLSYM_HELPER(clGetKernelWorkGroupInfo);
    CL_LOADER_DLSYM_HELPER(clWaitForEvents);
    CL_LOADER_DLSYM_HELPER(clGetEventInfo);
    CL_LOADER_DLSYM_HELPER(clCreateUserEvent);
    CL_LOADER_DLSYM_HELPER(clRetainEvent);
    CL_LOADER_DLSYM_HELPER(clReleaseEvent);
    CL_LOADER_DLSYM_HELPER(clSetUserEventStatus);
    CL_LOADER_DLSYM_HELPER(clSetEventCallback);
    CL_LOADER_DLSYM_HELPER(clGetEventProfilingInfo);
    CL_LOADER_DLSYM_HELPER(clFlush);
    CL_LOADER_DLSYM_HELPER(clFinish);
    CL_LOADER_DLSYM_HELPER(clEnqueueReadBuffer);
    CL_LOADER_DLSYM_HELPER(clEnqueueReadBufferRect);
    CL_LOADER_DLSYM_HELPER(clEnqueueWriteBuffer);
    CL_LOADER_DLSYM_HELPER(clEnqueueWriteBufferRect);
    CL_LOADER_DLSYM_HELPER(clEnqueueCopyBuffer);
    CL_LOADER_DLSYM_HELPER(clEnqueueCopyBufferRect);
    CL_LOADER_DLSYM_HELPER(clEnqueueReadImage);
    CL_LOADER_DLSYM_HELPER(clEnqueueWriteImage);
    CL_LOADER_DLSYM_HELPER(clEnqueueCopyImage);
    CL_LOADER_DLSYM_HELPER(clEnqueueCopyImageToBuffer);
    CL_LOADER_DLSYM_HELPER(clEnqueueCopyBufferToImage);
    CL_LOADER_DLSYM_HELPER(clEnqueueUnmapMemObject);
    CL_LOADER_DLSYM_HELPER(clEnqueueNDRangeKernel);
    CL_LOADER_DLSYM_HELPER(clEnqueueTask);
    CL_LOADER_DLSYM_HELPER(clEnqueueNativeKernel);

#ifdef CL_USE_DEPRECATED_OPENCL_1_0_APIS
    CL_LOADER_DLSYM_HELPER(clSetCommandQueueProperty);
#endif

#ifdef CL_USE_DEPRECATED_OPENCL_1_1_APIS
    
    CL_LOADER_DLSYM_HELPER(clCreateImage2D);
    CL_LOADER_DLSYM_HELPER(clCreateImage3D);
    CL_LOADER_DLSYM_HELPER(clEnqueueMarker);
    CL_LOADER_DLSYM_HELPER(clEnqueueWaitForEvents);
    CL_LOADER_DLSYM_HELPER(clEnqueueBarrier);
    CL_LOADER_DLSYM_HELPER(clUnloadCompiler);
#endif

    return CL_LOADER_SUCCESS;
}

void clLoaderExit()
{
    if(handle)
        CL_LOADER_CLCLOSE(handle);
}

const char * clLoaderGetLibPath()
{
    return opened_lib;
}
