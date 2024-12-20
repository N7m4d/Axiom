#include "HitBackAnimController.h"

#include "HitBackAnim.h"

namespace Axiom
{
	HitBackAnimController::HitBackAnimController(AnimTime& delta)
	{
		mAnim = new HitBackAnim();
		assert(mAnim);
		
		AnimTime maxTime = mAnim->FindMaxTime();
		AnimTime minTime = AnimTime(AnimTime::Duration::ZERO);
		mTimerControl = new TimerController(delta, minTime, maxTime);
		assert(mTimerControl);
	}
}

