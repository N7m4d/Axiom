#include "MathEngine.h"
#include "MathApp.h"

//----------------------------------------------------------------------------- 
// Mutates result to be a slerp between the source and target by the
// specified factor.
// For a factor of 0.0, result == source.
// For a factor of 1.0, result == target.
//----------------------------------------------------------------------------- 

namespace Axiom
{
	void QuatApp::Slerp(Quat &result, const Quat &source, const Quat &target, const float slerpFactor)
	{
		float dot = source.dot(target);

		Quat tmpTarget = target;

		// The quaternions are on opposite hemispheres.
		// To ensure the shortest path, negate one of the quaternions.
		if (dot < 0.0f)
		{
			dot = -dot;
			tmpTarget = -target;
		}

		const float epsilon = 0.0001f;
		if (dot > 1.0f - epsilon) {
			result = (source * (1.0f - slerpFactor) + tmpTarget * slerpFactor).norm();
			return;
		}

		const float theta = Trig::acos(dot);

		const float s0 = Trig::sin((1.0f - slerpFactor) * theta) / Trig::sin(theta);
		const float s1 = Trig::sin(slerpFactor * theta) / Trig::sin(theta);

		result = source * s0 + tmpTarget * s1;
	}

	void QuatApp::SlerpArray(Quat* result, const Quat* source, const Quat* target, const float slerpFactor, const int numQuats)
	{
		for (int i = 0; i < numQuats; ++i)
		{
			Slerp(result[i], source[i], target[i], slerpFactor);
		}
	}
}

// ---  End of File ---------------
