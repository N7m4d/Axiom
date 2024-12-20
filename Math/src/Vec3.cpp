#include "MathEngine.h"

namespace Axiom
{
	Vec3::Vec3()
		: _mv{0.0f}
	{
	}

	Vec3::Vec3(const float in_x, const float in_y, const float in_z)
		: _vx{in_x}, _vy{in_y}, _vz{in_z}
	{

	}

	Vec3::Vec3(const Vec4& v)
		: _vx{v._vx}, _vy{v._vy}, _vz{v._vz}
	{
	}

	Vec3& Vec3::operator=(const Vec4& v)
	{
		_vx = v._vx;
		_vy = v._vy;
		_vz = v._vz;

		return *this;
	}

	float& Vec3::operator[](const enum x_enum)
	{
		return _vx;
	}

	float& Vec3::operator[](const enum y_enum)
	{
		return _vy;
	}

	float& Vec3::operator[](const enum z_enum)
	{
		return _vz;
	}

	float Vec3::operator[](const enum x_enum) const
	{
		return _vx;
	}

	float Vec3::operator[](const enum y_enum) const
	{
		return _vy;
	}

	float Vec3::operator[](const enum z_enum) const
	{
		return _vz;
	}

	void Vec3::x(const float v)
	{
		_vx = v;
	}

	void Vec3::y(const float v)
	{
		_vy = v;
	}

	void Vec3::z(const float v)
	{
		_vz = v;
	}

	Vec3 Vec3::operator+(const Vec3& inV) const
	{
		return Vec3(_vx + inV._vx, _vy + inV._vy, _vz + inV._vz);
	}

	Vec3& Vec3::operator+=(const Vec3& inV)
	{
		_vx += inV._vx;
		_vy += inV._vy;
		_vz += inV._vz;

		return *this;
	}

	Vec3 Vec3::operator+(void) const
	{
		return Vec3(+_vx, +_vy, +_vz);
	}

	Vec3 Vec3::operator-(const Vec3& inV) const
	{
		return Vec3(_vx - inV._vx, _vy - inV._vy, _vz - inV._vz);
	}

	Vec3 Vec3::operator-(void) const
	{
		return Vec3(-_vx, -_vy, -_vz);
	}

	Vec3& Vec3::operator-=(const Vec3& inV)
	{
		_vx -= inV._vx;
		_vy -= inV._vy;
		_vz -= inV._vz;

		return *this;
	}

	float Vec3::x() const
	{
		return _vx;
	}

	float Vec3::y() const
	{
		return _vy;
	}

	float Vec3::z() const
	{
		return _vz;
	}

	Vec3 Vec3::operator*(const float scale) const
	{
		return Vec3(_vx * scale, _vy * scale, _vz * scale);
	}

	Vec3 operator*(const float scale, const Vec3& inV)
	{
		return inV * scale;
	}

	Vec3& Vec3::operator*=(const float scale)
	{
		_vx *= scale;
		_vy *= scale;
		_vz *= scale;

		return *this;
	}

	Vec3& Vec3::operator*=(const Mat3& m)
	{
		const float x = _vx * m._m0 + _vy * m._m4 + _vz * m._m8;
		const float y = _vx * m._m1 + _vy * m._m5 + _vz * m._m9;
		const float z = _vx * m._m2 + _vy * m._m6 + _vz * m._m10;

		_vx = x;
		_vy = y;
		_vz = z;

		return *this;
	}

	Vec3 Vec3::operator*(const Quat& q) const
	{
		Vec3 out;
		q.Lqcvq(*this, out);

		return out;
	}

	Vec3& Vec3::operator*=(const Quat& q)
	{
		q.Lqcvq(*this, *this);
		return *this;
	}

	Vec3 Vec3::operator*(const Mat3& m) const
	{
		return Vec3(
			_vx * m._m0 + _vy * m._m4 + _vz * m._m8,
			_vx * m._m1 + _vy * m._m5 + _vz * m._m9,
			_vx * m._m2 + _vy * m._m6 + _vz * m._m10);
	}

	Vec3& Vec3::norm(void)
	{
		float magnitude = len();

		if (magnitude > 0.0f) {
			float invLen = 1.0f / magnitude;
			_vx *= invLen;
			_vy *= invLen;
			_vz *= invLen;
		}

		return *this;
	}

	Vec3 Vec3::getNorm(void) const
	{
		Vec3 result;
		float magnitude = len();

		if (magnitude > 0.0f) {
			float invLen = 1.0f / magnitude;
			result._vx = _vx * invLen;
			result._vy = _vy * invLen;
			result._vz = _vz * invLen;
		}

		return result;
	}

	float Vec3::dot(const Vec3& vIn) const
	{
		return _vx * vIn._vx + _vy * vIn._vy + _vz * vIn._vz;
	}

	Vec3 Vec3::cross(const Vec3& vIn) const
	{
		return Vec3(
			_vy * vIn._vz - _vz * vIn._vy,
			_vz * vIn._vx - _vx * vIn._vz,
			_vx * vIn._vy - _vy * vIn._vx
		);
	}

	Axiom::Vec3Proxy Vec3::len(void) const
	{
		return Vec3Proxy(_vx, _vy, _vz);
	}

	float Vec3::getAngle(const Vec3& vIn) const
	{
		return Trig::acos(dot(vIn) / (len() * vIn.len()));
	}

	void Vec3::set(const float inX, const float inY, const float inZ)
	{
		_vx = inX;
		_vy = inY;
		_vz = inZ;
	}

	void Vec3::set(const Vec3& A)
	{
		*this = A;
	}

	void Vec3::set(const Vec4& A)
	{
		_vx = A._vx;
		_vy = A._vy;
		_vz = A._vz;
	}

	bool Vec3::isEqual(const Vec3& v, const float epsilon /*= MATH_TOLERANCE*/) const
	{
		float tmpX = _vx - v._vx;
		float tmpY = _vy - v._vy;
		float tmpZ = _vz - v._vz;

		return ((tmpX >= -epsilon) && (tmpX <= epsilon)) 
			&& ((tmpY >= -epsilon) && (tmpY <= epsilon))
			&& ((tmpZ >= -epsilon) && (tmpZ <= epsilon));
	}

	bool Vec3::isZero(const float epsilon) const
	{
		return ((_vx >= -epsilon) && (_vx <= epsilon))
			&& ((_vy >= -epsilon) && (_vy <= epsilon))
			&& ((_vz >= -epsilon) && (_vz <= epsilon));
	}

	void Vec3::Print(const char* pName) const
	{
		Trace::out("%s - \n", pName);
		Trace::out("x: %.6f, y: %.6f, z: %.6f", _vx, _vy, _vz);
	}
}

//--- End of File ---
