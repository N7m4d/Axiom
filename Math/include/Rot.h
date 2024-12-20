#ifndef ENGINE_MATH_ROT_4x4_H
#define ENGINE_MATH_ROT_4x4_H

#include "Mat4.h"

namespace Axiom
{
	class Rot final : public Mat4
	{
	public:
		// Big 4
		Rot();
		Rot &operator = (const Rot &) = default;
		Rot(const Rot &) = default;
		~Rot() = default;

		explicit Rot(const Quat &);
		Rot & operator = (const Quat &);

		// Big 6
		Rot(Rot &&) = default;
		Rot &operator = (Rot &&) = default;

		Rot(const enum Identity_enum);
		Rot(const Rot1 type, const float angle);
		Rot(const Rot3 mode, const float angle_0, const float angle_1, const float angle_2);
		Rot(const Axis mode, const Vec3 &vAxis, const float angle_radians);
		Rot(const Orient type, const Vec3 &dof, const Vec3 &up);

		void set(const Quat &);
		void set(const enum Identity_enum);
		void set(const Rot &);
		void set(const Rot1 type, const float angle);
		void set(const Rot3 mode, const float angle_0, const float angle_1, const float angle_2);
		void set(const Axis mode, const Vec3 &vAxis, const float angle_radians);
		void set(const Orient, const Vec3 &dof, const Vec3 &up);

		// Multiply
		Mat4 operator * (const Mat4 &A) const;
		Rot &operator *= (const Mat4 &A) = delete;

		Rot operator * (const Quat &A) const;
		Rot &operator *= (const Quat &A);

		Mat4 operator * (const Scale &A) const;
		Rot &operator *= (const Scale &A) = delete;

		Rot operator * (const Rot &A) const;
		Rot &operator *= (const Rot &A);

		Mat4 operator * (const Trans &A) const;
		Rot &operator *= (const Trans &A) = delete;

	private:

	};
}

#endif
