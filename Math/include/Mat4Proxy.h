#ifndef ENGINE_MATH_MAT4_PROXY_H
#define ENGINE_MATH_MAT4_PROXY_H

namespace Axiom
{
	struct Mat4Proxy
	{
		Mat4Proxy(Mat4& m, float& _x)
			: ref(m), x(_x)
		{
		}

		inline Mat4Proxy operator=(float v)
		{
			x = v;
			ref._u_m15 &= (unsigned int)(0xFFFFFFF8);

			return *this;
		}

		inline operator float()
		{
			return x;
		}

		Mat4& ref;
		float& x;
	};
}

#endif
