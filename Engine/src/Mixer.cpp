#include "Mixer.h"
#include "MathApp.h"

namespace Axiom
{
	void Mixer::Blend(Bone *pResult,
					  const Bone *pA,
					  const Bone *pB,
					  const float tS,
					  int numBones)
	{

		// Interpolate to tS time, for all bones
		for(int i = 0; i < numBones; i++)
		{
			// interpolate ahoy!
			Vec3App::Lerp(pResult->T, pA->T, pB->T, tS);
			QuatApp::Slerp(pResult->Q, pA->Q, pB->Q, tS);
			Vec3App::Lerp(pResult->S, pA->S, pB->S, tS);

			// advance the pointer
			pA++;
			pB++;
			pResult++;
		}
	}
}
