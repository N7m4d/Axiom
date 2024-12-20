#ifndef ANIM_H
#define ANIM_H

#include "AnimTime.h"
#include "Clip.h"

namespace Axiom
{
	constexpr auto NUM_BONES = 12;

	class Anim
	{
	public:
		Anim();
		Anim(const Anim&) = delete;
		Anim& operator = (const Anim&) = delete;
		virtual ~Anim();

		virtual void Animate(AnimTime curr);
		virtual void AnimateReverse(AnimTime curr);
		virtual AnimTime FindMaxTime() = 0;

		Clip* mClip;
		Bone* mBone;
		int mNumBones;
	};
}

#endif
