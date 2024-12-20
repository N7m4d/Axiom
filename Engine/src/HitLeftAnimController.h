#ifndef HIT_LEFT_ANIM_CONTROLLER_H
#define HIT_LEFT_ANIM_CONTROLLER_H

#include "GameObjectAnim.h"
#include "AnimController.h"

namespace Axiom
{
	class HitLeftAnimController : public AnimController
	{
	public:
		HitLeftAnimController(AnimTime delta);
		HitLeftAnimController(const HitLeftAnimController&) = delete;
		HitLeftAnimController& operator = (const HitLeftAnimController&) = delete;
		virtual ~HitLeftAnimController() = default;
	};
}

#endif
