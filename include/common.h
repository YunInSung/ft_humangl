#ifndef __COMMON_H__
#define __COMMON_H__

#include <memory>
#include <string>
#include <optional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <algorithm>
#include "glm.hpp"

#define CLASS_PTR(className) \
class className; \
using className ## UPtr = std::unique_ptr<className>; \
using className ## Ptr = std::shared_ptr<className>; \
using className ## WPtr = std::weak_ptr<className>; // className ## Ptr = ${className} + 'Ptr'이 된다.

std::optional<std::string> LoadTextFile(const std::string &filename);
glm::vec3 GetAttenuationCoeff(float distance);

#endif