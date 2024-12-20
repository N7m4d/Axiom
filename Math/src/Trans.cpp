#include "MathEngine.h"

namespace Axiom
{
	Trans::Trans()
		: Mat4(Identity)
	{
		privSetTransHint();
	}

	Trans::Trans(const float tx, const float ty, const float tz)
		: Mat4(Identity)
	{
		_m12 = tx;
		_m13 = ty;
		_m14 = tz;

		privSetTransHint();
	}

	Trans::Trans(const Vec3& vTrans)
		: Trans(vTrans._vx, vTrans._vy, vTrans._vz)
	{
	}

	void Trans::set(const float tx, const float ty, const float tz)
	{
		_m12 = tx;
		_m13 = ty;
		_m14 = tz;

		privSetTransHint();
	}

	void Trans::set(const Vec3& vTrans)
	{
		_m12 = vTrans._vx;
		_m13 = vTrans._vy;
		_m14 = vTrans._vz;

		privSetTransHint();
	}

	Mat4 Trans::operator*(const Mat4& A) const
	{
		return Mat4(A._m0, A._m1, A._m2, A._m3, A._m4, A._m5, A._m6, A._m7, A._m8, A._m9, A._m10, A._m11, 
			_m12 * A._m0 + _m13 * A._m4 + _m14 * A._m8 + _m15 * A._m12,
			_m12 * A._m1 + _m13 * A._m5 + _m14 * A._m9 + _m15 * A._m13,
			_m12 * A._m2 + _m13 * A._m6 + _m14 * A._m10 + _m15 * A._m14,
			_m12 * A._m3 + _m13 * A._m7 + _m14 * A._m11 + _m15 * A._m15);
	}

	Mat4 Trans::operator*(const Quat& q) const
	{
		return *this * Rot(q);
	}

	Mat4 Trans::operator*(const Scale& A) const
	{
		Mat4 result;

		// Diagonal
		result._m0 = A._m0;
		result._m5 = A._m5;
		result._m10 = A._m10;

		// Row 4
		result._m12 = _m12 * A._m0;
		result._m13 = _m13 * A._m5;
		result._m14 = _m14 * A._m10;
		result._m15 = 1.0f;

		result.privSetNewHint(Hint::Trans, Hint::Scale);

		return result;
	}

	Mat4 Trans::operator*(const Rot& A) const
	{
		Mat4 result;

		// Row 1
		result._m0 = A._m0;
		result._m1 = A._m1;
		result._m2 = A._m2;

		// Row 2
		result._m4 = A._m4;
		result._m5 = A._m5;
		result._m6 = A._m6;

		// Row 3
		result._m8 = A._m8;
		result._m9 = A._m9;
		result._m10 = A._m10;

		// Row 4
		result._m12 = _m12 * A._m0 + _m13 * A._m4 + _m14 * A._m8;
		result._m13 = _m12 * A._m1 + _m13 * A._m5 + _m14 * A._m9;
		result._m14 = _m12 * A._m2 + _m13 * A._m6 + _m14 * A._m10;
		result._m15 = 1.0f;

		result.privSetNewHint(Hint::Trans, Hint::Rot);

		return result;
	}

	Trans Trans::operator*(const Trans& A) const
	{
		return Trans(_m12 + A._m12, _m13 + A._m13, _m14 + A._m14);
	}

	Trans& Trans::operator*=(const Trans& A)
	{
		set(_m12 + A._m12, _m13 + A._m13, _m14 + A._m14);
		return *this;
	}
}

// ---  End of File ---
