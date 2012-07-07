LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

subdirs := $(LOCAL_PATH)/libs/cocos2dx/Android.mk
subdirs += $(LOCAL_PATH)/libs/CocosDenshion/android/Android.mk
subdirs += $(LOCAL_PATH)/libs/Box2D/Android.mk
subdirs += $(LOCAL_PATH)/src/Android.mk


include $(subdirs)
