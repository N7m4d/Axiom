#ifndef SIDE_STEP_LEFT_ANIM_H
#define SIDE_STEP_LEFT_ANIM_H

#include "GameObjectAnimSkin.h"
#include "GameObjectAnimSkeleton.h"
#include "SideStepLeftSkeleton.h"
#include "Anim.h"

namespace Axiom
{
    class SideStepLeftAnim : public Anim
    {
    public:
        SideStepLeftAnim();
        SideStepLeftAnim(const SideStepLeftAnim&) = delete;
        SideStepLeftAnim& operator =(const SideStepLeftAnim&) = delete;
        virtual ~SideStepLeftAnim();

        AnimTime FindMaxTime() override;

        static void PoseSkeleton(GameObjectAnimSkeleton* node);

    private:
        SideStepLeftSkeleton* mSkeleton;
    };
}

#endif
