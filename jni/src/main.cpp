#include "AppDelegate.h"
#include "cocos2d.h"
#include "JavaScriptEngine.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include "ViewAutoScale.h"
#include "Log.h"
using namespace cocos2d;

#define TAG "main"
extern "C" {

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
	JniHelper::setJavaVM(vm);
	return JNI_VERSION_1_4;
}

void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv* env,
		jobject thiz, jint w, jint h) {
	if (!cocos2d::CCDirector::sharedDirector()->getOpenGLView()) {
		cocos2d::CCEGLView *view = &cocos2d::CCEGLView::sharedOpenGLView();
		view->setFrameWidthAndHeight(w, h);
		cocos2d::CCDirector::sharedDirector()->setOpenGLView(view);
		cocos2d::CCDirector::sharedDirector()->setDisplayFPS(true);
		CCDirector::sharedDirector()->setAnimationInterval(1.0 / 60);
		AppDelegate *pAppDelegate = new AppDelegate();
		cocos2d::CCApplication::sharedApplication().run();
	} else {
		cocos2d::CCTextureCache::reloadAllTextures();
		cocos2d::CCDirector::sharedDirector()->setGLDefaultValues();
	}
}
}
