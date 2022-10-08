#ifndef LEARNOPENGL_MESH_H
#define LEARNOPENGL_MESH_H

#include "Shader.h"

#include <glm/glm.hpp>
#include <string>
#include <vector>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

    void Draw(Shader &shader);

private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    void setupMesh();

};

#endif //LEARNOPENGL_MESH_H
