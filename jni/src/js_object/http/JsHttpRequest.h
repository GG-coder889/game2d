#ifndef _JS_HTTPREQUEST_H
#define _JS_HTTPREQUEST_H
#include "curl/curl.h"
#include <string>
using namespace std;
class JsHttpRequest {
public:
	static JsHttpRequest* ShareJsHttpRequest();
public:
	string Post(const string& url, const string& content) const;
	string Get(const string& url) const;
protected:
	JsHttpRequest(void);
	~JsHttpRequest(void);
	static int Writer(char *data, size_t size, size_t nmemb,
			std::string *writerData);
private:
	inline void SetCurlopt(CURL *curl, const string& url) const;
private:
	static const int DEFAULTTIMEOUT = 300;
	static string buffer;
};
#endif
