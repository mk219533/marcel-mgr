LOCAL_PATH := $(call my-dir)
 
include $(CLEAR_VARS)

LOCAL_MODULE    := shellcode
LOCAL_SRC_FILES := shellcode.c
LOCAL_CFLAGS += -g -ggdb -fno-stack-protector
 
include $(BUILD_EXECUTABLE)
