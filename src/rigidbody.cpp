#include "rigidbody.hpp"

float Rigidbody::smoothRound(float value)
{
    if (value == 0)
        return 0;
    return value * (std::abs(value) / std::abs(value) + this->ep);
}

void Rigidbody::updatePosition(glm::vec2* position)
{
    this->acceleration.x -= this->smoothRound(this->acceleration.x * this->k);
    this->acceleration.y -= this->smoothRound(this->acceleration.y * this->k);

    if (acceleration.x != 0 || acceleration.y != 0)
        SDL_Log("%f %f", acceleration.x, acceleration.y);

    *position += this->acceleration;
}

void Rigidbody::applyForce(glm::vec2 force)
{
    this->acceleration += force;
}