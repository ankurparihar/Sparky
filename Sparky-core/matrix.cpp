#include "matrix.h"

namespace sparky {
	namespace maths {

		mat4::mat4() {
			for (int i = 0; i < 16; ++i) {
				elements[i] = 0.0f;
			}
		}
		mat4::mat4(float f) {
			for (int i = 0; i < 16; ++i) {
				elements[i] = f;
			}
		}
		mat4::mat4(float f, int flag) {
			// mat4();
			if (flag == FILL_IN_MAT) {
				for (int i = 0; i < 16; ++i) {
					elements[i] = f;
				}
			}
			if (flag == DIAGONAL_MAT) {
				for (int i = 0; i < 16; ++i) {
					elements[i] = 0.0f;
				}
				for (int i = 0; i < 16; i += 5) {
					elements[i] = f;
				}
			}
		}
		mat4::mat4(const mat4& mat) {
			for (int i = 0; i < 16; ++i) {
				elements[i] = mat.elements[i];
			}
		}
		mat4::mat4(
			float f00, float f01, float f02, float f03,
			float f10, float f11, float f12, float f13,
			float f20, float f21, float f22, float f23,
			float f30, float f31, float f32, float f33
		) {
				elements[0] = f00, elements[1] = f01, elements[2] = f02, elements[3] = f03,
				elements[4] = f10, elements[5] = f11, elements[6] = f12, elements[7] = f13,
				elements[8] = f20, elements[9] = f21, elements[10] = f22, elements[11] = f23,
				elements[12] = f30, elements[13] = f31, elements[14] = f32, elements[15] = f33;
		}
		mat4 mat4::indentity() {
			mat4 mat = mat4();
			for (int i = 0; i < 16; i += 5) {
				mat[i] = 1.0f;
			}
			return mat;
		}
		
		mat4 mat4::operator+(const float& f) const {
			mat4 new_mat = mat4();
			for (int i = 0; i < 16; ++i) {
				new_mat.elements[i] = elements[i] + f;
			}
			return new_mat;
		}
		mat4 mat4::operator-(const float& f) const {
			mat4 new_mat = mat4();
			for (int i = 0; i < 16; ++i) {
				new_mat.elements[i] = elements[i] - f;
			}
			return new_mat;
		}
		mat4 mat4::operator*(const float& f) const {
			mat4 new_mat = mat4();
			for (int i = 0; i < 16; ++i) {
				new_mat.elements[i] = elements[i] * f;
			}
			return new_mat;
		}
		mat4 mat4::operator/(const float& f) const {
			mat4 new_mat = mat4();
			for (int i = 0; i < 16; ++i) {
				new_mat.elements[i] = elements[i] / f;
			}
			return new_mat;
		}

		mat4 mat4::operator+(const mat4& mat) const {
			mat4 new_mat = mat4();
			for (int i = 0; i < 16; ++i) {
				new_mat.elements[i] = elements[i] + mat.elements[i];
			}
			return new_mat;
		}
		mat4 mat4::operator-(const mat4& mat) const {
			mat4 new_mat = mat4();
			for (int i = 0; i < 16; ++i) {
				new_mat.elements[i] = elements[i] - mat.elements[i];
			}
			return new_mat;
		}
		mat4 mat4::operator*(const mat4& mat) const {
			mat4 new_mat = mat4();
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					for (int k = 0; k < 4; ++k) {
						new_mat.elements[4* i + j] += elements[4 * i + k] * mat.elements[4 * k + j];
					}
				}
			}
			return new_mat;
		}
		vec4 mat4::operator*(const vec4& vec) const {
			return vec4(
				elements[4 * 0 + 0] * vec.x + elements[4 * 0 + 1] * vec.y + elements[4 * 0 + 2] * vec.z + elements[4 * 0 + 3] * vec.w,
				elements[4 * 1 + 0] * vec.x + elements[4 * 1 + 1] * vec.y + elements[4 * 1 + 2] * vec.z + elements[4 * 1 + 3] * vec.w,
				elements[4 * 2 + 0] * vec.x + elements[4 * 2 + 1] * vec.y + elements[4 * 2 + 2] * vec.z + elements[4 * 2 + 3] * vec.w,
				elements[4 * 3 + 0] * vec.x + elements[4 * 3 + 1] * vec.y + elements[4 * 3 + 2] * vec.z + elements[4 * 3 + 3] * vec.w
			);
		}

		void mat4::operator+=(const float& f) {
			for (int i = 0; i < 16; ++i) {
				elements[i] += f;
			}
		}
		void mat4::operator-=(const float& f) {
			for (int i = 0; i < 16; ++i) {
				elements[i] -= f;
			}
		}
		void mat4::operator*=(const float& f) {
			for (int i = 0; i < 16; ++i) {
				elements[i] *= f;
			}
		}
		void mat4::operator/=(const float& f) {
			for (int i = 0; i < 16; ++i) {
				elements[i] /= f;
			}
		}

		void mat4::operator+=(const mat4& mat) {
			for (int i = 0; i < 16; ++i) {
				elements[i] += mat.elements[i];
			}
		}
		void mat4::operator-=(const mat4& mat) {
			for (int i = 0; i < 16; ++i) {
				elements[i] -= mat.elements[i];
			}
		}
		void mat4::operator*=(const mat4& mat) {
			mat4 temp = mat4(*this) * mat;;
			for (int i = 0; i < 16; ++i) {
				elements[i] = temp.elements[i];
			}
			// delete(&temp);
		}

		bool mat4::operator==(const mat4& mat) {
			for (int i = 0; i < 16; ++i) {
				for (int j = 0; j < 16; ++j) {
					if (elements[i] != mat.elements[i]) return false;
				}
			}
			return true;
		}
		bool mat4::operator!=(const mat4& mat) {
			for (int i = 0; i < 16; ++i) {
				for (int j = 0; j < 16; ++j) {
					if (elements[i] != mat.elements[i]) return true;
				}
			}
			return false;
		}

		void mat4::transpose() {
			float temp;
			for (int i = 0; i < 4; ++i) {
				for (int j = i+1; j < 4; ++j) {
					temp = elements[4 * i + j];
					elements[4 * i + j] = elements[4 * j + i];
					elements[4 * j + i] = temp;
				}
			}
		}

		mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far) {
			mat4 mat = mat4();
			mat[0 + 0 * 4] = 2 / (right - left);
			mat[1 + 1 * 4] = 2 / (top - bottom);
			mat[2 + 2 * 4] = 2 / (near - far);
			mat[0 + 3 * 4] = (right + left) / (right - left);
			mat[1 + 3 * 4] = (top + bottom) / (top - bottom);
			mat[2 + 3 * 4] = (far + near) / (far - near);
			mat[3 + 3 * 4] = 1;
			return mat;
		}
		mat4 mat4::perspective(float fov, float aspectRatio, float near, float far) {
			mat4 mat = mat4();
			float tan_a2 = 1 / (float)tan(toRadian(fov / 2));
			mat[0 + 0 * 4] = tan_a2 / aspectRatio;
			mat[1 + 1 * 4] = tan_a2;
			mat[2 + 2 * 4] = (far + near) / (far - near);
			mat[2 + 3 * 4] = 2 * near * far / (near - far);
			mat[3 + 2 * 4] = 1;
			return mat;
		}
		mat4 mat4::translation(const vec3& translation) {
			mat4 mat = mat4::indentity();
			mat[0 + 3 * 4] = translation.x;
			mat[1 + 3 * 4] = translation.y;
			mat[2 + 3 * 4] = translation.z;
			return mat;
		}
		mat4 mat4::Transpose(const mat4& mat) {
			mat4 new_mat = mat4();
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					new_mat.elements[4 * i + j] = mat.elements[4 * j + i];
				}
			}
			return new_mat;
		}
		mat4 mat4::rotation(float angle, const vec3& axis) {
			double r = toRadian(angle);
			float s = (float)sin(r);
			float c = (float)cos(r);
			float omc = 1.0f - c;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			return Transpose(mat4(
				x * x * omc + c    , x * y * omc - z * s, x * z * omc + y * s, 0,
				x * y * omc + z * s, y * y * omc + c    , y * x * omc - x * s, 0,
				x * z * omc - y * s, y * z * omc + x * s, z * z * omc + c    , 0,
				0                  , 0                  , 0                  , 1
			));
		}
		mat4 mat4::scale(const vec3& scale) {
			mat4 mat = mat4();
			mat[0 + 0 * 4] = scale.x;
			mat[1 + 1 * 4] = scale.y;
			mat[2 + 2 * 4] = scale.z;
			mat[3 + 3 * 4] = 1;
			return mat;
		}

		void mat4::glMultiply(const mat4& mat) {
			*this = glMultiply(*this, mat);
		}
		mat4 mat4::glMultiply(const mat4& mat1, const mat4& mat2) {
			mat4 new_mat = mat4();
			float sum;
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					sum = 0.0f;
					for (int k = 0; k < 4; ++k) {
						sum += mat1.elements[4 * k + j] * mat2.elements[4 * i + k];
					}
					new_mat.elements[4 * i + j] = sum;
				}
			}
			return new_mat;
		}

		std::ostream& operator<<(std::ostream& stream, const mat4& mat) {
			stream << "mat4:" << std::endl;
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					stream << mat.elements[4 * i + j] << " ";
				}
				stream << std::endl;
			}
			stream << std::endl;
			return stream;
		}
	}
}