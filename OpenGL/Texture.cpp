#include "Texture.h"
#include <iostream>
#include <GLEW/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>


Texture::Texture(const std::string& path)
{
	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	const char * img_path = path.c_str();
	stbi_set_flip_vertically_on_load(true);
	stbi_uc * data = stbi_load(img_path, &m_Width, &m_Height, &m_nrChannels, STBI_rgb_alpha);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		0x1904+m_nrChannels,
		m_Width,
		m_Height,
		0,
		0x1904+m_nrChannels,
		GL_UNSIGNED_BYTE,
		data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
}  


Texture::~Texture()
{
	glDeleteTextures(1, &m_TextureID);
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
