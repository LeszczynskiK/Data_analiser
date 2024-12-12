#include "plotter.h"

plotter::plotter(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Plotter window");

    const int x =1920*0.8;//x window size
    const int y=1080*0.8;//y window size

    setFixedSize(x, y);//Set window size

    //Background image
    background = QPixmap("/home/krzysiek89/Desktop/QT_aplikacje/Data_analiser/plotter_background.png").scaled(x, y);

    QFont font;
    font.setPointSize(21);//Font size -all font size

}

void plotter::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, background);//Background
    QWidget::paintEvent(event);
}
