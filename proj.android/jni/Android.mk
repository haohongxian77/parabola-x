LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   platform/HHPlatform.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/commonnode/SettingNode.cpp \
                   ../../Classes/commonnode/HMenu.cpp \
                   ../../Classes/commonnode/ShareNode.cpp \
                   ../../Classes/gamescene/GameMainLayer.cpp \
                   ../../Classes/gamescene/GameMainScene.cpp \
                   ../../Classes/gamescene/GameSpileLayer.cpp \
                   ../../Classes/gamesprite/HeroFrog.cpp \
                   ../../Classes/gamesprite/MonsterSpile.cpp \
                   ../../Classes/gamesprite/TouchNode.cpp \
                   ../../Classes/helper/CalculateHelper.cpp \
                   ../../Classes/helper/GameMainHelper.cpp \
                   ../../Classes/loadingscene/StartLayer.cpp \
                   ../../Classes/loadingscene/StartScene.cpp \
                   ../../Classes/loadingscene/GameMainLogoLayer.cpp \
                   ../../Classes/loadingscene/GameOverLayer.cpp \
                   ../../Classes/mainlayer/MainLayer.cpp 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
