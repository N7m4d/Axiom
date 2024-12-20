#ifndef HIT_BACK_ANIM_CONTROLLER_H
#define HIT_BACK_ANIM_CONTROLLER_H

#include "GameObjectAnim.h"
#include "AnimController.h"

namespace Axiom
{
    class HitBackAnimController : public AnimController
    {
    public:
        HitBackAnimController(AnimTime& delta);
        HitBackAnimController(const HitBackAnimController&) = delete;
        HitBackAnimController& operator =(const HitBackAnimController&) = delete;
        virtual ~HitBackAnimController() = default;
    };
}

#endif
