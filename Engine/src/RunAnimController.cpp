#include "RunAnimController.h"
#include "RunAnim.h"

namespace Axiom
{
	RunAnimController::RunAnimController(AnimTime delta)
	{
		// Animation object
		this->mAnim = new RunAnim();
		assert(this->mAnim);

		// TimerController
		AnimTime maxTime = mAnim->FindMaxTime();
		AnimTime minTime = AnimTime(AnimTime::Duration::ZERO);
		this->mTimerControl = new TimerController(delta, minTime, maxTime);
		assert(this->mTimerControl);
	}
}
