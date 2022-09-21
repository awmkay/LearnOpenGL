#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
	public:
		Shader(const std::string &vertexPath, const std::string &fragmentPath);

		void use() const;

		void setBool(const std::string &name, bool value) const;
		void setInt(const std::string &name, int value) const;
		void setFloat(const std::string &name, float value) const;
        void setMat4(const std::string &name, const glm::mat4 &value) const;

		unsigned int getID() const;

	private:
		static int compileShader(unsigned int shader, const std::string& shaderCode);

	private:
		unsigned int ID;
};

#endif
