#ifndef NUMBERCUBE_HPP
#define NUMBERCUBE_HPP

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <memory>

class QOpenGLTexture;
class QOpenGLShaderProgram;

class NumberCube : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    NumberCube(QWidget *parent = 0);
    ~NumberCube();

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

    void keyPressEvent(QKeyEvent *event);

private:
    void makeObject();

private:
    std::shared_ptr<QOpenGLShaderProgram> mProgram;
    std::shared_ptr<QOpenGLTexture> mTextures[6];
    QOpenGLBuffer mVbo;
    QMatrix4x4 mMatrix;
};

#endif // NUMBERCUBE_HPP
