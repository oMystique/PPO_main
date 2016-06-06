LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/MainScene.cpp \
				   ../../Classes/AnimationKit.cpp \
				   ../../Classes/ButtonsKit.cpp \
					../../Classes/player.cpp \
					../../Classes/Entities.cpp \
					../../Classes/SneakyInput/SneakyJoystickSkinnedBase.cpp \
					../../Classes/SneakyInput/SneakyJoystick.cpp \
					../../Classes/SneakyInput/SneakyButtonSkinnedBase.cpp \
					../../Classes/SneakyInput/SneakyButton.cpp \
					../../Classes/Enemy.cpp \
					../../Classes/Entities.cpp \
					../../Classes/Level.cpp \
					../../Classes/ToolbarManager.cpp \
					../../Classes/Toolbar.cpp \
					../../Classes/Lifebar.cpp \
					../../Classes/EnemyPuppeteer.cpp \
					../../Classes/PlayerPuppeteer.cpp \
					../../Classes/Puppet.cpp \
					../../Classes/World.cpp \
					../../Classes/UILayer.cpp \
					../../Classes/SpellObject.cpp \
					../../Classes/Bonus.cpp \
					../../Classes/MainMenuScene.cpp \
				
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
