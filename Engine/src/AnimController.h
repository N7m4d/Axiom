#ifndef ANIM_CONTROLLER_H
#define ANIM_CONTROLLER_H

#include "AnimTime.h"
#include "TimerController.h"
#include "Anim.h"

namespace Axiom
{
    class AnimController
    {
    public:
        enum class Name
        {
            Walk,
            Run,
            HitBack,
            HitLeft,
            SideStepLeft,
            Null
        };

        AnimController();
        AnimController(AnimController&) = delete;
        AnimController& operator =(AnimController&) = delete;
        virtual ~AnimController();

        char* GetName() const;
        void SetName(Name name);

        virtual void SetDeltaTime(AnimTime delta);
        virtual AnimTime GetDeltaTime() const;
        virtual void Update() const;

        Name mName;

        Anim* mAnim;
        TimerController* mTimerControl;
        bool mShouldAnimateReverse;
    };
}

#endif // !ANIM_CONTROLLER_H
