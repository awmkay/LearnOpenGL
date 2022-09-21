#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
	public:
		Shader(const std::string vertexPath, const std::string fragmentPath);

		void use();

		void setBool(const std::string &name, bool value) const;
		void setInt(const std::string &name, int value) const;
		void setFloat(const std::string &name, float value) const;

		unsigned int getID();

	private:
		int compileShader(const unsigned int shader, const std::string& shaderCode);

	private:
		unsigned int ID;
};

#endif
