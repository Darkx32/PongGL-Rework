#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <shader.hpp>
#include <global.hpp>

class Rect
{
private:
    glm::vec2 position, scale;
    glm::vec3 color;

    GLuint VAO;
    Shader shader;

    char infoLog[512];

public:
    SDL_AppResult init(glm::vec2, glm::vec2, glm::vec3);
    SDL_AppResult render();
    void close();

};

SDL_AppResult Rect::init(glm::vec2 position, glm::vec2 scale, glm::vec3 color)
{
    SDL_AppResult result = SDL_APP_CONTINUE;
    result = this->shader.init("assets/shaders/rectVertex.glsl", "assets/shaders/rectFragment.glsl");
    if (result != SDL_APP_CONTINUE)
        return result;

    GLuint VBO, EBO;
    glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &this->VAO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // vertices is created in global.hpp header

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // indices is created in global.hpp header

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

    this->position = position;
    this->scale = scale;
    this->color = color;

    return result;
}

SDL_AppResult Rect::render()
{
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(this->position, 0.0f));
    transform = glm::scale(transform, glm::vec3(this->scale, 1.0f));
    transform = m_projection * transform; // projection is created in global.hpp header

    glUseProgram(this->shader.program);
    if (glGetError() != GL_NO_ERROR)
    {
        glGetProgramInfoLog(this->shader.program, 512, nullptr, this->infoLog);
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error to use shader: %s", this->infoLog);
        return SDL_APP_FAILURE;
    }

    int transformLocation = glGetUniformLocation(this->shader.program, "uTransform");
    int colorLocation = glGetUniformLocation(this->shader.program, "uColor");

    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, &transform[0][0]);
    glUniform3f(colorLocation, this->color.r, this->color.g, this->color.b);
    
    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    return SDL_APP_CONTINUE;
}

void Rect::close()
{
    this->shader.close();
    glDeleteBuffers(1, &this->VAO);
}
