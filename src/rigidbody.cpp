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

    // Set max linear velocity
    float sum = std::abs(this->acceleration.x) + std::abs(this->acceleration.y);
    if (sum != 0)
    {
        float c_sum = std::clamp(sum, 0.0f, this->maxVelocity);
        float p_x = this->acceleration.x / sum * c_sum;
        float p_y = this->acceleration.y / sum * c_sum;
        this->acceleration.x = p_x;
        this->acceleration.y = p_y;
    }

    *position += this->acceleration;
}

void Rigidbody::applyForce(glm::vec2 force)
{
    this->acceleration += force;
}