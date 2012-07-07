#ifndef _JS_SCHEDULE_H
#define _JS_SCHEDULE_H
#include "jsapi.h"
#include "cocos2d.h"
#include "Macros.h"
#include "JavaScriptEngine.h"
using namespace cocos2d;

class JsSchedule: public CCObject {
private:
	jsval jsScheduleCallback;
	JSObject *callbackValue;
	int id;
public:
	void SetScheduleCallback(jsval jsCallback);
	void SetCallbackData(JSObject *callbackValue);
	void SetId(int id) {
		this->id = id;
	}
	int GetId() {
		return this->id;
	}
	JsSchedule();
	~JsSchedule();
	void update(ccTime dt);
};

#endif
