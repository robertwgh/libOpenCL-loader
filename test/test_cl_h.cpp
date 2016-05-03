/******************************************************************************
* Copyright (c) 2015-2016 Robert (Guohui) Wang
*
* Project:      A Cross-platform OpenCL Dynamic Library Loader
* File:         test_cl_h.cpp
* Description:  Test OpenCL program using cl.h
* E-mail:       robertwgh (at) gmail.com
* License:      Apache License Version 2.0.
*
* Revisions:    April 30 2016 -Initial version.
******************************************************************************/

#include "cl_loader.h"
 #if defined(__APPLE__) || defined(__MACOSX)
 #include <OpenCL/cl.h>
 #else
 #include <CL/cl.h>
 #endif

#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    int err = clLoaderInit();
    if(err)
    {
        cout << "Failed to init CL loader, err code: " << err << std::endl;
        return -1;
    }

    cl_int error = 0;
    cl_platform_id platform_ids[10];
    cl_uint num_platforms;
    error = clGetPlatformIDs(10, platform_ids, &num_platforms);
    if (error != CL_SUCCESS) {
        cout << "something went wrong, errorcode " << error << endl;
        return -1;
    }
    cout << "num platforms: " << num_platforms << endl;

    return 0;
}

