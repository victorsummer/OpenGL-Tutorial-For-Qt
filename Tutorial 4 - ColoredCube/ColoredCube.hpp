#ifndef COLOREDCUBE_HPP
#define COLOREDCUBE_HPP

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>

#include "glm/glm.hpp"

class ColoredCube : public QOpenGLWidget
{
    Q_OBJECT

public:
    ColoredCube(QWidget *parent = 0);
    ~ColoredCube();

protected:
    void initializeGL();
    void paintGL();

    void keyPressEvent(QKeyEvent *event);

private:
    GLuint mVertexArrayId;
    GLuint mVertexBuffer;
    GLuint mColorBuffer;
    QOpenGLShaderProgram mProgram;
    GLuint mMatrixId;
    glm::mat4 mMvp;
};

#endif // COLOREDCUBE_HPP
