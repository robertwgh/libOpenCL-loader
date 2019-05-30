/* ============================================================

Copyright (c) 2010 Advanced Micro Devices, Inc.  All rights reserved.

Redistribution and use of this material is permitted under the following
conditions:

Redistributions must retain the above copyright notice and all terms of this
license.

In no event shall anyone redistributing or accessing or using this material
commence or participate in any arbitration or legal action relating to this
material against Advanced Micro Devices, Inc. or any copyright holders or
contributors. The foregoing shall survive any expiration or termination of
this license or any agreement or access or use related to this material.

ANY BREACH OF ANY TERM OF THIS LICENSE SHALL RESULT IN THE IMMEDIATE REVOCATION
OF ALL RIGHTS TO REDISTRIBUTE, ACCESS OR USE THIS MATERIAL.

THIS MATERIAL IS PROVIDED BY ADVANCED MICRO DEVICES, INC. AND ANY COPYRIGHT
HOLDERS AND CONTRIBUTORS "AS IS" IN ITS CURRENT CONDITION AND WITHOUT ANY
REPRESENTATIONS, GUARANTEE, OR WARRANTY OF ANY KIND OR IN ANY WAY RELATED TO
SUPPORT, INDEMNITY, ERROR FREE OR UNINTERRUPTED OPERA TION, OR THAT IT IS FREE
FROM DEFECTS OR VIRUSES.  ALL OBLIGATIONS ARE HEREBY DISCLAIMED - WHETHER
EXPRESS, IMPLIED, OR STATUTORY - INCLUDING, BUT NOT LIMITED TO, ANY IMPLIED
WARRANTIES OF TITLE, MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE,
ACCURACY, COMPLETENESS, OPERABILITY, QUALITY OF SERVICE, OR NON-INFRINGEMENT.
IN NO EVENT SHALL ADVANCED MICRO DEVICES, INC. OR ANY COPYRIGHT HOLDERS OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, PUNITIVE,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, REVENUE, DATA, OR PROFITS; OR
BUSINESS INTERRUPTION) HOWEVER CAUSED OR BASED ON ANY THEORY OF LIABILITY
ARISING IN ANY WAY RELATED TO THIS MATERIAL, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE. THE ENTIRE AND AGGREGATE LIABILITY OF ADVANCED MICRO DEVICES,
INC. AND ANY COPYRIGHT HOLDERS AND CONTRIBUTORS SHALL NOT EXCEED TEN DOLLARS
(US $10.00). ANYONE REDISTRIBUTING OR ACCESSING OR USING THIS MATERIAL ACCEPTS
THIS ALLOCATION OF RISK AND AGREES TO RELEASE ADVANCED MICRO DEVICES, INC. AND
ANY COPYRIGHT HOLDERS AND CONTRIBUTORS FROM ANY AND ALL LIABILITIES,
OBLIGATIONS, CLAIMS, OR DEMANDS IN EXCESS OF TEN DOLLARS (US $10.00). THE
FOREGOING ARE ESSENTIAL TERMS OF THIS LICENSE AND, IF ANY OF THESE TERMS ARE
CONSTRUED AS UNENFORCEABLE, FAIL IN ESSENTIAL PURPOSE, OR BECOME VOID OR
DETRIMENTAL TO ADVANCED MICRO DEVICES, INC. OR ANY COPYRIGHT HOLDERS OR
CONTRIBUTORS FOR ANY REASON, THEN ALL RIGHTS TO REDISTRIBUTE, ACCESS OR USE
THIS MATERIAL SHALL TERMINATE IMMEDIATELY. MOREOVER, THE FOREGOING SHALL
SURVIVE ANY EXPIRATION OR TERMINATION OF THIS LICENSE OR ANY AGREEMENT OR
ACCESS OR USE RELATED TO THIS MATERIAL.

NOTICE IS HEREBY PROVIDED, AND BY REDISTRIBUTING OR ACCESSING OR USING THIS
MATERIAL SUCH NOTICE IS ACKNOWLEDGED, THAT THIS MATERIAL MAY BE SUBJECT TO
RESTRICTIONS UNDER THE LAWS AND REGULATIONS OF THE UNITED STATES OR OTHER
COUNTRIES, WHICH INCLUDE BUT ARE NOT LIMITED TO, U.S. EXPORT CONTROL LAWS SUCH
AS THE EXPORT ADMINISTRATION REGULATIONS AND NATIONAL SECURITY CONTROLS AS
DEFINED THEREUNDER, AS WELL AS STATE DEPARTMENT CONTROLS UNDER THE U.S.
MUNITIONS LIST. THIS MATERIAL MAY NOT BE USED, RELEASED, TRANSFERRED, IMPORTED,
EXPORTED AND/OR RE-EXPORTED IN ANY MANNER PROHIBITED UNDER ANY APPLICABLE LAWS,
INCLUDING U.S. EXPORT CONTROL LAWS REGARDING SPECIFICALLY DESIGNATED PERSONS,
COUNTRIES AND NATIONALS OF COUNTRIES SUBJECT TO NATIONAL SECURITY CONTROLS.
MOREOVER, THE FOREGOING SHALL SURVIVE ANY EXPIRATION OR TERMINATION OF ANY
LICENSE OR AGREEMENT OR ACCESS OR USE RELATED TO THIS MATERIAL.

NOTICE REGARDING THE U.S. GOVERNMENT AND DOD AGENCIES: This material is
provided with "RESTRICTED RIGHTS" and/or "LIMITED RIGHTS" as applicable to
computer software and technical data, respectively. Use, duplication,
distribution or disclosure by the U.S. Government and/or DOD agencies is
subject to the full extent of restrictions in all applicable regulations,
including those found at FAR52.227 and DFARS252.227 et seq. and any successor
regulations thereof. Use of this material by the U.S. Government and/or DOD
agencies is acknowledgment of the proprietary rights of any copyright holders
and contributors, including those of Advanced Micro Devices, Inc., as well as
the provisions of FAR52.227-14 through 23 regarding privately developed and/or
commercial computer software.

This license forms the entire agreement regarding the subject matter hereof and
supersedes all proposals and prior discussions and writings between the parties
with respect thereto. This license does not affect any ownership, rights, title,
or interest in, or relating to, this material. No terms of this license can be
modified or waived, and no breach of this license can be excused, unless done
so in a writing signed by all affected parties. Each term of this license is
separately enforceable. If any term of this license is determined to be or
becomes unenforceable or illegal, such term shall be reformed to the minimum
extent necessary in order for this license to remain in effect in accordance
with its terms as modified by such reformation. This license shall be governed
by and construed in accordance with the laws of the State of Texas without
regard to rules on conflicts of law of any state or jurisdiction or the United
Nations Convention on the International Sale of Goods. All disputes arising out
of this license shall be subject to the jurisdiction of the federal and state
courts in Austin, Texas, and all defenses are hereby waived concerning personal
jurisdiction and venue of these courts.

============================================================ */

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include <string>
#if !defined(_WIN32)
#include <errno.h>
#endif

#ifdef _MSC_VER
#pragma warning(disable : 4290)
#endif

#include "opencl_loader.h"

#if defined(HAVE_CL2_HPP)
#define CL_HPP_ENABLE_EXCEPTIONS
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#define CL_HPP_TARGET_OPENCL_VERSION 200
#define CL_HPP_ENABLE_PROGRAM_CONSTRUCTION_FROM_ARRAY_COMPATIBILITY
#include <CL/cl2.hpp>
#else  // !HAVE_CL2_HPP
#define __CL_ENABLE_EXCEPTIONS
#define __MAX_DEFAULT_VECTOR_SIZE 50
#define CL_USE_DEPRECATED_OPENCL_1_1_APIS
#define CL_USE_DEPRECATED_OPENCL_2_0_APIS
#include <CL/cl.hpp>
#endif  // !HAVE_CL2_HPP

bool verbose = false;

/// Returns EXIT_SUCCESS on success, EXIT_FAILURE on failure.
int main(int argc, char** argv)
{
    // Check if OpenCL is available in this system.
    cl_int err = OpenCLHelper::Loader::Init();
    if (err) {
        std::cout << "Failed to init CL loader, err code: " << err << std::endl;
        return -1;
    }

    // parse input
    for (int i = 1; i < argc; i++) {
        if ((strcmp(argv[i], "-v") == 0) ||
            (strcmp(argv[i], "--verbose") == 0)) {
            verbose = true;
        } else if ((strcmp(argv[i], "-h") == 0) ||
                   (strcmp(argv[i], "--help") == 0)) {
            std::cout << "Usage is: " << argv[0] << " [-v|--verbose]"
                      << std::endl;
            return EXIT_FAILURE;
        }
    }

    // Platform info
    std::vector<cl::Platform> platforms;

    try {
        err = cl::Platform::get(&platforms);

        // Iteratate over platforms
        std::cout << "Number of platforms:\t\t\t\t " << platforms.size()
                  << std::endl;
        for (std::vector<cl::Platform>::iterator i = platforms.begin();
             i != platforms.end();
             ++i) {
            const cl::Platform& platform = *i;

            std::cout << "  Platform Profile:\t\t\t\t "
                      << platform.getInfo<CL_PLATFORM_PROFILE>().c_str()
                      << std::endl;
            std::cout << "  Platform Version:\t\t\t\t "
                      << platform.getInfo<CL_PLATFORM_VERSION>().c_str()
                      << std::endl;
            std::cout << "  Platform Name:\t\t\t\t "
                      << platform.getInfo<CL_PLATFORM_NAME>().c_str()
                      << std::endl;
            std::cout << "  Platform Vendor:\t\t\t\t "
                      << platform.getInfo<CL_PLATFORM_VENDOR>().c_str()
                      << std::endl;
            if (platform.getInfo<CL_PLATFORM_EXTENSIONS>().size() > 0) {
                std::cout << "  Platform Extensions:\t\t\t\t "
                          << platform.getInfo<CL_PLATFORM_EXTENSIONS>().c_str()
                          << std::endl;
            }
        }

        std::cout << std::endl << std::endl;
        // Now Iteratate over each platform and its devices
        for (std::vector<cl::Platform>::iterator p = platforms.begin();
             p != platforms.end();
             ++p) {
            const cl::Platform& platform = *p;
            std::cout << "  Platform Name:\t\t\t\t "
                      << platform.getInfo<CL_PLATFORM_NAME>().c_str()
                      << std::endl;

            std::vector<cl::Device> devices;
            platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

            // Get OpenCL version
            std::string platformVersionStr =
                platform.getInfo<CL_PLATFORM_VERSION>();
            std::string openclVerstionStr(platformVersionStr.c_str());
            size_t vStart = openclVerstionStr.find(" ", 0);
            size_t vEnd = openclVerstionStr.find(" ", vStart + 1);
            std::string vStrVal =
                openclVerstionStr.substr(vStart + 1, vEnd - vStart - 1);

            std::cout << "Number of devices:\t\t\t\t " << devices.size()
                      << std::endl;
            for (std::vector<cl::Device>::iterator i = devices.begin();
                 i != devices.end();
                 ++i) {
                const cl::Device& device = *i;
                /* Get device name */
                std::string deviceName = device.getInfo<CL_DEVICE_NAME>();
                cl_device_type dtype = device.getInfo<CL_DEVICE_TYPE>();

                /* Get CAL driver version in int */
                std::string driverVersion = device.getInfo<CL_DRIVER_VERSION>();
                std::string calVersion(driverVersion.c_str());
                calVersion =
                    calVersion.substr(calVersion.find_last_of(".") + 1);
                int version = atoi(calVersion.c_str());

                std::cout << "  Device Type:\t\t\t\t\t ";
                switch (dtype) {
                    case CL_DEVICE_TYPE_ACCELERATOR:
                        std::cout << "CL_DEVICE_TYPE_ACCRLERATOR" << std::endl;
                        break;
                    case CL_DEVICE_TYPE_CPU:
                        std::cout << "CL_DEVICE_TYPE_CPU" << std::endl;
                        break;
                    case CL_DEVICE_TYPE_DEFAULT:
                        std::cout << "CL_DEVICE_TYPE_DEFAULT" << std::endl;
                        break;
                    case CL_DEVICE_TYPE_GPU:
                        std::cout << "CL_DEVICE_TYPE_GPU" << std::endl;
                        break;
                }

                std::cout << "  Vendor ID:\t\t\t\t\t " << std::hex
                          << device.getInfo<CL_DEVICE_VENDOR_ID>() << "h"
                          << std::dec << std::endl;

                std::cout << "  Max compute units:\t\t\t\t "
                          << device.getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>()
                          << std::endl;

                std::cout
                    << "  Max work items dimensions:\t\t\t "
                    << device.getInfo<CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS>()
                    << std::endl;

                std::vector< ::size_t> witems =
                    device.getInfo<CL_DEVICE_MAX_WORK_ITEM_SIZES>();
                for (unsigned int x = 0;
                     x < device.getInfo<CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS>();
                     x++) {
                    std::cout << "    Max work items[" << x << "]:\t\t\t\t "
                              << witems[x] << std::endl;
                }

                std::cout << "  Max work group size:\t\t\t\t "
                          << device.getInfo<CL_DEVICE_MAX_WORK_GROUP_SIZE>()
                          << std::endl;

                std::cout
                    << "  Preferred vector width char:\t\t\t "
                    << device.getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR>()
                    << std::endl;

                std::cout
                    << "  Preferred vector width short:\t\t\t "
                    << device.getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT>()
                    << std::endl;

                std::cout
                    << "  Preferred vector width int:\t\t\t "
                    << device.getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT>()
                    << std::endl;

                std::cout
                    << "  Preferred vector width long:\t\t\t "
                    << device.getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG>()
                    << std::endl;

                std::cout
                    << "  Preferred vector width float:\t\t\t "
                    << device.getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT>()
                    << std::endl;

                std::cout
                    << "  Preferred vector width double:\t\t "
                    << device.getInfo<CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE>()
                    << std::endl;

#ifdef CL_VERSION_1_1
                if (vStrVal.compare("1.0") > 0) {
                    std::cout
                        << "  Native vector width char:\t\t\t "
                        << device.getInfo<CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR>()
                        << std::endl;

                    std::cout
                        << "  Native vector width short:\t\t\t "
                        << device.getInfo<CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT>()
                        << std::endl;

                    std::cout
                        << "  Native vector width int:\t\t\t "
                        << device.getInfo<CL_DEVICE_NATIVE_VECTOR_WIDTH_INT>()
                        << std::endl;

                    std::cout
                        << "  Native vector width long:\t\t\t "
                        << device.getInfo<CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG>()
                        << std::endl;

                    std::cout
                        << "  Native vector width float:\t\t\t "
                        << device.getInfo<CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT>()
                        << std::endl;

                    std::cout
                        << "  Native vector width double:\t\t\t "
                        << device
                               .getInfo<CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE>()
                        << std::endl;
                }
#endif  // CL_VERSION_1_1
                std::cout << "  Max clock frequency:\t\t\t\t "
                          << device.getInfo<CL_DEVICE_MAX_CLOCK_FREQUENCY>()
                          << "Mhz" << std::endl;

                std::cout << "  Address bits:\t\t\t\t\t "
                          << device.getInfo<CL_DEVICE_ADDRESS_BITS>()
                          << std::endl;

                std::cout << "  Max memory allocation:\t\t\t "
                          << device.getInfo<CL_DEVICE_MAX_MEM_ALLOC_SIZE>()
                          << std::endl;

                std::cout << "  Image support:\t\t\t\t "
                          << (device.getInfo<CL_DEVICE_IMAGE_SUPPORT>() ? "Yes"
                                                                        : "No")
                          << std::endl;

                if (device.getInfo<CL_DEVICE_IMAGE_SUPPORT>()) {
                    std::cout << "  Max number of images read arguments:\t\t "
                              << device.getInfo<CL_DEVICE_MAX_READ_IMAGE_ARGS>()
                              << std::endl;

                    std::cout
                        << "  Max number of images write arguments:\t\t "
                        << device.getInfo<CL_DEVICE_MAX_WRITE_IMAGE_ARGS>()
                        << std::endl;

                    std::cout << "  Max image 2D width:\t\t\t\t "
                              << device.getInfo<CL_DEVICE_IMAGE2D_MAX_WIDTH>()
                              << std::endl;

                    std::cout << "  Max image 2D height:\t\t\t\t "
                              << device.getInfo<CL_DEVICE_IMAGE2D_MAX_HEIGHT>()
                              << std::endl;

                    std::cout << "  Max image 3D width:\t\t\t\t "
                              << device.getInfo<CL_DEVICE_IMAGE3D_MAX_WIDTH>()
                              << std::endl;

                    std::cout << "  Max image 3D height:\t\t\t\t "
                              << device.getInfo<CL_DEVICE_IMAGE3D_MAX_HEIGHT>()
                              << std::endl;

                    std::cout << "  Max image 3D depth:\t\t\t\t "
                              << device.getInfo<CL_DEVICE_IMAGE3D_MAX_DEPTH>()
                              << std::endl;

                    std::cout << "  Max samplers within kernel:\t\t\t "
                              << device.getInfo<CL_DEVICE_MAX_SAMPLERS>()
                              << std::endl;

                    if (verbose) {
                        std::cout << "  Image formats supported:" << std::endl;
                        std::vector<cl::ImageFormat> formats;

                        cl_context_properties cps[3] = {
                            CL_CONTEXT_PLATFORM,
                            (cl_context_properties)(*p)(),
                            0};
                        std::vector<cl::Device> device;
                        device.push_back(*i);
                        cl::Context context(device, cps, NULL, NULL, &err);

                        std::map<int, std::string> channelOrder;
                        channelOrder[CL_R] = "CL_R";
                        channelOrder[CL_A] = "CL_A";
                        channelOrder[CL_RG] = "CL_RG";
                        channelOrder[CL_RA] = "CL_RA";
                        channelOrder[CL_RGB] = "CL_RGB";
                        channelOrder[CL_RGBA] = "CL_RGBA";
                        channelOrder[CL_BGRA] = "CL_BGRA";
                        channelOrder[CL_ARGB] = "CL_ARGB";
                        channelOrder[CL_INTENSITY] = "CL_INTENSITY";
                        channelOrder[CL_LUMINANCE] = "CL_LUMINANCE";
                        channelOrder[CL_Rx] = "CL_Rx";
                        channelOrder[CL_RGx] = "CL_RGx";
                        channelOrder[CL_RGBx] = "CL_RGBx";

                        std::map<int, std::pair<std::string, std::string> >
                            channelType;
                        channelType[CL_SNORM_INT8] =
                            std::make_pair("snorm", "int8");
                        channelType[CL_SNORM_INT16] =
                            std::make_pair("snorm", "int16");
                        channelType[CL_UNORM_INT8] =
                            std::make_pair("unorm", "int8");
                        channelType[CL_UNORM_INT16] =
                            std::make_pair("unorm", "int16");
                        channelType[CL_UNORM_SHORT_565] =
                            std::make_pair("unorm", "short_565");
                        channelType[CL_UNORM_SHORT_555] =
                            std::make_pair("unorm", "short_555");
                        channelType[CL_UNORM_INT_101010] =
                            std::make_pair("unorm", "int_101010");
                        channelType[CL_SIGNED_INT8] =
                            std::make_pair("signed", "int8");
                        channelType[CL_SIGNED_INT16] =
                            std::make_pair("signed", "int16");
                        channelType[CL_SIGNED_INT32] =
                            std::make_pair("signed", "int32");
                        channelType[CL_UNSIGNED_INT8] =
                            std::make_pair("unsigned", "int8");
                        channelType[CL_UNSIGNED_INT16] =
                            std::make_pair("unsigned", "int16");
                        channelType[CL_UNSIGNED_INT32] =
                            std::make_pair("unsigned", "int32");
                        channelType[CL_HALF_FLOAT] =
                            std::make_pair("half_float", "");
                        channelType[CL_FLOAT] = std::make_pair("float", "");

                        std::vector<std::pair<int, std::string> >
                            imageDimensions;
                        imageDimensions.push_back(std::make_pair(
                            CL_MEM_OBJECT_IMAGE2D, std::string("2D ")));
                        imageDimensions.push_back(std::make_pair(
                            CL_MEM_OBJECT_IMAGE3D, std::string("3D ")));
                        for (std::vector<std::pair<int, std::string> >::iterator
                                 id = imageDimensions.begin();
                             id != imageDimensions.end();
                             id++) {
                            struct imageAccessStruct
                            {
                                std::string name;
                                int access;
                                std::vector<cl::ImageFormat> formats;
                            } imageAccess[] = {
                                {std::string("Read-Write/Read-Only/Write-Only"),
                                 CL_MEM_READ_WRITE,
                                 std::vector<cl::ImageFormat>()},
                                {std::string("Read-Only"),
                                 CL_MEM_READ_ONLY,
                                 std::vector<cl::ImageFormat>()},
                                {std::string("Write-Only"),
                                 CL_MEM_WRITE_ONLY,
                                 std::vector<cl::ImageFormat>()}};

                            for (size_t ia = 0;
                                 ia < sizeof(imageAccess) /
                                          sizeof(imageAccessStruct);
                                 ia++) {
                                context.getSupportedImageFormats(
                                    imageAccess[ia].access,
                                    (*id).first,
                                    &(imageAccess[ia].formats));
                                bool printTopHeader = true;
                                for (std::map<int, std::string>::iterator o =
                                         channelOrder.begin();
                                     o != channelOrder.end();
                                     o++) {
                                    bool printHeader = true;

                                    for (std::vector<
                                             cl::ImageFormat>::iterator it =
                                             imageAccess[ia].formats.begin();
                                         it != imageAccess[ia].formats.end();
                                         ++it) {
                                        if ((*o).first ==
                                            (int) (*it).image_channel_order) {
                                            bool printedAlready = false;
                                            // see if this was already print in
                                            // RW/RO/WO
                                            if (ia != 0) {
                                                for (std::vector<
                                                         cl::ImageFormat>::
                                                         iterator searchIt =
                                                             imageAccess[0]
                                                                 .formats
                                                                 .begin();
                                                     searchIt !=
                                                     imageAccess[0]
                                                         .formats.end();
                                                     searchIt++) {
                                                    if (((*searchIt)
                                                             .image_channel_data_type ==
                                                         (*it)
                                                             .image_channel_data_type) &&
                                                        ((*searchIt)
                                                             .image_channel_order ==
                                                         (*it)
                                                             .image_channel_order)) {
                                                        printedAlready = true;
                                                        break;
                                                    }
                                                }
                                            }
                                            if (printedAlready) {
                                                continue;
                                            }
                                            if (printTopHeader) {
                                                std::cout
                                                    << "   " << (*id).second
                                                    << imageAccess[ia].name
                                                    << std::endl;
                                                printTopHeader = false;
                                            }
                                            if (printHeader) {
                                                std::cout << "    "
                                                          << (*o).second
                                                          << ": ";
                                                printHeader = false;
                                            }
                                            std::cout
                                                << channelType
                                                       [(*it)
                                                            .image_channel_data_type]
                                                           .first;
                                            if (channelType
                                                    [(*it)
                                                         .image_channel_data_type]
                                                        .second != "") {
                                                std::cout
                                                    << "-"
                                                    << channelType
                                                           [(*it)
                                                                .image_channel_data_type]
                                                               .second;
                                            }
                                            if (it !=
                                                (imageAccess[ia].formats.end() -
                                                 1)) {
                                                std::cout << " ";
                                            }
                                        }
                                    }
                                    if (printHeader == false) {
                                        std::cout << std::endl;
                                    }
                                }
                            }
                        }
                    }
                }

                std::cout << "  Max size of kernel argument:\t\t\t "
                          << device.getInfo<CL_DEVICE_MAX_PARAMETER_SIZE>()
                          << std::endl;

                std::cout << "  Alignment (bits) of base address:\t\t "
                          << device.getInfo<CL_DEVICE_MEM_BASE_ADDR_ALIGN>()
                          << std::endl;

                std::cout
                    << "  Minimum alignment (bytes) for any datatype:\t "
                    << device.getInfo<CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE>()
                    << std::endl;

                std::cout << "  Single precision floating point capability"
                          << std::endl;
                std::cout << "    Denorms:\t\t\t\t\t "
                          << (device.getInfo<CL_DEVICE_SINGLE_FP_CONFIG>() &
                                      CL_FP_DENORM
                                  ? "Yes"
                                  : "No")
                          << std::endl;
                std::cout << "    Quiet NaNs:\t\t\t\t\t "
                          << (device.getInfo<CL_DEVICE_SINGLE_FP_CONFIG>() &
                                      CL_FP_INF_NAN
                                  ? "Yes"
                                  : "No")
                          << std::endl;
                std::cout << "    Round to nearest even:\t\t\t "
                          << (device.getInfo<CL_DEVICE_SINGLE_FP_CONFIG>() &
                                      CL_FP_ROUND_TO_NEAREST
                                  ? "Yes"
                                  : "No")
                          << std::endl;
                std::cout << "    Round to zero:\t\t\t\t "
                          << (device.getInfo<CL_DEVICE_SINGLE_FP_CONFIG>() &
                                      CL_FP_ROUND_TO_ZERO
                                  ? "Yes"
                                  : "No")
                          << std::endl;
                std::cout << "    Round to +ve and infinity:\t\t\t "
                          << (device.getInfo<CL_DEVICE_SINGLE_FP_CONFIG>() &
                                      CL_FP_ROUND_TO_INF
                                  ? "Yes"
                                  : "No")
                          << std::endl;
                std::cout << "    IEEE754-2008 fused multiply-add:\t\t "
                          << (device.getInfo<CL_DEVICE_SINGLE_FP_CONFIG>() &
                                      CL_FP_FMA
                                  ? "Yes"
                                  : "No")
                          << std::endl;

                std::cout << "  Cache type:\t\t\t\t\t ";
                switch (device.getInfo<CL_DEVICE_GLOBAL_MEM_CACHE_TYPE>()) {
                    case CL_NONE:
                        std::cout << "None" << std::endl;
                        break;
                    case CL_READ_ONLY_CACHE:
                        std::cout << "Read only" << std::endl;
                        break;
                    case CL_READ_WRITE_CACHE:
                        std::cout << "Read/Write" << std::endl;
                        break;
                }

                std::cout
                    << "  Cache line size:\t\t\t\t "
                    << device.getInfo<CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE>()
                    << std::endl;

                std::cout << "  Cache size:\t\t\t\t\t "
                          << device.getInfo<CL_DEVICE_GLOBAL_MEM_CACHE_SIZE>()
                          << std::endl;

                std::cout << "  Global memory size:\t\t\t\t "
                          << device.getInfo<CL_DEVICE_GLOBAL_MEM_SIZE>()
                          << std::endl;

                std::cout
                    << "  Constant buffer size:\t\t\t\t "
                    << device.getInfo<CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE>()
                    << std::endl;

                std::cout << "  Max number of constant args:\t\t\t "
                          << device.getInfo<CL_DEVICE_MAX_CONSTANT_ARGS>()
                          << std::endl;

                std::cout << "  Local memory type:\t\t\t\t ";
                switch (device.getInfo<CL_DEVICE_LOCAL_MEM_TYPE>()) {
                    case CL_LOCAL:
                        std::cout << "Scratchpad" << std::endl;
                        break;
                    case CL_GLOBAL:
                        std::cout << "Global" << std::endl;
                        break;
                }

                std::cout << "  Local memory size:\t\t\t\t "
                          << device.getInfo<CL_DEVICE_LOCAL_MEM_SIZE>()
                          << std::endl;

#if defined(CL_VERSION_2_0)
                if (vStrVal.compare("2") > 0) {
                    std::cout << "  Max pipe arguments:\t\t\t\t "
                              << device.getInfo<CL_DEVICE_MAX_PIPE_ARGS>()
                              << std::endl;

                    std::cout << "  Max pipe active reservations:\t\t\t "
                              << device.getInfo<
                                     CL_DEVICE_PIPE_MAX_ACTIVE_RESERVATIONS>()
                              << std::endl;

                    std::cout
                        << "  Max pipe packet size:\t\t\t\t "
                        << device.getInfo<CL_DEVICE_PIPE_MAX_PACKET_SIZE>()
                        << std::endl;

                    std::cout
                        << "  Max global variable size:\t\t\t "
                        << device.getInfo<CL_DEVICE_MAX_GLOBAL_VARIABLE_SIZE>()
                        << std::endl;

                    std::cout
                        << "  Max global variable preferred total size:\t "
                        << device.getInfo<
                               CL_DEVICE_GLOBAL_VARIABLE_PREFERRED_TOTAL_SIZE>()
                        << std::endl;

                    std::cout
                        << "  Max read/write image args:\t\t\t "
                        << device.getInfo<CL_DEVICE_MAX_READ_WRITE_IMAGE_ARGS>()
                        << std::endl;

                    std::cout
                        << "  Max on device events:\t\t\t\t "
                        << device.getInfo<CL_DEVICE_MAX_ON_DEVICE_EVENTS>()
                        << std::endl;

                    std::cout
                        << "  Queue on device max size:\t\t\t "
                        << device.getInfo<CL_DEVICE_QUEUE_ON_DEVICE_MAX_SIZE>()
                        << std::endl;

                    std::cout
                        << "  Max on device queues:\t\t\t\t "
                        << device.getInfo<CL_DEVICE_MAX_ON_DEVICE_QUEUES>()
                        << std::endl;

                    std::cout << "  Queue on device preferred size:\t\t "
                              << device.getInfo<
                                     CL_DEVICE_QUEUE_ON_DEVICE_PREFERRED_SIZE>()
                              << std::endl;

                    std::cout << "  SVM capabilities:\t\t\t\t " << std::endl;
                    std::cout << "    Coarse grain buffer:\t\t\t "
                              << (device.getInfo<CL_DEVICE_SVM_CAPABILITIES>() &
                                          CL_DEVICE_SVM_COARSE_GRAIN_BUFFER
                                      ? "Yes"
                                      : "No")
                              << std::endl;
                    std::cout << "    Fine grain buffer:\t\t\t\t "
                              << (device.getInfo<CL_DEVICE_SVM_CAPABILITIES>() &
                                          CL_DEVICE_SVM_FINE_GRAIN_BUFFER
                                      ? "Yes"
                                      : "No")
                              << std::endl;
                    std::cout << "    Fine grain system:\t\t\t\t "
                              << (device.getInfo<CL_DEVICE_SVM_CAPABILITIES>() &
                                          CL_DEVICE_SVM_FINE_GRAIN_SYSTEM
                                      ? "Yes"
                                      : "No")
                              << std::endl;
                    std::cout << "    Atomics:\t\t\t\t\t "
                              << (device.getInfo<CL_DEVICE_SVM_CAPABILITIES>() &
                                          CL_DEVICE_SVM_ATOMICS
                                      ? "Yes"
                                      : "No")
                              << std::endl;

                    std::cout
                        << "  Preferred platform atomic alignment:\t\t "
                        << device.getInfo<
                               CL_DEVICE_PREFERRED_PLATFORM_ATOMIC_ALIGNMENT>()
                        << std::endl;

                    std::cout
                        << "  Preferred global atomic alignment:\t\t "
                        << device.getInfo<
                               CL_DEVICE_PREFERRED_GLOBAL_ATOMIC_ALIGNMENT>()
                        << std::endl;

                    std::cout
                        << "  Preferred local atomic alignment:\t\t "
                        << device.getInfo<
                               CL_DEVICE_PREFERRED_LOCAL_ATOMIC_ALIGNMENT>()
                        << std::endl;
                }
#endif  // CL_VERSION_2_0

                std::cout
                    << "  Error correction support:\t\t\t "
                    << device.getInfo<CL_DEVICE_ERROR_CORRECTION_SUPPORT>()
                    << std::endl;
#ifdef CL_VERSION_1_1
                if (vStrVal.compare("1.0") > 0) {
                    std::cout << "  Unified memory for Host and Device:\t\t "
                              << device.getInfo<CL_DEVICE_HOST_UNIFIED_MEMORY>()
                              << std::endl;
                }
#endif  // CL_VERSION_1_1
                std::cout
                    << "  Profiling timer resolution:\t\t\t "
                    << device.getInfo<CL_DEVICE_PROFILING_TIMER_RESOLUTION>()
                    << std::endl;

                std::cout << "  Device endianess:\t\t\t\t "
                          << (device.getInfo<CL_DEVICE_ENDIAN_LITTLE>()
                                  ? "Little"
                                  : "Big")
                          << std::endl;

                std::cout << "  Available:\t\t\t\t\t "
                          << (device.getInfo<CL_DEVICE_AVAILABLE>() ? "Yes"
                                                                    : "No")
                          << std::endl;

                std::cout << "  Compiler available:\t\t\t\t "
                          << (device.getInfo<CL_DEVICE_COMPILER_AVAILABLE>()
                                  ? "Yes"
                                  : "No")
                          << std::endl;

                std::cout << "  Execution capabilities:\t\t\t\t " << std::endl;
                std::cout
                    << "    Execute OpenCL kernels:\t\t\t "
                    << (device.getInfo<CL_DEVICE_EXECUTION_CAPABILITIES>() &
                                CL_EXEC_KERNEL
                            ? "Yes"
                            : "No")
                    << std::endl;
                std::cout
                    << "    Execute native function:\t\t\t "
                    << (device.getInfo<CL_DEVICE_EXECUTION_CAPABILITIES>() &
                                CL_EXEC_NATIVE_KERNEL
                            ? "Yes"
                            : "No")
                    << std::endl;

#ifdef CL_VERSION_2_0
                if (vStrVal.compare("2") > 0) {
                    std::cout << "  Queue on Host properties:\t\t\t\t "
                              << std::endl;
                    std::cout
                        << "    Out-of-Order:\t\t\t\t "
                        << (device.getInfo<
                                    CL_DEVICE_QUEUE_ON_HOST_PROPERTIES>() &
                                    CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE
                                ? "Yes"
                                : "No")
                        << std::endl;
                    std::cout
                        << "    Profiling :\t\t\t\t\t "
                        << (device.getInfo<
                                    CL_DEVICE_QUEUE_ON_HOST_PROPERTIES>() &
                                    CL_QUEUE_PROFILING_ENABLE
                                ? "Yes"
                                : "No")
                        << std::endl;

                    std::cout << "  Queue on Device properties:\t\t\t\t "
                              << std::endl;
                    std::cout
                        << "    Out-of-Order:\t\t\t\t "
                        << (device.getInfo<
                                    CL_DEVICE_QUEUE_ON_DEVICE_PROPERTIES>() &
                                    CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE
                                ? "Yes"
                                : "No")
                        << std::endl;
                    std::cout
                        << "    Profiling :\t\t\t\t\t "
                        << (device.getInfo<
                                    CL_DEVICE_QUEUE_ON_DEVICE_PROPERTIES>() &
                                    CL_QUEUE_PROFILING_ENABLE
                                ? "Yes"
                                : "No")
                        << std::endl;
                }
#endif

                std::cout << "  Platform ID:\t\t\t\t\t "
                          << device.getInfo<CL_DEVICE_PLATFORM>() << std::endl;

                std::cout << "  Name:\t\t\t\t\t\t "
                          << device.getInfo<CL_DEVICE_NAME>().c_str()
                          << std::endl;

                std::cout << "  Vendor:\t\t\t\t\t "
                          << device.getInfo<CL_DEVICE_VENDOR>().c_str()
                          << std::endl;
#ifdef CL_VERSION_1_1
                if (vStrVal.compare("1.0") > 0) {
                    std::cout
                        << "  Device OpenCL C version:\t\t\t "
                        << device.getInfo<CL_DEVICE_OPENCL_C_VERSION>().c_str()
                        << std::endl;
                }
#endif  // CL_VERSION_1_1
                std::cout << "  Driver version:\t\t\t\t "
                          << device.getInfo<CL_DRIVER_VERSION>().c_str()
                          << std::endl;

                std::cout << "  Profile:\t\t\t\t\t "
                          << device.getInfo<CL_DEVICE_PROFILE>().c_str()
                          << std::endl;

                std::cout << "  Version:\t\t\t\t\t "
                          << device.getInfo<CL_DEVICE_VERSION>().c_str()
                          << std::endl;

                std::cout << "  Extensions:\t\t\t\t\t "
                          << device.getInfo<CL_DEVICE_EXTENSIONS>().c_str()
                          << std::endl;

                std::cout << std::endl << std::endl;
            }
        }
    } catch (cl::Error err) {
        std::cerr << "ERROR: " << err.what() << "(" << err.err() << ")"
                  << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
