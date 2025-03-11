#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

static const glm::mat4 projection = glm::ortho(0.0f, 360.0f, 480.0f, 0.0f);