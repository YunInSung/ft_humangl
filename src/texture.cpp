#include "texture.h"

TextureUPtr Texture::CreateFromImage(const Image *image) {
	if (image == nullptr)
		return nullptr;
	auto texture = TextureUPtr(new Texture());
	texture->CreateTexture();
	texture->SetTextureFromImage(image);
	return std::move(texture);
}

Texture::~Texture() {
	if (m_texture)
	{
		glDeleteTextures(1, &m_texture);
	}
}

void Texture::Bind() const {
	glBindTexture(GL_TEXTURE_2D, m_texture); // 앞으로 사용할 2d texture은 m_texture로 바인딩
}

void Texture::SetFilter(uint32_t minFilter, uint32_t magFilter) const {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	//glTexParameteri에서 GL_TEXTURE_2D는 바인딩된 m_texture를 사용하겠다는 의미이다.
	//GL_TEXTURE_MIN_FILTER는 이미지가 많이 축소되었을때 사용하는 필터
    //GL_TEXTURE_MAG_FILTER는 이미지가 많이 확대되었을때 사용하는 필터
}

void Texture::SetWrap(uint32_t sWarp, uint32_t tWrap) const {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWarp);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap);
	//glTexParameteri에서 GL_TEXTURE_2D는 바인딩된 m_texture를 사용하겠다는 의미이다.
    //GL_TEXTURE_WRAP_ S는 좌표평면상 x축, T는 y축을 의미한다.
    //GL_CLAMP_TO_EDGE 텍스쳐가 범위를 벗어나면 제일 모서리 부분의 컬러를 그대로 가져다 쓰겠다는 의미
}

void Texture::CreateTexture() {
	glGenTextures(1, &m_texture); // opengl texture obj 생성
	Bind();
	SetFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
	//GL_LINEAR_MIPMAP_LINEAR : 적합한 두 레벨의 텍스처에서 linear filtering된 값을 다시 linear interpolation한다.
	//GL_NEAREST_MIPMAP_NEAREST : 적합한 레벨의 텍스처를 선택한 뒤 nearest neighbor 픽셀을 선택한다.
	SetWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
}

void Texture::SetTextureFromImage(const Image* image)
{
	GLenum format = GL_RGBA;
	switch (image->GetChannelCount()) {
		default: break;
		case 1: format = GL_RED; break;
		case 2: format = GL_RG; break;
		case 3: format = GL_RGB; break;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->GetWidth(), image->GetHeight(), 0, format, GL_UNSIGNED_BYTE, image->GetData());
	//glTexImage2D(target, level, internalFormat, width, height, border, format, type, data)
    // 바인딩된 텍스처의 크기/픽셀 포맷을 설정하고 GPU에 이미지 데이터를 복사
    // target : 대상이 될 바인딩 텍스쳐
    // level : 설정할 텍스처의 레벨
    // internalFormat : 텍스처의 픽셀 포맷
    // width, height : 텍스처 이미지의 가로 세로 크기
    // border : 텍스처 외곽의 border의 크기
    // format : 입력하는 이미지의 픽셀 포맷
    // type : 입력하는 이미지의 채널별 데이터 타입
    // data : 이미지 데이터가 기록된 메모리 주소

	glGenerateMipmap(GL_TEXTURE_2D); // GL_LINEAR_MIPMAP_LINEAR 설정을 적용하면 밉맵을 자동으로 생성해준다.
}