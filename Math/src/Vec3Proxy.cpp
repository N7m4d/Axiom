#include "MathEngine.h"

namespace Axiom
{
	Vec3Proxy::Vec3Proxy(float a, float b, float c)
		: x{a}
		, y{b}
		, z{c}
		, len{x * x + y * y + z * z}
	{
	}

	Vec3Proxy::operator float() const
	{
		return Trig::sqrt(len);
	}

	float Vec3Proxy::operator*(const Vec3Proxy& r) const
	{
		return Trig::sqrt(len * r.len);
	}

	bool Vec3Proxy::operator>(const Vec3Proxy& r) const
	{
		return len > r.len;
	}

	bool Vec3Proxy::operator<(const Vec3Proxy& r) const
	{
		return len < r.len;
	}

	bool Vec3Proxy::operator==(const Vec3Proxy& r) const
	{
		return len == r.len;
	}

	bool Vec3Proxy::operator>=(const Vec3Proxy& r) const
	{
		return len >= r.len;
	}

	bool Vec3Proxy::operator<=(const Vec3Proxy& r) const
	{
		return len <= r.len;
	}

	bool Vec3Proxy::operator!=(const Vec3Proxy& r) const
	{
		return len != r.len;
	}
}

//--- End of File ---
