#pragma once
#include <cstddef>
#include <cstdint>
#include <utility>
namespace rage {
	class Vector2;
	class Vector3;
	class Vector4;
	struct vector2 {
		float x, y;
		Vector2 serialize();
	};
	struct vector3 {
		float x, y, z;
		Vector3 serialize();
	};
	struct vector4 {
		float x, y, z, w;
		Vector4 serialize();
	};
	union matrix34 {
		float data[3][4];
		struct { struct { float x, y, z, w; } rows[3]; };
	};
	union matrix44 {
		float data[4][4];
		struct { struct { float x, y, z, w; } rows[4]; };
	};
	class scrVector {
	public:
		scrVector() : x(0.f), y(0.f), z(0.f) {}
		scrVector(float x, float y, float z) : x(x), y(y), z(z) {}
	public:
		alignas(8) float x, y, z;
	};
	union scrValue {
		int32_t Int;
		uint32_t Uns;
		float Float;
		const char* String;
		scrValue* Reference;
		size_t Any;
		bool operator==(const scrValue& val) {
			return Int == val.Int;
		}
	};
	class scrVectorSpace {
	public:
		void Reset() {
			BufferCount = 0;
		}
		void CopyReferencedParametersOut() {
			while (BufferCount--) {
				Orig[BufferCount][0].Float = Buffer[BufferCount].x;
				Orig[BufferCount][1].Float = Buffer[BufferCount].y;
				Orig[BufferCount][2].Float = Buffer[BufferCount].z;
			}
		}
//Bug: The variable BufferCount is used without being initialized.
		uint32_t BufferCount; //0x0000
		scrValue* Orig[4]; //0x0004
		scrVector Buffer[4]; //0x0020
	}; //Size: 0x0060
	class scrNativeCallContext {
	public:
		void Reset() {
			ArgCount = 0;
			VectorSpace.Reset();
		}
		template <typename t>
		void PushArg(t&& value) {
			static_assert(sizeof(t) <= sizeof(std::uint64_t));
			*reinterpret_cast<std::remove_cv_t<std::remove_reference_t<t>>*>(reinterpret_cast<std::uint64_t*>(Args) + (ArgCount++)) = std::forward<t>(value);
		}
		template <typename t>
		t& Arg(std::size_t index) {
			static_assert(sizeof(t) <= sizeof(std::uint64_t));
			return *reinterpret_cast<t*>(reinterpret_cast<std::uint64_t*>(Args) + index);
		}
		template<typename type>
		inline type GetArgument(int index)
		{
			intptr_t* args = (intptr_t*)Args;
			return *(type*)&args[index];
		}
		template <typename t>
		void SetArg(std::size_t index, t&& value) {
			static_assert(sizeof(t) <= sizeof(std::uint64_t));
			*reinterpret_cast<std::remove_cv_t<std::remove_reference_t<t>>*>(reinterpret_cast<std::uint64_t*>(Args) + index) = std::forward<t>(value);
		}
		template <typename t>
		t* GetReturn() {
			return reinterpret_cast<t*>(Return);
		}

		void* GetResultPtr() {
			return Return;
		}
		template <typename t>
		void SetReturn(t value) {
			*reinterpret_cast<std::remove_cv_t<std::remove_reference_t<t>>*>(Return) = value;
		}
		template<typename type>
		inline void SetReturn(int index, type value)
		{
			intptr_t* return_values = (intptr_t*)Return;
			*(type*)&return_values[index] = value;
		}
	public:
		scrValue* Return; //0x0000
		uint32_t ArgCount; //0x0008
		scrValue* Args; //0x0010
		scrVectorSpace VectorSpace;
	}; //Size: 0x00E0
	using scrNativeHash = uint64_t;
	struct scrNativePair {
		scrNativeHash hash, translatedHash;
	};
	using scrNativeHandler = void(*)(scrNativeCallContext*);
}
class Vector2 final {
public:
	Vector2() : x(0.f), y(0.f) {}
	Vector2(float x, float y) : x(x), y(y) {}
public:
	alignas(8) float x, y;
	rage::vector2 deserialize() {
		return { x, y };
	}
	bool empty() {
		return x == 0.f && y == 0.f;
	}
public:
	Vector2 operator*(const float amount) {
		return { x * amount, y * amount };
	}
	Vector2 operator*(const Vector2 vec) {
		return { x * vec.x, y * vec.y };
	}
	Vector2 operator/(const float amount) {
		return { x / amount, y / amount };
	}
	Vector2 operator/(const Vector2 vec) {
		return { x / vec.x, y - vec.y };
	}
	Vector2 operator+(const float amount) {
		return { x + amount, y + amount };
	}
	Vector2 operator+(const Vector2 vec) {
		return { x + vec.x, y + vec.y };
	}
	Vector2 operator-(const float amount) {
		return { x - amount, y - amount };
	}
	Vector2 operator-(const Vector2 vec) {
		return { x - vec.x, y - vec.y };
	}
};
class Vector3 : public rage::scrVector {
public:
	Vector3() : rage::scrVector() {}
	Vector3(float x, float y, float z) : rage::scrVector(x, y, z) {}
public:
	rage::vector3 deserialize() {
		return { x, y, z };
	}
	bool empty() {
		return x == 0.f && y == 0.f && z == 0.f;
	}
	bool contains_zero() {
		return x == 0.f || y == 0.f || z == 0.f;
	}
	float length() {
		return std::sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
	}
public:
	Vector3 operator*(const float amount) {
		return { x * amount, y * amount, z * amount };
	}
	Vector3 operator*(const Vector3 vec) {
		return { x * vec.x, y * vec.y, z * vec.z };
	}
	Vector3 operator/(const float amount) {
		return { x / amount, y / amount, z / amount };
	}
	Vector3 operator/(const Vector3 vec) {
		return { x / vec.x, y - vec.y, z / vec.z };
	}
	Vector3 operator+(const float amount) {
		return { x + amount, y + amount, z + amount };
	}
	Vector3 operator+(const Vector3 vec) {
		return { x + vec.x, y + vec.y, z + vec.z };
	}
	Vector3 operator-(const float amount) {
		return { x - amount, y - amount, z - amount };
	}
	Vector3 operator-(const Vector3 vec) {
		return { x - vec.x, y - vec.y, z - vec.z };
	}
	Vector3& operator*=(const float amount) {
		x *= amount;
		y *= amount;
		z *= amount;
		return *this;
	}

	Vector3& operator/=(const float amount) {
		x /= amount;
		y /= amount;
		z /= amount;
		return *this;
	}

	Vector3& operator+=(const float amount) {
		x += amount;
		y += amount;
		z += amount;
		return *this;
	}

	Vector3& operator-=(const float amount) {
		x -= amount;
		y -= amount;
		z -= amount;
		return *this;
	}

	Vector3& operator*=(const Vector3& vec) {
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;
		return *this;
	}

	Vector3& operator/=(const Vector3& vec) {
		x /= vec.x;
		y /= vec.y;
		z /= vec.z;
		return *this;
	}

	Vector3& operator+=(const Vector3& vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	Vector3& operator-=(const Vector3& vec) {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}


};
class Vector4 final {
public:
	Vector4() = default;
	Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
public:
	alignas(8) float x, y, z, w;
	rage::vector4 deserialize() {
		return { x, y, z, w };
	}
	bool empty() {
		return x == 0.f && y == 0.f && z == 0.f && w == 0.f;
	}
public:
	Vector4 operator*(const float amount) {
		return { x * amount, y * amount, z * amount, w * amount };
	}
	Vector4 operator*(const Vector4 vec) {
		return { x * vec.x, y * vec.y, z * vec.z, w * vec.w };
	}
	Vector4 operator/(const float amount) {
		return { x / amount, y / amount, z / amount, w / amount };
	}
	Vector4 operator/(const Vector4 vec) {
		return { x / vec.x, y / vec.y, z / vec.z, w / vec.w };
	}
	Vector4 operator+(const float amount) {
		return { x + amount, y + amount, z + amount, w + amount };
	}
	Vector4 operator+(const Vector4 vec) {
		return { x + vec.x, y + vec.y, z + vec.z, w + vec.z };
	}
	Vector4 operator-(const float amount) {
		return { x - amount, y - amount, z - amount, w - amount };
	}
	Vector4 operator-(const Vector4 vec) {
		return { x - vec.x, y - vec.y, z - vec.z, w - vec.z };
	}
};
class NativeVector3 {
public:
	NativeVector3() = default;
	NativeVector3(float x, float y, float z) : x(x), y(y), z(z) {}
public:
	float x;
private:
	char m_paddingx[0x04];
public:
	float y;
private:
	char m_paddingy[0x04];
public:
	float z;
private:
	char m_paddingz[0x04];
};

template <typename T>
class vector3 : public rage::scrVector {
public:
	vector3() : rage::scrVector() {}
	vector3(T x, T y, T z) : rage::scrVector(x, y, z) {}
public:
	rage::vector3 deserialize() {
		return { x, y, z };
	}
	bool empty() {
		return x == 0.f && y == 0.f && z == 0.f;
	}
public:
	vector3 operator*(const T amount) {
		return { x * amount, y * amount, z * amount };
	}
	vector3 operator*(const vector3 vec) {
		return { x * vec.x, y * vec.y, z * vec.z };
	}
	vector3 operator/(const T amount) {
		return { x / amount, y / amount, z / amount };
	}
	vector3 operator/(const vector3 vec) {
		return { x / vec.x, y - vec.y, z / vec.z };
	}
	vector3 operator+(const T amount) {
		return { x + amount, y + amount, z + amount };
	}
	vector3 operator+(const vector3 vec) {
		return { x + vec.x, y + vec.y, z + vec.z };
	}
	vector3 operator-(const T amount) {
		return { x - amount, y - amount, z - amount };
	}
	vector3 operator-(const vector3 vec) {
		return { x - vec.x, y - vec.y, z - vec.z };
	}
	vector3& operator*=(const T amount) {
		x *= amount;
		y *= amount;
		z *= amount;
		return *this;
	}

	vector3& operator/=(const T amount) {
		x /= amount;
		y /= amount;
		z /= amount;
		return *this;
	}

	vector3& operator+=(const T amount) {
		x += amount;
		y += amount;
		z += amount;
		return *this;
	}

	vector3& operator-=(const T amount) {
		x -= amount;
		y -= amount;
		z -= amount;
		return *this;
	}

	vector3& operator*=(const vector3& vec) {
		x *= vec.x;
		y *= vec.y;
		z *= vec.z;
		return *this;
	}

	vector3& operator/=(const vector3& vec) {
		x /= vec.x;
		y /= vec.y;
		z /= vec.z;
		return *this;
	}

	vector3& operator+=(const vector3& vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	vector3& operator-=(const vector3& vec) {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}


};