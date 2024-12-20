#include "MathEngine.h"

namespace Axiom
{
	Vec4Proxy::Vec4Proxy(float a, float b, float c, float d)
		: x{a}
		, y{b}
		, z{c}
		, w{d}
		, len{x * x + y * y + z * z + w * w}
	{
	}

	Vec4Proxy::operator float() const
	{
		return Trig::sqrt(len);
	}

	float Vec4Proxy::operator*(const Vec4Proxy& r) const
	{
		return Trig::sqrt(len * r.len);
	}

	bool Vec4Proxy::operator>(const Vec4Proxy& r) const
	{
		return len > r.len;
	}

	bool Vec4Proxy::operator<(const Vec4Proxy& r) const
	{
		return len < r.len;
	}

	bool Vec4Proxy::operator==(const Vec4Proxy& r) const
	{
		return len == r.len;
	}

	bool Vec4Proxy::operator>=(const Vec4Proxy& r) const
	{
		return len >= r.len;
	}

	bool Vec4Proxy::operator<=(const Vec4Proxy& r) const
	{
		return len <= r.len;
	}

	bool Vec4Proxy::operator!=(const Vec4Proxy& r) const
	{
		return len != r.len;
	}
}

//--- End of File ---
