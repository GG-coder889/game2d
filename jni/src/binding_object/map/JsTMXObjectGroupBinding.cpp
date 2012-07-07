#define TAG "JsTMXObjectGroupBinding"
#include "JsTMXObjectGroupBinding.h"
#include "JsStringDictionaryBinding.h"

JSClass JsTMXObjectGroupBinding::clz = { "TMXObjectGroup", JSCLASS_HAS_PRIVATE,
		JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
		JS_StrictPropertyStub, JS_EnumerateStub, JS_ResolveStub,
		JS_ConvertStub, JS_FinalizeStub, JSCLASS_NO_OPTIONAL_MEMBERS };
JSObject *JsTMXObjectGroupBinding::obj = NULL;

JS_CLASS_METHOD(JsTMXObjectGroupBinding,GetObjects) {
	if (argc == 0) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCTMXObjectGroup *pObjectGroup = static_cast<CCTMXObjectGroup*>(JS_GetPrivate(context,thisObj));
		CCMutableArray<CCStringToStringDictionary*> *pObjects =
		pObjectGroup->getObjects();
		CCMutableArray<CCStringToStringDictionary*>::CCMutableArrayIterator it;
		CCStringToStringDictionary* pDict;
		JSObject *arrayObj = JS_NewArrayObject(context, 0, NULL);
		int i = 0;
		JSObject *newObj = NULL;
		jsval newObjVal;
		for (it = pObjects->begin(); it != pObjects->end(); it++) {
			pDict = (*it);
			if (!pDict) {
				break;
			} else {
				newObj = JS_NewObject(context, &JsStringDictionaryBinding::clz,
						JsStringDictionaryBinding::obj, NULL);
				JS_SetPrivate(context, newObj, pDict);
				newObjVal = OBJECT_TO_JSVAL(newObj);
				JS_SetElement(context,arrayObj,i,&newObjVal);
				i++;
			}
		}
		JS_SET_RVAL(context, vp, OBJECT_TO_JSVAL(arrayObj));
	}
	return JS_TRUE;
}

JSBool JsTMXObjectGroupBinding::Create(JSContext *context, unsigned int argc,
		jsval *vp) {
	return JS_FALSE;
}

JSObject * JsTMXObjectGroupBinding::BindingOnEngine(JSContext *context,
		JSObject *global, JSObject *parent) {
	JSFunctionSpec methods[] = { { "getObjects", GetObjects, 0,
			JSPROP_PERMANENT | JSPROP_SHARED }, JS_FS_END };

	obj = JS_InitClass(context, global, parent, &clz, Create, 0, NULL, methods,
			NULL, NULL);
	return obj;
}
