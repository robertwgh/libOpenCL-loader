/******************************************************************************
* Copyright (c) 2015-2016 Robert (Guohui) Wang
*
* Project:    A Cross-platform OpenCL Dynamic Library Loader
* File:       libopencl_loader.h
* E-mail:     robertwgh (at) gmail.com
* License:    Apache License Version 2.0.
*
* Revisions:  April  7 2015 -first version.
*             April 30 2016 -revised for release on github.
******************************************************************************/

#ifndef LIBOPENCL_LOADER_H
#define LIBOPENCL_LOADER_H

#ifdef __APPLE__
#include <OpenCL/cl_platform.h>
#include <OpenCL/cl.h>
#else
#include <CL/cl_platform.h>
#include <CL/cl.h>
#endif  

#ifdef __ANDROID_API__
#include <android/log.h>
#define CL_LOADER_LOG(...) __android_log_print(ANDROID_LOG_VERBOSE, "opencl_api", __VA_ARGS__)
#define CL_LOADER_LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "opencl_api", __VA_ARGS__)
#define CL_LOADER_LOGW(...) __android_log_print(ANDROID_LOG_WARN, "opencl_api", __VA_ARGS__)
#define CL_LOADER_LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "opencl_api", __VA_ARGS__)
#else
#include <stdio.h>
#define LOGV(...) printf(__VA_ARGS__)
#define LOGD(...) printf(__VA_ARGS__)
#define LOGW(...) printf(__VA_ARGS__)
#define LOGE(...) printf(__VA_ARGS__)
#endif

#ifdef __cplusplus
extern "C" {
#endif


// Error message for loadOpenCL() function.
#define CL_LOADER_SUCCESS                      0
#define CL_LOADER_FAILED_LOCATE_LIB_OPENCL    -1
#define CL_LOADER_FAILED_MAP_SYMBOL           -2
#define CL_LOADER_FAILED_REG_ATEXIT           -3


// Function interface.
int          clLoaderInit();
void         clLoaderExit();
const char * clLoaderGetLibPath();


// Platform APIs
cl_int 
(*clLoaderGetPlatformIDs)(cl_uint          /* num_entries */,
                          cl_platform_id * /* platforms */,
                          cl_uint *        /* num_platforms */);

cl_int  
(*clLoaderGetPlatformInfo)(cl_platform_id   /* platform */, 
                           cl_platform_info /* param_name */,
                           size_t           /* param_value_size */, 
                           void *           /* param_value */,
                           size_t *         /* param_value_size_ret */);


// Device APIs
cl_int 
(*clLoaderGetDeviceIDs)(cl_platform_id   /* platform */,
                        cl_device_type   /* device_type */, 
                        cl_uint          /* num_entries */, 
                        cl_device_id *   /* devices */, 
                        cl_uint *        /* num_devices */);

cl_int 
(*clLoaderGetDeviceInfo)(cl_device_id    /* device */,
                         cl_device_info  /* param_name */, 
                         size_t          /* param_value_size */, 
                         void *          /* param_value */,
                         size_t *        /* param_value_size_ret */);


// Context APIs
cl_context 
(*clLoaderCreateContext)(const cl_context_properties * /* properties */,
                         cl_uint                 /* num_devices */,
                         const cl_device_id *    /* devices */,
                         void (CL_CALLBACK * /* pfn_notify */)(const char *, const void *, size_t, void *),
                         void *                  /* user_data */,
                         cl_int *                /* errcode_ret */);

cl_context 
(*clLoaderCreateContextFromType)(const cl_context_properties * /* properties */,
                                 cl_device_type          /* device_type */,
                                 void (CL_CALLBACK *     /* pfn_notify*/ )(const char *, const void *, size_t, void *),
                                 void *                  /* user_data */,
                                 cl_int *                /* errcode_ret */);

cl_int 
(*clLoaderRetainContext)(cl_context /* context */);

cl_int 
(*clLoaderReleaseContext)(cl_context /* context */);

cl_int 
(*clLoaderGetContextInfo)(cl_context         /* context */, 
                          cl_context_info    /* param_name */, 
                          size_t             /* param_value_size */, 
                          void *             /* param_value */, 
                          size_t *           /* param_value_size_ret */);


/* Command queue APIs */
cl_command_queue 
(*clLoaderCreateCommandQueue)(cl_context                     /* context */, 
                              cl_device_id                   /* device */, 
                              cl_command_queue_properties    /* properties */,
                              cl_int *                       /* errcode_ret */);

cl_int 
(*clLoaderRetainCommandQueue)(cl_command_queue /* command_queue */);

cl_int 
(*clLoaderReleaseCommandQueue)(cl_command_queue /* command_queue */);

cl_int 
(*clLoaderGetCommandQueueInfo)(cl_command_queue      /* command_queue */,
                               cl_command_queue_info /* param_name */,
                               size_t                /* param_value_size */,
                               void *                /* param_value */,
                               size_t *              /* param_value_size_ret */);


/* Memory object APIs */
cl_mem 
(*clLoaderCreateBuffer)(cl_context   /* context */,
                        cl_mem_flags /* flags */,
                        size_t       /* size */,
                        void *       /* host_ptr */,
                        cl_int *     /* errcode_ret */);

cl_mem 
(*clLoaderCreateSubBuffer)(cl_mem                   /* buffer */,
                           cl_mem_flags             /* flags */,
                           cl_buffer_create_type    /* buffer_create_type */,
                           const void *             /* buffer_create_info */,
                           cl_int *                 /* errcode_ret */);

                       
cl_int 
(*clLoaderRetainMemObject)(cl_mem /* memobj */);

cl_int 
(*clLoaderReleaseMemObject)(cl_mem /* memobj */);

cl_int 
(*clLoaderGetSupportedImageFormats)(cl_context           /* context */,
                                    cl_mem_flags         /* flags */,
                                    cl_mem_object_type   /* image_type */,
                                    cl_uint              /* num_entries */,
                                    cl_image_format *    /* image_formats */,
                                    cl_uint *            /* num_image_formats */);
                                    
cl_int 
(*clLoaderGetMemObjectInfo)(cl_mem           /* memobj */,
                            cl_mem_info      /* param_name */, 
                            size_t           /* param_value_size */,
                            void *           /* param_value */,
                            size_t *         /* param_value_size_ret */);

cl_int 
(*clLoaderGetImageInfo)(cl_mem           /* image */,
                        cl_image_info    /* param_name */, 
                        size_t           /* param_value_size */,
                        void *           /* param_value */,
                        size_t *         /* param_value_size_ret */);

cl_int 
(*clLoaderSetMemObjectDestructorCallback)(cl_mem /* memobj */, 
                                          void (CL_CALLBACK * /*pfn_notify*/)( cl_mem /* memobj */, void* /*user_data*/), 
                                          void * /*user_data */ );  


// Sampler APIs
cl_sampler 
(*clLoaderCreateSampler)(cl_context          /* context */,
                         cl_bool             /* normalized_coords */, 
                         cl_addressing_mode  /* addressing_mode */, 
                         cl_filter_mode      /* filter_mode */,
                         cl_int *            /* errcode_ret */);

cl_int 
(*clLoaderRetainSampler)(cl_sampler /* sampler */);

cl_int 
(*clLoaderReleaseSampler)(cl_sampler /* sampler */);

cl_int 
(*clLoaderGetSamplerInfo)(cl_sampler         /* sampler */,
                          cl_sampler_info    /* param_name */,
                          size_t             /* param_value_size */,
                          void *             /* param_value */,
                          size_t *           /* param_value_size_ret */);
                            
// Program object APIs
cl_program 
(*clLoaderCreateProgramWithSource)(cl_context        /* context */,
                                   cl_uint           /* count */,
                                   const char **     /* strings */,
                                   const size_t *    /* lengths */,
                                   cl_int *          /* errcode_ret */);

cl_program 
(*clLoaderCreateProgramWithBinary)(cl_context                     /* context */,
                                   cl_uint                        /* num_devices */,
                                   const cl_device_id *           /* device_list */,
                                   const size_t *                 /* lengths */,
                                   const unsigned char **         /* binaries */,
                                   cl_int *                       /* binary_status */,
                                   cl_int *                       /* errcode_ret */);


cl_int 
(*clLoaderRetainProgram)(cl_program /* program */);

cl_int 
(*clLoaderReleaseProgram)(cl_program /* program */);

cl_int 
(*clLoaderBuildProgram)(cl_program           /* program */,
                        cl_uint              /* num_devices */,
                        const cl_device_id * /* device_list */,
                        const char *         /* options */, 
                        void (CL_CALLBACK *  /* pfn_notify */)(cl_program /* program */, void * /* user_data */),
                        void *               /* user_data */);

cl_int 
(*clLoaderGetProgramInfo)(cl_program         /* program */,
                          cl_program_info    /* param_name */,
                          size_t             /* param_value_size */,
                          void *             /* param_value */,
                          size_t *           /* param_value_size_ret */);

cl_int 
(*clLoaderGetProgramBuildInfo)(cl_program            /* program */,
                               cl_device_id          /* device */,
                               cl_program_build_info /* param_name */,
                               size_t                /* param_value_size */,
                               void *                /* param_value */,
                               size_t *              /* param_value_size_ret */);
                            
// Kernel object APIs
cl_kernel 
(*clLoaderCreateKernel)(cl_program      /* program */,
                        const char *    /* kernel_name */,
                        cl_int *        /* errcode_ret */);

cl_int 
(*clLoaderCreateKernelsInProgram)(cl_program     /* program */,
                                  cl_uint        /* num_kernels */,
                                  cl_kernel *    /* kernels */,
                                  cl_uint *      /* num_kernels_ret */);

cl_int 
(*clLoaderRetainKernel)(cl_kernel    /* kernel */);

cl_int 
(*clLoaderReleaseKernel)(cl_kernel   /* kernel */);

cl_int 
(*clLoaderSetKernelArg)(cl_kernel    /* kernel */,
                        cl_uint      /* arg_index */,
                        size_t       /* arg_size */,
                        const void * /* arg_value */);

cl_int 
(*clLoaderGetKernelInfo)(cl_kernel       /* kernel */,
                         cl_kernel_info  /* param_name */,
                         size_t          /* param_value_size */,
                         void *          /* param_value */,
                         size_t *        /* param_value_size_ret */);

cl_int 
(*clLoaderGetKernelWorkGroupInfo)(cl_kernel                  /* kernel */,
                                  cl_device_id               /* device */,
                                  cl_kernel_work_group_info  /* param_name */,
                                  size_t                     /* param_value_size */,
                                  void *                     /* param_value */,
                                  size_t *                   /* param_value_size_ret */);

// Event object APIs
cl_int 
(*clLoaderWaitForEvents)(cl_uint             /* num_events */,
                         const cl_event *    /* event_list */);

cl_int 
(*clLoaderGetEventInfo)(cl_event         /* event */,
                        cl_event_info    /* param_name */,
                        size_t           /* param_value_size */,
                        void *           /* param_value */,
                        size_t *         /* param_value_size_ret */);
                            
cl_event 
(*clLoaderCreateUserEvent)(cl_context    /* context */,
                           cl_int *      /* errcode_ret */);               
                            

cl_int 
(*clLoaderRetainEvent)(cl_event /* event */);

cl_int 
(*clLoaderReleaseEvent)(cl_event /* event */);

cl_int 
(*clLoaderSetUserEventStatus)(cl_event   /* event */,
                              cl_int     /* execution_status */);
                     
cl_int 
(*clLoaderSetEventCallback)(cl_event    /* event */,
                            cl_int      /* command_exec_callback_type */,
                            void (CL_CALLBACK * /* pfn_notify */)(cl_event,cl_int, void *),
                            void *      /* user_data */);

// Event profiling APIs
cl_int 
(*clLoaderGetEventProfilingInfo)(cl_event            /* event */,
                                 cl_profiling_info   /* param_name */,
                                 size_t              /* param_value_size */,
                                 void *              /* param_value */,
                                 size_t *            /* param_value_size_ret */);
        
                                
// Command queue control APIs
cl_int 
(*clLoaderFlush)(cl_command_queue /* command_queue */);

cl_int 
(*clLoaderFinish)(cl_command_queue /* command_queue */);


// Command queue enqueue APIs
cl_int 
(*clLoaderEnqueueReadBuffer)(cl_command_queue    /* command_queue */,
                             cl_mem              /* buffer */,
                             cl_bool             /* blocking_read */,
                             size_t              /* offset */,
                             size_t              /* size */, 
                             void *              /* ptr */,
                             cl_uint             /* num_events_in_wait_list */,
                             const cl_event *    /* event_wait_list */,
                             cl_event *          /* event */);
                            
cl_int 
(*clLoaderEnqueueReadBufferRect)(cl_command_queue    /* command_queue */,
                                 cl_mem              /* buffer */,
                                 cl_bool             /* blocking_read */,
                                 const size_t *      /* buffer_offset */,
                                 const size_t *      /* host_offset */, 
                                 const size_t *      /* region */,
                                 size_t              /* buffer_row_pitch */,
                                 size_t              /* buffer_slice_pitch */,
                                 size_t              /* host_row_pitch */,
                                 size_t              /* host_slice_pitch */,                        
                                 void *              /* ptr */,
                                 cl_uint             /* num_events_in_wait_list */,
                                 const cl_event *    /* event_wait_list */,
                                 cl_event *          /* event */);
                            
cl_int 
(*clLoaderEnqueueWriteBuffer)(cl_command_queue   /* command_queue */, 
                              cl_mem             /* buffer */, 
                              cl_bool            /* blocking_write */, 
                              size_t             /* offset */, 
                              size_t             /* size */, 
                              const void *       /* ptr */, 
                              cl_uint            /* num_events_in_wait_list */, 
                              const cl_event *   /* event_wait_list */, 
                              cl_event *         /* event */);
                            
cl_int 
(*clLoaderEnqueueWriteBufferRect)(cl_command_queue    /* command_queue */,
                                  cl_mem              /* buffer */,
                                  cl_bool             /* blocking_write */,
                                  const size_t *      /* buffer_offset */,
                                  const size_t *      /* host_offset */, 
                                  const size_t *      /* region */,
                                  size_t              /* buffer_row_pitch */,
                                  size_t              /* buffer_slice_pitch */,
                                  size_t              /* host_row_pitch */,
                                                          size_t              /* host_slice_pitch */,                        
                                  const void *        /* ptr */,
                                  cl_uint             /* num_events_in_wait_list */,
                                  const cl_event *    /* event_wait_list */,
                                  cl_event *          /* event */);
                                
                                    
cl_int 
(*clLoaderEnqueueCopyBuffer)(cl_command_queue    /* command_queue */, 
                             cl_mem              /* src_buffer */,
                             cl_mem              /* dst_buffer */, 
                             size_t              /* src_offset */,
                             size_t              /* dst_offset */,
                             size_t              /* size */, 
                             cl_uint             /* num_events_in_wait_list */,
                             const cl_event *    /* event_wait_list */,
                             cl_event *          /* event */);
                            
cl_int 
(*clLoaderEnqueueCopyBufferRect)(cl_command_queue    /* command_queue */, 
                                 cl_mem              /* src_buffer */,
                                 cl_mem              /* dst_buffer */, 
                                 const size_t *      /* src_origin */,
                                 const size_t *      /* dst_origin */,
                                 const size_t *      /* region */, 
                                 size_t              /* src_row_pitch */,
                                 size_t              /* src_slice_pitch */,
                                 size_t              /* dst_row_pitch */,
                                 size_t              /* dst_slice_pitch */,
                                 cl_uint             /* num_events_in_wait_list */,
                                 const cl_event *    /* event_wait_list */,
                                 cl_event *          /* event */);
                            
cl_int 
(*clLoaderEnqueueReadImage)(cl_command_queue     /* command_queue */,
                            cl_mem               /* image */,
                            cl_bool              /* blocking_read */, 
                            const size_t *       /* origin[3] */,
                            const size_t *       /* region[3] */,
                            size_t               /* row_pitch */,
                            size_t               /* slice_pitch */, 
                            void *               /* ptr */,
                            cl_uint              /* num_events_in_wait_list */,
                            const cl_event *     /* event_wait_list */,
                            cl_event *           /* event */);

cl_int 
(*clLoaderEnqueueWriteImage)(cl_command_queue    /* command_queue */,
                             cl_mem              /* image */,
                             cl_bool             /* blocking_write */, 
                             const size_t *      /* origin[3] */,
                             const size_t *      /* region[3] */,
                             size_t              /* input_row_pitch */,
                             size_t              /* input_slice_pitch */, 
                             const void *        /* ptr */,
                             cl_uint             /* num_events_in_wait_list */,
                             const cl_event *    /* event_wait_list */,
                             cl_event *          /* event */);

cl_int 
(*clLoaderEnqueueCopyImage)(cl_command_queue     /* command_queue */,
                            cl_mem               /* src_image */,
                            cl_mem               /* dst_image */, 
                            const size_t *       /* src_origin[3] */,
                            const size_t *       /* dst_origin[3] */,
                            const size_t *       /* region[3] */, 
                            cl_uint              /* num_events_in_wait_list */,
                            const cl_event *     /* event_wait_list */,
                            cl_event *           /* event */);

cl_int 
(*clLoaderEnqueueCopyImageToBuffer)(cl_command_queue /* command_queue */,
                                    cl_mem           /* src_image */,
                                    cl_mem           /* dst_buffer */, 
                                    const size_t *   /* src_origin[3] */,
                                    const size_t *   /* region[3] */, 
                                    size_t           /* dst_offset */,
                                    cl_uint          /* num_events_in_wait_list */,
                                    const cl_event * /* event_wait_list */,
                                    cl_event *       /* event */);

cl_int 
(*clLoaderEnqueueCopyBufferToImage)(cl_command_queue /* command_queue */,
                                    cl_mem           /* src_buffer */,
                                    cl_mem           /* dst_image */, 
                                    size_t           /* src_offset */,
                                    const size_t *   /* dst_origin[3] */,
                                    const size_t *   /* region[3] */, 
                                    cl_uint          /* num_events_in_wait_list */,
                                    const cl_event * /* event_wait_list */,
                                    cl_event *       /* event */);
void * 
(*clLoaderEnqueueMapBuffer)(cl_command_queue /* command_queue */,
                            cl_mem           /* buffer */,
                            cl_bool          /* blocking_map */, 
                            cl_map_flags     /* map_flags */,
                            size_t           /* offset */,
                            size_t           /* size */,
                            cl_uint          /* num_events_in_wait_list */,
                            const cl_event * /* event_wait_list */,
                            cl_event *       /* event */,
                            cl_int *         /* errcode_ret */);

void * 
(*clLoaderEnqueueMapImage)(cl_command_queue  /* command_queue */,
                           cl_mem            /* image */, 
                           cl_bool           /* blocking_map */, 
                           cl_map_flags      /* map_flags */, 
                           const size_t *    /* origin[3] */,
                           const size_t *    /* region[3] */,
                           size_t *          /* image_row_pitch */,
                           size_t *          /* image_slice_pitch */,
                           cl_uint           /* num_events_in_wait_list */,
                           const cl_event *  /* event_wait_list */,
                           cl_event *        /* event */,
                           cl_int *          /* errcode_ret */);

cl_int 
(*clLoaderEnqueueUnmapMemObject)(cl_command_queue /* command_queue */,
                                 cl_mem           /* memobj */,
                                 void *           /* mapped_ptr */,
                                 cl_uint          /* num_events_in_wait_list */,
                                 const cl_event *  /* event_wait_list */,
                                 cl_event *        /* event */);

cl_int 
(*clLoaderEnqueueNDRangeKernel)(cl_command_queue /* command_queue */,
                                cl_kernel        /* kernel */,
                                cl_uint          /* work_dim */,
                                const size_t *   /* global_work_offset */,
                                const size_t *   /* global_work_size */,
                                const size_t *   /* local_work_size */,
                                cl_uint          /* num_events_in_wait_list */,
                                const cl_event * /* event_wait_list */,
                                cl_event *       /* event */);

cl_int 
(*clLoaderEnqueueTask)(cl_command_queue  /* command_queue */,
                       cl_kernel         /* kernel */,
                       cl_uint           /* num_events_in_wait_list */,
                       const cl_event *  /* event_wait_list */,
                       cl_event *        /* event */);

cl_int 
(*clLoaderEnqueueNativeKernel)(cl_command_queue  /* command_queue */,
                               void (CL_CALLBACK * /*user_func*/)(void *), 
                               void *            /* args */,
                               size_t            /* cb_args */, 
                               cl_uint           /* num_mem_objects */,
                               const cl_mem *    /* mem_list */,
                               const void **     /* args_mem_loc */,
                               cl_uint           /* num_events_in_wait_list */,
                               const cl_event *  /* event_wait_list */,
                               cl_event *        /* event */);


#ifdef CL_USE_DEPRECATED_OPENCL_1_0_APIS
cl_int 
(*clLoaderSetCommandQueueProperty)(cl_command_queue              /* command_queue */,
                                   cl_command_queue_properties   /* properties */, 
                                   cl_bool                        /* enable */,
                                   cl_command_queue_properties * /* old_properties */);
#endif /* CL_USE_DEPRECATED_OPENCL_1_0_APIS */
    
    
#ifdef CL_USE_DEPRECATED_OPENCL_1_1_APIS
cl_mem 
(*clLoaderCreateImage2D)(cl_context              /* context */,
                         cl_mem_flags            /* flags */,
                         const cl_image_format * /* image_format */,
                         size_t                  /* image_width */,
                         size_t                  /* image_height */,
                         size_t                  /* image_row_pitch */, 
                         void *                  /* host_ptr */,
                         cl_int *                /* errcode_ret */);
    
cl_mem 
(*clLoaderCreateImage3D)(cl_context              /* context */,
                         cl_mem_flags            /* flags */,
                         const cl_image_format * /* image_format */,
                         size_t                  /* image_width */, 
                         size_t                  /* image_height */,
                         size_t                  /* image_depth */, 
                         size_t                  /* image_row_pitch */, 
                         size_t                  /* image_slice_pitch */, 
                         void *                  /* host_ptr */,
                         cl_int *                /* errcode_ret */);
    
cl_int 
(*clLoaderEnqueueMarker)(cl_command_queue    /* command_queue */,
                         cl_event *          /* event */);
    
cl_int 
(*clLoaderEnqueueWaitForEvents)(cl_command_queue /* command_queue */,
                                cl_uint          /* num_events */,
                                const cl_event * /* event_list */);
    
cl_int 
(*clLoaderEnqueueBarrier)(cl_command_queue /* command_queue */);

cl_int 
(*clLoaderUnloadCompiler)(void);

#endif
#ifdef __cplusplus
}
#endif

#define clGetPlatformIDs                  clLoaderGetPlatformIDs
#define clGetPlatformInfo                 clLoaderGetPlatformInfo
#define clGetDeviceIDs                    clLoaderGetDeviceIDs
#define clGetDeviceInfo                   clLoaderGetDeviceInfo
#define clCreateContext                   clLoaderCreateContext
#define clCreateContextFromType           clLoaderCreateContextFromType
#define clRetainContext                   clLoaderRetainContext
#define clReleaseContext                  clLoaderReleaseContext
#define clGetContextInfo                  clLoaderGetContextInfo
#define clCreateCommandQueue              clLoaderCreateCommandQueue
#define clRetainCommandQueue              clLoaderRetainCommandQueue
#define clReleaseCommandQueue             clLoaderReleaseCommandQueue
#define clGetCommandQueueInfo             clLoaderGetCommandQueueInfo
#define clCreateBuffer                    clLoaderCreateBuffer
#define clCreateSubBuffer                 clLoaderCreateSubBuffer
#define clRetainMemObject                 clLoaderRetainMemObject
#define clReleaseMemObject                clLoaderReleaseMemObject
#define clGetSupportedImageFormats        clLoaderGetSupportedImageFormats
#define clGetMemObjectInfo                clLoaderGetMemObjectInfo
#define clGetImageInfo                    clLoaderGetImageInfo
#define clSetMemObjectDestructorCallback  clLoaderSetMemObjectDestructorCallback
#define clCreateSampler                   clLoaderCreateSampler
#define clRetainSampler                   clLoaderRetainSampler
#define clReleaseSampler                  clLoaderReleaseSampler
#define clGetSamplerInfo                  clLoaderGetSamplerInfo
#define clCreateProgramWithSource         clLoaderCreateProgramWithSource
#define clCreateProgramWithBinary         clLoaderCreateProgramWithBinary
#define clRetainProgram                   clLoaderRetainProgram
#define clReleaseProgram                  clLoaderReleaseProgram
#define clBuildProgram                    clLoaderBuildProgram
#define clGetProgramInfo                  clLoaderGetProgramInfo
#define clGetProgramBuildInfo             clLoaderGetProgramBuildInfo
#define clCreateKernel                    clLoaderCreateKernel
#define clCreateKernelsInProgram          clLoaderCreateKernelsInProgram
#define clRetainKernel                    clLoaderRetainKernel
#define clReleaseKernel                   clLoaderReleaseKernel
#define clSetKernelArg                    clLoaderSetKernelArg
#define clGetKernelInfo                   clLoaderGetKernelInfo
#define clGetKernelWorkGroupInfo          clLoaderGetKernelWorkGroupInfo
#define clWaitForEvents                   clLoaderWaitForEvents
#define clGetEventInfo                    clLoaderGetEventInfo
#define clCreateUserEvent                 clLoaderCreateUserEvent
#define clRetainEvent                     clLoaderRetainEvent
#define clReleaseEvent                    clLoaderReleaseEvent
#define clSetUserEventStatus              clLoaderSetUserEventStatus
#define clSetEventCallback                clLoaderSetEventCallback
#define clGetEventProfilingInfo           clLoaderGetEventProfilingInfo
#define clFlush                           clLoaderFlush
#define clFinish                          clLoaderFinish
#define clEnqueueReadBuffer               clLoaderEnqueueReadBuffer
#define clEnqueueReadBufferRect           clLoaderEnqueueReadBufferRect
#define clEnqueueWriteBuffer              clLoaderEnqueueWriteBuffer
#define clEnqueueWriteBufferRect          clLoaderEnqueueWriteBufferRect
#define clEnqueueCopyBuffer               clLoaderEnqueueCopyBuffer
#define clEnqueueCopyBufferRect           clLoaderEnqueueCopyBufferRect
#define clEnqueueReadImage                clLoaderEnqueueReadImage
#define clEnqueueWriteImage               clLoaderEnqueueWriteImage
#define clEnqueueCopyImage                clLoaderEnqueueCopyImage
#define clEnqueueCopyImageToBuffer        clLoaderEnqueueCopyImageToBuffer
#define clEnqueueCopyBufferToImage        clLoaderEnqueueCopyBufferToImage
#define clEnqueueUnmapMemObject           clLoaderEnqueueUnmapMemObject
#define clEnqueueNDRangeKernel            clLoaderEnqueueNDRangeKernel
#define clEnqueueTask                     clLoaderEnqueueTask
#define clEnqueueNativeKernel             clLoaderEnqueueNativeKernel
#define clSetCommandQueueProperty         clLoaderSetCommandQueueProperty
#define clCreateImage2D                   clLoaderCreateImage2D
#define clCreateImage3D                   clLoaderCreateImage3D
#define clEnqueueMarker                   clLoaderEnqueueMarker
#define clEnqueueWaitForEvents            clLoaderEnqueueWaitForEvents
#define clEnqueueBarrier                  clLoaderEnqueueBarrier
#define clUnloadCompiler                  clLoaderUnloadCompiler

#endif  /* LIBOPENCL_LOADER_H */

