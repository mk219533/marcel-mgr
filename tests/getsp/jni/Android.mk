LOCAL_PATH := $(call my-dir)
 
include $(CLEAR_VARS)
  
LOCAL_MODULE    := getsp
LOCAL_SRC_FILES := getsp.c
LOCAL_CFLAGS += -g -ggdb -fno-stack-protector
# LOCAL_DISABLE_NO_EXECUTE := true
# LOCAL_DISABLE_RELRO := true
 
include $(BUILD_EXECUTABLE)
