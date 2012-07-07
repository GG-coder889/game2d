#ifndef _THREAD_H
#define _THREAD_H
#include "pthread.h"
class GCThread {
private:
	static bool isStop;
private:
	static void *WrokFunc(void *args);
public:
	static void Start();
	static void Stop();

	static pthread_t gcThread;
};
#endif
