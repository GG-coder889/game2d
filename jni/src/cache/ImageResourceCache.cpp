#include "ImageResourceCache.h"

ImageResourceCache* ImageResourceCache::s_pSharedImageResourcesCache = NULL;

ImageResourceCache* ImageResourceCache::SharedImageResourceCache(void) {
	if (!s_pSharedImageResourcesCache) {
		s_pSharedImageResourcesCache = new ImageResourceCache();
		s_pSharedImageResourcesCache->Init();
	}

	return s_pSharedImageResourcesCache;
}

void ImageResourceCache::PurgeImageResourceCache(void) {
	CC_SAFE_RELEASE_NULL( s_pSharedImageResourcesCache);
}

bool ImageResourceCache::Init() {
	pImages = new CCMutableDictionary<std::string, CCString*> ();
	return true;
}

ImageResourceCache::ImageResourceCache() :
	pImages(NULL) {
}

ImageResourceCache::~ImageResourceCache() {
	CC_SAFE_RELEASE( pImages);
}

bool ImageResourceCache::AddImage(const char *pKey, const char * pFileName) {
	if (!pKey && !pFileName) {
		return false;
	}
	std::string key = std::string(pKey);
	CCString *pFile = pImages->objectForKey(key);
	if (!pFile) {
		CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(
				pFileName);
		if (pTexture) {
			CCString *pFileString = new CCString(pFileName);
			pImages->setObject(pFileString, key);
			pFileString->release();
			return true;
		}
	}
	return false;
}

void ImageResourceCache::RemoveImage(const char* pKey) {
	if (!pKey) {
		return;
	}
	std::string key = std::string(pKey);
	CCString *pFile = pImages->objectForKey(key);
	if (pFile) {
		const char *pFileName = pFile->toStdString().c_str();
		CCTextureCache::sharedTextureCache()->removeTextureForKey(pFileName);
		pImages->removeObjectForKey(key);
	}
}

CCTexture2D* ImageResourceCache::GetImage(const char* pKey) {
	if (!pKey) {
		return NULL;
	}
	std::string key = std::string(pKey);
	CCString *pFile = pImages->objectForKey(key);
	if (pFile) {
		const char *pFileName = pFile->toStdString().c_str();
		return CCTextureCache::sharedTextureCache()->addImage(pFileName);
	}
	return NULL;

}
