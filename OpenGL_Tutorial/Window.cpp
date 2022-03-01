#include "Window.h"
#include "Scene.h"
#include <iostream>

Window::Window(int width, int height, const char* title)
{
	m_ShouldClose = true;

	//inicilizar biblioteca glfw
	if (!glfwInit())
	{
		std::cerr << "Erro ao inicializar GLFW" << std::endl;
		return;
	}
	//definicao dos atributos do contexto OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GL_FALSE);

	//glfwSetErrorCallback(Window::errorCallback);

	// Criar a janela
	m_Window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (!m_Window)
	{
		std::cerr << "Erro criando janela" << std::endl;
		return;
	}

	//Torna o contexto atual
	glfwMakeContextCurrent(m_Window);
	glewExperimental = GLU_TRUE;
	GLenum glewInitErr = glewInit();

	if (glewInitErr != GLEW_OK)
	{
		std::cerr << "Erro inicializacao GLEW: " << glewGetErrorString(glewInitErr) << std::endl;
		return;
	}

	// Mostrar dados do ambiente
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);

	std::cout << "Renderizador: " << renderer << std::endl;
	std::cout << "Versao do Opengl suportada: " << version << std::endl;
	
	
	//system("pause");
	glClearColor(0.5f, 0.5f, 1, 0); //colocando a cor azul claro
	
	m_ShouldClose = false;
}

void Window::update()
{
	
	glfwPollEvents();

	if (m_Scene)
		m_Scene->update();

	glfwSwapBuffers(m_Window);

	if (!m_ShouldClose)
		m_ShouldClose = (glfwWindowShouldClose(m_Window) == GL_TRUE);
}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Window::errorCallback(int error, const char* description)
{
	std::cerr << "Erro " << error << ":" << description << std::endl;
}