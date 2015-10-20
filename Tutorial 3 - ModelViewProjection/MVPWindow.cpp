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

#include "MVPWindow.hpp"

MVPWindow::MVPWindow(QWidget *parent)
    : QOpenGLWidget(parent)
{
    this->setWindowTitle("Tutorial 3 - Model View Projection");
}

MVPWindow::~MVPWindow()
{
    // Cleanup VBO
    glDeleteVertexArrays(1, &mVertexArrayId);
    glDeleteBuffers(1, &mVertexBuffer);
}

void MVPWindow::initializeGL()
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        exit(0);
    }

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glGenVertexArrays(1, &mVertexArrayId);
    glBindVertexArray(mVertexArrayId);

    mProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/glsl/SimpleTransform.vertexshader");
    mProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/glsl/SingleColor.fragmentshader");
    mProgram.link();

    mMatrixId = glGetUniformLocation(mProgram.programId(), "mvp");

    glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(4, 3, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 model = glm::mat4(1.0f);
    mMvp = projection * view * model;

    static const GLfloat gVertexBufferData[] =
    {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
    };

    glGenBuffers(1, &mVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(gVertexBufferData), gVertexBufferData, GL_STATIC_DRAW);
}

void MVPWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Bind our shader
    mProgram.bind();

    glUniformMatrix4fv(mMatrixId, 1, GL_FALSE, &mMvp[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
}

void MVPWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        event->accept();
        qApp->quit();
    }
}
