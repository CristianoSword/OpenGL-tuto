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

	//Link shader program
	glLinkProgram(m_ShaderProgram);
	checkProgramLink(m_ShaderProgram);

	glUseProgram(m_ShaderProgram);
	glClearColor(0.5f, 0.5f, 1, 0);

	//Vertices
	m_Vertices = new GLfloat[18]{
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
	};

	//Vertices Buffer Object
	glGenBuffers(1, &m_VBO);

	// Cria um ID na GPU pra um array de Buffers
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	//Vertice Array Object - VAO

	//Vertices e atributos de vertcices GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, 
		18 * sizeof(GL_FLOAT),
		m_Vertices, 
		GL_STATIC_DRAW);

	//Vertices
	glVertexAttribPointer(0,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GL_FLOAT),
		(GLvoid*)0);
	
	//Cores
	glVertexAttribPointer(1,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GL_FLOAT),
		(GLvoid*)(3 * sizeof(GL_FLOAT)));
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	//Instala o programa como parte da pipeline de renderizador
	glUseProgram(m_ShaderProgram);
}

MyScene::~MyScene()
{
	std::cout << "MyScene DESTRUCTOR!" << std::endl;
	glDeleteProgram(m_ShaderProgram);
}

void MyScene::update()
{
	//afeta o resultado final na tela
	//std::cout << "MyScene update" << std::endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Instala o programa como parte da renderizacao
	glUseProgram(m_ShaderProgram);
	glBindVertexArray(m_VAO);
	glDrawArrays( GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
	
}



