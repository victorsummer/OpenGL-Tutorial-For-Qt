#include "PinkWindow.hpp"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PinkWindow w;
    int width = 500;
    int height = 500;
    // Move the window to the center of the screen
    w.setGeometry((QApplication::desktop()->availableGeometry().width() - width) / 2,
                  (QApplication::desktop()->availableGeometry().height() - height) / 2,
                  width, height);

    w.show();

    return a.exec();
}
