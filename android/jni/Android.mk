LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LIB_ROOT_PATH   := ../..
LOCAL_MODULE    := opencl_loader
LOCAL_SRC_FILES := $(LIB_ROOT_PATH)/src/opencl_loader.cpp
LOCAL_C_INCLUDES := ../include/

LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog
LOCAL_CFLAGS += -mfpu=neon -std=c++11 -DENABLE_OPENCL
LOCAL_LDLIBS += -llog -ldl
LOCAL_CPPFLAGS += -ffunction-sections -fdata-sections -DENABLE_OPENCL
LOCAL_LDFLAGS += -Wl,--gc-sections

include $(BUILD_SHARED_LIBRARY)