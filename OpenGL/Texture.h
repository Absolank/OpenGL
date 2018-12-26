#pragma once
#include <string>
struct TextureData
{
	int m_Width = 0, m_Height = 0, m_nrChannels = 0;
	unsigned char * m_LocalBuffer;
};
class Texture
{
private:
	unsigned int m_TextureID = 0;
	int m_Width = 0, m_Height = 0, m_nrChannels = 0;
	unsigned char * TextureBuffer;
public:

	Texture(const std::string& path);
	~Texture();
	void Bind(unsigned int slot = 0) const;
	void UnBind() const;
	inline int GetWidth() { return m_Width; }
	inline int GetHeight() { return m_Height; }
};

