#ifndef _IMAGE_RESOURCE_CACHE_H_
#define _IMAGE_RESOURCE_CACHE_H_
#include "cocos2d.h"
using namespace cocos2d;

class ImageResourceCache: public CCObject {

public:
	~ImageResourceCache();
	ImageResourceCache();

	static ImageResourceCache* SharedImageResourceCache(void);

	static void PurgeImageResourceCache(void);

	bool AddImage(const char *pKey, const char * pFileName);

	void RemoveImage(const char* pKey);

	CCTexture2D* GetImage(const char* pKey);

	bool Init(void);
private:
	CCMutableDictionary<std::string, CCString*> *pImages;
	static ImageResourceCache *s_pSharedImageResourcesCache;
};
#endif
