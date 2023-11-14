#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "context.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


const int width = WINDOW_WIDTH;
const int height = WINDOW_HEIGHT;

void OnFramebufferSizeChange(GLFWwindow* window, int width, int height) {
	SPDLOG_INFO("framebuffer size changed: ({} x {})", width, height);
	auto context = reinterpret_cast<Context *>(window);
	context->Reshape(width, height);
}

void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
	SPDLOG_INFO("key: {}, scancode: {}, mods: {}{}{}", \
		key, scancode, \
		action == GLFW_PRESS ? "Pressed" : \
		action == GLFW_RELEASE ?  "Released" : \
		action == GLFW_REPEAT ? "Repeat" : "Unknown",
		mods & GLFW_MOD_CONTROL ? "C" : "-",
		mods & GLFW_MOD_SHIFT ? "S" : "_",
		mods & GLFW_MOD_ALT ? "A" : "-");
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void OnCursorPos(GLFWwindow *window, double x, double y) {
	auto context = reinterpret_cast<Context *>(glfwGetWindowUserPointer(window));
	context->MouseMove(x, y);
}

void OnMouseButton(GLFWwindow *window, int button, int action, int modifier)
{
	ImGui_ImplGlfw_MouseButtonCallback(window, button, action, modifier);
	auto context = reinterpret_cast<Context *>(glfwGetWindowUserPointer(window));
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	context->MouseButton(button, action, x, y);
}

void OnCharEvent(GLFWwindow* window, unsigned int ch) {
    ImGui_ImplGlfw_CharCallback(window, ch);
}

void OnScroll(GLFWwindow* window, double xoffset, double yoffset) {
    ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
}

int main(int ac, char **av)
{
	std::cout << "Initialize glfw" << std::endl;
	if (!glfwInit())
	{
		const char *description = NULL;
		glfwGetError(&description);
		std::cout << "Failed to initialize glfw: " << description << std::endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);
	if (!window)
	{
		std::cout << "failed to create glfw window" << std::endl;
		glfwTerminate();

		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to initialize glad" << std::endl;
		glfwTerminate();
		return -1;
	}
	auto glVersion = glGetString(GL_VERSION);
	// SPDLOG_INFO("OpenGL context version: {}", glVersion);

	auto imguiContext = ImGui::CreateContext();
	ImGui::SetCurrentContext(imguiContext);
	ImGui_ImplGlfw_InitForOpenGL(window, false);
	ImGui_ImplOpenGL3_Init();
	ImGui_ImplOpenGL3_CreateFontsTexture();
	ImGui_ImplOpenGL3_CreateDeviceObjects();

	auto context = Context::Create();
	if (!context)
	{
		SPDLOG_ERROR("failed to create context");
		glfwTerminate();
		return -1;
	}
	glfwSetWindowUserPointer(window, context.get());//
	// auto pointer = glfwGetWindowUserPointer(window);를 사용하면 context의 포인터를 얻어올 수 있다.

	// OnFramebufferSizeChange(window, width, height);
	glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChange);
	glfwSetKeyCallback(window, OnKeyEvent);
	glfwSetCharCallback(window, OnCharEvent);
	glfwSetCursorPosCallback(window, OnCursorPos);
	glfwSetMouseButtonCallback(window, OnMouseButton);
	glfwSetScrollCallback(window, OnScroll);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		ImGui_ImplGlfw_NewFrame();
    	ImGui::NewFrame();

		context->ProcessInput(window);
		context->Render();

		ImGui::Render(); // 무엇을 그릴지 축적
    	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData()); // 실제로 렌터를 맡는 부분
		glfwSwapBuffers(window);
	}
	context.reset();
	// context = nullptr;
	ImGui_ImplOpenGL3_DestroyFontsTexture();
	ImGui_ImplOpenGL3_DestroyDeviceObjects();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext(imguiContext);

	glfwTerminate();
}
