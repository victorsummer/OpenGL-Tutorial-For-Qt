#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <QKeyEvent>
#include <QApplication>
#include <QOpenGLShader>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>

#include "NumberCube.hpp"

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1

NumberCube::NumberCube(QWidget *parent)
    : QOpenGLWidget(parent)
{
    this->setWindowTitle("Tutorial 5 - Number cube");
}

NumberCube::~NumberCube()
{
    makeCurrent();
    // Cleanup VBO
    mVbo.destroy();
}

void NumberCube::initializeGL()
{
    initializeOpenGLFunctions();

    makeObject();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    mProgram = std::make_shared<QOpenGLShaderProgram>(nullptr);
    mProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/glsl/TransformVertexShader.vertexshader");
    mProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/glsl/TextureFragmentShader.fragmentshader");
    mProgram->bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
    mProgram->bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
    mProgram->link();
    mProgram->bind();
    mProgram->setUniformValue("texture", 0);

    mMatrix.ortho(-2.0f, +2.0f, +2.0f, -2.0f, 0.0f, 15.0f);
    mMatrix.translate(0.0f, 0.0f, -10.0f);
    mMatrix.rotate(45.0f, 1.0f, 0.0f, 0.0f);
    mMatrix.rotate(45.0f, 0.0f, 1.0f, 0.0f);
    mMatrix.rotate(45.0f, 0.0f, 0.0f, 1.0f);

    mProgram->setUniformValue("matrix", mMatrix);
}

void NumberCube::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mProgram->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
    mProgram->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
    mProgram->setAttributeBuffer(PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, 0, 3, 5 * sizeof(GLfloat));
    mProgram->setAttributeBuffer(PROGRAM_TEXCOORD_ATTRIBUTE, GL_FLOAT, 3 * sizeof(GLfloat), 2, 5 * sizeof(GLfloat));

    for (int i = 0; i < 6; ++i)
    {
        mTextures[i]->bind();
        glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
    }
}

void NumberCube::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        event->accept();
        qApp->quit();
    }
}

void NumberCube::makeObject()
{
    static const int coords[6][4][3] =
    {
        { {1, -1, -1}, {-1, -1, -1}, {-1, 1, -1}, {1, 1, -1} }, // front
        { {1, 1, -1}, {-1, 1, -1}, {-1, 1, 1}, {1, 1, 1} }, // top
        { {-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1} }, // back
        { {1, -1, 1}, {-1, -1, 1}, {-1, -1, -1}, {1, -1, -1} }, // bottom
        { {1, -1, 1}, {1, -1, -1}, {1, 1, -1}, {1, 1, 1} }, // left
        { {-1, -1, -1}, {-1, -1, 1}, {-1, 1, 1}, {-1, 1, -1} } // right
    };

    for (int i = 0; i < 6; ++i)
        mTextures[i] = std::make_shared<QOpenGLTexture>(QImage(QString(":/glsl/images/side%1.png").arg(i + 1)).mirrored());

    QVector<GLfloat> vertData;
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            // vertex position
            vertData.append(coords[i][j][0]);
            vertData.append(coords[i][j][1]);
            vertData.append(coords[i][j][2]);
            // texture coordinate
            vertData.append(j == 0 || j == 3);
            vertData.append(j == 0 || j == 1);
        }
    }

    mVbo.create();
    mVbo.bind();
    mVbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));
}
