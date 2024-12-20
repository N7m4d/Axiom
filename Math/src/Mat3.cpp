#include "MathEngine.h"

namespace Axiom
{
	Mat3::Mat3()
	{
		memset(this, 0, sizeof(_rows));
		//_m15 = 1.0f;
	}

	Mat3::Mat3(const Vec3& tV0, const Vec3& tV1, const Vec3& tV2)
		: _v0{tV0, 0.0f}
		, _v1{tV1, 0.0f}
		, _v2{tV2, 0.0f}
		, _v3{0.0f, 0.0f, 0.0f, 1.0f}
	{
	}

	Mat3::Mat3(const float m0, const float m1, const float m2, const float m4, const float m5, const float m6, const float m8, const float m9, const float m10)
		: _m0{m0}
		, _m1{m1}
		, _m2{m2}
		, _m3{0.0f}
		, _m4{m4}
		, _m5{m5}
		, _m6{m6}
		, _m7{0.0f}
		, _m8{m8}
		, _m9{m9}
		, _m10{m10}
		, _m11{0.0f}
		, _m12{0.0f}
		, _m13{0.0f}
		, _m14{0.0f}
		, _m15{1.0f}
	{
	}

	Mat3::Mat3(const Mat4& m)
		: _v0{m._v0}
		, _v1{m._v1}
		, _v2{m._v2}
		, _v3{0.0f, 0.0f, 0.0f, 1.0f}
	{
	}

	Mat3::Mat3(const enum Identity_enum)
		: Mat3()
	{
		_m0 = 1.0f;
		_m5 = 1.0f;
		_m10 = 1.0f;
		_m15 = 1.0f;
	}

	Axiom::Vec3 Mat3::get(const Row3 type) const
	{
		switch (type)
		{
		case Row3::i0:
			return Vec3(_v0);
		case Row3::i1:
			return Vec3(_v1);
		case Row3::i2:
			return Vec3(_v2);
		}

		return Vec3();
	}

	void Mat3::set(const Mat3& mIn)
	{
		_v0 = mIn._v0;
		_v1 = mIn._v1;
		_v2 = mIn._v2;
		_v3 = mIn._v3;
	}

	void Mat3::set(const Identity_enum type)
	{
		memset(this, 0, sizeof(_rows));

		_m0 = 1.0f;
		_m5 = 1.0f;
		_m10 = 1.0f;
		_m15 = 1.0f;
	}

	void Mat3::set(const Row3 type, const Vec3& V)
	{
		switch (type)
		{
		case Row3::i0:
			_v0 = Vec4(V, 0.0f);
			break;
		case Row3::i1:
			_v1 = Vec4(V, 0.0f);
			break;
		case Row3::i2:
			_v2 = Vec4(V, 0.0f);
			break;
		}
	}

	void Mat3::set(const Vec3& V0, const Vec3& V1, const Vec3& V2)
	{
		_v0 = Vec4(V0, 0.0f);
		_v1 = Vec4(V1, 0.0f);
		_v2 = Vec4(V2, 0.0f);
	}

	float& Mat3::operator[](const enum m0_enum)
	{
		return _m0;
	}

	float& Mat3::operator[](const enum m1_enum)
	{
		return _m1;
	}

	float& Mat3::operator[](const enum m2_enum)
	{
		return _m2;
	}

	float& Mat3::operator[](const enum m4_enum)
	{
		return _m4;
	}

	float& Mat3::operator[](const enum m5_enum)
	{
		return _m5;
	}

	float& Mat3::operator[](const enum m6_enum)
	{
		return _m6;
	}

	float& Mat3::operator[](const enum m8_enum)
	{
		return _m8;
	}

	float& Mat3::operator[](const enum m9_enum)
	{
		return _m9;
	}

	float& Mat3::operator[](const enum m10_enum)
	{
		return _m10;
	}

	float Mat3::operator[](const enum m0_enum) const
	{
		return _m0;
	}

	float Mat3::operator[](const enum m1_enum) const
	{
		return _m1;
	}

	float Mat3::operator[](const enum m2_enum) const
	{
		return _m2;
	}

	float Mat3::operator[](const enum m4_enum) const
	{
		return _m4;
	}

	float Mat3::operator[](const enum m5_enum) const
	{
		return _m5;
	}

	float Mat3::operator[](const enum m6_enum) const
	{
		return _m6;
	}

	float Mat3::operator[](const enum m8_enum) const
	{
		return _m8;
	}

	float Mat3::operator[](const enum m9_enum) const
	{
		return _m9;
	}

	float Mat3::operator[](const enum m10_enum) const
	{
		return _m10;
	}

	void Mat3::m0(const float v)
	{
		_m0 = v;
	}

	void Mat3::m1(const float v)
	{
		_m1 = v;
	}

	void Mat3::m2(const float v)
	{
		_m2 = v;
	}

	void Mat3::m4(const float v)
	{
		_m4 = v;
	}

	void Mat3::m5(const float v)
	{
		_m5 = v;
	}

	void Mat3::m6(const float v)
	{
		_m6 = v;
	}

	void Mat3::m8(const float v)
	{
		_m8 = v;
	}

	void Mat3::m9(const float v)
	{
		_m9 = v;
	}

	void Mat3::m10(const float v)
	{
		_m10 = v;
	}

	float Mat3::m0() const
	{
		return _m0;
	}

	float Mat3::m1() const
	{
		return _m1;
	}

	float Mat3::m2() const
	{
		return _m2;
	}

	float Mat3::m4() const
	{
		return _m4;
	}

	float Mat3::m5() const
	{
		return _m5;
	}

	float Mat3::m6() const
	{
		return _m6;
	}

	float Mat3::m8() const
	{
		return _m8;
	}

	float Mat3::m9() const
	{
		return _m9;
	}

	float Mat3::m10() const
	{
		return _m10;
	}

	float Mat3::det() const
	{
		return _m0 * (_m5 * _m10 - _m6 * _m9)
			- _m1 * (_m4 * _m10 - _m6 * _m8)
			+ _m2 * (_m4 * _m9 - _m5 * _m8);
	}

	Mat3& Mat3::T(void)
	{
		Vec4 tmpV0 = Vec4(_m0, _m4, _m8, _m12);
		Vec4 tmpV1 = Vec4(_m1, _m5, _m9, _m13);
		Vec4 tmpV2 = Vec4(_m2, _m6, _m10, _m14);

		_v0 = tmpV0;
		_v1 = tmpV1;
		_v2 = tmpV2;

		return *this;
	}

	Mat3 Mat3::getT(void) const
	{
		return Mat3(_m0, _m4, _m8, _m1, _m5, _m9, _m2, _m6, _m10);
	}

	Mat3 Mat3::getInv(void) const
	{
		const float determinant = det();

		if (determinant == 0.0f) {
			return Mat3(Identity); // Return an identity matrix if the current matrix is singular.
		}

		const float inversedDet = 1.0f / determinant;

		return Mat3((_m5 * _m10 - _m6 * _m9) * inversedDet, -(_m1 * _m10 - _m2 * _m9) * inversedDet, (_m1 * _m6 - _m2 * _m5) * inversedDet,
			-(_m4 * _m10 - _m6 * _m8) * inversedDet, (_m0 * _m10 - _m2 * _m8) * inversedDet, -(_m0 * _m6 - _m2 * _m4) * inversedDet,
			(_m4 * _m9 - _m5 * _m8) * inversedDet, -(_m0 * _m9 - _m1 * _m8) * inversedDet, (_m0 * _m5 - _m1 * _m4) * inversedDet);
	}

	Mat3& Mat3::inv(void)
	{
		const float determinant = det();

		if (determinant == 0.0f) {
			set(Identity); // Return an identity matrix if the current matrix is singular.
			return *this;
		}

		const float inversedDet = 1.0f / determinant;

		const float m0 = (_m5 * _m10 - _m6 * _m9) * inversedDet;
		const float m1 = -(_m1 * _m10 - _m2 * _m9) * inversedDet;
		const float m2 = (_m1 * _m6 - _m2 * _m5) * inversedDet;
		const float m4 = -(_m4 * _m10 - _m6 * _m8) * inversedDet;
		const float m5 = (_m0 * _m10 - _m2 * _m8) * inversedDet;
		const float m6 = -(_m0 * _m6 - _m2 * _m4) * inversedDet;
		const float m8 = (_m4 * _m9 - _m5 * _m8) * inversedDet;
		const float m9 = -(_m0 * _m9 - _m1 * _m8) * inversedDet;
		const float m10 = (_m0 * _m5 - _m1 * _m4) * inversedDet;

		_v0.set(m0, m1, m2, 0.0f);
		_v1.set(m4, m5, m6, 0.0f);
		_v2.set(m8, m9, m10, 0.0f);

		return *this;
	}

	bool Mat3::isEqual(const Mat3& A, const float epsilon /*= MATH_TOLERANCE*/) const
	{
		return _v0.isEqual(A._v0, epsilon)
			&& _v1.isEqual(A._v1, epsilon)
			&& _v2.isEqual(A._v2, epsilon);
	}

	bool Mat3::isIdentity(const float epsilon /*= MATH_TOLERANCE*/) const
	{
		return 
			Util::isOne(_m0, epsilon)
			&& Util::isZero(_m1, epsilon)
			&& Util::isZero(_m2, epsilon)
			&& Util::isZero(_m4, epsilon)
			&& Util::isOne(_m5, epsilon)
			&& Util::isZero(_m6, epsilon)
			&& Util::isZero(_m8, epsilon)
			&& Util::isZero(_m9, epsilon)
			&& Util::isOne(_m10, epsilon);
	}

	Mat3 Mat3::operator+(void) const
	{
		return Mat3(+Vec3(_v0), +Vec3(_v1), +Vec3(_v2));
	}

	Mat3 Mat3::operator+(const Mat3& A) const
	{
		return Mat3(Vec3(_v0 + A._v0), Vec3(_v1 + A._v1), Vec3(_v2 + A._v2));
	}

	Mat3& Mat3::operator+=(const Mat3& A)
	{
		_v0 += A._v0;
		_v1 += A._v1;
		_v2 += A._v2;

		return *this;
	}

	Mat3 Mat3::operator-(void) const
	{
		return Mat3(-Vec3(_v0), -Vec3(_v1), -Vec3(_v2));
	}

	Mat3 Mat3::operator-(const Mat3& A) const
	{
		return Mat3(Vec3(_v0 - A._v0), Vec3(_v1 - A._v1), Vec3(_v2 - A._v2));
	}

	Mat3& Mat3::operator-=(const Mat3& A)
	{
		_v0 -= A._v0;
		_v1 -= A._v1;
		_v2 -= A._v2;

		return *this;
	}

	Mat3 Mat3::operator*(const float s) const
	{
		return Mat3(Vec3(_v0 * s), Vec3(_v1 * s), Vec3(_v2 * s));
	}

	Mat3 operator*(const float scale, const Mat3& A)
	{
		return A * scale;
	}

	Mat3& Mat3::operator*=(const float scale)
	{
		_v0 *= scale;
		_v1 *= scale;
		_v2 *= scale;

		return *this;
	}

	Mat3 Mat3::operator*(const Mat3& A) const
	{
		Mat3 result;

		float x = _m0;
		float y = _m1;
		float z = _m2;

		result._m0 = x * A._m0 + y * A._m4 + z * A._m8;
		result._m1 = x * A._m1 + y * A._m5 + z * A._m9;
		result._m2 = x * A._m2 + y * A._m6 + z * A._m10;

		x = _m4;
		y = _m5;
		z = _m6;

		result._m4 = x * A._m0 + y * A._m4 + z * A._m8;
		result._m5 = x * A._m1 + y * A._m5 + z * A._m9;
		result._m6 = x * A._m2 + y * A._m6 + z * A._m10;

		x = _m8;
		y = _m9;
		z = _m10;

		result._m8 = x * A._m0 + y * A._m4 + z * A._m8;
		result._m9 = x * A._m1 + y * A._m5 + z * A._m9;
		result._m10 = x * A._m2 + y * A._m6 + z * A._m10;

		x = _m12;
		y = _m13;
		z = _m14;

		result._m12 = x * A._m0 + y * A._m4 + z * A._m8;
		result._m13 = x * A._m1 + y * A._m5 + z * A._m9;
		result._m14 = x * A._m2 + y * A._m6 + z * A._m10;

		return result;
	}

	Mat3& Mat3::operator*=(const Mat3& A)
	{
		float x = _m0;
		float y = _m1;
		float z = _m2;

		_m0 = x * A._m0 + y * A._m4 + z * A._m8;
		_m1 = x * A._m1 + y * A._m5 + z * A._m9;
		_m2 = x * A._m2 + y * A._m6 + z * A._m10;

		x = _m4;
		y = _m5;
		z = _m6;

		_m4 = x * A._m0 + y * A._m4 + z * A._m8;
		_m5 = x * A._m1 + y * A._m5 + z * A._m9;
		_m6 = x * A._m2 + y * A._m6 + z * A._m10;

		x = _m8;
		y = _m9;
		z = _m10;

		_m8 = x * A._m0 + y * A._m4 + z * A._m8;
		_m9 = x * A._m1 + y * A._m5 + z * A._m9;
		_m10 = x * A._m2 + y * A._m6 + z * A._m10;

		x = _m12;
		y = _m13;
		z = _m14;

		_m12 = x * A._m0 + y * A._m4 + z * A._m8;
		_m13 = x * A._m1 + y * A._m5 + z * A._m9;
		_m14 = x * A._m2 + y * A._m6 + z * A._m10;

		return *this;
	}

	void Mat3::Print(const char* pName) const
	{
		Trace::out("%s - \n", pName);
		_v0.Print("Row[0]");
		_v1.Print("Row[1]");
		_v2.Print("Row[2]");
	}

	void Mat3::reset()
	{
		memset(this, 0, sizeof(_rows));
		_m15 = 1.0f;
	}
}

// ---  End of File ---
