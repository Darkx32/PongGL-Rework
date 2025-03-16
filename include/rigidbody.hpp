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
