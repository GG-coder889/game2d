#ifndef _JS_MENI_ITEM_FONT_H
#define _JS_MENI_ITEM_FONT_H
#include "jsapi.h"
#include "cocos2d.h"
using namespace cocos2d;
class JsMenuItemFont: public CCMenuItemFont {
public:
	static JsMenuItemFont
	* ItemFromString(jsval jsCallback, const char * title);
	static JsMenuItemFont * ItemFromString(const char * title);
	void MenuItemCallback(CCObject * pSender);
	jsval GetJsMenuItemCallback();
	void SetJsMenuItemCallback(jsval jsCallback);
private:
	jsval jsMenuItemCallback;
};
#endif
