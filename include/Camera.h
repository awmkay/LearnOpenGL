#ifndef LEARNOPENGL_CAMERA_H
#define LEARNOPENGL_CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.2f;
const float FOV = 45.0f;

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
public:
    explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
                    float yaw = YAW, float pitch = PITCH);

    ~Camera();

    glm::mat4 GetViewMatrix();

    void ProcessKeyboard(CameraMovement, float deltaTime);

    void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true);

    void ProcessMouseScroll(float yOffset);

    float GetFov() const;

    glm::vec3 GetPosition() const;

private:
    void UpdateCameraVectors();

private:
    glm::vec3 position{};
    glm::vec3 front;
    glm::vec3 up{};
    glm::vec3 right{};
    glm::vec3 worldUp{};

    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;
    float fov;
};

#endif //LEARNOPENGL_CAMERA_H
