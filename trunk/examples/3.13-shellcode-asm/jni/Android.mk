LOCAL_PATH := $(call my-dir)
 
include $(CLEAR_VARS)

LOCAL_MODULE    := shellcode-asm
LOCAL_SRC_FILES := shellcode-asm.c
LOCAL_CFLAGS += -g -ggdb -fno-stack-protector
 
include $(BUILD_EXECUTABLE)
