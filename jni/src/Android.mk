LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libjsengine

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../libs/ \
					$(LOCAL_PATH)/../libs/spidermonkey/include \
		    		$(LOCAL_PATH)/../libs/cocos2dx \
                    $(LOCAL_PATH)/../libs/cocos2dx/platform \
                    $(LOCAL_PATH)/../libs/cocos2dx/platform/third_party/android/modules/libcurl/include \
                    $(LOCAL_PATH)/../libs/cocos2dx/include \
                    $(LOCAL_PATH)/../libs/CocosDenshion/include \
                    $(LOCAL_PATH)/../libs/nspr/include \
				    $(LOCAL_PATH)/utility			\
				    $(LOCAL_PATH)/cache 			\
				    $(LOCAL_PATH)/binding_object	\
				    $(LOCAL_PATH)/binding_object/fsm \
				    $(LOCAL_PATH)/binding_object/animation	\
				    $(LOCAL_PATH)/binding_object/action	\
				    $(LOCAL_PATH)/binding_object/action/actionEase	\
				    $(LOCAL_PATH)/binding_object/box2d/dynamics/	\
				    $(LOCAL_PATH)/binding_object/box2d/collision/shape/		\
				    $(LOCAL_PATH)/binding_object/callback	\
				    $(LOCAL_PATH)/binding_object/menu	\
				    $(LOCAL_PATH)/binding_object/label	\
				    $(LOCAL_PATH)/binding_object/node	\
				    $(LOCAL_PATH)/binding_object/layer	\
				    $(LOCAL_PATH)/binding_object/scene	\
				    $(LOCAL_PATH)/binding_object/sprite	\
				    $(LOCAL_PATH)/binding_object/texture \
				    $(LOCAL_PATH)/binding_object/include	\
				    $(LOCAL_PATH)/binding_object/map	\
				    $(LOCAL_PATH)/binding_object/misc	\
				    $(LOCAL_PATH)/binding_object/utility	\
				    $(LOCAL_PATH)/binding_object/particle_system	\
				    $(LOCAL_PATH)/binding_object/global_function \
				    $(LOCAL_PATH)/binding_object/geometry \
				    $(LOCAL_PATH)/binding_object/audio \
				    $(LOCAL_PATH)/binding_object/support\
				    $(LOCAL_PATH)/binding_object/http\
				    $(LOCAL_PATH)/binding_object/type\
				    $(LOCAL_PATH)/js_object	\
				    $(LOCAL_PATH)/js_object/include	\
				    $(LOCAL_PATH)/js_object/schedule \
				    $(LOCAL_PATH)/js_object/callback \
				    $(LOCAL_PATH)/js_object/layer	\
				    $(LOCAL_PATH)/js_object/label	\
				    $(LOCAL_PATH)/js_object/sprite	\
				    $(LOCAL_PATH)/js_object/menu	\
				    $(LOCAL_PATH)/js_object/scene	\
				    $(LOCAL_PATH)/js_object/geometry	\
				    $(LOCAL_PATH)/js_object/support	\
				    $(LOCAL_PATH)/js_object/http	\
				    $(LOCAL_PATH)/extension \
				    $(LOCAL_PATH)/fsm \
				    $(LOCAL_PATH)/
	
LOCAL_SRC_FILES:= main.cpp \
				  AppDelegate.cpp \
				  extension/JavaScriptEngine.cpp \
				  cache/ImageResourceCache.cpp\
				  utility/ViewAutoScale.cpp\
				  binding_object/JsDirectorBinding.cpp	\
				  binding_object/utility/JsLogBinding.cpp	\
				  binding_object/audio/JsSimpleAudioEngineBinding.cpp	\
				  binding_object/animation/JsAnimationBinding.cpp \
				  binding_object/action/JsMoveByBinding.cpp\
				  binding_object/action/JsRepeatForeverBinding.cpp \
				  binding_object/action/JsRepeatBinding.cpp \
				  binding_object/action/JsSpawnBinding.cpp \
				  binding_object/action/JsProgressToBinding.cpp\
				  binding_object/action/JsRotateToBinding.cpp \
				  binding_object/action/JsRotateByBinding.cpp \
				  binding_object/action/JsSequenceBinding.cpp \
				  binding_object/action/JsFadeOutBinding.cpp\
				  binding_object/action/JsFadeInBinding.cpp \
				  binding_object/action/JsDelayTimeBinding.cpp \
				  binding_object/action/JsEaseOutBinding.cpp \
				  binding_object/action/JsMoveToBinding.cpp \
				  binding_object/action/JsBezierToBinding.cpp \
				  binding_object/action/JsBezierByBinding.cpp \
				  binding_object/action/JsSpeedBinding.cpp\
				  binding_object/action/actionEase/JsEaseElasticOutBinding.cpp\
				  binding_object/animation/JsAnimateBinding.cpp \
				  binding_object/animation/JsAnimationCacheBinding.cpp \
				  binding_object/node/JsNodeBinding.cpp	\
				  binding_object/label/JsLabelTTFBinding.cpp \
				  binding_object/label/JsLabelBMFontBinding.cpp \
				  binding_object/sprite/JsSpriteBinding.cpp	\
				  binding_object/sprite/JsSpriteFrameBinding.cpp\
				  binding_object/sprite/JsSpriteBatchNodeBinding.cpp\
				  binding_object/sprite/JsSpriteFrameCacheBinding.cpp\
				  binding_object/texture/JsTexture2DBinding.cpp	\
				  binding_object/texture/JsTextureCacheBinding.cpp\
				  binding_object/geometry/JsPointBinding.cpp	\
				  binding_object/geometry/JsSizeBinding.cpp	\
				  binding_object/geometry/JsRectBinding.cpp	\
				  binding_object/scene/JsSceneBinding.cpp	\
				  binding_object/type/JsTransitionSceneBinding.cpp \
				  binding_object/type/JsTextAlignmentBinding.cpp \
				  binding_object/scene/JsSceneManagerBinding.cpp\
				  binding_object/layer/JsLayerBinding.cpp	\
				  binding_object/layer/JsLayerColorBinding.cpp \
				  binding_object/layer/JsGLESDebugDrawBinding.cpp\
				  binding_object/layer/JsBox2dDebugLayerBinding.cpp\
				  binding_object/callback/JsCallFuncBinding.cpp\
				  binding_object/global_function/GlobalFunction.cpp	\
				  binding_object/misc/JsProgressTimerBinding.cpp \
				  binding_object/particle_system/JsParticleSystemQuadBinding.cpp\
				  binding_object/menu/JsMenuBinding.cpp  \
				  binding_object/menu/JsMenuItemImageBinding.cpp \
				  binding_object/menu/JsMenuItemFontBinding.cpp \
				  binding_object/map/JsTMXTiledMapBinding.cpp \
				  binding_object/map/JsTMXLayerBinding.cpp \
				  binding_object/map/JsStringDictionaryBinding.cpp\
				  binding_object/map/JsTMXObjectGroupBinding.cpp\
				  binding_object/support/JsColor4BBinding.cpp\
				  binding_object/support/JsColor3BBinding.cpp\
				  binding_object/support/JsTouchBinding.cpp\
				  binding_object/box2d/dynamics/Jsb2WorldBinding.cpp\
				  binding_object/box2d/dynamics/Jsb2BodyBinding.cpp \
				  binding_object/box2d/dynamics/Jsb2BodyDefBinding.cpp \
				  binding_object/box2d/dynamics/Jsb2FixtureDefBinding.cpp \
				  binding_object/box2d/collision/shape/Jsb2PolygonShapeBinding.cpp \
				  binding_object/box2d/collision/shape/Jsb2CircleShapeBinding.cpp \
				  binding_object/box2d/collision/shape/Jsb2EdgeShapeBinding.cpp \
				  js_object/schedule/JsScheduleManager.cpp	\
				  js_object/schedule/JsSchedule.cpp	\
				  js_object/callback/JsCallback.cpp \
				  js_object/scene/JsScene.cpp \
				  js_object/scene/JsSceneManager.cpp \
				  js_object/layer/JsBox2dDebugLayer.cpp \
				  js_object/layer/JsGLESDebugDraw.cpp \
				  js_object/layer/JsLayer.cpp \
				  js_object/sprite/JsSprite.cpp \
				  js_object/sprite/JsSkillSprite.cpp \
				  js_object/menu/JsMenuItemImage.cpp \
				  js_object/menu/JsMenuItemFont.cpp \
			  	  
LOCAL_LDLIBS := -llog -lz
LOCAL_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_STATIC_LIBRARIES += box2d_static
LOCAL_STATIC_LIBRARIES += png_static_prebuilt
LOCAL_STATIC_LIBRARIES += xml2_static_prebuilt
LOCAL_STATIC_LIBRARIES += jpeg_static_prebuilt
LOCAL_STATIC_LIBRARIES += curl_static_prebuilt
LOCAL_STATIC_LIBRARIES += nspr_static_prebuilt
LOCAL_WHOLE_STATIC_LIBRARIES := spidermonkey_static_prebuilt
LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static


            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,spidermonkey)
$(call import-module,nspr)
$(call import-module,cocos2dx/platform/third_party/android/modules/libcurl)
$(call import-module,cocos2dx/platform/third_party/android/modules/libpng)
$(call import-module,cocos2dx/platform/third_party/android/modules/libxml2)
$(call import-module,cocos2dx/platform/third_party/android/modules/libjpeg)
