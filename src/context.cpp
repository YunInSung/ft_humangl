#include "context.h"
#include "GLFW/glfw3.h"
#include <imgui.h>
#include "image.h"

#include <ios>
#include <iostream>

#include <vector>

ContextUPtr Context::Create() 
{
    auto context = ContextUPtr(new Context());
    if (!context->Init())
        return nullptr;
    return std::move(context);
}

void Context::ProcessInput(GLFWwindow* window) {
    const float cameraSpeed = 0.05f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_cameraPos += cameraSpeed * m_cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_cameraPos -= cameraSpeed * m_cameraFront;
    
    auto cameraRight = glm::normalize(glm::cross(m_cameraUp, -m_cameraFront));
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_cameraPos += cameraSpeed * cameraRight;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_cameraPos -= cameraSpeed * cameraRight;
    
    auto cameraUp = glm::normalize(glm::cross(-m_cameraFront, cameraRight));
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        m_cameraPos += cameraSpeed * cameraUp;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        m_cameraPos -= cameraSpeed * cameraUp;
}

void Context::MouseMove(double x, double y)
{
    if (!m_cameraControl)
        return ;
    auto pos = glm::vec2((float)x, (float)y);
    auto deltaPos = pos - m_prevMousePos;

    const float cameraRotSpeed = 0.05f;
    m_cameraYaw -= deltaPos.x * cameraRotSpeed;
    m_cameraPitch -= deltaPos.y * cameraRotSpeed;

    if (m_cameraYaw < 0.0f) m_cameraYaw += 360.0f;
    if (m_cameraYaw > 360.0f) m_cameraYaw -= 360.0f;

    if (m_cameraPitch > 89.0f) m_cameraPitch = 89.0f;
    if (m_cameraPitch < -89.0f) m_cameraPitch = -89.0f;

    m_prevMousePos = pos;
}

void Context::MouseButton(int button, int action, double x, double y)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            m_prevMousePos = glm::vec2((float)x, (float)y);
            m_cameraControl = true;
        }
        else if (action == GLFW_RELEASE)
        {
            m_cameraControl = false; 
        }
    }
}

void Context::Reshape(int width, int height)
{
    m_width = width;
    m_height = height;
    glViewport(0, 0, m_width, m_height);
}

bool Context::Init() 
{
    skeleton = Skeleton::Load("./resource/skeleton/143.asf", "./resource/motion/143.amc");
    if (skeleton == nullptr)
        return false;
    auto VBO = skeleton->getVBO();
    this->VBOsize = skeleton->getVBOsize();

    m_vertexArrayObject = VertexLayout::Create();
    m_vertexBuffer = Buffer::CreateWithData(GL_ARRAY_BUFFER, GL_STATIC_DRAW, VBO.get(), VBOsize * sizeof(float));

    m_vertexArrayObject->SetAttrib(0, 1, GL_INT, GL_FALSE, sizeof(int) * 1, 0);
    // m_vertexArrayObject->SetAttrib(1, 3, GL_FLOAT, GL_FALSE, sizeof(int) * 2, sizeof(int) * 1);
    // m_vertexArrayObject->SetAttrib(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, sizeof(float) * 6);


    m_program = Program::Create("./shader/skeleton.vs", "./shader/skeleton.fs");
    if (!m_program)
        return false;
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    this->initTime = (float)glfwGetTime();

    m_program->Use();
    m_vertexArrayObject->Bind();

    auto model = glm::rotate(glm::mat4(1.0f),
        glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f)
    );
    auto view = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
    auto projection = glm::perspective(glm::radians(45.0f), (float)m_width/(float)m_height, 0.01f, 100.0f);
    auto transform = projection * view * model;
    m_program->SetUniform("transform", transform);
    
    return true;
}

void Context::Render()
{
    if (ImGui::Begin("ui window")) {
        if (ImGui::ColorEdit4("clear color", glm::value_ptr(m_clearColor))) {
            glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);
        }
        ImGui::Separator();
        ImGui::DragFloat3("camera pos", glm::value_ptr(m_cameraPos), 0.01f);
        ImGui::DragFloat("camera yaw", &m_cameraYaw, 0.5f);
        ImGui::DragFloat("camera pitch", &m_cameraPitch, 0.5f, -89.0f, 89.0f);
        ImGui::Separator();
        if (ImGui::Button("reset camera")) {
            m_cameraYaw = 0.0f;
            m_cameraPitch = 0.0f;
            m_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
        }
        if (ImGui::CollapsingHeader("light", ImGuiTreeNodeFlags_DefaultOpen)) {
            // ImGui::DragFloat3("l.position", glm::value_ptr(m_light.position), 0.01f);
            // ImGui::DragFloat3("l.direction", glm::value_ptr(m_light.direction), 0.01f);
            // ImGui::DragFloat2("l.cutoff", glm::value_ptr(m_light.cutoff), 0.5f, 0.0f, 180.0f);
            // ImGui::DragFloat("l.distance", &m_light.distance, 0.5f, 0.0f, 3000.0f);
            // ImGui::ColorEdit3("l.ambient", glm::value_ptr(m_light.ambient));
            // ImGui::ColorEdit3("l.diffuse", glm::value_ptr(m_light.diffuse));
            // ImGui::ColorEdit3("l.specular", glm::value_ptr(m_light.specular));
        }
        
        if (ImGui::CollapsingHeader("material", ImGuiTreeNodeFlags_DefaultOpen)) {
            // ImGui::ColorEdit3("m.ambient", glm::value_ptr(m_material.attribute.ambient));
            // ImGui::ColorEdit3("m.diffuse", glm::value_ptr(m_material.attribute.diffuse));
            // ImGui::ColorEdit3("m.specular", glm::value_ptr(m_material.attribute.specular));
            // ImGui::DragFloat("m.shininess", &m_material.attribute.shininess, 1.0f, 1.0f, 256.0f);
        }
        ImGui::Checkbox("animation", &m_animation);
        ImGui::Checkbox("texture", &m_texture);
    }
    ImGui::End();

    // 색상버퍼 초기화
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    m_program->Use();

    auto projection = glm::perspective(glm::radians(45.0f),
        (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.01f, 150.0f);
    auto view = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);

    m_program->Use();
    m_program->SetUniform("COLOR", glm::vec4({0.0f, 0.0f, 0.0f, 1.0f}));
    m_program->SetUniform("TransForms", skeleton->getTransMats(initTime), skeleton->getJointsSize());

    auto model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -50.0f));
    auto transform = projection * view * model;
    m_program->SetUniform("MVP", transform);
    glPointSize(10);
    glDrawArrays(GL_POINTS, 0, VBOsize);
    glDrawArrays(GL_LINES, 0, VBOsize);
}