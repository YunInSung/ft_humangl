#ifndef __SHADER_H__
#define __SHADER_H__

#include "common.h"

CLASS_PTR(Shader);
class Shader {
    public:
        static ShaderUPtr CreateFromFile(const std::string& filename, GLenum shaderType);

        ~Shader();
        // shader 오브젝트의 생성 관리는 Shader 내부에서만 관리.
        uint32_t Get() const { return m_shader; };
    private:
        // CreateFormFile() 함수 외의 방식으로 Shader 인스턴스의 생성을 막는다.
        Shader() {}
        // 생성에 실패할 경우 false를 리턴하기 위해 bool타입으로 리턴.
        bool LoadFile(const std::string& filename, GLenum shaderType);
        uint32_t m_shader {0};
};

#endif