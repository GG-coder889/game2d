#define TAG "JsHttpRequest"
#include "JsHttpRequest.h"
#include "Log.h"

string JsHttpRequest::buffer;
static char errorBuffer[CURL_ERROR_SIZE];

JsHttpRequest* JsHttpRequest::ShareJsHttpRequest() {
	static JsHttpRequest globalHttpRequest;
	return &globalHttpRequest;
}

int JsHttpRequest::Writer(char *data, size_t size, size_t nmemb,
		string *writerData) {
	size_t returnLen = 0;
	if (writerData) {
		returnLen = size * nmemb;
		writerData->append(data, returnLen);
	}
	return returnLen;
}

JsHttpRequest::JsHttpRequest(void) {

	CURLcode code = curl_global_init(CURL_GLOBAL_ALL);
	if (code != CURLE_OK) {
		LogInfo(TAG, "curl_init failed, error code is: %d", code);
	}
}

JsHttpRequest::~JsHttpRequest(void) {
	curl_global_cleanup();
}

string JsHttpRequest::Post(const string& url, const string& content) const {
	buffer = "";
	CURL *curl = curl_easy_init();
	if (curl == NULL) {
		LogInfo(TAG, "curl_init failed");
	}

	SetCurlopt(curl, url);
	curl_easy_setopt(curl, CURLOPT_POST, 1);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, content.c_str());

	CURLcode code = curl_easy_perform(curl);
	if (code != CURLE_OK) {
		LogInfo(TAG, "curl_easy_perform failed, error code is: %d", code);
	}
	curl_easy_cleanup(curl);

	return buffer;
}
string JsHttpRequest::Get(const string& url) const {
	buffer = "";
	CURL *curl = curl_easy_init();
	if (curl == NULL) {
		LogInfo(TAG, "curl_init failed");
	}
	SetCurlopt(curl, url);
	CURLcode code = curl_easy_perform(curl);
	if (code != CURLE_OK) {
		LogInfo(TAG, "curl_easy_perform failed, error code is: %d", code);
	}
	curl_easy_cleanup(curl);
	return buffer;
}

void JsHttpRequest::SetCurlopt(CURL *curl, const string& url) const {
	curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
	curl_easy_setopt(curl, CURLOPT_HEADER, 0);
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, DEFAULTTIMEOUT);
	//curl_easy_setopt(curl, CURLOPT_VERBOSE, true);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, JsHttpRequest::Writer);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

}
