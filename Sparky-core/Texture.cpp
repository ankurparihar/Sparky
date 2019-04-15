#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

namespace sparky {
	namespace graphics {
		Texture::Texture(const std::string& path)
			: m_FilePath(path), m_Data(nullptr), m_Width(0), m_Height(0), m_Channels(0)
		{
			// flip image vertically
			stbi_set_flip_vertically_on_load(1);
			m_Data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Channels, 0);

			glGenTextures(1, &m_TexID);
			glBindTexture(GL_TEXTURE_2D, m_TexID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			if (m_Data) {
				glTexImage2D(GL_TEXTURE_2D, 0, (m_Channels==3) ? GL_RGB : GL_RGBA, m_Width, m_Height, 0, (m_Channels == 3) ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, m_Data);
				glGenerateMipmap(GL_TEXTURE_2D);
			}
			else {
				SPARKY_ERROR("Failed to load textures from file: {0}", m_FilePath);
			}

			if (m_Data) {
				stbi_image_free(m_Data);
			}
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		Texture::~Texture() {
			glDeleteTextures(1, &m_TexID);
		}

		void Texture::bind(unsigned int slot /*= 0*/) const {
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, m_TexID);
		}

		void Texture::unbind() const {
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}