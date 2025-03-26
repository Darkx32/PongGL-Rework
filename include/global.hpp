#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define TARGET_FPS 1000.f / 60.f

static constexpr int WINDOW_SIZE[2] = { 360, 480 };

static constexpr GLfloat vertices[8] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f
};

static constexpr GLuint indices[6] = {
    0, 1, 2,
    3, 2, 1
};

static const glm::mat4 m_projection = glm::ortho(0.0f, static_cast<float>(WINDOW_SIZE[0]), static_cast<float>(WINDOW_SIZE[1]), 0.0f);