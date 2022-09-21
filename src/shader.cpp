#include "shader.h"

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {

	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vertexFile;
	std::ifstream fragmentFile;

	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		std::stringstream vertexStream;
		vertexFile.open(vertexPath);
		vertexStream << vertexFile.rdbuf();
        vertexStream << "\0";
		vertexCode = vertexStream.str();
		vertexFile.close();

		std::stringstream fragmentStream;
		fragmentFile.open(fragmentPath);
		fragmentStream << fragmentFile.rdbuf();
        fragmentStream << "\0";
		fragmentCode = fragmentStream.str();
		fragmentFile.close();
	} catch (std::ifstream::failure &e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }

	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	compileShader(vertex, vertexCode);

	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	compileShader(fragment, fragmentCode);

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	int success;
	char infoLog[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILURE" << std::endl << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() const {
	glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

unsigned int Shader::getID() const {
	return ID;
}

int Shader::compileShader(const unsigned int shader, const std::string& shaderCode) {
	int success;
	char infoLog[512];

	const char *cShaderCode = shaderCode.c_str();
	
	glShaderSource(shader, 1, &cShaderCode, nullptr);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILURE" << std::endl << infoLog << std::endl;
	}

	return success;
}
