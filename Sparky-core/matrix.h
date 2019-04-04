#pragma once
#include "common_math.h"
#include "maths.h"

namespace sparky {
	namespace maths {

		struct mat4 {

			union
			{
				float elements[16];
				vec4 columns[4];
			};
			
			mat4();
			mat4(float f);
			mat4(float f, int flag);
			mat4(const mat4& mat);
			mat4(
				float f00, float f01, float f02, float f03,
				float f10, float f11, float f12, float f13,
				float f20, float f21, float f22, float f23,
				float f30, float f31, float f32, float f33
			);
			static mat4 indentity();

			vec4& operator [] (const int n) { return columns[n]; }
			// float& operator [] (const float& k, const float& m) { return (&k)[m]; }

			mat4 operator+(const float& f) const;
			mat4 operator-(const float& f) const;
			mat4 operator*(const float& f) const;
			mat4 operator/(const float& f) const;
			
			mat4 operator+(const mat4& mat) const;
			mat4 operator-(const mat4& mat) const;
			mat4 operator*(const mat4& mat) const;

			vec4 operator*(const vec4& vec) const;
			vec4 getColumn(const int col) const;
			
			void operator+=(const float& f);
			void operator-=(const float& f);
			void operator*=(const float& f);
			void operator/=(const float& f);

			void operator+=(const mat4& mat);
			void operator-=(const mat4& mat);
			void operator*=(const mat4& mat);

			bool operator==(const mat4& mat);
			bool operator!=(const mat4& mat);

			void transpose();

			static mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
			static mat4 perspective(float fov, float aspectRatio, float near, float far);

			// static void translateX(float x);
			// static void translateY(float y);
			// static void translateZ(float z);
			// static void translate(const vec3& vec);
			static mat4 translation(const vec3& translation);
			
			// static void rotateX(float x);
			// static void rotateY(float y);
			// static void rotateZ(float z);
			// static void rotate(static vec3& vec);
			static mat4 rotation(float angle, const vec3& axis);
			
			// static void scaleX(float x);
			// static void scaleY(float y);
			// static void scaleZ(float z);
			static mat4 scale(const vec3& scale);

			static mat4 Transpose(const mat4& mat);
			
			void glMultiply(const mat4& mat);
			static mat4 glMultiply(const mat4& mat1, const mat4& mat2);


			friend std::ostream& operator<<(std::ostream& stream, const mat4& mat);
		};
	}
}