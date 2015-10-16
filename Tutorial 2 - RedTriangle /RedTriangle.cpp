#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>

#include <QKeyEvent>
#include <QApplication>
#include <QOpenGLShader>

#include <QOpenGLFunctions_4_5_Core>

#include "RedTriangle.hpp"

RedTriangle::RedTriangle(QWidget *parent)
    : QOpenGLWidget(parent)
{
    this->setWindowTitle("Tutorial 2 - Red triangle");
}

RedTriangle::~RedTriangle()
{
    // Cleanup VBO
    glDeleteVertexArrays(1, &mVertexArrayId);
    glDeleteBuffers(1, &mVertexBuffer);
}

void RedTriangle::initializeGL()
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

    GLfloat gVertexBufferData[] =
    {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
    };

    glGenBuffers(1, &mVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(gVertexBufferData), gVertexBufferData, GL_STATIC_DRAW);

    mProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/glsl/SimpleVertexShader.vertexshader");
    mProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/glsl/SimpleFragmentShader.fragmentshader");
    mProgram.link();
}

void RedTriangle::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Bind our shader
    mProgram.bind();

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
}

void RedTriangle::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        event->accept();
        qApp->quit();
    }
}
