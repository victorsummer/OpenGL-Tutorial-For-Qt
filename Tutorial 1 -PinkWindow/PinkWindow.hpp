#ifndef PINKWINDOW_HPP
#define PINKWINDOW_HPP

#include <QOpenGLWidget>

class PinkWindow : public QOpenGLWidget
{
    Q_OBJECT

public:
    PinkWindow(QWidget *parent = 0);
    ~PinkWindow();

protected:
    void initializeGL();
    void paintGL();

    void keyPressEvent(QKeyEvent *event);
};

#endif // PINKWINDOW_HPP
