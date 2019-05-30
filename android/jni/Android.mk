LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LIB_ROOT_PATH   := ../..
LOCAL_MODULE    := opencl_loader
LOCAL_SRC_FILES := $(LIB_ROOT_PATH)/src/opencl_loader.cpp
LOCAL_C_INCLUDES := ../include/
LOCAL_CFLAGS += -mfpu=neon -std=c++11 -DENABLE_OPENCL
LOCAL_CPPFLAGS += -ffunction-sections -fdata-sections -DENABLE_OPENCL
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LIB_ROOT_PATH   := ../..
LOCAL_MODULE    := test_cl_hpp
LOCAL_SRC_FILES := $(LIB_ROOT_PATH)/test/test_cl_hpp.cpp
LOCAL_C_INCLUDES := ../include/
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog
LOCAL_CFLAGS += -mfpu=neon -std=c++11 -DENABLE_OPENCL
LOCAL_STATIC_LIBRARIES := opencl_loader
LOCAL_LDLIBS += -llog -ldl -Lprebuilt-opencl-loader
LOCAL_CPPFLAGS += -ffunction-sections -fdata-sections -DENABLE_OPENCL
LOCAL_LDFLAGS += -Wl,--gc-sections
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LIB_ROOT_PATH   := ../..
LOCAL_MODULE    := test_cl_h
LOCAL_SRC_FILES := $(LIB_ROOT_PATH)/test/test_cl_h.cpp
LOCAL_C_INCLUDES := ../include/
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog
LOCAL_CFLAGS += -mfpu=neon -std=c++11 -DENABLE_OPENCL
LOCAL_STATIC_LIBRARIES := opencl_loader
LOCAL_LDLIBS += -llog -ldl -Lprebuilt-opencl-loader
LOCAL_CPPFLAGS += -ffunction-sections -fdata-sections -DENABLE_OPENCL
LOCAL_LDFLAGS += -Wl,--gc-sections
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LIB_ROOT_PATH   := ../..
LOCAL_MODULE    := clinfo
LOCAL_SRC_FILES := $(LIB_ROOT_PATH)/test/clinfo.cpp
LOCAL_C_INCLUDES := ../include/
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog
LOCAL_CFLAGS += -mfpu=neon -std=c++11 -DENABLE_OPENCL
LOCAL_STATIC_LIBRARIES := opencl_loader
LOCAL_LDLIBS += -llog -ldl -Lprebuilt-opencl-loader
LOCAL_CPPFLAGS += -ffunction-sections -fdata-sections -DENABLE_OPENCL
LOCAL_LDFLAGS += -Wl,--gc-sections
include $(BUILD_EXECUTABLE)