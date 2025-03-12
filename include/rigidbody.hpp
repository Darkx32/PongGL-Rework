#pragma once
#include <cmath>
#include <glm/glm.hpp>

class Rigidbody
{
private:
    static float smoothRound(float);

protected:
    void updatePosition(glm::vec2*);

    glm::vec2 acceleration = glm::vec2(0.0f);
    float k = 0.2f; // Percentage discount

public:
    void applyForce(glm::vec2);
};

float Rigidbody::smoothRound(float value)
{
    return std::round(value * 100.f) / 100.f;
}

void Rigidbody::updatePosition(glm::vec2* position)
{
    this->acceleration.x -= this->smoothRound(this->acceleration.x * this->k);
    this->acceleration.y -= this->smoothRound(this->acceleration.y * this->k);

    *position += this->acceleration;
}

void Rigidbody::applyForce(glm::vec2 force)
{
    this->acceleration += force;
}
