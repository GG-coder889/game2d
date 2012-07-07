#ifndef _JS_MENU_ITEM_IMAGE_H
#define _JS_MENU_ITEM_IMAGE_H
#include "jsapi.h"
#include "cocos2d.h"
using namespace cocos2d;
class JsMenuItemImage: public CCMenuItemImage {
public:
	static JsMenuItemImage * ItemFromNormalImage(jsval jsCallback,
			const char * normalImage, const char * selectedIamge);
	static JsMenuItemImage * ItemFromNormalImage(const char * normalImage,
			const char * selectedIamge);
	void MenuItemCallback(CCObject * pSender);
	jsval GetJsMenuItemCallback();
	void SetJsMenuItemCallback(jsval jsCallback);
private:
	jsval jsMenuItemCallback;
};
#endif
