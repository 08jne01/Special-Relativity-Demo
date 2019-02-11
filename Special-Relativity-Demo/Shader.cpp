#include "Shader.h"

Shader::Shader(unsigned int shaderType, std::string shaderFilename) : type(shaderType), filename(shaderFilename)

{
	id = glCreateShader(shaderType);
	readSource();
	compile();
}

void Shader::readSource()

{
	std::ifstream in(filename);
	std::string line;
	std::stringstream os;

	while (getline(in, line))

	{
		os << line << std::endl;
	}

	source = os.str();
	in.close();
}

void Shader::compile()

{
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	int success;
	char infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)

	{
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR SHADER " << id << " COMPILATION FAILED " << infoLog << std::endl;
	}
}

unsigned int Shader::getID()

{
	return id;
}

void Shader::deleteShader()

{
	glDeleteShader(id);
}
