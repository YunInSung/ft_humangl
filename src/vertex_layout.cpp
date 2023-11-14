#include "vertex_layout.h"

VertexLayoutUPtr VertexLayout::Create() {
	auto vertexLayout = VertexLayoutUPtr(new VertexLayout());
	vertexLayout->Init();
	return std::move(vertexLayout);
}

VertexLayout::~VertexLayout() {
	if (m_vertexArrayObject) {
		glDeleteVertexArrays(1, &m_vertexArrayObject);
	}
}

void VertexLayout::Bind() const {
	glBindVertexArray(m_vertexArrayObject);
}

void VertexLayout::SetAttrib(
	uint32_t attribIndex, int count,
	uint32_t type, bool normalized,
	size_t stride, uint64_t offset
) const {
	// [3] Vertex attribute setting
    // vertices의 위치를 각각 어떻게 구성할것인지! layout = x의 x에 들어오는 값!
    // 정점 attribute 중 n번째를 사용하도록 (0번 attribute를 사용할거다!)
	glEnableVertexAttribArray(attribIndex);
	glVertexAttribPointer(attribIndex, count, type, normalized, stride, (const void *)offset);
}

void VertexLayout::Init() {
	// [1] VAO binding :: vertex array obj 생성 & 바인딩
	glGenVertexArrays(1, &m_vertexArrayObject);
	Bind();
}
