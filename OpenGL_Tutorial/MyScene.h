#pragma once
#include "Scene.h"

class MyScene :
    public Scene
{
private:
    GLuint m_ShaderProgram;
    GLuint m_VertexShader;
    GLuint m_FragmentShader;

public:
    MyScene();
    ~MyScene();
    void update() override;
};

