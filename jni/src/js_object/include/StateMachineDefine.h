#ifndef _STATE_MACHINE_DEFINE_H
#define _STATE_MACHINE_DEFINE_H

#define STATE_MACHINE_DEFINE(className) \
		private:						\
			StateMachine<className>* pStateMachine; \
		public:							\
			void Loop(ccTime dt,JSObject* obj);	\
			void OnLoop(ccTime dt); \
			void SetStatus(jsval status);\
			jsval GetStatus();

#define NEW_STATE_MACHINE(className) \
		pStateMachine = new StateMachine<className> (this);

#define DELETE_STATE_MACHINE(className) \
		if (pStateMachine) { \
			delete pStateMachine; \
			unschedule( schedule_selector(className::OnLoop));\
		} \


#define STATE_MACHINE_IMPLEMENT(className) \
		void className::OnLoop(ccTime dt) { \
			if (pStateMachine) { \
				pStateMachine->Loop(); \
			 } \
		} \
		void className::Loop(ccTime dt,JSObject* obj) { \
			if (pStateMachine) { \
				pStateMachine->SetHostObj(obj);\
				schedule(schedule_selector(className::OnLoop), dt);\
			}\
		}\
		void className::SetStatus(jsval status)\
		{\
			pStateMachine->SetStatus(status);\
		}\
		jsval className::GetStatus()\
		{\
			return pStateMachine->GetStatus(); \
		}

#endif
