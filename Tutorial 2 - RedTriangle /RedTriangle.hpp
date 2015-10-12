#ifndef REDTRIANGLE_HPP
#define REDTRIANGLE_HPP

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>

class RedTriangle : public QOpenGLWidget
{
    Q_OBJECT

public:
    RedTriangle(QWidget *parent = 0);
    ~RedTriangle();

protected:
    void initializeGL();
    void paintGL();

    void keyPressEvent(QKeyEvent *event);

private:
    GLuint mVertexArrayId;
    GLuint mVertexBuffer;
    QOpenGLShaderProgram mProgram;
};

#endif // REDTRIANGLE_HPP
