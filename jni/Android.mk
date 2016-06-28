LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := interface
LOCAL_SRC_FILES := interface.c testcpp.cpp minmax_ai.cpp
LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)