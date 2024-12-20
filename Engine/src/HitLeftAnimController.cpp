#include "HitLeftAnimController.h"
#include "HitLeftAnim.h"

namespace Axiom
{
	HitLeftAnimController::HitLeftAnimController(AnimTime delta)
	{
		// Animation object
		this->mAnim = new HitLeftAnim();
		assert(this->mAnim);

		// TimerController
		AnimTime maxTime = mAnim->FindMaxTime();
		AnimTime minTime = AnimTime(AnimTime::Duration::ZERO);
		this->mTimerControl = new TimerController(delta, minTime, maxTime);
		assert(this->mTimerControl);
	}
}
