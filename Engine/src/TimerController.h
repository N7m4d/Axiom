#ifndef TIMER_CONTROLLER_H
#define TIMER_CONTROLLER_H

#include "AnimTimer.h"

namespace Axiom
{
    class TimerController
    {
    public:
        TimerController(AnimTime& delta, AnimTime& min, AnimTime& max);

        TimerController() = delete;
        TimerController(const TimerController&) = delete;
        TimerController& operator =(const TimerController&) = delete;
        ~TimerController() = default;

        void Update();

        void SetCurrTime(const AnimTime& time);
        AnimTime GetCurrTime() const;

        void SetDeltaTime(const AnimTime& time);
        AnimTime GetDeltaTime() const;

        void SetMaxTime(const AnimTime& time);
        AnimTime GetMaxTime() const;

        void SetMinTime(const AnimTime& time);
        AnimTime GetMinTime() const;

    private:
        AnimTime mCurr;
        AnimTime mDelta;
        AnimTime mMax;
        AnimTime mMin;
    };
}

#endif
