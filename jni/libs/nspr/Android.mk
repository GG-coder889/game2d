LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := nspr_static_prebuilt
LOCAL_SRC_FILES := libnspr4.a
include $(PREBUILT_STATIC_LIBRARY)
