# libopencl-loader
Cross-platform OpenCL Dynamic Library Loader

## Introduction
This library provides the capability to inquery the OpenCL availability and load all the required symbols for OpenCL at run time. 

CMake build scripts and Android build scripts are provided. Several sample codes are also provided. Please refer to the `test` code for the usage of the library.
- test/test_cl_h: test the usage of `#include <CL/cl.h>`.
- test/test_cl_hpp: test the usage of `#include <CL/cl.hpp>` (C++ bindings).
- test/clinfo: test code to print out all the platform and device information.

## Usage
It is pretty straighforward to use this library. First, include `#include "opencl_loader.h"` header before including `cl.h` or `cl.hpp` header. Then, in the code, first initialize OpenCL runtime by call a function and then start to use OpenCL as usual. 

```C++
#include "opencl_loader.h"
#define __CL_ENABLE_EXCEPTIONS
#include <CL/cl.hpp>
int
main(int argc, char** argv)
{
    // Check if OpenCL is available in this system.
    cl_int err = OpenCLHelper::Loader::Init();
    if(err)
    {
       std::cout << "Failed to init CL loader, err code: " << err << std::endl;
        return -1;
    }
    // From here, we start to use OpenCL APIs as usual.
    try { 
        // Get available platforms
        std::vector<cl::Platform> platforms;
        cl::Platform::get(&platforms);
        std::cout << "\nNumber of available platforms " << platforms.size() << std::endl;
        for (auto& plat : platforms) {
            // Select the default platform and create a context using this platform and the GPU
            cl_context_properties cps[3] = { 
                CL_CONTEXT_PLATFORM, 
                (cl_context_properties)(plat)(), 
                0 
            };
            cl::Context context( CL_DEVICE_TYPE_GPU, cps);
            // Get a list of devices on this platform
            std::vector<cl::Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();
            std::cout << "  Number of available devices for this platform " << devices.size() << std::endl;
        }
    } catch(cl::Error& error) {
       std::cout << error.what() << "(" << error.err() << ")" << std::endl;
    }

    return 0;
}
```


## Build
### MacOS X
```bash
cd projects/macos
./build.sh
# run the test
#../../bin/test_cl_h
#../../bin/test_cl_hpp
#../../bin/clinfo -v
./runtest.sh
```

### Android
Install ndk first, 
```bash
cd projects/android
ndk-build
# then use the following scripts to run the code on an Android phone. 
# please connect the Android phone to the computer using a USB cable first. 
./run.sh
```
