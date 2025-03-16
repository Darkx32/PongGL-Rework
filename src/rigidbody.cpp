#include "rigidbody.hpp"

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