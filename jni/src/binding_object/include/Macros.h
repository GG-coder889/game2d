#ifndef _JS_MACROS_H
#define _JS_MACROS_H

#define JS_METHOD(methodName) JSBool methodName(JSContext *context, unsigned int argc, jsval *vp)
#define JS_CLASS_METHOD(className,methodName) JSBool className::methodName(JSContext *context, unsigned int argc, jsval *vp)
#define JS_GET_PROPERTY(methodName) JSBool Get##methodName(JSContext *context, JSObject *obj, jsid id,\
			jsval *vp)
#define JS_SET_PROPERTY(methodName) JSBool Set##methodName(JSContext *context, JSObject *obj, jsid id, \
			JSBool strict, jsval *vp)
#define JS_CLASS_GET_PROPERTY(className,methodName) JSBool className::Get##methodName(JSContext *context, JSObject *obj, jsid id,\
			jsval *vp)
#define JS_CLASS_SET_PROPERTY(className,methodName) JSBool className::Set##methodName(JSContext *context, JSObject *obj, jsid id, \
			JSBool strict, jsval *vp)
#endif
