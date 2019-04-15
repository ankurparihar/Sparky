#pragma once
#include "sppch.h"
#include "Shader.h"

namespace sparky {
	namespace graphics {
		class Texture {
		private:
			unsigned int m_TexID;
			int m_Width, m_Height, m_Channels;
			std::string m_FilePath;
			unsigned char* m_Data;
		public:
			Texture(const std::string& path);
			~Texture();

			void bind(unsigned int slot = 0) const;
			void unbind() const;

			inline int GetWidth() { return m_Width; }
			inline int GetHeight() { return m_Height; }
		};
	}
}