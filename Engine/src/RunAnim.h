#ifndef RUN_ANIM_H
#define RUN_ANIM_H

#include "AnimTimer.h"
#include "MathEngine.h"
#include "GameObjectAnimSkin.h"
#include "GameObjectAnimSkeleton.h"
#include "RunClip.h"
#include "RunSkeleton.h"
#include "Anim.h"

namespace Axiom
{
	class RunAnim : public Anim
	{
	public:
		RunAnim();
		RunAnim(const RunAnim&) = delete;
		RunAnim& operator = (const RunAnim&) = delete;
		virtual ~RunAnim();

		AnimTime FindMaxTime() override;

		static void PoseSkeleton(GameObjectAnimSkeleton* node);

	private:
		RunSkeleton* poSkeleton;
	};

}

#endif
