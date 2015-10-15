#ifndef MVPWINDOW_HPP
#define MVPWINDOW_HPP

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>

#include "glm/glm.hpp"

class MVPWindow : public QOpenGLWidget
{
    Q_OBJECT

public:
    MVPWindow(QWidget *parent = 0);
    ~MVPWindow();

protected:
    void initializeGL();
    void paintGL();

    void keyPressEvent(QKeyEvent *event);

private:
    GLuint mVertexArrayId;
    GLuint mVertexBuffer;
    QOpenGLShaderProgram mProgram;
    GLuint mMatrixId;
    glm::mat4 mMvp;
};

#endif // MVPWINDOW_HPP
