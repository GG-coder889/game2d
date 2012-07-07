LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libsqlite3
LOCAL_C_INCLUDES = $(LOCAL_PATH)/
LOCAL_SRC_FILES := sqlite3.c
include $(BUILD_SHARED_LIBRARY)
