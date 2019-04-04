#pragma once
#include "common_math.h"

namespace sparky {
	namespace maths {
		struct vec2 {

			float x, y;

			vec2() : x(0.0f), y(0.0f) {}
			vec2(const float& k) : x(k), y(k) {}
			vec2(const vec2& v) : x(v.x), y(v.y) {}
			vec2(const float& x, const float& y) : x(x), y(y) {};

			vec2 operator+(const vec2& v);
			vec2 operator-(const vec2& v);
			vec2 operator+(const float f);
			vec2 operator-(const float f);
			vec2 operator*(const float f);
			vec2 operator/(const float f);

			void operator+=(const vec2& v);
			void operator-=(const vec2& v);
			void operator+=(const float f);
			void operator-=(const float f);
			void operator*=(const float f);
			void operator/=(const float f);

			bool operator==(const vec2& v);
			bool operator!=(const vec2& v);

			friend std::ostream& operator<<(std::ostream& stream, const vec2& v);
		};

		struct vec3 {

			float x, y, z;

			vec3() : x(0.0f), y(0.0f), z(0.0f) {}
			vec3(const float& k) : x(k), y(k), z(k) {}
			vec3(const vec3& v) : x(v.x), y(v.y), z(v.z) {}
			vec3(const vec2& v, float z) : x(v.x), y(v.y), z(z) {}
			vec3(const float x, const vec2& v) : x(x), y(v.x), z(v.y) {}
			vec3(const float& x, const float& y, const float& z) : x(x), y(y), z(z) {};

			vec3 operator+(const vec3& v);
			vec3 operator-(const vec3& v);
			vec3 operator+(const float f);
			vec3 operator-(const float f);
			vec3 operator*(const float f);
			vec3 operator/(const float f);

			void operator+=(const vec3& v);
			void operator-=(const vec3& v);
			void operator+=(const float f);
			void operator-=(const float f);
			void operator*=(const float f);
			void operator/=(const float f);

			bool operator==(const vec3& v);
			bool operator!=(const vec3& v);

			friend std::ostream& operator<<(std::ostream& stream, const vec3& v);
		};

		struct vec4 {

			float x, y, z, w;

			vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
			vec4(const float& k) : x(k), y(k), z(k), w(k) {}
			vec4(const vec4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
			vec4(const vec3& v, const float& w) : x(v.x), y(v.y), z(v.z), w(w) {}
			vec4(const float& x, const vec3& v) : x(x), y(v.x), z(v.y), w(v.z) {}
			vec4(const vec2& v1, const vec2& v2) :x(v1.x), y(v1.y), z(v2.x), w(v2.y) {}
			vec4(const float& x, const float& y, const vec2& v) : x(x), y(y), z(v.x), w(v.y) {}
			vec4(const float& x, const vec2& v, const float& w) : x(x), y(v.x), z(v.y), w(w) {}
			vec4(const vec2& v, const float& z, const float& w) : x(v.x), y(v.y), z(z), w(w) {}
			vec4(const float& x, const float& y, const float& z, const float& w) : x(x), y(y), z(z), w(w) {};

			vec4 operator+(const vec4& v);
			vec4 operator-(const vec4& v);
			vec4 operator+(const float f);
			vec4 operator-(const float f);
			vec4 operator*(const float f);
			vec4 operator/(const float f);

			void operator+=(const vec4& v);
			void operator-=(const vec4& v);
			void operator+=(const float f);
			void operator-=(const float f);
			void operator*=(const float f);
			void operator/=(const float f);

			bool operator==(const vec4& v);
			bool operator!=(const vec4& v);

			friend std::ostream& operator<<(std::ostream& stream, const vec4& v);
		};

		float dot(const vec2& v1, const vec2& v2);
		// static float cross(const vec2& v1, const vec2& v2);
	}
}