LOCAL_PATH := $(call my-dir)
 
include $(CLEAR_VARS)

LOCAL_MODULE    := reverse_tcp
LOCAL_SRC_FILES := reverse_tcp.c
LOCAL_CFLAGS += -g -ggdb -fno-stack-protector
 
include $(BUILD_EXECUTABLE)
