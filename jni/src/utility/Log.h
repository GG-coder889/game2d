#ifndef _LOG_H_
#define _LOG_H_
#include <android/log.h>

#define LogInfo(...)  __android_log_print(ANDROID_LOG_INFO, __VA_ARGS__)
#define LogError(...)  __android_log_print(ANDROID_LOG_ERROR,__VA_ARGS__)
#endif
