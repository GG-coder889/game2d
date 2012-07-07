#include "GCThread.h"
#include "JavaScriptEngine.h"
#include "Log.h"
bool GCThread::isStop = false;
pthread_t GCThread::gcThread = NULL;

void *GCThread::WrokFunc(void *args) {
	while (!isStop) {
		JSContext *context = static_cast<JSContext *> (args);
		if (context == NULL) {
			LogInfo("GCThread", "context is empty!!!!!!!!");
		}
		JS_MaybeGC(context);
		sleep(1);
	}
	return NULL;
}

void GCThread::Start() {
	static bool isFirstRun = true;
	if (!isStop && isFirstRun) {
		JSContext *context = JavaScriptEngine::ShareInstance().ShareContext();
		pthread_create(&gcThread, NULL, WrokFunc, context);
		isFirstRun = false;
	}
}

void GCThread::Stop() {
	isStop = true;
}
