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


    int frame_x_size=x/2+130;//frame x_size
    int frame_y_size=y/2 + 370;//frame y_size
    //Drawing area
    chart = new QChart();
    chartView = new QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setGeometry(600, 30, frame_x_size, frame_y_size);//size of view
    chartView->setStyleSheet("background-color: white; color:black;border: 1px solid black;");
    chart->setBackgroundVisible(true);
    chart->setBackgroundBrush(QBrush(QColor("grey")));


    exit_button = new QPushButton("Exit app...", this);//leave from app
    exit_button->setFont(font);
    exit_button->setStyleSheet("color: yellow;");
    exit_button->setGeometry(260, 770, 225, 70);
    connect(exit_button, &QPushButton::clicked, this, &plotter::exitApp);

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
    connect(main_button, &QPushButton::clicked, this, &plotter::mainPage);

    int start_y=230;
    int x_length=275;
    int gap=60;
    int width_button=50;


    //options to plot-x is 1st column, y- is 2nd column, t-is number of sample
    plot1 = new QPushButton("Plot: f(x,y)", this);
    plot1->setFont(font);
    plot1->setStyleSheet("color: yellow;");
    plot1->setGeometry(30, start_y, x_length, width_button);
    connect(plot1, &QPushButton::clicked, this, &plotter::Plot1);

    plot2 = new QPushButton("Plot: f(y,x)", this);
    plot2->setFont(font);
    plot2->setStyleSheet("color: yellow;");
    plot2->setGeometry(30, start_y + gap, x_length, width_button);
    connect(plot2, &QPushButton::clicked, this, &plotter::Plot2);

    plot3 = new QPushButton("Plot: f(t,x)", this);
    plot3->setFont(font);
    plot3->setStyleSheet("color: yellow;");
    plot3->setGeometry(30, start_y + 2*gap, x_length, width_button);
    connect(plot3, &QPushButton::clicked, this, &plotter::Plot3);

    plot4 = new QPushButton("Plot: f(t,y)", this);
    plot4->setFont(font);
    plot4->setStyleSheet("color: yellow;");
    plot4->setGeometry(30, start_y + 3*gap, x_length, width_button);
    connect(plot4, &QPushButton::clicked, this, &plotter::Plot4);

    plot5 = new QPushButton("Plot: f(x,t)", this);
    plot5->setFont(font);
    plot5->setStyleSheet("color: yellow;");
    plot5->setGeometry(30, start_y + 4*gap, x_length, width_button);
    connect(plot5, &QPushButton::clicked, this, &plotter::Plot5);

    plot6 = new QPushButton("Plot: f(y,t)", this);
    plot6->setFont(font);
    plot6->setStyleSheet("color: yellow;");
    plot6->setGeometry(30, start_y + 5*gap, x_length, width_button);
    connect(plot6, &QPushButton::clicked, this, &plotter::Plot6);

    clear_screen = new QPushButton("Clear screen", this);
    clear_screen->setFont(font);
    clear_screen->setStyleSheet("color: yellow;");
    clear_screen->setGeometry(10, start_y + 6*gap+90, x_length+40, width_button+20);
    connect(clear_screen, &QPushButton::clicked, this, &plotter::clearPlot);
}


void plotter::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, background);//Background
    QWidget::paintEvent(event);
}

void plotter::exitApp()
{
    this->close();//turn off app...
}

void plotter::mainPage()
{
    mainapp *appWindow = new mainapp();
    appWindow->show();
    this->close();
}


//x is 1st choosen column, y is 2nd choosen column
//if only 1 column mode - impossible to draw(schow information on board)
void plotter::Plot1()//draw x y diagram
{

}

void plotter::Plot2()//draw y x diagram
{

}

void plotter::Plot3()//draw time x diagram
{

}

void plotter::Plot4()//draw time y diagram
{

}

void plotter::Plot5()//draw x time diagram
{

}

void plotter::Plot6()//draw y time diagram
{

}

void plotter::clearPlot()
{
    chart->removeAllSeries();
    chart->createDefaultAxes();
}
