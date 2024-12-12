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

    exit_button = new QPushButton("Exit app...", this);//leave from app
    exit_button->setFont(font);
    exit_button->setStyleSheet("color: yellow;");
    exit_button->setGeometry(260, 770, 225, 70);
    connect(exit_button, &QPushButton::clicked, this, &stats2::exitApp);

    //Add frame based on QLabel
    frame = new QLabel(this);//Frame 1
    int frame_x=x/2+130;//frame x_size
    int frame_y=y/2 + 370;//frame y_size
    frame->setGeometry(600, 30, frame_x, frame_y);//Pos and size
    frame->setStyleSheet("border: 3px solid black;");//Style of frame

    main_button = new QPushButton("Go to menu...", this);
    main_button->setFont(font);
    main_button->setStyleSheet("color: yellow;");
    main_button->setGeometry(10, 770, 225, 70);
    connect(main_button, &QPushButton::clicked, this, &stats2::mainPage);

    //display data field(screen)
    dataDisplay = new QTextEdit(this);
    dataDisplay->setGeometry(600+10, 30+10, frame_x-20, frame_y-20);;
    dataDisplay->setFont(font);
    dataDisplay->setReadOnly(true);//only to read
    dataDisplay->setStyleSheet("background-color: white;border: 1px solid black;");//background colour and font colour
}

void stats2::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, background);//Background
    QWidget::paintEvent(event);
}

void stats2::exitApp()
{
    this->close();//turn off app...
}

void stats2::mainPage()
{
    mainapp *appWindow = new mainapp();
    appWindow->show();
    this->close();
}

