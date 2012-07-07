#define TAG "AppDelegate"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "Log.h"
#include "GCThread.h"
#include "JavaScriptEngine.h"
using namespace CocosDenshion;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() {
	LogInfo(TAG, "AppDelegate");

}

bool AppDelegate::initInstance() {
	return true;
}

bool AppDelegate::applicationDidFinishLaunching() {
	JavaScriptEngine::ShareInstance().Start();
	return true;
}

void AppDelegate::applicationDidEnterBackground() {
	CCDirector::sharedDirector()->pause();
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void AppDelegate::applicationWillEnterForeground() {
	CCDirector::sharedDirector()->resume();
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

