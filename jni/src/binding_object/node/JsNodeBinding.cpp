#define TAG "JsNodeBinding"
#include "JsNodeBinding.h"
#include "JsSizeBinding.h"
#include "JsPointBinding.h"
#include "JsRectBinding.h"
#include "JsSchedule.h"
#include "JsScheduleManager.h"
#include "Log.h"
JSObject *JsNodeBinding::obj = NULL;
JSClass JsNodeBinding::clz = { "Node", JSCLASS_HAS_PRIVATE, JS_PropertyStub,
		JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
		JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
		JSCLASS_NO_OPTIONAL_MEMBERS };

JSBool JsNodeBinding::IsClass(JSContext *context, JSObject *obj, jsid id,
		jsval *val) {
	int propId = JSID_TO_INT(id);
	CCNode *pNode = static_cast<CCNode*> (JS_GetPrivate(context, obj));
	if (pNode) {
		JS_SET_RVAL(context, val, BOOLEAN_TO_JSVAL(true));
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsNodeBinding,StopAllActions) {
	if (argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCNode *pNode = static_cast<CCNode*>(JS_GetPrivate(context,thisObj));
		pNode->stopAllActions();
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsNodeBinding,RunAction) {
	if (argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCNode *pNode = static_cast<CCNode*>(JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		JSObject *actionObj;
		JS_ValueToObject(context,args[0],&actionObj);
		CCAction *pAction = static_cast<CCAction*>(JS_GetPrivate(context,actionObj));
		if (pNode && pAction) {
			pNode->runAction(pAction);
		}
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsNodeBinding ,SetAnchorPoint) {
	if (argc == 2) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCNode *pNode = static_cast<CCNode*>(JS_GetPrivate(context,thisObj));
		if(pNode) {
			double x = 0;
			double y = 0;
			jsval *args = JS_ARGV(context, vp);
			JS_ConvertArguments(context,argc,args,"dd",&x,&y);
			pNode->setAnchorPoint(ccp(x, y));
		}
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsNodeBinding ,SetRotation) {
	if (argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCNode *pNode = static_cast<CCNode*>(JS_GetPrivate(context,thisObj));
		if(pNode) {
			double rotation = 0;
			jsval *args = JS_ARGV(context, vp);
			JS_ValueToNumber(context, args[0], &rotation);
			pNode->setRotation(rotation);
		}
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsNodeBinding,SetPosition) {
	if(argc == 2) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCNode *pNode = static_cast<CCNode*>(JS_GetPrivate(context,thisObj));
		if(pNode) {
			jsval *args = JS_ARGV(context, vp);
			double x = 0;
			double y = 0;
			JS_ConvertArguments(context,2,args,"dd",&x,&y);
			pNode->setPosition(x,y);
		}
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsNodeBinding ,GetPosition) {
	if(argc == 0) {
		jsval thisVal = JS_THIS(context,vp);
		if(JSVAL_IS_OBJECT(thisVal) && !JSVAL_IS_NULL(thisVal)) {
			JSObject *thisObj = JS_THIS_OBJECT(context,vp);
			if(thisObj) {
				void *data = JS_GetPrivate(context,thisObj);
				if(data) {
					CCNode *pNode = static_cast<CCNode*>(data);
					if(pNode) {
						CCPoint point = pNode->getPosition();
						CCPoint *pPoint = new CCPoint(point.x,point.y);
						JSObject *newObj = JS_NewObject(context, &JsPointBinding::clz, JsPointBinding::obj, NULL);
						JS_SetPrivate(context,newObj, pPoint);
						JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
					}
				}
			}
		}
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsNodeBinding, SetIsVisible) {
	if(argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCNode *pNode = static_cast<CCNode*>(JS_GetPrivate(context,thisObj));
		if(pNode) {
			jsval *args = JS_ARGV(context, vp);
			JSBool bp;
			JS_ValueToBoolean(context, args[0], &bp);
			pNode->setIsVisible(bp);
		}
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsNodeBinding ,SetScaleX) {
	if (argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCNode *pNode = static_cast<CCNode*>(JS_GetPrivate(context,thisObj));
		if(pNode) {
			double x = 0;
			jsval *args = JS_ARGV(context, vp);
			JS_ValueToNumber(context, args[0], &x);
			pNode->setScaleX(x);
		}
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsNodeBinding, GetScaleY) {
	if (argc == 0) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCNode *pNode = static_cast<CCNode*>(JS_GetPrivate(context,thisObj));
		if(pNode) {
			double y = pNode->getScaleY();
			jsval resultVal;
			JS_NewNumberValue(context, y, &resultVal);
			JS_SET_RVAL(context, vp, resultVal);
		}
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsNodeBinding ,SetScaleY) {
	if (argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCNode *pNode = static_cast<CCNode*>(JS_GetPrivate(context,thisObj));
		if(pNode) {
			double y = 0;
			jsval *args = JS_ARGV(context, vp);
			JS_ValueToNumber(context, args[0], &y);
			pNode->setScaleY(y);
		}
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsNodeBinding, GetScaleX) {
	if (argc == 0) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCNode *pNode = static_cast<CCNode*>(JS_GetPrivate(context,thisObj));
		if(pNode) {
			double x = pNode->getScaleX();
			jsval resultVal;
			JS_NewNumberValue(context, x, &resultVal);
			JS_SET_RVAL(context, vp, resultVal);
		}
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsNodeBinding ,GetContentSize) {
	if (argc == 0) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCNode *pNode = static_cast<CCNode*>(JS_GetPrivate(context,thisObj));
		if(pNode) {
			CCSize *pSize = new CCSize( pNode->getContentSize().width, pNode->getContentSize().height);
			JSObject *newObj = JS_NewObject(context, &JsSizeBinding::clz,
					JsSizeBinding::obj, NULL);
			JS_SetPrivate(context, newObj, pSize);
			JS_SET_RVAL(context, vp, OBJECT_TO_JSVAL(newObj));
		}
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsNodeBinding ,SetContentSize) {
	if (argc == 2) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCNode *pNode = static_cast<CCNode*>(JS_GetPrivate(context,thisObj));
		if(pNode) {
			jsval *args = JS_ARGV(context, vp);
			double w = 0;
			double h = 0;
			JS_ConvertArguments(context,2,args,"dd",&w,&h);
			pNode->setContentSize(CCSizeMake(w, h));
		}
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsNodeBinding,AddChild) {
	JSObject *thisObj = JS_THIS_OBJECT(context,vp);
	CCNode *pNode = static_cast<CCNode*>(JS_GetPrivate(context,thisObj));
	if(pNode) {
		jsval *args = JS_ARGV(context, vp);
		JSObject *childObj;
		JS_ValueToObject(context,args[0],&childObj);
		CCNode *pChild = static_cast<CCNode*>(JS_GetPrivate(context,childObj));
		if(pChild) {
			if(argc == 1) {
				pNode->addChild(pChild);
			} else if(argc == 2) {
				int zOrder = 0;
				JS_ValueToInt32(context,args[1],&zOrder);
				pNode->addChild(pChild,zOrder);
			} else if(argc == 3) {
				int zOrder = 0;
				JS_ValueToInt32(context,args[1],&zOrder);
				int tag = 0;
				JS_ValueToInt32(context,args[2],&tag);
				pNode->addChild(pChild,zOrder,tag);
			}
		}
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsNodeBinding ,RemoveChildByTag) {
	if ( argc == 2) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCNode *pNode = static_cast<CCNode*>(JS_GetPrivate(context,thisObj));
		if(pNode) {
			jsval *args = JS_ARGV(context, vp);
			int zTag = 0;
			JSBool cleanUp = false;
			JS_ConvertArguments(context,2,args,"ib",&zTag,&cleanUp);
			pNode->removeChildByTag(zTag, cleanUp);
		}
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsNodeBinding ,RemoveChild) {
	if(argc == 2) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCNode *pNode = static_cast<CCNode*>(JS_GetPrivate(context,thisObj));
		if(pNode) {
			jsval *args = JS_ARGV(context, vp);
			if(JSVAL_IS_OBJECT(args[0])) {
				JSObject *childObj;
				JS_ValueToObject(context,args[0],&childObj);
				if(childObj) {
					CCNode *pChild = static_cast<CCNode*>(JS_GetPrivate(context,childObj));
					JSBool bp;
					JS_ValueToBoolean(context, args[1], &bp);
					if(pChild) {
						pNode->removeChild(pChild,bp);
					}
				}
			}
		}
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsNodeBinding ,GetChildByTag) {
	if (argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCNode *pNode = static_cast<CCNode*>(JS_GetPrivate(context,thisObj));
		if(pNode) {
			jsval *args = JS_ARGV(context, vp);
			int zTag = 0;
			JS_ConvertArguments(context,1,args,"i",&zTag);
			CCNode *pChild = pNode->getChildByTag(zTag);
			JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
			JS_SetPrivate(context, newObj, pChild);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
		}
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsNodeBinding ,GetChildren) {
	if (argc == 0) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCNode *pNode = static_cast<CCNode*>(JS_GetPrivate(context,thisObj));
		if(pNode) {
			CCArray *pChilds = pNode->getChildren();
			CCObject* pChild = NULL;
			JSObject *arrayObj = JS_NewArrayObject(context, 0, NULL);
			int i = 0;
			JSObject *newObj = NULL;
			jsval newObjVal;
			CCARRAY_FOREACH(pChilds, pChild)
			{	newObj = JS_NewObject(context, &clz,
						obj, NULL);
				JS_SetPrivate(context, newObj, (CCNode*)pChild);
				newObjVal = OBJECT_TO_JSVAL(newObj);
				JS_SetElement(context,arrayObj,i,&newObjVal);
				i++;
			}
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(arrayObj));
		}
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsNodeBinding, GetZOrder) {
	if (argc == 0) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCNode *pNode = static_cast<CCNode*>(JS_GetPrivate(context,thisObj));
		if(pNode) {
			jsval resultVal;
			JS_NewNumberValue(context, pNode->getZOrder(), &resultVal);
			JS_SET_RVAL(context, vp, resultVal);
		}
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsNodeBinding, RemoveFromParentAndCleanup) {
	if (argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCNode *pNode = static_cast<CCNode*>(JS_GetPrivate(context,thisObj));
		if(pNode) {
			jsval *args = JS_ARGV(context, vp);
			JSBool cleanUp = false;
			JS_ConvertArguments(context,1,args,"b",&cleanUp);
			pNode->removeFromParentAndCleanup(cleanUp);
		}
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsNodeBinding ,SetTag) {
	if (argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCNode *pNode = static_cast<CCNode*>(JS_GetPrivate(context,thisObj));
		if(pNode) {
			int zTag = 0;
			jsval *args = JS_ARGV(context, vp);
			JS_ConvertArguments(context,1,args,"i",&zTag);
			pNode->setTag(zTag);
		}
	}
	return JS_TRUE;
}
JS_CLASS_METHOD(JsNodeBinding ,GetTag) {
	if (argc == 0) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCNode *pNode = static_cast<CCNode*>(JS_GetPrivate(context,thisObj));
		if(pNode) {
			jsval resultVal;
			JS_NewNumberValue(context, pNode->getTag(), &resultVal);
			JS_SET_RVAL(context, vp, resultVal);
		}
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsNodeBinding, BoundingBox) {
	if(argc == 0) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCNode *pNode = static_cast<CCNode*>(JS_GetPrivate(context,thisObj));
		CCRect rect = pNode->boundingBox();
		CCRect *pRect = new CCRect(rect.origin.x,rect.origin.y,rect.size.width,rect.size.height);
		JSObject *newObj = JS_NewObject(context, &JsRectBinding::clz, JsRectBinding::obj, NULL);
		JS_SetPrivate(context,newObj, pRect);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsNodeBinding, GetParent) {
	if(argc == 0) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCNode *pNode = static_cast<CCNode*>(JS_GetPrivate(context,thisObj));
		CCNode *pParent = pNode->getParent();
		JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
		JS_SetPrivate(context,newObj, pParent);
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsNodeBinding, Schedule) {
	if (argc == 2) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		jsval *args = JS_ARGV(context, vp);
		JsSchedule *jsSchedule = new JsSchedule();
		jsSchedule->SetScheduleCallback(args[0]);
		double delay = 0;
		JS_ValueToNumber(context, args[1], &delay);
		jsSchedule->SetCallbackData(thisObj);
		int returnId = JsScheduleManager::SharedScheduleManager()->AddSchedule(
				jsSchedule, delay);
		JS_SET_RVAL(context, vp, INT_TO_JSVAL(returnId));
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsNodeBinding, Unschedule) {
	if (argc == 1) {
		jsval *args = JS_ARGV(context, vp);
		int id = 0;
		JS_ValueToInt32(context, args[0], &id);
		JsScheduleManager::SharedScheduleManager()->RemoveSchedule(id);
	}
	return JS_TRUE;
}

JS_CLASS_METHOD(JsNodeBinding, StopAction) {
	if (argc == 1) {
		JSObject *thisObj = JS_THIS_OBJECT(context,vp);
		CCNode *pNode = static_cast<CCNode*>(JS_GetPrivate(context,thisObj));
		jsval *args = JS_ARGV(context, vp);
		JSObject *actionObj;
		JS_ValueToObject(context,args[0],&actionObj);
		CCAction *pAction = static_cast<CCAction*>(JS_GetPrivate(context,actionObj));
		if (pNode && pAction) {
			pNode->stopAction(pAction);
		}
	}
	return JS_TRUE;
}

JSBool JsNodeBinding::Create(JSContext *context, unsigned int argc, jsval *vp) {
	if (argc == 0) {
		CCNode* pNode = CCNode::node();
		if (pNode == NULL) {
			JS_ReportOutOfMemory(context);
			return JS_FALSE;
		}
		if (JS_IsConstructing(context, vp)) {
			JSObject *newObj = JS_NewObject(context, &clz, obj, NULL);
			JS_SetPrivate(context, newObj, pNode);
			JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(newObj));
		} else {
			JSObject *thisObj = JS_THIS_OBJECT(context, vp);
			JS_SetPrivate(context, thisObj, pNode);
		}
	}
	return JS_TRUE;
}

JSObject * JsNodeBinding::BindingOnEngine(JSContext *context, JSObject *global,
		JSObject *parent) {
	JSFunctionSpec methods[] = { JS_FN("stopAction", StopAction, 1,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"unschedule", Unschedule, 1,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"schedule", Schedule, 2,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"getChildren", GetChildren, 0,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"getParent", GetParent, 0,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"stopAllActions", StopAllActions, 0,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"runAction", RunAction, 1,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"setAnchorPoint", SetAnchorPoint, 2,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"setRotation", SetRotation, 1,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"setPosition", SetPosition, 2,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"getPosition", GetPosition, 0,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"setIsVisible", SetIsVisible, 1,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"setScaleX", SetScaleX, 1,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"getScaleX", GetScaleX, 0,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"setScaleY", SetScaleY, 1,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"getScaleY", GetScaleY, 0,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"getContentSize", GetContentSize, 0,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"setContentSize", SetContentSize, 2,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"addChild", AddChild, 1,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"removeChildByTag", RemoveChildByTag, 2,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"removeChild", RemoveChild, 2,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"getChildByTag", GetChildByTag, 1,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"getZOrder", GetZOrder, 0,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"removeFromParentAndCleanup", RemoveFromParentAndCleanup, 2,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"setTag", SetTag, 1,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"getTag", GetTag, 0,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"boundingBox", BoundingBox, 0,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FN(
			"constructor", Create, 0,
			JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE), JS_FS_END };

	JSPropertySpec properties[] = {
			{ "isClass", 0,
					JSPROP_PERMANENT | JSPROP_SHARED | JSPROP_ENUMERATE,
					IsClass, JS_StrictPropertyStub }, { 0 } };

	obj = JS_InitClass(context, global, parent, &clz, Create, 0, properties,
			methods, NULL, NULL);

	return obj;
}

