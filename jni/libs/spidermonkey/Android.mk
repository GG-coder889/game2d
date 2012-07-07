LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := spidermonkey_static_prebuilt
LOCAL_SRC_FILES := libspidermonkey.a
include $(PREBUILT_STATIC_LIBRARY)
