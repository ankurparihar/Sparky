#include "vector.h"

namespace sparky {
	namespace maths {
		// vec2 methods
		vec2 vec2::operator+(const vec2& v) {
			return vec2(x + v.x, y + v.y);
		}
		vec2 vec2::operator-(const vec2& v) {
			return vec2(x - v.x, y - v.y);
		}

		vec2 vec2::operator+(const float f) {
			return vec2(x + f, y + f);
		}
		vec2 vec2::operator-(const float f) {
			return vec2(x - f, y - f);
		}
		vec2 vec2::operator*(const float f) {
			return vec2(x * f, y * f);
		}
		vec2 vec2::operator/(const float f) {
			return vec2(x / f, y / f);
		}

		void vec2::operator+=(const vec2& v) {
			x += v.x;
			y += v.y;
		}
		void vec2::operator-=(const vec2& v) {
			x -= v.x;
			y -= v.y;
		}
		void vec2::operator+=(const float f) {
			x += f;
			y += f;
		}
		void vec2::operator-=(const float f) {
			x -= f;
			y -= f;
		}
		void vec2::operator*=(const float f) {
			x *= f;
			y *= f;
		}
		void vec2::operator/=(const float f) {
			x /= f;
			y /= f;
		}

		bool vec2::operator==(const vec2& v) {
			return x == v.x && y == v.y;
		}
		bool vec2::operator!=(const vec2& v) {
			return x != v.x || y != v.y;
		}

		std::ostream& operator<<(std::ostream& stream, const vec2& v) {
			stream << "vec2: (" << v.x << ", " << v.y << ")";
			return stream;
		}

		// vec3 methods
		vec3 vec3::operator+(const vec3& v) {
			return vec3(x + v.x, y + v.y, z + v.z);
		}
		vec3 vec3::operator-(const vec3& v) {
			return vec3(x - v.x, y - v.y, z - v.z);
		}

		vec3 vec3::operator+(const float f) {
			return vec3(x + f, y + f, z + f);
		}
		vec3 vec3::operator-(const float f) {
			return vec3(x - f, y - f, z - f);
		}
		vec3 vec3::operator*(const float f) {
			return vec3(x * f, y * f, z * f);
		}
		vec3 vec3::operator/(const float f) {
			return vec3(x / f, y / f, z / f);
		}

		void vec3::operator+=(const vec3& v) {
			x += v.x;
			y += v.y;
			z += v.z;
		}
		void vec3::operator-=(const vec3& v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}
		void vec3::operator+=(const float f) {
			x += f;
			y += f;
			z += f;
		}
		void vec3::operator-=(const float f) {
			x -= f;
			y -= f;
			z -= f;
		}
		void vec3::operator*=(const float f) {
			x *= f;
			y *= f;
			z *= f;
		}
		void vec3::operator/=(const float f) {
			x /= f;
			y /= f;
			z /= f;
		}

		bool vec3::operator==(const vec3& v) {
			return x == v.x && y == v.y && z == v.z;
		}
		bool vec3::operator!=(const vec3& v) {
			return x != v.x || y != v.y || z != v.z;
		}

		std::ostream& operator<<(std::ostream& stream, const vec3& v) {
			stream << "vec3: (" << v.x << ", " << v.y << ", " << v.z << ")";
			return stream;
		}

		// vec4 methods
		vec4 vec4::operator+(const vec4& v) {
			return vec4(x + v.x, y + v.y, z + v.z, w + v.w);
		}
		vec4 vec4::operator-(const vec4& v) {
			return vec4(x - v.x, y - v.y, z - v.z, w - v.w);
		}

		vec4 vec4::operator+(const float f) {
			return vec4(x + f, y + f, z + f, w + f);
		}
		vec4 vec4::operator-(const float f) {
			return vec4(x - f, y - f, z - f, w - f);
		}
		vec4 vec4::operator*(const float f) {
			return vec4(x * f, y * f, z * f, w * f);
		}
		vec4 vec4::operator/(const float f) {
			return vec4(x / f, y / f, z / f, w / f);
		}

		void vec4::operator+=(const vec4& v) {
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;
		}
		void vec4::operator-=(const vec4& v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;
		}
		void vec4::operator+=(const float f) {
			x += f;
			y += f;
			z += f;
			w += f;
		}
		void vec4::operator-=(const float f) {
			x -= f;
			y -= f;
			z -= f;
			w -= f;
		}
		void vec4::operator*=(const float f) {
			x *= f;
			y *= f;
			z *= f;
			w *= f;
		}
		void vec4::operator/=(const float f) {
			x /= f;
			y /= f;
			z /= f;
			w /= f;
		}

		bool vec4::operator==(const vec4& v) {
			return x == v.x && y == v.y && z == v.z && w == v.w;
		}
		bool vec4::operator!=(const vec4& v) {
			return x != v.x || y != v.y || z != v.z || w != v.w;
		}

		std::ostream& operator<<(std::ostream& stream, const vec4& v) {
			stream << "vec4: (" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
			return stream;
		}

		// Common functions
		float dot(const vec2& v1, const vec2& v2) {
			return v1.x * v2.x + v1.y * v2.y;
		}
	}
}