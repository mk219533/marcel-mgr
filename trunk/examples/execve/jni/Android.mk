LOCAL_PATH := $(call my-dir)
 
include $(CLEAR_VARS)
  
LOCAL_MODULE    := execve
LOCAL_SRC_FILES := execve.c
LOCAL_CFLAGS += -g -ggdb 
 
include $(BUILD_EXECUTABLE)
