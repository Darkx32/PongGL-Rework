#include "rigidbody.hpp"

float Rigidbody::smoothRound(float value)
{
    if (value == 0)
        return 0;
    return value * (std::abs(value) / std::abs(value) + this->ep);
}

bool Rigidbody::detectCircleRectCollision(const Rigidbody &circle, const Rigidbody &rect)
{
    const glm::vec2& posA = *circle.r_position;
    const float& radius = *circle.r_radius;
    const glm::vec2& posB = *rect.r_position;
    const glm::vec2& scaleB = *rect.r_scale;

    glm::vec2 center(posA + radius);
    glm::vec2 aabb_half_extends(scaleB.x / 2.0f, scaleB.y / 2.0f);
    glm::vec2 aabb_center(
        posB.x + aabb_half_extends.x,
        posB.y + aabb_half_extends.y  
    );

    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extends, aabb_half_extends);

    glm::vec2 closest = aabb_center + clamped;
    difference = closest - center;
    return glm::length(difference) < radius;
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

bool Rigidbody::detectCollision(const Rigidbody& rb)
{
    if (this->r_scale && rb.r_scale)
    {
        const glm::vec2& posA = *this->r_position;
        const glm::vec2& scaleA = *this->r_scale;
        const glm::vec2& posB = *rb.r_position;
        const glm::vec2& scaleB = *rb.r_scale;

        bool collisionX = posA.x + scaleA.x >= posB.x && 
                          posB.x + scaleB.x >= posA.x;
        bool collisionY = posA.y + scaleA.y >= posB.y &&
                          posB.y + scaleB.y >= posA.y;

        return collisionX && collisionY;
    }
    else if (this->r_radius && rb.r_scale)
        return detectCircleRectCollision(*this, rb); 
    else if (this->r_scale && rb.r_radius)
        return detectCircleRectCollision(rb, *this);

    return false;
}
