LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

include $(CLEAR_VARS)
LOCAL_MODULE := libweibosdkcore
LOCAL_SRC_FILES := prebuild/armeabi/libweibosdkcore.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libweibosdkcorev8
LOCAL_SRC_FILES := prebuild/arm64-v8a/libweibosdkcore.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libweibosdkcorev7
LOCAL_SRC_FILES := prebuild/armeabi-v7a/libweibosdkcore.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libweibosdkcoremips
LOCAL_SRC_FILES := prebuild/mips/libweibosdkcore.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libweibosdkcoremips64
LOCAL_SRC_FILES := prebuild/mips64/libweibosdkcore.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libweibosdkcorex86
LOCAL_SRC_FILES := prebuild/x86/libweibosdkcore.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libweibosdkcorex64
LOCAL_SRC_FILES := prebuild/x86_64/libweibosdkcore.so
include $(PREBUILT_SHARED_LIBRARY)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/Cocos2dx/Android/CCUMSocialController.cpp  \
                   ../../Classes/Cocos2dx/ShareButton/UMShareButton.cpp \
                   ../../Classes/Cocos2dx/Common/CCUMSocialSDK.cpp 
                 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
