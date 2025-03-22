#pragma once
#include <cmath>
#include <glm/glm.hpp>
#include <SDL3/SDL.h>
#include <algorithm>

class Rigidbody
{
private:
    float smoothRound(float);

protected:
    void updatePosition();

    glm::vec2 acceleration = glm::vec2(0.0f);
    float k = 0.3f; // Percentage discount
    float ep = 0.01f; // Episilion
    float maxVelocity = 5.0f;

public:
    glm::vec2* r_position = nullptr;
    glm::vec2* r_scale = nullptr;
    float* r_radius = nullptr;

    void applyForce(glm::vec2);
    bool detectCollision(Rigidbody&);
};
