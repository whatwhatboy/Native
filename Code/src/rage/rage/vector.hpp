#pragma once

namespace rage
{
	template<typename T>
	union nvector2
	{
		T data[2];
		struct { T x, y; };

		nvector2(T x, T y) :
			x(x),
			y(y)
		{
		}

		nvector2() :
			x(),
			y()
		{
		}
	};

	template<typename T>
	union nvector3
	{
		T data[3];
		struct { T x, y, z; };

		nvector3(T x, T y, T z) :
			x(x),
			y(y),
			z(z)
		{
		}

		nvector3() :
			x(),
			y(),
			z()
		{
		}
	};

	template<typename T>
	union nvector4
	{
		T data[4];
		struct { T x, y, z, w; };

		nvector4(T x, T y, T z, T w) :
			x(x),
			y(y),
			z(z),
			w(w)
		{
		}

		nvector4() :
			x(),
			y(),
			z(),
			w()
		{
		}
	};

	template<typename T>
	union nmatrix34
	{
		T data[3][4];
		struct { struct { T x, y, z, w; } rows[3]; };
	};

	template<typename T>
	union nmatrix44
	{
		T data[4][4];
		struct { struct { T x, y, z, w; } rows[4]; };
	};

	typedef nvector2<float> fvector2;
	typedef nvector3<float> fvector3;
	typedef nvector4<float> fvector4;
	typedef nmatrix34<float> fmatrix34;
	typedef nmatrix44<float> fmatrix44;
}
