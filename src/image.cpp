#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

ImageUPtr Image::Load(const std::string& filepath) {
	auto image = ImageUPtr(new Image());
	if (!image->LoadWithStb(filepath))
		return nullptr;
	return std::move(image);
}

ImageUPtr Image::Create(int width, int height, int channelCount) {
	auto image = ImageUPtr(new Image());
	if (!image->Allocate(width, height, channelCount))
		return nullptr;
	return std::move(image);
}

bool Image::Allocate(int width, int height, int channelCount)
{
	m_width = width;
	m_height = height;
	m_channelCount = channelCount;
	m_data = (uint8_t*)malloc(m_width * m_height * m_channelCount);
	return m_data ? true : false;
}

Image::~Image() {
	if (m_data)
		stbi_image_free(m_data);
}

bool Image::LoadWithStb(const std::string& filepath) {
	stbi_set_flip_vertically_on_load(true); // 보통의 이미지는 좌상단을 원점으로 한다. 그러나 opengl은 좌하단을 원점으로 하기 때문에 상기한 코드로 이미지 로딩시 상하를 반전시켜 상하가 반전된 문제를 해결할 수 있다.
	m_data = stbi_load(filepath.c_str(), &m_width, &m_height, &m_channelCount, 0);
	if (!m_data) {
		SPDLOG_ERROR("failed to load image: {}", filepath);
		return false;
	}
	return true;
}

void Image::SetCheckImage(int gridX, int gridY)
{
	for (int j = 0 ; j < m_height;j++) {
		for (int i = 0; i < m_width; i++) {
			int pos = (j * m_width + i) * m_channelCount;//pixel마다 channelCount만큼의 바이트를 사용하고 있으므로 그만큼 건너뛰는 것이다.
			bool even = ((i / gridX) + (j / gridY)) % 2 == 0;
			uint8_t value = even ? 255 : 0;
			for (int k = 0; k < m_channelCount; k++)
			{
				m_data[pos+k] = value;
			}
			if (m_channelCount > 3)
				m_data[pos + 3] = 255;
		}
	}

}
 