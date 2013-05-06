LOCAL_PATH := $(call my-dir)
 
include $(CLEAR_VARS)

LOCAL_MODULE    := rop
LOCAL_SRC_FILES := rop.c
LOCAL_CFLAGS += -g -ggdb 
 
include $(BUILD_EXECUTABLE)
