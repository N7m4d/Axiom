#include "WalkAnimController.h"
#include "WalkAnim.h"
#include "RunClip.h"

namespace Axiom
{
	WalkAnimController::WalkAnimController(AnimTime delta)
	{
		// Animation object
		this->mAnim = new WalkAnim();
		assert(this->mAnim);

		// TimerController
		AnimTime maxTime = mAnim->FindMaxTime();
		AnimTime minTime = AnimTime(AnimTime::Duration::ZERO);
		this->mTimerControl = new TimerController(delta, minTime, maxTime);
		assert(this->mTimerControl);
	}

	void WalkAnimController::ChangeAnimation(AnimController::Name name)
	{
		delete mAnim->mClip;

		AnimTime delta = mTimerControl->GetDeltaTime();
		delete mTimerControl;

		AnimTime minTime = AnimTime(AnimTime::Duration::ZERO);

		switch(name)
		{
		case Name::Run:
		{
			mAnim->mClip = new RunClip(NUM_BONES);
			mTimerControl = new TimerController(delta, minTime, mAnim->mClip->GetTotalTime());
		}
		break;
		}
		
	}
}
