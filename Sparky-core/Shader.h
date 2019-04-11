#pragma once

#include <iostream>
// #include <GL/glew.h>
#include <glad/glad.h>
#include "fileutils.h"
#include "maths.h"
#include "glm/glm.hpp"

namespace sparky {
	namespace graphics {
		class Shader {
		public:
			GLuint m_ShaderID;
			const char *m_VertPath;
			const char* m_FragPath;
		public:
			Shader(const char* vertPath, const char* fragPath);
			~Shader();

			GLint getUniformLocation(const GLchar* name);

			void setUniform1f(const GLchar* name, float value);
			void setUniform1i(const GLchar* name, int value);
			void setUniform2f(const GLchar* name, maths::vec2& vec);
			void setUniform3f(const GLchar* name, maths::vec3& vec);
			void setUniform4f(const GLchar* name, maths::vec4& vec);

			void setUniform2f(const GLchar* name, glm::vec2& vec);
			void setUniform3f(const GLchar* name, glm::vec3& vec);
			void setUniform4f(const GLchar* name, glm::vec4& vec);

			void setUniformMat4(const GLchar* name, const maths::mat4& mat);
			void setUniformMat4(const GLchar* name, const glm::mat4& mat);
			void enable() const;
			void disable() const;
		private:
			GLuint load();
		};
	}
}