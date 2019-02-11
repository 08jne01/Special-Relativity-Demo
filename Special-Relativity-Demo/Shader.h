#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader

{
public:
	Shader(unsigned int shaderType, std::string shaderFilename);
	unsigned int getID();
	void deleteShader();
private:
	void readSource();
	void compile();
	unsigned int type;
	unsigned int id;
	std::string source;
	std::string filename;
};