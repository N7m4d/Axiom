#include "TimerController.h"

namespace Axiom
{
    TimerController::TimerController(AnimTime& delta, AnimTime& min, AnimTime& max)
        : mCurr(AnimTime::Duration::ZERO),
          mDelta(delta),
          mMax(max),
          mMin(min)
    {
    }

    void TimerController::Update()
    {
        mCurr += mDelta;

        if (mCurr < mMin)
        {
            mCurr = mMax;
        }
        else if (mCurr > mMax)
        {
            mCurr = mMin;
        }
        else
        {
            // do nothing
        }
    }

    void TimerController::SetCurrTime(const AnimTime& time)
    {
        this->mCurr = time;
    }

    AnimTime TimerController::GetCurrTime() const
    {
        return this->mCurr;
    }

    void TimerController::SetDeltaTime(const AnimTime& time)
    {
        mDelta = time;
    }

    AnimTime TimerController::GetDeltaTime() const
    {
        return this->mDelta;
    }

    void TimerController::SetMaxTime(const AnimTime& time)
    {
        mMax = time;
    }

    AnimTime TimerController::GetMaxTime() const
    {
        return mMax;
    }

    void TimerController::SetMinTime(const AnimTime& time)
    {
        mMin = time;
    }

    AnimTime TimerController::GetMinTime() const
    {
        return mMin;
    }
}
