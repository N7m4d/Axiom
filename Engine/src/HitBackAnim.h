#ifndef HIT_BACK_ANIM_H
#define HIT_BACK_ANIM_H

#include "GameObjectAnimSkeleton.h"
#include "HitBackSkeleton.h"
#include "Anim.h"

namespace Axiom
{
    class HitBackAnim : public Anim
    {
    public:
        HitBackAnim();
        HitBackAnim(const HitBackAnim&) = delete;
        HitBackAnim& operator =(const HitBackAnim&) = delete;
        virtual ~HitBackAnim();

        AnimTime FindMaxTime() override;

        static void PoseSkeleton(GameObjectAnimSkeleton* node);

    private:
        HitBackSkeleton* mSkeleton;
    };
}

#endif
