#define TAG "JsScheduleManager"
#include "JsScheduleManager.h"
#include "Log.h"
JsScheduleManager *JsScheduleManager::s_pSharedScheduleManager = NULL;
int JsScheduleManager::scheduleId = 0;

JsScheduleManager::~JsScheduleManager() {
	UnscheduleAllSelector();
	CC_SAFE_RELEASE( pSchedules);
}

JsScheduleManager::JsScheduleManager() :
	pSchedules(NULL) {
}

JsScheduleManager* JsScheduleManager::SharedScheduleManager(void) {
	if (!s_pSharedScheduleManager) {
		s_pSharedScheduleManager = new JsScheduleManager();
		s_pSharedScheduleManager->Init();
	}

	return s_pSharedScheduleManager;
}

bool JsScheduleManager::Init() {
	pSchedules = new CCMutableDictionary<int, JsSchedule*> ();
	return true;
}

void JsScheduleManager::PurgeScheduleManager(void) {
	CC_SAFE_RELEASE_NULL( s_pSharedScheduleManager);
}

int JsScheduleManager::AddSchedule(JsSchedule * pSchedule, float delay) {
	scheduleId++;
	pSchedules->setObject(pSchedule, scheduleId);
	pSchedule->SetId(scheduleId);
	CCScheduler::sharedScheduler()->scheduleSelector(
			schedule_selector(JsSchedule::update), pSchedule, delay, false);
	pSchedule->release();
	return scheduleId;
}

void JsScheduleManager::UnscheduleAllSelector() {

	pSchedules->begin();
	int key = 0;
	JsSchedule* jsSchedule = NULL;
	while ((jsSchedule = pSchedules->next(&key))) {
		CCScheduler::sharedScheduler()->unscheduleSelector(
				schedule_selector(JsSchedule::update), jsSchedule);
		pSchedules->removeObjectForKey(key);
	}
	pSchedules->end();

}

void JsScheduleManager::RemoveSchedule(int pKey) {
	JsSchedule* jsSchedule = pSchedules->objectForKey(pKey);
	if (jsSchedule) {
		CCScheduler::sharedScheduler()->unscheduleSelector(
				schedule_selector(JsSchedule::update), jsSchedule);
		pSchedules->removeObjectForKey(pKey);
	}
}

