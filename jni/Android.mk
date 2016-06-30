LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := interface
LOCAL_SRC_FILES := interface.cpp minmax_ai.cpp Astar.cpp
LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)