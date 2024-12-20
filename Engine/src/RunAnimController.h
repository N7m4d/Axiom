#ifndef RUN_ANIM_CONTROLLER_H
#define RUN_ANIM_CONTROLLER_H

#include "TimerController.h"
#include "GameObjectAnim.h"
#include "RunAnim.h"
#include "AnimController.h"

namespace Axiom
{
	class RunAnimController : public AnimController
	{
	public:
		RunAnimController(AnimTime delta);
		RunAnimController(const RunAnimController&) = delete;
		RunAnimController& operator = (const RunAnimController&) = delete;
		virtual ~RunAnimController() = default;
	};
}

#endif
