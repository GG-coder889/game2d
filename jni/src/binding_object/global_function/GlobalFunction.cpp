#define TAG "GlobalFunction"
#include "GlobalFunction.h"
#include "JavaScriptEngine.h"
#include "cocos2d.h"
#include "JsSchedule.h"
#include "JsScheduleManager.h"
#include "JsColor4BBinding.h"
#include "JsColor3BBinding.h"
#include "ViewAutoScale.h"
using namespace cocos2d;

void GlobalFunction::BindingOnEngine(JSContext *context, JSObject *global) {
	JSFunctionSpec methods[] = { { "require", Include, 1, 0 }, { "random01",
			Random01, 1, 0 }, { "getScaleX", GetScaleX, 0, 0 }, { "getScaleY",
			GetScaleY, 0, 0 }, { "random", Random, 0, 0 },
			{ "abs", Abs, 1, 0 },
			{ "radiansToDegrees", RadiansToDegrees, 1, 0 }, { "ccc4", CCC4, 4,
					0 }, { "ccc3", CCC3, 3, 0 },
			{ "schedule", Schedule, 1, 0 }, { "unschedule", Unschedule, 1, 0 },
			{ "log", Log, 2, 0 }, { "unschedule", Unschedule, 1, 0 }, { 0 } };
	JS_DefineFunctions(context, global, methods);
}

JSBool GlobalFunction::Schedule(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc >= 2) {
		jsval *args = JS_ARGV(context, vp);
		JsSchedule *jsSchedule = new JsSchedule();
		jsSchedule->SetScheduleCallback(args[0]);
		double delay = 0;
		if (argc == 2) {
			JS_ValueToNumber(context, args[1], &delay);
		} else if (argc == 3) {
			JSObject *callObj;
			JS_ValueToObject(context, args[1], &callObj);
			jsSchedule->SetCallbackData(callObj);
			JS_ValueToNumber(context, args[2], &delay);
		}
		int returnId = JsScheduleManager::SharedScheduleManager()->AddSchedule(
				jsSchedule, delay);
		JS_SET_RVAL(context, vp, INT_TO_JSVAL(returnId));
	}
	return JS_TRUE;
}

JSBool GlobalFunction::Log(JSContext *context, unsigned int argc, jsval *vp) {
	if (argc == 2) {
		jsval *args = JS_ARGV(context, vp);
		JSString *tagStr = JS_ValueToString(context, args[0]);
		JSString *contentStr = JS_ValueToString(context, args[1]);
		char *tag = JS_EncodeString(context, tagStr);
		char *content = JS_EncodeString(context, contentStr);
		LogInfo(tag, content);
		JS_free(context, tag);
		JS_free(context, content);
	}
	return JS_TRUE;
}

JSBool GlobalFunction::Unschedule(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		int id = 0;
		JS_ValueToInt32(context, args[0], &id);
		JsScheduleManager::SharedScheduleManager()->RemoveSchedule(id);
	}
	return JS_TRUE;
}

JSBool GlobalFunction::CCC4(JSContext *context, unsigned int argc, jsval *vp) {
	if (argc == 4) {
		int r = 0;
		int g = 0;
		int b = 0;
		int o = 0;
		jsval *args = JS_ARGV(context, vp);
		JS_ConvertArguments(context, argc, args, "iiii", &r, &g, &b, &o);
		ccColor4B *pColor = new ccColor4B();
		pColor->r = r;
		pColor->g = g;
		pColor->b = b;
		pColor->a = o;
		JSObject *newObj = JS_NewObject(context, &JsColor4BBinding::clz,
				JsColor4BBinding::obj, NULL);
		JS_SetPrivate(context, newObj, pColor);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
	}
	return JS_TRUE;
}

JSBool GlobalFunction::CCC3(JSContext *context, unsigned int argc, jsval *vp) {
	if (argc == 3) {
		int r = 0;
		int g = 0;
		int b = 0;
		jsval *args = JS_ARGV(context, vp);
		JS_ConvertArguments(context, argc, args, "iii", &r, &g, &b);
		ccColor3B *pColor = new ccColor3B();
		pColor->r = r;
		pColor->g = g;
		pColor->b = b;
		JSObject *newObj = JS_NewObject(context, &JsColor3BBinding::clz,
				JsColor3BBinding::obj, NULL);
		JS_SetPrivate(context, newObj, pColor);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
	}
	return JS_TRUE;
}

JSBool GlobalFunction::Include(JSContext *context, unsigned int argc, jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		JSString *fileStr = JS_ValueToString(context, args[0]);
		char *fileName = JS_EncodeString(context, fileStr);
		JavaScriptEngine::ShareInstance().RunScript(fileName);
		JS_free(context, fileName);
	}
	return JS_TRUE;
}

JSBool GlobalFunction::Random01(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc == 0) {
		int result = CCRANDOM_0_1();
		JS_SET_RVAL(context, vp, INT_TO_JSVAL(rand()));
	}
	return JS_TRUE;
}

JSBool GlobalFunction::GetScaleY(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc == 0) {
		double result = ViewAutoScale::GetScaleY();
		JS_SET_RVAL(context, vp, DOUBLE_TO_JSVAL(result));
	}
	return JS_TRUE;
}

JSBool GlobalFunction::GetScaleX(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc == 0) {
		double result = ViewAutoScale::GetScaleX();
		JS_SET_RVAL(context, vp, DOUBLE_TO_JSVAL(result));
	}
	return JS_TRUE;
}

JSBool GlobalFunction::Random(JSContext *context, unsigned int argc, jsval *vp) {
	if (argc == 0) {
		JS_SET_RVAL(context, vp, INT_TO_JSVAL(rand()));
	}
	return JS_TRUE;
}


JSBool GlobalFunction::Abs(JSContext *context, unsigned int argc, jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		if (JSVAL_IS_INT(args[0])) {
			int arg = 0;
			JS_ValueToInt32(context, args[0], &arg);
			JS_SET_RVAL(context, vp, INT_TO_JSVAL(abs(arg)));
		}
		if (JSVAL_IS_NUMBER(args[0])) {
			double arg = 0;
			JS_ValueToNumber(context, args[0], &arg);
			JS_SET_RVAL(context, vp, INT_TO_JSVAL(abs(arg)));
		}

	}
	return JS_TRUE;
}

JSBool GlobalFunction::RadiansToDegrees(JSContext *context, unsigned int argc,
		jsval *vp) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		double radians = 0;
		JS_ValueToNumber(context, args[0], &radians);
		double result = CC_RADIANS_TO_DEGREES(radians);
		JS_SET_RVAL(context, vp, result);
	}
	return JS_TRUE;
}
