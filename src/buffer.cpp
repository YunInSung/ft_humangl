#include "buffer.h"

BufferUPtr Buffer::CreateWithData(
	uint32_t bufferType, uint32_t usage,
	const void* data, size_t dataSize
) {
	auto buffer = BufferUPtr(new Buffer);
	if (!buffer->Init(bufferType, usage, data, dataSize))
	{
		return nullptr;
	}
	return std::move(buffer);
}

Buffer::~Buffer() {
	if (m_buffer) {
		glDeleteBuffers(1, &m_buffer);
	}
}

void Buffer::Bind() const {
	// Bind array_buffer <- vertex buffer
	glBindBuffer(m_bufferType, m_buffer);
}

bool Buffer::Init(
	uint32_t bufferType, uint32_t usage,
	const void* data, size_t dataSize
) {
	m_bufferType = bufferType;
	m_usage = usage;
	// [2] VBO binding :: 버텍스 버퍼 생성(generate)
	glGenBuffers(1, &m_buffer);
	Bind();
	// 실제로 데이터를 복사하는 과정 : (버텍스 버퍼, 크기 지정, vertices(pointer), 용도) 를 넣어줌.
	glBufferData(m_bufferType, dataSize, data, usage);
	return true;
}


