#ifndef _STATE_MACHINE_H
#define _STATE_MACHINE_H
#include "jsapi.h"
#include "cocos2d.h"
#include "Log.h"
#include "JavaScriptEngine.h"
template<class entityType>
class StateMachine {
private:
	entityType* pOwner;
	jsval status;
	JSObject* hostObj;
public:
	StateMachine(entityType* owner) :
		pOwner(owner), hostObj(NULL), status(JSVAL_NULL) {
	}

	~StateMachine() {
		JS_RemoveObjectRoot(JavaScriptEngine::ShareInstance().ShareContext(),
				&hostObj);
	}

	void Loop() {
		if (status != JSVAL_NULL) {
			jsval rVal;
			JSContext *context =
					JavaScriptEngine::ShareInstance().ShareContext();
			JS_CallFunctionValue(context, hostObj, status, 0, NULL, &rVal);
			status = JSVAL_NULL;
			if (!JSVAL_IS_VOID(rVal) && JSVAL_IS_OBJECT(rVal)) {
				status = rVal;
			}
		}

	}

	jsval GetStatus() {
		return status;
	}

	void SetStatus(jsval status) {
		this->status = status;
	}

	void SetHostObj(JSObject* obj) {
		hostObj = obj;
		JS_AddObjectRoot(JavaScriptEngine::ShareInstance().ShareContext(),
				&hostObj);
	}
};
#endif
