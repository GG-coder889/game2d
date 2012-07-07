#ifndef _JS_SCHEDULE_MANAGER_H_
#define _JS_SCHEDULE_MANAGER_H_
#include "cocos2d.h"
#include "JsSchedule.h"
using namespace cocos2d;

class JsScheduleManager: public CCObject {

public:
	~JsScheduleManager();
	JsScheduleManager();

	static JsScheduleManager* SharedScheduleManager(void);

	static void PurgeScheduleManager();

	void UnscheduleAllSelector();

	int AddSchedule(JsSchedule * pSchedule, float delay);

	void RemoveSchedule(int pKey);

	bool Init(void);
private:
	CCMutableDictionary<int, JsSchedule*> *pSchedules;
	static JsScheduleManager *s_pSharedScheduleManager;
	static int scheduleId;
};
#endif
