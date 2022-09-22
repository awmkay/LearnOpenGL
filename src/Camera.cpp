#include "Camera.h"

#include <algorithm>
#include <cmath>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)),
                                                                           movementSpeed(SPEED),
                                                                           mouseSensitivity(SENSITIVITY), fov(FOV) {
    this->position = position;
    this->worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;
    UpdateCameraVectors();
}

Camera::~Camera() = default;

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;

    if (direction == FORWARD) {
        position += front * velocity;
    }

    if (direction == BACKWARD) {
        position -= front * velocity;
    }

    if (direction == LEFT) {
        position -= right * velocity;
    }

    if (direction == RIGHT) {
        position += right * velocity;
    }
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch) {
    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (constrainPitch) {
        pitch = std::min(89.0f, pitch);
        pitch = std::max(-89.0f, pitch);
    }

    UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yOffset) {
    fov -= (float) yOffset;
    fov = std::max(1.0f, fov);
    fov = std::min(45.0f, fov);
}

float Camera::GetFov() const {
    return fov;
}

glm::vec3 Camera::GetPosition() const {
    return position;
}

void Camera::UpdateCameraVectors() {
    glm::vec3 frontTemp = {
            std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch)),
            std::sin(glm::radians(pitch)),
            std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch))
    };

    front = glm::normalize(frontTemp);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}