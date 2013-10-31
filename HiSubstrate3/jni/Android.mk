LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)


LOCAL_C_INCLUDES := i:/DevTool/Android/adt-bundle-windows-x86-20130219/sdk/extras/saurikit/cydia_substrate
LOCAL_LDFLAGS := -Li:/DevTool/Android/adt-bundle-windows-x86-20130219/sdk/extras/saurikit/cydia_substrate/lib/armeabi

LOCAL_LDLIBS    := -lsubstrate  -lsubstrate-dvm

LOCAL_MODULE    := HiSubs.cy
LOCAL_SRC_FILES := HiSubs.cy.cpp

include $(BUILD_SHARED_LIBRARY)
