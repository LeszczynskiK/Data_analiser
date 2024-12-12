#include "stats2.h"

stats2::stats2(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Math stats II window");

    const int x =1920*0.8;//x window size
    const int y=1080*0.8;//y window size

    setFixedSize(x, y);//Set window size

    //Background image
    background = QPixmap("/home/krzysiek89/Desktop/QT_aplikacje/Data_analiser/stats2_background.png").scaled(x, y);

    QFont font;
    font.setPointSize(21);//Font size -all font size
}

void stats2::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, background);//Background
    QWidget::paintEvent(event);
}
