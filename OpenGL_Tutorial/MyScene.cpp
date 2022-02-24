#include "MyScene.h"
#include <GL\glew.h>
#include <iostream>
#include <sstream>
#include "Util.h"

GLuint checkShaderCompilation(GLuint shader)
{
	GLint sucess = 0;
	GLchar infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &sucess);

	if (!sucess)
	{
		glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
		std::cerr << infoLog << std::endl;
	}
	return sucess;
}

GLuint checkProgramLink(GLuint program)
{
	GLint sucess = 0;
	GLchar infoLog[512];

	glGetShaderiv(program, GL_LINK_STATUS, &sucess);

	if (!sucess)
	{
		glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
		std::cerr << infoLog << std::endl;
	}
	return sucess;
}


MyScene::MyScene()
{
	std::stringstream vertexSourceStream;
	std::stringstream fragmentSourceStream;

	loadFile("vertex.vs", vertexSourceStream);
	loadFile("fragment.vs", fragmentSourceStream);

	std::string vertexSource = vertexSourceStream.str();
	std::string fragmentSource = fragmentSourceStream.str();

	const char* buff;

	//create shader program
	m_ShaderProgram = glCreateProgram();

	//Vertex shader
	buff = vertexSource.c_str();
	m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_VertexShader, 1, &buff, NULL);
	glCompileShader(m_VertexShader);
	checkShaderCompilation(m_VertexShader);
	glAttachShader(m_ShaderProgram, m_VertexShader);
	glDeleteShader(m_VertexShader);

	//Fragment shader
	buff = fragmentSource.c_str();
	m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_FragmentShader, 1, &buff, NULL);
	glCompileShader(m_FragmentShader);
	checkShaderCompilation(m_FragmentShader);
	glAttachShader(m_ShaderProgram, m_FragmentShader);
	glDeleteShader(m_FragmentShader);

	//link shader program
	glLinkProgram(m_ShaderProgram);
	checkProgramLink(m_ShaderProgram);

	glUseProgram(m_ShaderProgram);

	glClearColor(0.5f, 0.5f, 1, 0);
	

}

MyScene::~MyScene()
{
	std::cout << "MyScene DESTRUCTOR!" << std::endl;
	glDeleteProgram(m_ShaderProgram);
}

void MyScene::update()
{
	//afeta o resultado final na tela
	std::cout << "MyScene update" << std::endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}