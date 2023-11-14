#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "image.h"

CLASS_PTR(Texture)
class Texture {
	public:
		static TextureUPtr CreateFromImage(const Image* image);//ImagePtr이나 ImageUPtr이 아니라 그냥 *를 사용하는 이유 : 소유권에 구애받을 필요 없는 구조이기 때문
		~Texture();

		const uint32_t Get() const { return m_texture; }
	 	void Bind() const;
		void SetFilter(uint32_t minFilter, uint32_t magFilter) const;
		void SetWrap(uint32_t sWarp, uint32_t tWrap) const;

	private:
		Texture() {}
		void CreateTexture();
		void SetTextureFromImage(const Image* image);

		uint32_t m_texture { 0 };
};

#endif