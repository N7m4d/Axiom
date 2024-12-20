#ifndef HIT_LEFT_ANIM_H
#define HIT_LEFT_ANIM_H

#include "AnimTimer.h"
#include "MathEngine.h"
#include "GameObjectAnimSkin.h"
#include "GameObjectAnimSkeleton.h"
#include "HitLeftClip.h"
#include "HitLeftSkeleton.h"
#include "Anim.h"

namespace Axiom
{
	class HitLeftAnim : public Anim
	{
	public:
		HitLeftAnim();
		HitLeftAnim(const HitLeftAnim&) = delete;
		HitLeftAnim& operator = (const HitLeftAnim&) = delete;
		virtual ~HitLeftAnim();

		AnimTime FindMaxTime() override;

		static void PoseSkeleton(GameObjectAnimSkeleton* node);

	private:
		HitLeftSkeleton* poSkeleton;
	};

}

#endif
