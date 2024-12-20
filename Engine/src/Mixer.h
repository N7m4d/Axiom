#ifndef MIXER_H
#define MIXER_H

#include "AnimTimer.h"
#include "Bone.h"

namespace Axiom
{
	class Mixer
	{
	public:
		static void Blend(Bone *pResult,
						  const Bone *pA,
						  const Bone *pB,
						  const float tS,
						  const int numBones);
	};
}

#endif
