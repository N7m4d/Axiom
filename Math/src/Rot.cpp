#include "MathEngine.h"

namespace Axiom
{
	Rot::Rot()
		: Mat4(Identity)
	{
		privSetRotHint();
	}

	Rot::Rot(const Quat& q)
	{
		set(q);
	}

	Rot& Rot::operator=(const Quat&)
	{
		return *this;
	}

	Rot::Rot(const enum Identity_enum)
		: Mat4(Identity)
	{
		privSetRotHint();
	}

	Rot::Rot(const Rot1 type, const float angle)
		: Mat4(Identity)
	{
		float cos = 0.0f;
		float sin = 0.0f;

		Trig::cossin(cos, sin, angle);

		switch (type)
		{
		case Rot1::X:
			_m5 = cos;
			_m6 = sin;
			_m9 = -sin;
			_m10 = cos;
			break;
		case Rot1::Y:
			_m0 = cos;
			_m2 = -sin;
			_m8 = sin;
			_m10 = cos;
			break;
		case Rot1::Z:
			_m0 = cos;
			_m1 = sin;
			_m4 = -sin;
			_m5 = cos;
			break;
		default:
			assert("Invalid input");
		}

		privSetRotHint();
	}

	Rot::Rot(const Rot3 mode, const float angle_0, const float angle_1, const float angle_2)
	{
		Rot x(Rot1::X, angle_0);
		Rot y(Rot1::Y, angle_1);
		Rot z(Rot1::Z, angle_2);

		switch (mode)
		{
		case Rot3::XYZ:
			*this = x * y * z;
			break;
		case Rot3::XZY:
			*this = x * z * y;
			break;
		case Rot3::YXZ:
			*this = y * x * z;
			break;
		case Rot3::YZX:
			*this = y * z * x;
			break;
		case Rot3::ZXY:
			*this = z * x * y;
			break;
		case Rot3::ZYX:
			*this = z * y * x;
			break;
		default:
			assert("Invalid input");
		}

		privSetRotHint();
	}

	Rot::Rot(const Axis mode, const Vec3& vAxis, const float angle_radians)
	{
		const float angle_a = 0.5f * angle_radians;
		float cos_a = 0.0f;
		float sin_a = 0.0f;

		Trig::cossin(cos_a, sin_a, angle_a);

		Vec3 qV = vAxis;			
		if (mode == Axis::AxisAngle) {
			qV.norm();
		}

		qV *= sin_a;;

		Vec4 Q(qV[x], qV[y], qV[z], cos_a);

		// this function has been transposed
		float x2, y2, z2;
		float xx, xy, xz;
		float yy, yz, zz;
		float wx, wy, wz;

		// ADD test to make sure that quat is normalized

		x2 = Q[x] + Q[x];
		y2 = Q[y] + Q[y];
		z2 = Q[z] + Q[z];

		xx = Q[x] * x2;
		xy = Q[x] * y2;
		xz = Q[x] * z2;

		yy = Q[y] * y2;
		yz = Q[y] * z2;
		zz = Q[z] * z2;

		wx = Q[w] * x2;
		wy = Q[w] * y2;
		wz = Q[w] * z2;

		this->_m0 = 1.0f - (yy + zz);
		this->_m1 = xy + wz;
		this->_m2 = xz - wy;
		this->_m3 = 0.0f;

		this->_m4 = xy - wz;
		this->_m5 = 1.0f - (xx + zz);
		this->_m6 = yz + wx;
		this->_m7 = 0.0f;

		this->_m8 = xz + wy;
		this->_m9 = yz - wx;
		this->_m10 = 1.0f - (xx + yy);
		this->_m11 = 0.0f;

		this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);

		privSetRotHint();
	}

	Rot::Rot(const Orient type, const Vec3& dof, const Vec3& up)
		: Mat4(Identity)
	{
		const Vec3 rz = dof.getNorm();

		/* find rx */
		Vec3 rx = up.cross(rz);
		rx.norm();

		/* find ry */
		Vec3 ry = rz.cross(rx);
		ry.norm();

		Mat4::set(Vec4(rx, 0.0f), Vec4(ry, 0.0f), Vec4(rz, 0.0f), Vec4(0.0f, 0.0f, 0.0f, 1.0f));
		_m3 = 0.0f;
		_m7 = 0.0f;
		_m11 = 0.0f;
		_m15 = 1.0f;

		if (type == Orient::WorldToLocal)
		{
			Mat4::T();
		}

		privSetRotHint();
	}

	void Rot::set(const Quat& q)
	{
		Mat4::set(q);
	}

	void Rot::set(const enum Identity_enum)
	{
		_v0.set(1.0f, 0.0f, 0.0f, 0.0f);
		_v1.set(0.0f, 1.0f, 0.0f, 0.0f);
		_v2.set(0.0f, 0.0f, 1.0f, 0.0f);
		_v3.set(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void Rot::set(const Rot& m)
	{
		// Refactor
		*this = m;
	}

	void Rot::set(const Rot1 type, const float angle)
	{
		float cos;
		float sin;

		Trig::cossin(cos, sin, angle);

		Mat4::set(Identity);

		switch (type)
		{
		case Rot1::X:
			_m5 = cos;
			_m6 = sin;
			_m9 = -sin;
			_m10 = cos;
			break;
		case Rot1::Y:
			_m0 = cos;
			_m2 = -sin;
			_m8 = sin;
			_m10 = cos;
			break;
		case Rot1::Z:
			_m0 = cos;
			_m1 = sin;
			_m4 = -sin;
			_m5 = cos;
			break;
		default:
			assert("Invalid input");
		}

		privSetRotHint();
	}

	void Rot::set(const Rot3 mode, const float angle_0, const float angle_1, const float angle_2)
	{
		Rot x = Rot(Rot1::X, angle_0);
		Rot y = Rot(Rot1::Y, angle_1);
		Rot z = Rot(Rot1::Z, angle_2);

		Mat4& res = *this;

		switch (mode)
		{
		case Rot3::XYZ:
			res = x * y * z;
			break;
		case Rot3::XZY:
			res = x * z * y;
			break;
		case Rot3::YXZ:
			res = y * x * z;
			break;
		case Rot3::YZX:
			res = y * z * x;
			break;
		case Rot3::ZXY:
			res = z * x * y;
			break;
		case Rot3::ZYX:
			res = z * y * x;
			break;
		default:
			assert("Invalid input");
		}
	}

	void Rot::set(const Axis mode, const Vec3& vAxis, const float angle_radians)
	{
		const float angle_a = 0.5f * angle_radians;
		float cos_a = 0.0f;
		float sin_a = 0.0f;

		Trig::cossin(cos_a, sin_a, angle_a);

		Vec3 qV = vAxis;
		if (mode == Axis::AxisAngle) {
			qV.norm();
		}

		qV *= sin_a;;

		Vec4 Q(qV[x], qV[y], qV[z], cos_a);

		// this function has been transposed
		float x2, y2, z2;
		float xx, xy, xz;
		float yy, yz, zz;
		float wx, wy, wz;

		// ADD test to make sure that quat is normalized

		x2 = Q[x] + Q[x];
		y2 = Q[y] + Q[y];
		z2 = Q[z] + Q[z];

		xx = Q[x] * x2;
		xy = Q[x] * y2;
		xz = Q[x] * z2;

		yy = Q[y] * y2;
		yz = Q[y] * z2;
		zz = Q[z] * z2;

		wx = Q[w] * x2;
		wy = Q[w] * y2;
		wz = Q[w] * z2;

		this->_m0 = 1.0f - (yy + zz);
		this->_m1 = xy + wz;
		this->_m2 = xz - wy;
		this->_m3 = 0.0f;

		this->_m4 = xy - wz;
		this->_m5 = 1.0f - (xx + zz);
		this->_m6 = yz + wx;
		this->_m7 = 0.0f;

		this->_m8 = xz + wy;
		this->_m9 = yz - wx;
		this->_m10 = 1.0f - (xx + yy);
		this->_m11 = 0.0f;

		this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void Rot::set(const Orient type, const Vec3& dof, const Vec3& up)
	{
		const Vec3 rz = dof.getNorm();

		/* find rx */
		Vec3 rx = up.cross(rz);
		rx.norm();

		/* find ry */
		Vec3 ry = rz.cross(rx);
		ry.norm();

		Mat4::set(Vec4(rx, 0.0f), Vec4(ry, 0.0f), Vec4(rz, 0.0f), Vec4(0.0f, 0.0f, 0.0f, 1.0f));
		_m3 = 0.0f;
		_m7 = 0.0f;
		_m11 = 0.0f;
		_m15 = 1.0f;

		if (type == Orient::WorldToLocal)
		{
			Mat4::T();
		}
	}

	Mat4 Rot::operator*(const Mat4& A) const
	{
		return Mat4(
			_m0 * A._m0 + _m1 * A._m4 + _m2 * A._m8,
			_m0 * A._m1 + _m1 * A._m5 + _m2 * A._m9,
			_m0 * A._m2 + _m1 * A._m6 + _m2 * A._m10,
			_m0 * A._m3 + _m1 * A._m7 + _m2 * A._m11,
			_m4 * A._m0 + _m5 * A._m4 + _m6 * A._m8,
			_m4 * A._m1 + _m5 * A._m5 + _m6 * A._m9,
			_m4 * A._m2 + _m5 * A._m6 + _m6 * A._m10,
			_m4 * A._m3 + _m5 * A._m7 + _m6 * A._m11,
			_m8 * A._m0 + _m9 * A._m4 + _m10 * A._m8,
			_m8 * A._m1 + _m9 * A._m5 + _m10 * A._m9,
			_m8 * A._m2 + _m9 * A._m6 + _m10 * A._m10,
			_m8 * A._m3 + _m9 * A._m7 + _m10 * A._m11,
			A._m12, A._m13, A._m14, A._m15);
	}

	Rot Rot::operator*(const Quat& A) const
	{
		return *this * Rot(A);
	}

	Rot& Rot::operator*=(const Quat& A)
	{
		*this *= Rot(A);
		return *this;
	}

	Mat4 Rot::operator*(const Scale& A) const
	{
		Mat4 result;

		// Row 1
		result._m0 = _m0 * A._m0;
		result._m1 = _m1 * A._m5;
		result._m2 = _m2 * A._m10;

		// Row 2
		result._m4 = _m4 * A._m0;
		result._m5 = _m5 * A._m5;
		result._m6 = _m6 * A._m10;

		// Row 3
		result._m8 = _m8 * A._m0;
		result._m9 = _m9 * A._m5;
		result._m10 = _m10 * A._m10;

		result._m15 = 1.0f;

		result.privSetNewHint(Hint::Rot, Hint::Scale);

		return result;
	}

	Rot Rot::operator*(const Rot& A) const
	{
		Rot result;

		// Row 1
		result._m0 = _m0 * A._m0 + _m1 * A._m4 + _m2 * A._m8;
		result._m1 = _m0 * A._m1 + _m1 * A._m5 + _m2 * A._m9;
		result._m2 = _m0 * A._m2 + _m1 * A._m6 + _m2 * A._m10;

		// Row 2
		result._m4 = _m4 * A._m0 + _m5 * A._m4 + _m6 * A._m8;
		result._m5 = _m4 * A._m1 + _m5 * A._m5 + _m6 * A._m9;
		result._m6 = _m4 * A._m2 + _m5 * A._m6 + _m6 * A._m10;

		// Row 3
		result._m8 = _m8 * A._m0 + _m9 * A._m4 + _m10 * A._m8;
		result._m9 = _m8 * A._m1 + _m9 * A._m5 + _m10 * A._m9;
		result._m10 = _m8 * A._m2 + _m9 * A._m6 + _m10 * A._m10;

		return result;
	}

	Rot& Rot::operator*=(const Rot& A)
	{
		float x = _m0;
		float y = _m1;
		float z = _m2;

		// Row 1
		_m0 = x * A._m0 + y * A._m4 + z * A._m8;
		_m1 = x * A._m1 + y * A._m5 + z * A._m9;
		_m2 = x * A._m2 + y * A._m6 + z * A._m10;

		x = _m4;
		y = _m5;
		z = _m6;

		// Row 2
		_m4 = x * A._m0 + y * A._m4 + z * A._m8;
		_m5 = x * A._m1 + y * A._m5 + z * A._m9;
		_m6 = x * A._m2 + y * A._m6 + z * A._m10;

		x = _m8;
		y = _m9;
		z = _m10;

		// Row 3
		_m8 = x * A._m0 + y * A._m4 + z * A._m8;
		_m9 = x * A._m1 + y * A._m5 + z * A._m9;
		_m10 = x * A._m2 + y * A._m6 + z * A._m10;

		return *this;
	}

	Mat4 Rot::operator*(const Trans& A) const
	{
		Mat4 result;

		// Row 1
		result._m0 = _m0;
		result._m1 = _m1;
		result._m2 = _m2;

		// Row 2
		result._m4 = _m4;
		result._m5 = _m5;
		result._m6 = _m6;

		// Row 3
		result._m8 = _m8;
		result._m9 = _m9;
		result._m10 = _m10;

		// Row 4
		result._m12 = A._m12;
		result._m13 = A._m13;
		result._m14 = A._m14;
		result._m15 = A._m15;

		result.privSetNewHint(Hint::Rot, Hint::Trans);

		return result;
	}
}

// ---  End of File ---
