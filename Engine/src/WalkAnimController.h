#ifndef WALK_ANIM_CONTROLLER_H
#define WALK_ANIM_CONTROLLER_H

#include "AnimController.h"

namespace Axiom
{
	class WalkAnimController : public AnimController
	{
	public:
		WalkAnimController(AnimTime delta);
		WalkAnimController(const WalkAnimController &) = delete;
		WalkAnimController &operator = (const WalkAnimController &) = delete;
		virtual ~WalkAnimController() = default;

		void ChangeAnimation(AnimController::Name name);
	};
}

#endif
