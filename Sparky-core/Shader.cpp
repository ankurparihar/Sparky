#include "Shader.h"

namespace sparky {
	namespace graphics {
		Shader::Shader(const char* vertPath, const char* fragPath)
			: m_VertPath(vertPath), m_FragPath(fragPath)
		{
			m_ShaderID = load();
		}

		GLuint Shader::load() {
			GLuint program = glCreateProgram();
			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

			std::string fragSourceString = read_file(m_FragPath);
			std::string vertSourceString = read_file(m_VertPath);

			const char* vertSource = vertSourceString.c_str();
			const char* fragSource = fragSourceString.c_str();

			GLint result;

			glShaderSource(vertex, 1, &vertSource, NULL);
			glCompileShader(vertex);

			glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);

			if (result == GL_FALSE) {
				int length;
				glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
				char* message = (char*)malloc((length+1)*sizeof(char));
				glGetShaderInfoLog(vertex, length, &length, message);
				std::cout << "Failed to compile vertex shader: \n" << message << std::endl;
				glDeleteShader(vertex);
				return 0;
			}

			glShaderSource(fragment, 1, &fragSource, NULL);
			glCompileShader(fragment);

			glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);

			if (result == GL_FALSE) {
				int length;
				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
				char* message = (char*)malloc((length + 1) * sizeof(char));
				glGetShaderInfoLog(fragment, length, &length, message);
				std::cout << "Failed to compile fragment shader: \n" << message << std::endl;
				glDeleteShader(fragment);
				return 0;
			}

			glAttachShader(program, vertex);
			glAttachShader(program, fragment);

			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return program;
		}

		Shader::~Shader() {
			glDeleteProgram(m_ShaderID);
		}

		GLint Shader::getUniformLocation(const GLchar* name) {
			return glGetUniformLocation(m_ShaderID, name);
		}

		void Shader::setUniform1f(const GLchar* name, float value) {
			glUniform1f(getUniformLocation(name), value);
		}
		void Shader::setUniform1i(const GLchar* name, int value) {
			glUniform1i(getUniformLocation(name), value);
		}
		void Shader::setUniform2f(const GLchar* name, maths::vec2& vec) {
			glUniform2f(getUniformLocation(name), vec.x, vec.y);
		}
		void Shader::setUniform3f(const GLchar* name, maths::vec3& vec) {
			glUniform3f(getUniformLocation(name), vec.x, vec.y, vec.z);
		}
		void Shader::setUniform4f(const GLchar* name, maths::vec4& vec) {
			glUniform4f(getUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
		}

		void Shader::setUniformMat4(const GLchar* name, const maths::mat4& mat) {
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, mat.elements);
		}

		void Shader::enable() const {
			glUseProgram(m_ShaderID);
		}
		void Shader::disable() const {
			glUseProgram(0);
		}
	}
}