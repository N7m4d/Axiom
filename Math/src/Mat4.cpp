#include "MathEngine.h"

namespace Axiom
{
	Mat4::Mat4()
	{
		memset(this, 0, sizeof(_rows));
		privSetGeneralHint();
	}

	Mat4::Mat4(const Vec4& tV0, const Vec4& tV1, const Vec4& tV2, const Vec4& tV3)
		: _v0{ tV0 }
		, _v1{ tV1 }
		, _v2{ tV2 }
		, _v3{ tV3 }
	{
		privSetGeneralHint();
	}

	Mat4::Mat4(const Mat3& m)
		: _v0{ m._v0 }
		, _v1{ m._v1 }
		, _v2{ m._v2 }
		, _v3{ m._v3 }
	{
	}

	Mat4::Mat4(const Quat& q)
	{
		const float qx = q._qx * q._qx;
		const float qy = q._qy * q._qy;
		const float qz = q._qz * q._qz;
		const float qxy = q._qx * q._qy;
		const float qwz = q._qw * q._qz;
		const float qxz = q._qx * q._qz;
		const float qwy = q._qw * q._qy;
		const float qyz = q._qy * q._qz;
		const float qwx = q._qw * q._qx;

		_v0.set(1.0f - 2.0f * (qy + qz), 2.0f * (qxy + qwz), 2.0f * (qxz - qwy), 0.0f);
		_v1.set(2.0f * (qxy - qwz), 1.0f - 2.0f * (qx + qz), 2.0f * (qyz + qwx), 0.0f);
		_v2.set(2.0f * (qxz + qwy), 2.0f * (qyz - qwx), 1.0f - 2.0f * (qx + qy), 0.0f);
		_v3.set(0.0f, 0.0f, 0.0f, 1.0f);
	}

	Mat4::Mat4(const float m0, const float m1, const float m2, const float m3, const float m4, const float m5, const float m6, const float m7, const float m8,
		const float m9, const float m10, const float m11, const float m12, const float m13, const float m14, const float m15)
		: _m0{ m0 }
		, _m1{ m1 }
		, _m2{ m2 }
		, _m3{ m3 }
		, _m4{ m4 }
		, _m5{ m5 }
		, _m6{ m6 }
		, _m7{ m7 }
		, _m8{ m8 }
		, _m9{ m9 }
		, _m10{ m10 }
		, _m11{ m11 }
		, _m12{ m12 }
		, _m13{ m13 }
		, _m14{ m14 }
		, _m15{ m15 }
	{
	}

	Mat4::Mat4(const enum Identity_enum)
		: Mat4()
	{
		_m0 = 1.0f;
		_m5 = 1.0f;
		_m10 = 1.0f;
		_m15 = 1.0f;
	}

	void Mat4::set(const Mat4& mIn)
	{
		_v0 = mIn._v0;
		_v1 = mIn._v1;
		_v2 = mIn._v2;
		_v3 = mIn._v3;

		privSetCopyHint();
	}

	void Mat4::set(const Vec4& V0, const Vec4& V1, const Vec4& V2, const Vec4& V3)
	{
		_v0 = V0;
		_v1 = V1;
		_v2 = V2;
		_v3 = V3;

		privSetCopyHint();
	}

	void Mat4::set(const enum Identity_enum)
	{
		Hint hint = privGetHint();

		memset(this, 0, sizeof(_rows));

		_m0 = 1.0f;
		_m5 = 1.0f;
		_m10 = 1.0f;
		_m15 = 1.0f;

		switch (hint)
		{
		case Hint::Generalize:
			privSetGeneralHint();
			break;
		case Hint::Rot:
			privSetRotHint();
			break;
		case Hint::Scale:
			privSetScaleHint();
			break;
		case Hint::Trans:
			privSetTransHint();
			break;
		case Hint::RotScale:
		{
			privSetRotHint();
			privSetScaleHint();
		}
		break;
		case Hint::RotTrans:
		{
			privSetRotHint();
			privSetTransHint();
		}
		break;
		case Hint::TransScale:
		{
			privSetTransHint();
			privSetScaleHint();
		}
		break;
		case Hint::Affine:
		{
			privSetTransHint();
			privSetScaleHint();
			privSetRotHint();
		}
		break;

		default:
			privSetGeneralHint();
			break;
		}
	}

	void Mat4::set(const Row4 type, const Vec4& V)
	{
		switch (type)
		{
		case Row4::i0:
			_v0 = V;
			break;
		case Row4::i1:
			_v1 = V;
			break;
		case Row4::i2:
			_v2 = V;
			break;
		case Row4::i3:
			_v3 = V;
			break;
		}

		privClearHint();
	}

	void Mat4::set(const Quat& q)
	{
		const float qx = q._qx * q._qx;
		const float qy = q._qy * q._qy;
		const float qz = q._qz * q._qz;
		const float qxy = q._qx * q._qy;
		const float qwz = q._qw * q._qz;
		const float qxz = q._qx * q._qz;
		const float qwy = q._qw * q._qy;
		const float qyz = q._qy * q._qz;
		const float qwx = q._qw * q._qx;

		_v0.set(1.0f - 2.0f * (qy + qz), 2.0f * (qxy + qwz), 2.0f * (qxz - qwy), 0.0f);
		_v1.set(2.0f * (qxy - qwz), 1.0f - 2.0f * (qx + qz), 2.0f * (qyz + qwx), 0.0f);
		_v2.set(2.0f * (qxz + qwy), 2.0f * (qyz - qwx), 1.0f - 2.0f * (qx + qy), 0.0f);
		_v3.set(0.0f, 0.0f, 0.0f, 1.0f);
	}

	Axiom::Vec4 Mat4::get(const Row4 type) const
	{
		switch (type)
		{
		case Row4::i0:
			return _v0;
		case Row4::i1:
			return _v1;
		case Row4::i2:
			return _v2;
		case Row4::i3:
			return _v3;
		}

		return Vec4();
	}

	Mat4Proxy Mat4::operator[](const enum m0_enum)
	{
		return Mat4Proxy(*this, _m0);
	}

	Mat4Proxy Mat4::operator[](const enum m1_enum)
	{
		return Mat4Proxy(*this, _m1);
	}

	Mat4Proxy Mat4::operator[](const enum m2_enum)
	{
		return Mat4Proxy(*this, _m2);
	}

	Mat4Proxy Mat4::operator[](const enum m3_enum)
	{
		return Mat4Proxy(*this, _m3);
	}

	Mat4Proxy Mat4::operator[](const enum m4_enum)
	{
		return Mat4Proxy(*this, _m4);
	}

	Mat4Proxy Mat4::operator[](const enum m5_enum)
	{
		return Mat4Proxy(*this, _m5);
	}

	Mat4Proxy Mat4::operator[](const enum m6_enum)
	{
		return Mat4Proxy(*this, _m6);
	}

	Mat4Proxy Mat4::operator[](const enum m7_enum)
	{
		return Mat4Proxy(*this, _m7);
	}

	Mat4Proxy Mat4::operator[](const enum m8_enum)
	{
		return Mat4Proxy(*this, _m8);
	}

	Mat4Proxy Mat4::operator[](const enum m9_enum)
	{
		return Mat4Proxy(*this, _m9);
	}

	Mat4Proxy Mat4::operator[](const enum m10_enum)
	{
		return Mat4Proxy(*this, _m10);
	}

	Mat4Proxy Mat4::operator[](const enum m11_enum)
	{
		return Mat4Proxy(*this, _m11);
	}

	Mat4Proxy Mat4::operator[](const enum m12_enum)
	{
		return Mat4Proxy(*this, _m12);
	}

	Mat4Proxy Mat4::operator[](const enum m13_enum)
	{
		return Mat4Proxy(*this, _m13);
	}

	Mat4Proxy Mat4::operator[](const enum m14_enum)
	{
		return Mat4Proxy(*this, _m14);
	}

	Mat4Proxy Mat4::operator[](const enum m15_enum)
	{
		return Mat4Proxy(*this, _m15);
	}

	float Mat4::operator[](const enum m0_enum) const
	{
		return _m0;
	}

	float Mat4::operator[](const enum m1_enum) const
	{
		return _m1;
	}

	float Mat4::operator[](const enum m2_enum) const
	{
		return _m2;
	}

	float Mat4::operator[](const enum m3_enum) const
	{
		return _m3;
	}

	float Mat4::operator[](const enum m4_enum) const
	{
		return _m4;
	}

	float Mat4::operator[](const enum m5_enum) const
	{
		return _m5;
	}

	float Mat4::operator[](const enum m6_enum) const
	{
		return _m6;
	}

	float Mat4::operator[](const enum m7_enum) const
	{
		return _m7;
	}

	float Mat4::operator[](const enum m8_enum) const
	{
		return _m8;
	}

	float Mat4::operator[](const enum m9_enum) const
	{
		return _m9;
	}

	float Mat4::operator[](const enum m10_enum) const
	{
		return _m10;
	}

	float Mat4::operator[](const enum m11_enum) const
	{
		return _m11;
	}

	float Mat4::operator[](const enum m12_enum) const
	{
		return _m12;
	}

	float Mat4::operator[](const enum m13_enum) const
	{
		return _m13;
	}

	float Mat4::operator[](const enum m14_enum) const
	{
		return _m14;
	}

	float Mat4::operator[](const enum m15_enum) const
	{
		return _m15;
	}

	void Mat4::m0(const float v)
	{
		_m0 = v;
		privSetGeneralHint();
	}

	void Mat4::m1(const float v)
	{
		_m1 = v;
		privSetGeneralHint();
	}

	void Mat4::m2(const float v)
	{
		_m2 = v;
		privSetGeneralHint();
	}

	void Mat4::m3(const float v)
	{
		_m3 = v;
		privSetGeneralHint();
	}

	void Mat4::m4(const float v)
	{
		_m4 = v;
		privSetGeneralHint();
	}

	void Mat4::m5(const float v)
	{
		_m5 = v;
		privSetGeneralHint();
	}

	void Mat4::m6(const float v)
	{
		_m6 = v;
		privSetGeneralHint();
	}

	void Mat4::m7(const float v)
	{
		_m7 = v;
		privSetGeneralHint();
	}

	void Mat4::m8(const float v)
	{
		_m8 = v;
		privSetGeneralHint();
	}

	void Mat4::m9(const float v)
	{
		_m9 = v;
		privSetGeneralHint();
	}

	void Mat4::m10(const float v)
	{
		_m10 = v;
		privSetGeneralHint();
	}

	void Mat4::m11(const float v)
	{
		_m11 = v;
		privSetGeneralHint();
	}

	void Mat4::m12(const float v)
	{
		_m12 = v;
		privSetGeneralHint();
	}

	void Mat4::m13(const float v)
	{
		_m13 = v;
		privSetGeneralHint();
	}

	void Mat4::m14(const float v)
	{
		_m14 = v;
		privSetGeneralHint();
	}

	void Mat4::m15(const float v)
	{
		_m15 = v;
		privSetGeneralHint();
	}

	float Mat4::m0() const
	{
		return _m0;
	}

	float Mat4::m1() const
	{
		return _m1;
	}

	float Mat4::m2() const
	{
		return _m2;
	}

	float Mat4::m3() const
	{
		return _m3;
	}

	float Mat4::m4() const
	{
		return _m4;
	}

	float Mat4::m5() const
	{
		return _m5;
	}

	float Mat4::m6() const
	{
		return _m6;
	}

	float Mat4::m7() const
	{
		return _m7;
	}

	float Mat4::m8() const
	{
		return _m8;
	}

	float Mat4::m9() const
	{
		return _m9;
	}

	float Mat4::m10() const
	{
		return _m10;
	}

	float Mat4::m11() const
	{
		return _m11;
	}

	float Mat4::m12() const
	{
		return _m12;
	}

	float Mat4::m13() const
	{
		return _m13;
	}

	float Mat4::m14() const
	{
		return _m14;
	}

	float Mat4::m15() const
	{
		return _m15;
	}

	float Mat4::det() const
	{
		return _m0 * (_m5 * (_m10 * _m15 - _m11 * _m14) - _m6 * (_m9 * _m15 - _m11 * _m13) + _m7 * (_m9 * _m14 - _m10 * _m13))
			- _m1 * (_m4 * (_m10 * _m15 - _m11 * _m14) - _m6 * (_m8 * _m15 - _m11 * _m12) + _m7 * (_m8 * _m14 - _m10 * _m12))
			+ _m2 * (_m4 * (_m9 * _m15 - _m11 * _m13) - _m5 * (_m8 * _m15 - _m11 * _m12) + _m7 * (_m8 * _m13 - _m9 * _m12))
			- _m3 * (_m4 * (_m9 * _m14 - _m10 * _m13) - _m5 * (_m8 * _m14 - _m10 * _m12) + _m6 * (_m8 * _m13 - _m9 * _m12));
	}

	Mat4& Mat4::T(void)
	{
		const float m1 = _m4;
		const float m2 = _m8;
		const float m3 = _m12;
		const float m4 = _m1;
		const float m6 = _m9;
		const float m7 = _m13;
		const float m8 = _m2;
		const float m9 = _m6;
		const float m11 = _m14;
		const float m12 = _m3;
		const float m13 = _m7;
		const float m14 = _m11;

		_m1 = m1;
		_m2 = m2;
		_m3 = m3;
		_m4 = m4;
		_m6 = m6;
		_m7 = m7;
		_m8 = m8;
		_m9 = m9;
		_m11 = m11;
		_m12 = m12;
		_m13 = m13;
		_m14 = m14;

		if (privGetHint() == Hint::RotScale)
		{
			_m15 = 1.0f;
		}

		return *this;
	}

	Mat4 Mat4::getT(void) const
	{
		return Mat4(_m0, _m4, _m8, _m12, _m1, _m5, _m9, _m13, _m2, _m6, _m10, _m14, _m3, _m7, _m11, _m15);
	}

	Mat4 Mat4::getInv(void) const
	{
		switch (privGetHint())
		{
		case Hint::Rot:
			return getT();
		case Hint::Trans:
			return Mat4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
				0.0f, -_m12, -_m13, -_m14, 1.0f);
		case Hint::Scale:
			return Mat4(1.0f / _m0, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f / _m5, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f / _m10,
				0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		case Hint::RotTrans:
		{
			return Mat4(_m0, _m4, _m8, 0.0f, _m1, _m5, _m9, 0.0f, _m2, _m6, _m10, 0.0f, 
				(-_m12 * _m0) + (-_m13 * _m1) + (-_m14 * _m2), 
				(-_m12 * _m4) + (-_m13 * _m5) + (-_m14 * _m6), 
				(-_m12 * _m8) + (-_m13 * _m9) + (-_m14 * _m10), 1.0f);
		}

		case Hint::TransScale:
		{
			const float invM0 = 1.0f / _m0;
			const float invM5 = 1.0f / _m5;
			const float invM10 = 1.0f / _m10;

			return Mat4(invM0, 0.0f, 0.0f, 0.0f, 0.0f, invM5, 0.0f, 0.0f, 0.0f, 0.0f, invM10,
				0.0f, -_m12 * invM0, -_m13 * invM5, -_m14 * invM10, 1.0f);
		}

		case Hint::RotScale:
		{
			// Do a full 3x3 inverse
			const float determinant = _m0 * (_m5 * _m10 - _m6 * _m9)
			- _m1 * (_m4 * _m10 - _m6 * _m8)
			+ _m2 * (_m4 * _m9 - _m5 * _m8);;

			if (determinant == 0.0f) {
				return Mat4(Identity);
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

			return Mat4(m0, m1, m2, 0.0f, m4, m5, m6, 0.0f, m8, m9, m10, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		}

		case Hint::Affine:
		{
			// Do a full 3x3 inverse
			const float determinant = _m0 * (_m5 * _m10 - _m6 * _m9)
			- _m1 * (_m4 * _m10 - _m6 * _m8)
			+ _m2 * (_m4 * _m9 - _m5 * _m8);;

			if (determinant == 0.0f) {
				return Mat4(Identity);
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

			return Mat4(m0, m1, m2, 0.0f, m4, m5, m6, 0.0f, m8, m9, m10, 0.0f, 
				(-_m12 * m0) + (-_m13 * m4) + (-_m14 * m8), 
				(-_m12 * m1) + (-_m13 * m5) + (-_m14 * m9), 
				(-_m12 * m2) + (-_m13 * m6) + (-_m14 * m10), _m15);
		}

		case Hint::Generalize:
		default:
			break;
		};

		const float determinant = det();

		if (determinant == 0.0f) {
			return Mat4(Identity); // Return an identity matrix if the current matrix is singular.
		}

		const float inversedDet = 1.0f / determinant;

		float t1 = (_m10 * _m15) - (_m11 * _m14);
		float t2 = (_m9 * _m15) - (_m11 * _m13);
		float t3 = (_m9 * _m14) - (_m10 * _m13);
		float t4 = (_m8 * _m15) - (_m11 * _m12);
		float t5 = (_m8 * _m14) - (_m10 * _m12);

		const float m0 = (_m5 * t1) - (_m6 * t2) + (_m7 * t3);
		const float m1 = -((_m1 * t1) - (_m2 * t2) + (_m3 * t3));
		const float m4 = -((_m4 * t1) - (_m6 * t4) + (_m7 * t5));
		const float m5 = (_m0 * t1) - (_m2 * t4) + (_m3 * t5);

		t1 = (_m8 * _m13) - (_m9 * _m12);

		const float m12 = -((_m4 * t3) - (_m5 * t5) + (_m6 * t1));
		const float m13 = (_m0 * t3) - (_m1 * t5) + (_m2 * t1);

		t3 = (_m8 * _m15) - (_m11 * _m12);

		const float m8 = (_m4 * t2) - (_m5 * t3) + (_m7 * t1);
		const float m9 = -((_m0 * t2) - (_m1 * t3) + (_m3 * t1));

		t1 = (_m6 * _m15) - (_m7 * _m14);
		t2 = (_m4 * _m15) - (_m7 * _m12);
		t3 = (_m4 * _m14) - (_m6 * _m12);

		const float m6 = -((_m0 * t1) - (_m2 * t2) + (_m3 * t3));

		t4 = (_m5 * _m14) - (_m6 * _m13);
		t5 = (_m4 * _m13) - (_m5 * _m12);

		const float m14 = -((_m0 * t4) - (_m1 * t3) + (_m2 * t5));

		t3 = (_m5 * _m15) - (_m7 * _m13);

		const float m10 = (_m0 * t3) - (_m1 * t2) + (_m3 * t5);
		const float m2 = (_m1 * t1) - (_m2 * t3) + (_m3 * t4);

		t1 = (_m6 * _m11) - (_m7 * _m10);
		t2 = (_m5 * _m11) - (_m7 * _m9);
		t3 = (_m5 * _m10) - (_m6 * _m9);

		const float m3 = -((_m1 * t1) - (_m2 * t2) + (_m3 * t3));

		t4 = (_m4 * _m11) - (_m7 * _m8);
		t5 = (_m4 * _m10) - (_m6 * _m8);

		const float m7 = (_m0 * t1) - (_m2 * t4) + (_m3 * t5);

		t1 = (_m4 * _m9) - (_m5 * _m8);

		const float m11 = -((_m0 * t2) - (_m1 * t4) + (_m3 * t1));
		const float m15 = (_m0 * t3) - (_m1 * t5) + (_m2 * t1);

		return Mat4(
			m0 * inversedDet, m1 * inversedDet, m2 * inversedDet, m3 * inversedDet,
			m4 * inversedDet, m5 * inversedDet, m6 * inversedDet, m7 * inversedDet,
			m8 * inversedDet, m9 * inversedDet, m10 * inversedDet, m11 * inversedDet,
			m12 * inversedDet, m13 * inversedDet, m14 * inversedDet, m15 * inversedDet);
	}

	Mat4& Mat4::inv(void)
	{
		switch (privGetHint())
		{
		case Hint::Rot:
			T();
			break;

		case Hint::Trans:
		{
			_m12 = -_m12;
			_m13 = -_m13;
			_m14 = -_m14;
		}
		break;

		case Hint::Scale:
		{
			_m0 = 1.0f / _m0;
			_m5 = 1.0f / _m5;
			_m10 = 1.0f / _m10;
		}
		break;

		case Hint::TransScale:
		{
			_m0 = 1.0f / _m0;
			_m5 = 1.0f / _m5;
			_m10 = 1.0f / _m10;

			_m12 = -_m12 * _m0;
			_m13 = -_m13 * _m5;
			_m14 = -_m14 * _m10;
		}
		break;

		case Hint::RotScale:
		{
			// Do a full 3x3 inverse
			Mat3 m(*this);
			m.inv();

			_v0 = m._v0;
			_v1 = m._v1;
			_v2 = m._v2;
		}
		break;

		case Hint::RotTrans:
		{
			// Transpose the matrix
			T();

			// Negate the translation vector
			Vec4 invScale(-_m3, -_m7, -_m11, 1.0f);
			_m3 = 0.0f;
			_m7 = 0.0f;
			_m11 = 0.0f;

			invScale *= *this;

			_v3.set(invScale);
		}
		break;

		case Hint::Affine:
		{
			Mat3 invRotScale(*this);
			invRotScale.inv();

			_v0 = invRotScale._v0;
			_v1 = invRotScale._v1;
			_v2 = invRotScale._v2;

			const float tx = (-_m12 * _m0) + (-_m13 * _m4) + (-_m14 * _m8);
			const float ty = (-_m12 * _m1) + (-_m13 * _m5) + (-_m14 * _m9);
			const float tz = (-_m12 * _m2) + (-_m13 * _m6) + (-_m14 * _m10);

			_v3.set(tx, ty, tz, _m15);
		}
		break;

		case Hint::Generalize:
		default:
		{
			const float determinant = det();

			if (determinant == 0.0f) {
				set(Identity);
				return *this;	// Return an identity matrix if the current matrix is singular.
			}

			const float inversedDet = 1.0f / determinant;

			float t1 = (_m10 * _m15) - (_m11 * _m14);
			float t2 = (_m9 * _m15) - (_m11 * _m13);
			float t3 = (_m9 * _m14) - (_m10 * _m13);
			float t4 = (_m8 * _m15) - (_m11 * _m12);
			float t5 = (_m8 * _m14) - (_m10 * _m12);

			const float m0 = (_m5 * t1) - (_m6 * t2) + (_m7 * t3);
			const float m1 = -((_m1 * t1) - (_m2 * t2) + (_m3 * t3));
			const float m4 = -((_m4 * t1) - (_m6 * t4) + (_m7 * t5));
			const float m5 = (_m0 * t1) - (_m2 * t4) + (_m3 * t5);

			t1 = (_m8 * _m13) - (_m9 * _m12);

			const float m12 = -((_m4 * t3) - (_m5 * t5) + (_m6 * t1));
			const float m13 = (_m0 * t3) - (_m1 * t5) + (_m2 * t1);

			t3 = (_m8 * _m15) - (_m11 * _m12);

			const float m8 = (_m4 * t2) - (_m5 * t3) + (_m7 * t1);
			const float m9 = -((_m0 * t2) - (_m1 * t3) + (_m3 * t1));

			t1 = (_m6 * _m15) - (_m7 * _m14);
			t2 = (_m4 * _m15) - (_m7 * _m12);
			t3 = (_m4 * _m14) - (_m6 * _m12);

			const float m6 = -((_m0 * t1) - (_m2 * t2) + (_m3 * t3));

			t4 = (_m5 * _m14) - (_m6 * _m13);
			t5 = (_m4 * _m13) - (_m5 * _m12);

			const float m14 = -((_m0 * t4) - (_m1 * t3) + (_m2 * t5));

			t3 = (_m5 * _m15) - (_m7 * _m13);

			const float m10 = (_m0 * t3) - (_m1 * t2) + (_m3 * t5);
			const float m2 = (_m1 * t1) - (_m2 * t3) + (_m3 * t4);

			t1 = (_m6 * _m11) - (_m7 * _m10);
			t2 = (_m5 * _m11) - (_m7 * _m9);
			t3 = (_m5 * _m10) - (_m6 * _m9);

			const float m3 = -((_m1 * t1) - (_m2 * t2) + (_m3 * t3));

			t4 = (_m4 * _m11) - (_m7 * _m8);
			t5 = (_m4 * _m10) - (_m6 * _m8);

			const float m7 = (_m0 * t1) - (_m2 * t4) + (_m3 * t5);

			t1 = (_m4 * _m9) - (_m5 * _m8);

			const float m11 = -((_m0 * t2) - (_m1 * t4) + (_m3 * t1));
			const float m15 = (_m0 * t3) - (_m1 * t5) + (_m2 * t1);

			_v0.set(m0 * inversedDet, m1 * inversedDet, m2 * inversedDet, m3 * inversedDet);
			_v1.set(m4 * inversedDet, m5 * inversedDet, m6 * inversedDet, m7 * inversedDet);
			_v2.set(m8 * inversedDet, m9 * inversedDet, m10 * inversedDet, m11 * inversedDet);
			_v3.set(m12 * inversedDet, m13 * inversedDet, m14 * inversedDet, m15 * inversedDet);

			privSetGeneralHint();
		}
		break;
		};

		return *this;
	}

	bool Mat4::isEqual(const Mat4& A, const float epsilon /*= MATH_TOLERANCE*/) const
	{
		return _v0.isEqual(A._v0, epsilon)
			&& _v1.isEqual(A._v1, epsilon)
			&& _v2.isEqual(A._v2, epsilon)
			&& _v3.isEqual(A._v3, epsilon);
	}

	bool Mat4::isIdentity(const float epsilon /*= MATH_TOLERANCE*/) const
	{
		return
			Util::isOne(_m0, epsilon)
			&& Util::isZero(_m1, epsilon)
			&& Util::isZero(_m2, epsilon)
			&& Util::isZero(_m3, epsilon)
			&& Util::isZero(_m4, epsilon)
			&& Util::isOne(_m5, epsilon)
			&& Util::isZero(_m6, epsilon)
			&& Util::isZero(_m7, epsilon)
			&& Util::isZero(_m8, epsilon)
			&& Util::isZero(_m9, epsilon)
			&& Util::isOne(_m10, epsilon)
			&& Util::isZero(_m11, epsilon)
			&& Util::isZero(_m12, epsilon)
			&& Util::isZero(_m13, epsilon)
			&& Util::isZero(_m14, epsilon)
			&& Util::isOne(_m15, epsilon);
	}

	Mat4 Mat4::operator+(void) const
	{
		return Mat4(+_v0, +_v1, +_v2, +_v3);
	}

	Mat4 Mat4::operator+(const Mat4& A) const
	{
		return Mat4(_v0 + A._v0, _v1 + A._v1, _v2 + A._v2, _v3 + A._v3);
	}

	Mat4& Mat4::operator+=(const Mat4& A)
	{
		_v0 += A._v0;
		_v1 += A._v1;
		_v2 += A._v2;
		_v3 += A._v3;

		privSetGeneralHint();

		return *this;
	}

	Mat4 Mat4::operator-(void) const
	{
		return Mat4(-_v0, -_v1, -_v2, -_v3);
	}

	Mat4 Mat4::operator-(const Mat4& A) const
	{
		return Mat4(_v0 - A._v0, _v1 - A._v1, _v2 - A._v2, _v3 - A._v3);
	}

	Mat4& Mat4::operator-=(const Mat4& A)
	{
		_v0 -= A._v0;
		_v1 -= A._v1;
		_v2 -= A._v2;
		_v3 -= A._v3;

		privSetGeneralHint();

		return *this;
	}

	Mat4 Mat4::operator*(const float s) const
	{
		return Mat4(_v0 * s, _v1 * s, _v2 * s, _v3 * s);
	}

	Mat4 operator*(const float scale, const Mat4& A)
	{
		return A * scale;
	}

	Mat4& Mat4::operator*=(const float scale)
	{
		_v0 *= scale;
		_v1 *= scale;
		_v2 *= scale;
		_v3 *= scale;

		privSetGeneralHint();

		return *this;
	}

	Mat4 Mat4::operator*(const Mat4& A) const
	{
		Mat4 result;

		float x = _m0;
		float y = _m1;
		float z = _m2;
		float w = _m3;

		result._m0 = x * A._m0 + y * A._m4 + z * A._m8 + w * A._m12;
		result._m1 = x * A._m1 + y * A._m5 + z * A._m9 + w * A._m13;
		result._m2 = x * A._m2 + y * A._m6 + z * A._m10 + w * A._m14;
		result._m3 = x * A._m3 + y * A._m7 + z * A._m11 + w * A._m15;

		x = _m4;
		y = _m5;
		z = _m6;
		w = _m7;

		result._m4 = x * A._m0 + y * A._m4 + z * A._m8 + w * A._m12;
		result._m5 = x * A._m1 + y * A._m5 + z * A._m9 + w * A._m13;
		result._m6 = x * A._m2 + y * A._m6 + z * A._m10 + w * A._m14;
		result._m7 = x * A._m3 + y * A._m7 + z * A._m11 + w * A._m15;

		x = _m8;
		y = _m9;
		z = _m10;
		w = _m11;

		result._m8 = x * A._m0 + y * A._m4 + z * A._m8 + w * A._m12;
		result._m9 = x * A._m1 + y * A._m5 + z * A._m9 + w * A._m13;
		result._m10 = x * A._m2 + y * A._m6 + z * A._m10 + w * A._m14;
		result._m11 = x * A._m3 + y * A._m7 + z * A._m11 + w * A._m15;

		x = _m12;
		y = _m13;
		z = _m14;
		w = _m15;

		result._m12 = x * A._m0 + y * A._m4 + z * A._m8 + w * A._m12;
		result._m13 = x * A._m1 + y * A._m5 + z * A._m9 + w * A._m13;
		result._m14 = x * A._m2 + y * A._m6 + z * A._m10 + w * A._m14;
		result._m15 = x * A._m3 + y * A._m7 + z * A._m11 + w * A._m15;

		result.privSetNewHint(privGetHint(), A.privGetHint());

		return result;
	}

	Mat4& Mat4::operator*=(const Mat4& A)
	{
		float x = _m0;
		float y = _m1;
		float z = _m2;
		float w = _m3;

		_m0 = x * A._m0 + y * A._m4 + z * A._m8 + w * A._m12;
		_m1 = x * A._m1 + y * A._m5 + z * A._m9 + w * A._m13;
		_m2 = x * A._m2 + y * A._m6 + z * A._m10 + w * A._m14;
		_m3 = x * A._m3 + y * A._m7 + z * A._m11 + w * A._m15;

		x = _m4;
		y = _m5;
		z = _m6;
		w = _m7;

		_m4 = x * A._m0 + y * A._m4 + z * A._m8 + w * A._m12;
		_m5 = x * A._m1 + y * A._m5 + z * A._m9 + w * A._m13;
		_m6 = x * A._m2 + y * A._m6 + z * A._m10 + w * A._m14;
		_m7 = x * A._m3 + y * A._m7 + z * A._m11 + w * A._m15;

		x = _m8;
		y = _m9;
		z = _m10;
		w = _m11;

		_m8 = x * A._m0 + y * A._m4 + z * A._m8 + w * A._m12;
		_m9 = x * A._m1 + y * A._m5 + z * A._m9 + w * A._m13;
		_m10 = x * A._m2 + y * A._m6 + z * A._m10 + w * A._m14;
		_m11 = x * A._m3 + y * A._m7 + z * A._m11 + w * A._m15;

		x = _m12;
		y = _m13;
		z = _m14;
		w = _m15;

		_m12 = x * A._m0 + y * A._m4 + z * A._m8 + w * A._m12;
		_m13 = x * A._m1 + y * A._m5 + z * A._m9 + w * A._m13;
		_m14 = x * A._m2 + y * A._m6 + z * A._m10 + w * A._m14;
		_m15 = x * A._m3 + y * A._m7 + z * A._m11 + w * A._m15;

		return *this;
	}

	Mat4& Mat4::operator*=(const Quat& q)
	{
		*this *= Rot(q);
		return *this;
	}

	Mat4 Mat4::operator*(const Rot& A) const
	{
		Mat4 result;

		float x = _m0;
		float y = _m1;
		float z = _m2;

		result._m0 = x * A._m0 + y * A._m4 + z * A._m8;
		result._m1 = x * A._m1 + y * A._m5 + z * A._m9;
		result._m2 = x * A._m2 + y * A._m6 + z * A._m10;
		result._m3 = _m3;

		x = _m4;
		y = _m5;
		z = _m6;

		result._m4 = x * A._m0 + y * A._m4 + z * A._m8;
		result._m5 = x * A._m1 + y * A._m5 + z * A._m9;
		result._m6 = x * A._m2 + y * A._m6 + z * A._m10;
		result._m7 = _m7;

		x = _m8;
		y = _m9;
		z = _m10;

		result._m8 = x * A._m0 + y * A._m4 + z * A._m8;
		result._m9 = x * A._m1 + y * A._m5 + z * A._m9;
		result._m10 = x * A._m2 + y * A._m6 + z * A._m10;
		result._m11 = _m11;

		x = _m12;
		y = _m13;
		z = _m14;

		result._m12 = x * A._m0 + y * A._m4 + z * A._m8;
		result._m13 = x * A._m1 + y * A._m5 + z * A._m9;
		result._m14 = x * A._m2 + y * A._m6 + z * A._m10;
		result._m15 = _m15;

		result.privSetNewHint(privGetHint(), A.privGetHint());

		return result;
	}

	Mat4& Mat4::operator*=(const Rot& A)
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

		privSetNewHint(privGetHint(), A.privGetHint());

		return *this;
	}

	void Mat4::Print(const char* pName) const
	{
		Trace::out("%s - \n", pName);
		_v0.Print("Row[0]");
		_v1.Print("Row[1]");
		_v2.Print("Row[2]");
		_v3.Print("Row[3]");
	}
}

// ---  End of File ---
