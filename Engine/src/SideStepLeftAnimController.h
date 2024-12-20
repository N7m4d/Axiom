#ifndef SIDE_STEP_LEFT_ANIM_CONTROLLER_H
#define SIDE_STEP_LEFT_ANIM_CONTROLLER_H

#include "GameObjectAnim.h"
#include "AnimController.h"

namespace Axiom
{
	class SideStepLeftAnimController : public AnimController
	{
	public:
		SideStepLeftAnimController(AnimTime delta);
		SideStepLeftAnimController(const SideStepLeftAnimController&) = delete;
		SideStepLeftAnimController& operator = (const SideStepLeftAnimController&) = delete;
		virtual ~SideStepLeftAnimController() = default;
	};
}

#endif
