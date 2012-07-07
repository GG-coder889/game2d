#define TAG "JsSceneManager"
#include "JsSceneManager.h"
#include "Log.h"
void JsSceneManager::ChangeTo(TransitionSceneEnum transition, ccTime t,
		CCScene *pScene) {
	if (pScene) {
		if (CCDirector::sharedDirector()->getRunningScene()) {
			pScene = CreateTransitionScene(transition, t, pScene);
			CCDirector::sharedDirector()->replaceScene(pScene);
		}
	}
}

void JsSceneManager::ChangeTo(CCScene *pScene) {
	if (pScene) {
		if (CCDirector::sharedDirector()->getRunningScene()) {
			CCDirector::sharedDirector()->replaceScene(pScene);
		}
	}
}

CCScene * JsSceneManager::CreateTransitionScene(TransitionSceneEnum transition,
		ccTime t, CCScene *pScene) {

	switch (transition) {
	case RotoZoom:
		pScene = CCTransitionRotoZoom::transitionWithDuration(t, pScene);
		break;
	case SceneOriented:
		pScene = CCTransitionSceneOriented::transitionWithDuration(t, pScene,
				kOrientationUpOver);
		break;
	case ShrinkGrow:
		pScene = CCTransitionShrinkGrow::transitionWithDuration(t, pScene);
		break;
	case JumpZoom:
		pScene = CCTransitionJumpZoom::transitionWithDuration(t, pScene);
		break;
	case MoveInL:
		pScene = CCTransitionMoveInL::transitionWithDuration(t, pScene);
		break;
	case MoveInR:
		pScene = CCTransitionMoveInR::transitionWithDuration(t, pScene);
		break;
	case MoveInT:
		pScene = CCTransitionMoveInT::transitionWithDuration(t, pScene);
		break;
	case MoveInB:
		pScene = CCTransitionMoveInB::transitionWithDuration(t, pScene);
		break;
	case SlideInL:
		pScene = CCTransitionSlideInL::transitionWithDuration(t, pScene);
		break;
	case SlideInR:
		pScene = CCTransitionSlideInR::transitionWithDuration(t, pScene);
		break;
	case SlideInT:
		pScene = CCTransitionSlideInT::transitionWithDuration(t, pScene);
		break;
	case SlideInB:
		pScene = CCTransitionSlideInB::transitionWithDuration(t, pScene);
		break;
	case FlipY:
		pScene = CCTransitionFlipY::transitionWithDuration(t, pScene);
		break;
	case FlipX:
		pScene = CCTransitionFlipX::transitionWithDuration(t, pScene);
		break;
	case FlipAngular:
		pScene = CCTransitionFlipAngular::transitionWithDuration(t, pScene);
		break;
	case ZoomFlipY:
		pScene = CCTransitionZoomFlipY::transitionWithDuration(t, pScene);
		break;
	case ZoomFlipX:
		pScene = CCTransitionZoomFlipX::transitionWithDuration(t, pScene);
		break;
	case ZoomFlipAngular:
		pScene = CCTransitionZoomFlipAngular::transitionWithDuration(t, pScene);
		break;
	case Fade:
		pScene = CCTransitionFade::transitionWithDuration(t, pScene);
		break;
	case CrossFade:
		pScene = CCTransitionCrossFade::transitionWithDuration(t, pScene);
		break;
	case FadeUp:
		pScene = CCTransitionFadeUp::transitionWithDuration(t, pScene);
		break;
	case FadeTR:
		pScene = CCTransitionFadeTR::transitionWithDuration(t, pScene);
		break;
	case FadeBL:
		pScene = CCTransitionFadeBL::transitionWithDuration(t, pScene);
		break;
	case FadeDown:
		pScene = CCTransitionFadeDown::transitionWithDuration(t, pScene);
		break;
	case SplitCols:
		pScene = CCTransitionSplitCols::transitionWithDuration(t, pScene);
		break;
	case SplitRows:
		pScene = CCTransitionSplitRows::transitionWithDuration(t, pScene);
		break;
	default:
		break;
	}
	return pScene;
}
