#ifndef NULL_ANIM_CONTROLLER_H
#define NULL_ANIM_CONTROLLER_H

#include "AnimController.h"

namespace Axiom
{
    class NullAnimController : public AnimController
    {
    public:
        NullAnimController();
        NullAnimController(const NullAnimController&) = delete;
        NullAnimController& operator=(const NullAnimController& other) = delete;
        ~NullAnimController() override = default;
    };
}

#endif // !ANIM_CONTROLLER_H
