#include "MathEngine.h"

namespace Axiom
{
	Scale::Scale()
		: Mat4(Identity)
	{
		privSetScaleHint();
	}

	Scale::Scale(const float sx, const float sy, const float sz)
	{
		_m0 = sx;
		_m5 = sy;
		_m10 = sz;
		_m15 = 1.0f;

		privSetScaleHint();
	}

	Scale::Scale(const Vec3& vScale)
		: Scale(vScale._vx, vScale._vy, vScale._vz)
	{
	}

	void Scale::set(const float sx, const float sy, const float sz)
	{
		_m0 = sx;
		_m5 = sy;
		_m10 = sz;
	}

	void Scale::set(const Vec3& vScale)
	{
		_m0 = vScale._vx;
		_m5 = vScale._vy;
		_m10 = vScale._vz;
	}

	Mat4 Scale::operator*(const Mat4& A) const
	{
		Mat4 result;

		result._m0 = _m0 * A._m0;
		result._m1 = _m0 * A._m1;
		result._m2 = _m0 * A._m2;
		result._m3 = _m0 * A._m3;
		result._m4 = _m5 * A._m4;
		result._m5 = _m5 * A._m5;
		result._m6 = _m5 * A._m6;
		result._m7 = _m5 * A._m7;
		result._m8 = _m10 * A._m8;
		result._m9 = _m10 * A._m9;
		result._m10 = _m10 * A._m10;
		result._m11 = _m10 * A._m11;
		result._m12 = A._m12;
		result._m13 = A._m13;
		result._m14 = A._m14;
		result._m15 = A._m15;

		return result;
	}

	Mat4 Scale::operator*(const Quat& q) const
	{
		return *this * Rot(q);
	}

	Scale Scale::operator*(const Scale& A) const
	{
		return Scale(_m0 * A._m0, _m5 * A._m5, _m10 * A._m10);
	}

	Scale& Scale::operator*=(const Scale& A)
	{
		set(_m0 * A._m0, _m5 * A._m5, _m10 * A._m10);
		return *this;
	}

	Mat4 Scale::operator*(const Rot& A) const
	{
		Mat4 result;

		result._m0 = _m0 * A._m0;
		result._m1 = _m0 * A._m1;
		result._m2 = _m0 * A._m2;
		result._m4 = _m5 * A._m4;
		result._m5 = _m5 * A._m5;
		result._m6 = _m5 * A._m6;
		result._m8 = _m10 * A._m8;
		result._m9 = _m10 * A._m9;
		result._m10 = _m10 * A._m10;
		result._m15 = 1.0f;

		result.privSetNewHint(Hint::Scale, Hint::Rot);

		return result;
	}

	Mat4 Scale::operator*(const Trans& A) const
	{
		Mat4 result;

		result._m0 = _m0;
		result._m5 = _m5;
		result._m10 = _m10;
		result._m12 = A._m12;
		result._m13 = A._m13;
		result._m14 = A._m14;
		result._m15 = 1.0f;

		result.privSetNewHint(Hint::Scale, Hint::Trans);

		return result;
	}
}

// ---  End of File ---
