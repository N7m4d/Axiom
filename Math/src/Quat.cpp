#include "MathEngine.h"

namespace Axiom
{
	Quat::Quat()
		: Quat(Identity)
	{
	}

	Quat::Quat(const Vec3& vect, const float real)
		: _qV4{vect, real}
	{
	}

	Quat::Quat(const float vx, const float vy, const float vz, const float real)
		: _qx{vx}, _qy{vy}, _qz{vz}, _qw{real}
	{
	}

	Quat::Quat(const enum Identity_enum)
		: _qx{0.0f}, _qy{0.0f}, _qz{0.0f}, _qw{1.0f}
	{
	}

	Quat::Quat(const Rot& M)
	{
		float tr = M._m0 + M._m5 + M._m10;
		float S;

		if (tr > 0.0f)
		{
			S = 2.0f * sqrtf(tr + 1.0f);
			_qw = 0.25f * S;
			_qx = -(M._m9 - M._m6) / S;
			_qy = -(M._m2 - M._m8) / S;
			_qz = -(M._m4 - M._m1) / S;
		}
		else if (M._m0 > M._m5 && M._m0 > M._m10)
		{
			S = 2.0f * sqrtf(1.0f + M._m0 - M._m5 - M._m10);
			_qw = -(M._m9 - M._m6) / S;
			_qx = 0.25f * S;
			_qy = (M._m1 + M._m4) / S;
			_qz = (M._m2 + M._m8) / S;
		}
		else if (M._m5 > M._m10)
		{
			S = 2.0f * sqrtf(1.0f + M._m5 - M._m0 - M._m10);
			_qw = -(M._m2 - M._m8) / S;
			_qx = (M._m1 + M._m4) / S;
			_qy = 0.25f * S;
			_qz = (M._m6 + M._m9) / S;
		}
		else
		{
			S = 2.0f * sqrtf(1.0f + M._m10 - M._m0 - M._m5);
			_qw = -(M._m4 - M._m1) / S;
			_qx = (M._m2 + M._m8) / S;
			_qy = (M._m6 + M._m9) / S;
			_qz = 0.25f * S;
		}
	}

	Quat::Quat(const Rot1 type, const float angle)
		: Quat()
	{
		set(type, angle);
	}

	Quat::Quat(const Rot3 type, const float angle_x, const float angle_y, const float angle_z)
		: Quat()
	{
		set(type, angle_x, angle_y, angle_z);
	}

	Quat::Quat(const Axis type, const Vec3& vAxis, const float angle_radians)
	{
		set(type, vAxis, angle_radians);
	}

	Quat::Quat(const Orient orient, const Vec3& dof, const Vec3& up)
	{
		set(orient, dof, up);
	}

	void Quat::set(const enum Identity_enum)
	{
		_qx = 0.0f;
		_qy = 0.0f;
		_qz = 0.0f;
		_qw = 1.0f;
	}

	void Quat::set(const Rot& M)
	{
		float tr = M._m0 + M._m5 + M._m10;
		float S;

		if (tr > 0.0f)
		{
			S = 2.0f * sqrtf(tr + 1.0f);
			_qw = 0.25f * S;
			_qx = -(M._m9 - M._m6) / S;
			_qy = -(M._m2 - M._m8) / S;
			_qz = -(M._m4 - M._m1) / S;
		}
		else if (M._m0 > M._m5 && M._m0 > M._m10)
		{
			S = 2.0f * sqrtf(1.0f + M._m0 - M._m5 - M._m10);
			_qw = -(M._m9 - M._m6) / S;
			_qx = 0.25f * S;
			_qy = (M._m1 + M._m4) / S;
			_qz = (M._m2 + M._m8) / S;
		}
		else if (M._m5 > M._m10)
		{
			S = 2.0f * sqrtf(1.0f + M._m5 - M._m0 - M._m10);
			_qw = -(M._m2 - M._m8) / S;
			_qx = (M._m1 + M._m4) / S;
			_qy = 0.25f * S;
			_qz = (M._m6 + M._m9) / S;
		}
		else
		{
			S = 2.0f * sqrtf(1.0f + M._m10 - M._m0 - M._m5);
			_qw = -(M._m4 - M._m1) / S;
			_qx = (M._m2 + M._m8) / S;
			_qy = (M._m6 + M._m9) / S;
			_qz = 0.25f * S;
		}
	}

	void Quat::set(const Rot1 type, const float angle)
	{
		float cos;
		float sin;
		Trig::cossin(cos, sin, angle / 2);

		switch (type)
		{
		case Rot1::X:
			_qx = sin;
			break;
		case Rot1::Y:
			_qy = sin;
			break;
		case Rot1::Z:
			_qz = sin;
			break;
		default:
			break;
		}

		_qw = cos;
	}

	void Quat::set(const Rot3 type, const float angle_x, const float angle_y, const float angle_z)
	{
		Quat x(Rot1::X, angle_x);
		Quat y(Rot1::Y, angle_y);
		Quat z(Rot1::Z, angle_z);

		switch (type)
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
	}

	void Quat::set(const Axis type, const Vec3& vAxis, const float angle_radians)
	{
		switch (type)
		{
		case Axis::AxisAngle:
		{
			float cos;
			float sin;
			Trig::cossin(cos, sin, angle_radians / 2);
			Vec3 norm = vAxis.getNorm();
			set(vAxis.getNorm() * sin, cos);
		}
		break;
		case Axis::UnitAxisAngle:
		{
			set(vAxis, Trig::cos(angle_radians / 2));
		}
		break;
		default:
			break;
		}
	}

	void Quat::set(const Orient orient, const Vec3& dof, const Vec3& up)
	{
		set(Rot(orient, dof, up));
	}

	void Quat::set(const float vx, const float vy, const float vz, const float real)
	{
		_qx = vx;
		_qy = vy;
		_qz = vz;
		_qw = real;
	}

	float& Quat::operator[](const x_enum value)
	{
		return _qx;
	}

	float& Quat::operator[](const y_enum value)
	{
		return _qy;
	}

	float& Quat::operator[](const z_enum value)
	{
		return _qz;
	}

	float& Quat::operator[](const w_enum value)
	{
		return _qw;
	}

	void Quat::qx(const float value)
	{
		_qx = value;
	}

	void Quat::qy(const float value)
	{
		_qy = value;
	}

	void Quat::qz(const float value)
	{
		_qz = value;
	}

	void Quat::real(const float value)
	{
		_qw = value;
	}

	void Quat::setVec3(const Vec3& vect)
	{
		_qV3 = vect;
	}

	void Quat::set(const Vec3& vect, const float real)
	{
		_qV3 = vect;
		_qw = real;
	}

	float Quat::operator[](const x_enum value) const
	{
		return _qx;
	}

	float Quat::operator[](const y_enum value) const
	{
		return _qy;
	}

	float Quat::operator[](const z_enum value) const
	{
		return _qz;
	}

	float Quat::operator[](const w_enum value) const
	{
		return _qw;
	}

	float Quat::qx() const
	{
		return _qx;
	}

	float Quat::qy() const
	{
		return _qy;
	}

	float Quat::qz() const
	{
		return _qz;
	}

	float Quat::real() const
	{
		return _qw;
	}

	float Quat::getAngle() const
	{
		return 2 * Trig::acos(_qw);
	}

	void Quat::getVec3(Vec3& vOut) const
	{
		vOut = _qV3;
	}

	void Quat::getAxis(Vec3& vOut) const
	{
		const float sinAngle = Trig::sin(getAngle() / 2);
		vOut.set(_qx / sinAngle, _qy / sinAngle, _qz / sinAngle);
	}

	float Quat::dot(const Quat& qin) const
	{
		return _qV4.dot(qin._qV4);
	}

	float Quat::mag() const
	{
		return _qV4.len();
	}

	float Quat::magSquared() const
	{
		const float len = mag();
		return len * len;
	}

	float Quat::invMag() const
	{
		return 1.0f / mag();
	}

	Quat& Quat::conj()
	{
		_qx = -_qx;
		_qy = -_qy;
		_qz = -_qz;

		return *this;
	}

	Quat Quat::getConj() const
	{
		return Quat(-_qV3, _qw);
	}

	Quat& Quat::inv()
	{
		conj();
		*this /= magSquared();

		return *this;
	}

	Quat Quat::getInv() const
	{
		return Quat(getConj() / magSquared());
	}

	Quat& Quat::norm()
	{
		return *this /= mag();
	}

	Quat Quat::getNorm() const
	{
		return *this / mag();
	}

	void Quat::Lqvqc(const Vec3& vIn, Vec3& vOut) const
	{
		vOut = (*this * Quat(vIn, 0.0f) * getConj())._qV3;
	}

	void Quat::Lqcvq(const Vec3& vIn, Vec3& vOut) const
	{
		vOut = (getConj() * Quat(vIn, 0.0f) * *this)._qV3;
	}

	bool Quat::isEqual(const Quat& qin, const float epsilon) const
	{
		return _qV4.isEqual(qin._qV4, epsilon);
	}

	bool Quat::isEquivalent(const Quat& qin, const float epsilon) const
	{
		return isEqual(qin, epsilon) || isEqual(-qin, epsilon);
	}

	bool Quat::isNegEqual(const Quat& qin, const float epsilon) const
	{
		return Vec4(_qx + qin._qx, _qy + qin._qy, _qz + qin._qz, _qw + qin._qw).isZero(epsilon);
	}

	bool Quat::isConjugateEqual(const Quat& qin, const float epsilon) const
	{
		return Vec4(_qx + qin._qx, _qy + qin._qy, _qz + qin._qz, _qw - qin._qw).isZero(epsilon);
	}

	bool Quat::isIdentity(const float epsilon) const
	{
		return Util::isZero(_qx, epsilon)
			&& Util::isZero(_qy, epsilon)
			&& Util::isZero(_qz, epsilon)
			&& Util::isOne(_qw, epsilon);
	}

	bool Quat::isNormalized(const float epsilon) const
	{
		return Util::isOne(mag(), epsilon);
	}

	Quat& Quat::operator=(const Rot& M)
	{
		float tr = M._m0 + M._m5 + M._m10;
		float S;

		if (tr > 0.0f)
		{
			S = 2.0f * sqrtf(tr + 1.0f);
			float invS = 1.0f / S;
			_qV4.set(-(M._m9 - M._m6) * invS, -(M._m2 - M._m8) * invS, -(M._m4 - M._m1) * invS, 0.25f * S);
		}
		else if (M._m0 > M._m5 && M._m0 > M._m10)
		{
			S = 2.0f * sqrtf(1.0f + M._m0 - M._m5 - M._m10);
			float invS = 1.0f / S;
			_qV4.set(0.25f * S, (M._m1 + M._m4) * invS, (M._m2 + M._m8) * invS, -(M._m9 - M._m6) * invS);
		}
		else if (M._m5 > M._m10)
		{
			S = 2.0f * sqrtf(1.0f + M._m5 - M._m0 - M._m10);
			float invS = 1.0f / S;
			_qV4.set((M._m1 + M._m4) * invS, 0.25f * S, (M._m6 + M._m9) * invS, -(M._m2 - M._m8) * invS);
		}
		else
		{
			S = 2.0f * sqrtf(1.0f + M._m10 - M._m0 - M._m5);
			float invS = 1.0f / S;
			_qV4.set((M._m2 + M._m8) * invS, (M._m6 + M._m9) * invS, 0.25f * S, -(M._m4 - M._m1) * invS);
		}

		return *this;
	}

	Quat Quat::operator+() const
	{
		return Quat(+_qx, +_qy, +_qz, +_qw);
	}

	Quat Quat::operator+(const Quat& q) const
	{
		return Quat(_qx + q._qx, _qy + q._qy, _qz + q._qz, _qw + q._qw);
	}

	Quat& Quat::operator+=(const Quat& q)
	{
		_qV4 += q._qV4;
		return *this;
	}

	Quat Quat::operator+(const float a) const
	{
		return Quat(_qx + a, _qy + a, _qz + a, _qw + a);
	}

	Quat& Quat::operator+=(const float a)
	{
		_qx += a;
		_qy += a;
		_qz += a;
		_qw += a;

		return *this;
	}

	Quat Quat::operator-() const
	{
		return Quat(-_qx, -_qy, -_qz, -_qw);
	}

	Quat Quat::operator-(const Quat& q) const
	{
		return Quat(_qx - q._qx, _qy - q._qy, _qz - q._qz, _qw - q._qw);
	}

	Quat& Quat::operator-=(const Quat& q)
	{
		_qV4 -= q._qV4;
		return *this;
	}

	Quat Quat::operator-(const float a) const
	{
		return Quat(_qx - a, _qy - a, _qz - a, _qw - a);
	}

	Quat& Quat::operator-=(const float a)
	{
		_qx -= a;
		_qy -= a;
		_qz -= a;
		_qw -= a;

		return *this;
	}

	Quat Quat::operator*(const float a) const
	{
		return Quat(_qx * a, _qy * a, _qz * a, _qw * a);
	}

	Quat& Quat::operator*=(const float a)
	{
		_qx *= a;
		_qy *= a;
		_qz *= a;
		_qw *= a;

		return *this;
	}

	Mat4 Quat::operator*(const Mat4& m) const
	{
		return Rot(*this) * m;
	}

	Quat Quat::operator*(const Quat& q) const
	{
		return Quat(q._qV3.cross(_qV3) + q._qw * _qV3 + _qw * q._qV3, (_qw * q._qw) - _qV3.dot(q._qV3));
	}

	Quat& Quat::operator*=(const Quat& q)
	{
		set(q._qV3.cross(_qV3) + q._qw * _qV3 + _qw * q._qV3, (_qw * q._qw) - _qV3.dot(q._qV3));
		return *this;
	}

	Mat4 Quat::operator*(const Scale& m) const
	{
		return Rot(*this) * m;
	}

	Quat& Quat::operator*=(const Rot& m)
	{
		*this = *this * Quat(m);
		return *this;
	}

	Rot Quat::operator*(const Rot& m) const
	{
		return Rot(*this) *= m;
	}

	Mat4 Quat::operator*(const Trans& m) const
	{
		return Rot(*this) * m;
	}

	Quat Quat::operator/(const Quat& q) const
	{
		return Quat(_qx / q._qx, _qy / q._qy, _qz / q._qz, _qw / q._qw);
	}

	Quat& Quat::operator/=(const Quat& q)
	{
		_qx /= q._qx;
		_qy /= q._qy;
		_qz /= q._qz;
		_qw /= q._qw;

		return *this;
	}

	Quat Quat::operator/(const float a) const
	{
		return Quat(_qx / a, _qy / a, _qz / a, _qw / a);
	}

	Quat& Quat::operator/=(const float a)
	{
		_qV4.set(_qx / a, _qy / a, _qz / a, _qw / a);
		return *this;
	}

	void Quat::Print(const char* pName) const
	{
	}

	Quat operator+(const float a, const Quat& q)
	{
		return Quat(a + q._qx, a + q._qy, a + q._qz, a + q._qw);
	}

	Quat operator-(const float a, const Quat& q)
	{
		return Quat(a - q._qx, a - q._qy, a - q._qz, a - q._qw);
	}

	Quat operator*(const float a, const Quat& q)
	{
		return Quat(a * q._qx, a * q._qy, a * q._qz, a * q._qw);
	}

	Quat operator/(const float a, const Quat& q)
	{
		return Quat(a / q._qx, a / q._qy, a / q._qz, a / q._qw);
	}
}

//--- End of File ---
