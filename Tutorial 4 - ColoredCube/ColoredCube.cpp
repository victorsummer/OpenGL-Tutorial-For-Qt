#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <QKeyEvent>
#include <QApplication>
#include <QOpenGLShader>

#include "ColoredCube.hpp"

ColoredCube::ColoredCube(QWidget *parent)
    : QOpenGLWidget(parent)
{
    this->setWindowTitle("Tutorial 4 - Colored cube");
}

ColoredCube::~ColoredCube()
{
    // Cleanup VBO
    glDeleteVertexArrays(1, &mVertexArrayId);
    glDeleteBuffers(1, &mVertexBuffer);
    glDeleteBuffers(1, &mColorBuffer);
}

void ColoredCube::initializeGL()
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        exit(0);
    }

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glGenVertexArrays(1, &mVertexArrayId);
    glBindVertexArray(mVertexArrayId);

    mProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/glsl/TransformVertexShader.vertexshader");
    mProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/glsl/ColorFragmentShader.fragmentshader");
    mProgram.link();

    mMatrixId = glGetUniformLocation(mProgram.programId(), "mvp");

    glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(4, 3, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 model = glm::mat4(1.0f);
    mMvp = projection * view * model;

    GLfloat vertexBufferData[] =
    {
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f, 1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f
    };

    glGenBuffers(1, &mVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);

    static const GLfloat colorBufferData[] = {
        0.583f, 0.771f, 0.014f,
        0.609f, 0.115f, 0.436f,
        0.327f, 0.483f, 0.844f,
        0.822f, 0.569f, 0.201f,
        0.435f, 0.602f, 0.223f,
        0.310f, 0.747f, 0.185f,
        0.597f, 0.770f, 0.761f,
        0.559f, 0.436f, 0.730f,
        0.359f, 0.583f, 0.152f,
        0.483f, 0.596f, 0.789f,
        0.559f, 0.861f, 0.639f,
        0.195f, 0.548f, 0.859f,
        0.014f, 0.184f, 0.576f,
        0.771f, 0.328f, 0.970f,
        0.406f, 0.615f, 0.116f,
        0.676f, 0.977f, 0.133f,
        0.971f, 0.572f, 0.833f,
        0.140f, 0.616f, 0.489f,
        0.997f, 0.513f, 0.064f,
        0.945f, 0.719f, 0.592f,
        0.543f, 0.021f, 0.978f,
        0.279f, 0.317f, 0.505f,
        0.167f, 0.620f, 0.077f,
        0.347f, 0.857f, 0.137f,
        0.055f, 0.953f, 0.042f,
        0.714f, 0.505f, 0.345f,
        0.783f, 0.290f, 0.734f,
        0.722f, 0.645f, 0.174f,
        0.302f, 0.455f, 0.848f,
        0.225f, 0.587f, 0.040f,
        0.517f, 0.713f, 0.338f,
        0.053f, 0.959f, 0.120f,
        0.393f, 0.621f, 0.362f,
        0.673f, 0.211f, 0.457f,
        0.820f, 0.883f, 0.371f,
        0.982f, 0.099f, 0.879f
    };

    glGenBuffers(1, &mColorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorBufferData), colorBufferData, GL_STATIC_DRAW);
}

void ColoredCube::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Bind our shader
    mProgram.bind();

    glUniformMatrix4fv(mMatrixId, 1, GL_FALSE, &mMvp[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, mColorBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void ColoredCube::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        event->accept();
        qApp->quit();
    }
}
