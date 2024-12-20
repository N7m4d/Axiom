#include "SideStepLeftAnimController.h"

#include "SideStepLeftAnim.h"
#include "SideStepLeftClip.h"

namespace Axiom
{
    SideStepLeftAnimController::SideStepLeftAnimController(AnimTime delta)
    {
        // Animation object
        mAnim = new SideStepLeftAnim();
        assert(mAnim);

        // TimerController
        AnimTime maxTime = mAnim->FindMaxTime();
        AnimTime minTime = AnimTime(AnimTime::Duration::ZERO);
        mTimerControl = new TimerController(delta, minTime, maxTime);
        assert(mTimerControl);
    }
}
