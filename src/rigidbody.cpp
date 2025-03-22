#include "rigidbody.hpp"

float Rigidbody::smoothRound(float value)
{
    if (value == 0)
        return 0;
    return value * (std::abs(value) / std::abs(value) + this->ep);
}

void Rigidbody::updatePosition()
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

    *r_position += this->acceleration;
}

void Rigidbody::applyForce(glm::vec2 force)
{
    this->acceleration += force;
}

bool Rigidbody::detectCollision(Rigidbody& rb)
{   
    if (this->r_scale)
    {
        bool collisionX = (*this->r_position).x + (*this->r_scale).x >= (*rb.r_position).x && 
            (*rb.r_position).x + (*rb.r_scale).x >= (*this->r_position).x;
        bool collisionY = (*this->r_position).y + (*this->r_scale).y >= (*rb.r_position).y &&
            (*rb.r_position).y + (*rb.r_scale).y >= (*this->r_position).y;

        return collisionX && collisionY;
    } else if (this->r_radius)
    {
        return false;
    }
    return false;
}
