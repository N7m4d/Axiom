#ifndef WALK_ANIM_H
#define WALK_ANIM_H

#include "AnimTimer.h"
#include "GameObjectAnimSkin.h"
#include "GameObjectAnimSkeleton.h"
#include "WalkSkeleton.h"
#include "Anim.h"

namespace Axiom
{
	class WalkAnim : public Anim
	{
	public:
		WalkAnim();
		WalkAnim(const WalkAnim &) = delete;
		WalkAnim &operator = (const WalkAnim &) = delete;
		virtual ~WalkAnim();

		AnimTime FindMaxTime() override;

		static void PoseSkeleton(GameObjectAnimSkeleton *node);

	private:
		WalkSkeleton   *poSkeleton;
	};
}

#endif
