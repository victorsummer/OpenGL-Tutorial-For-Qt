#include "PinkWindow.hpp"
#include <GL/gl.h>
#include <QKeyEvent>
#include <QApplication>

PinkWindow::PinkWindow(QWidget *parent)
    : QOpenGLWidget(parent)
{
    this->setWindowTitle("Tutorial 1 - Pink window");
}

PinkWindow::~PinkWindow()
{

}

void PinkWindow::initializeGL()
{
    glClearColor(1.0f, 0.0f, 0.4f, 0.0f);
}

void PinkWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void PinkWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        event->accept();
        qApp->quit();
    }
}
