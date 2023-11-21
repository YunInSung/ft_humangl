#include "program.h" 

ProgramUPtr Program::Create(const std::vector<ShaderPtr>& shaders) {
	auto program = ProgramUPtr(new Program());
	if (!program->Link(shaders))
		return nullptr;
	return std::move(program);
}

ProgramUPtr Program::Create(const std::string& vertShaderFilename,  const std::string& fragShaderFilename) {
	ShaderPtr vs = Shader::CreateFromFile(vertShaderFilename, GL_VERTEX_SHADER);
	ShaderPtr fs = Shader::CreateFromFile(fragShaderFilename, GL_FRAGMENT_SHADER);
	if (!vs || !fs)
		return nullptr;
	return std::move(Create({vs, fs}));
}

Program::~Program() {
	if (m_program)
	{
		glDeleteProgram(m_program);
	}
}

bool Program::Link(const std::vector<ShaderPtr>& shaders) {
	m_program = glCreateProgram();
	for (auto& shader: shaders)
		glAttachShader(m_program, shader->Get());
	glLinkProgram(m_program);

	int success = 0;
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[1024];
		glGetProgramInfoLog(m_program, 1024, nullptr, infoLog);
		SPDLOG_ERROR("failed to link program: {}", infoLog);
		return false;
	}
	return true;
}

void Program::Use() const {
	glUseProgram(m_program);
}

void Program::SetUniform(const std::string& name, int value) const {
	// glActiveTexture(GL_TEXTURE0);// glActiveTexture는 앞으로 내가 건드릴 텍스트 슬롯의 번호를 알려준다.
    // glBindTexture(GL_TEXTURE_2D, m_texture->Get()); // 0번 슬롯에 할당할 텍스처는 2d 텍스처이고 그 텍스처를 할당한다.
    // glActiveTexture(GL_TEXTURE1);
    // glBindTexture(GL_TEXTURE_2D, m_texture2->Get());
	auto loc = glGetUniformLocation(m_program, name.c_str());
	glUniform1i(loc, value);// value번 슬롯에 바인딩한다는 뜻
}

void Program::SetUniform(const std::string& name, bool value) const {
	// glActiveTexture(GL_TEXTURE0);// glActiveTexture는 앞으로 내가 건드릴 텍스트 슬롯의 번호를 알려준다.
    // glBindTexture(GL_TEXTURE_2D, m_texture->Get()); // 0번 슬롯에 할당할 텍스처는 2d 텍스처이고 그 텍스처를 할당한다.
    // glActiveTexture(GL_TEXTURE1);
    // glBindTexture(GL_TEXTURE_2D, m_texture2->Get());
	auto loc = glGetUniformLocation(m_program, name.c_str());
	glUniform1ui(loc, value);
}

void Program::SetUniform(const std::string& name, float value) const
{
	auto loc = glGetUniformLocation(m_program, name.c_str());
	glUniform1f(loc, value);
}

void Program::SetUniform(const std::string& name, const glm::vec2& value) const
{
	auto loc = glGetUniformLocation(m_program, name.c_str());
	glUniform2fv(loc, 1, glm::value_ptr(value));
	// glUniform3f(loc, value.x, value.y, value.z);
}

void Program::SetUniform(const std::string& name, const glm::vec3& value) const
{
	auto loc = glGetUniformLocation(m_program, name.c_str());
	glUniform3fv(loc, 1, glm::value_ptr(value));
	// glUniform3f(loc, value.x, value.y, value.z);
}

void Program::SetUniform(const std::string& name, const glm::vec4& value) const 
{
	auto loc = glGetUniformLocation(m_program, name.c_str());
	glUniform4fv(loc, 1, glm::value_ptr(value));
}

void Program::SetUniform(const std::string& name, glm::mat4& value) const {
	auto loc = glGetUniformLocation(m_program, name.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

void Program::SetUniform(const std::string& name, std::vector<glm::mat4> value, GLsizei size) const {
	auto loc = glGetUniformLocation(m_program, name.c_str());
	std::vector<GLfloat> flattenedMatrices;
	for (const glm::mat4& matrix : value) {
		flattenedMatrices.insert(flattenedMatrices.end(), glm::value_ptr(matrix), glm::value_ptr(matrix) + 16);
	}
	glUniformMatrix4fv(loc, size, GL_FALSE, flattenedMatrices.data());
}