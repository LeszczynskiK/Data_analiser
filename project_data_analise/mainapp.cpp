#include "mainapp.h"

mainapp::mainapp(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Data menager window");

    const int x =1920*0.8;//x window size
    const int y=1080*0.8;//y window size

    setFixedSize(x, y);//Set window size

    //Background image
    background = QPixmap("/home/krzysiek89/Desktop/QT_aplikacje/Data_analiser/background1.jpg").scaled(x, y);

    QFont font;
    font.setPointSize(21);//Font size -all font size

    exit_button = new QPushButton("Exit app...", this);//leave from app
    exit_button->setFont(font);
    exit_button->setStyleSheet("color: yellow;");
    exit_button->setGeometry(30, 770, 360, 70);
    connect(exit_button, &QPushButton::clicked, this, &mainapp::exitApp);

    //Add frame based on QLabel
    QLabel *frame = new QLabel(this);//Frame 1
    int frame_x=x/2+130;//frame x_size
    int frame_y=y/2 + 370;//frame y_size
    frame->setGeometry(600, 30, frame_x, frame_y);//Pos and size
    frame->setStyleSheet("border: 3px solid black;");//Style of frame

}

void mainapp::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, background);//Background
    QWidget::paintEvent(event);
}

void mainapp::exitApp()
{
    this->close();//turn off app...
}
