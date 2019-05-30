/******************************************************************************
* Copyright (c) 2015-2018 Robert (Guohui) Wang
*
* Project:      A Cross-platform OpenCL Dynamic Library Loader
* File:         test_cl_h.cpp
* Description:  Test OpenCL program using cl.h
* E-mail:       robertwgh (at) gmail.com
* License:      Apache License Version 2.0.
*
* Revisions:    April 30 2016 -Initial version.
                December 2018 -Updated version.
******************************************************************************/

#define ENABLE_OPENCL 1

#include "opencl_loader.h"
#include <CL/cl.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
    cl_int err = OpenCLHelper::Loader::Init();
    if(err)
    {
        std::cout << "Failed to init CL loader, err code: " << err << std::endl;
        return -1;
    }

    cl_int error = 0;
    cl_platform_id platform_ids[10];
    cl_uint num_platforms;
    error = clGetPlatformIDs(10, platform_ids, &num_platforms);
    if (error != CL_SUCCESS) {
        std::cout << "something went wrong, errorcode " << error << std::endl;
        return -1;
    }
    std::cout << "num platforms: " << num_platforms << std::endl;

    return 0;
}

