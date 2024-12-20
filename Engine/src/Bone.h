#ifndef BONE_H
#define BONE_H

#include "MathEngine.h"

namespace Axiom
{
	struct Bone : Align16
	{
		Vec3  T;
		Quat  Q;
		Vec3  S;
	};
}

#endif
