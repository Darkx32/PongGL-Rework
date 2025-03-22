#include "circle.hpp"

SDL_AppResult Circle::init(glm::vec2 pos, float rad, glm::vec3 c)
{
    SDL_AppResult result = SDL_APP_CONTINUE;
    if ((result = this->shader.init("assets/shaders/circleVertex.glsl", "assets/shaders/circleFragment.glsl")) != SDL_APP_CONTINUE)
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

    this->position = pos;
    this->radius = rad;
    this->color = c;

    r_position = &this->position;
    r_radius = &this->radius;

    return result;
}

SDL_AppResult Circle::render()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, glm::vec3(this->position, 0.0f));
    transform = glm::scale(transform, glm::vec3(glm::vec2(this->radius * 2.0f), 1.0f));
    transform = m_projection * transform;

    glUseProgram(this->shader.program);
    if (glGetError() != GL_NO_ERROR)
    {
        glGetProgramInfoLog(this->shader.program, 512, nullptr, this->infoLog);
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error to use shader: %s", this->infoLog);
        return SDL_APP_FAILURE;
    }

    int transformLocation = glGetUniformLocation(this->shader.program, "uTransform");
    int colorLocation = glGetUniformLocation(this->shader.program, "uColor");
    int radiusLocation = glGetUniformLocation(this->shader.program, "uRadius");
    int positionLocation = glGetUniformLocation(this->shader.program, "uPosition");

    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, &transform[0][0]);
    glUniform3f(colorLocation, this->color.r, this->color.g, this->color.b);
    glUniform1f(radiusLocation, this->radius);
    glUniform2f(positionLocation, this->position.x, this->position.y);

    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glDisable(GL_BLEND);

    return SDL_APP_CONTINUE;
}

void Circle::updatePhysics()
{
    this->updatePosition();
}