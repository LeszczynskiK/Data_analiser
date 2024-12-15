#include "stats1.h"

stats1::stats1(bool allLeft, bool allRight, bool twoColumn,QWidget *parent)
    : QWidget(parent),
    all_numbers_left(allLeft),
    all_numbers_right(allRight),
    two_column_mode(twoColumn)
{
    setWindowTitle("Math stats I window");

    const int x =1920*0.8;//x window size
    const int y=1080*0.8;//y window size

    setFixedSize(x, y);//Set window size

    //Background image
    background = QPixmap("/home/krzysiek89/Desktop/QT_aplikacje/Data_analiser/stats1_background.png").scaled(x, y);

    QFont font;
    font.setPointSize(21);//Font size -all font size

    QFont font_stats;
    font_stats.setPointSize(16);//Font size -all font size

    exit_button = new QPushButton("Exit app...", this);//leave from app
    exit_button->setFont(font);
    exit_button->setStyleSheet("color: yellow;");
    exit_button->setGeometry(230, 770, 200, 70);
    connect(exit_button, &QPushButton::clicked, this, &stats1::exitApp);

    //Add frame based on QLabel
    frame = new QLabel(this);//Frame 1
    int frame_x=x/2+130;//frame x_size
    int frame_y=y/2 + 370;//frame y_size
    frame->setGeometry(600, 30, frame_x, frame_y);//Pos and size
    frame->setStyleSheet("border: 3px solid black;");//Style of frame

    main_button = new QPushButton("Go to menu...", this);
    main_button->setFont(font);
    main_button->setStyleSheet("color: yellow;");
    main_button->setGeometry(10, 770, 200, 70);
    connect(main_button, &QPushButton::clicked, this, &stats1::mainPage);

    //display data field(screen)
    dataDisplay = new QTextEdit(this);
    dataDisplay->setGeometry(600+10, 30+10, frame_x-20, frame_y-20);;
    dataDisplay->setFont(font_stats);
    dataDisplay->setReadOnly(true);//only to read
    dataDisplay->setStyleSheet("background-color: white;color: black; border: 1px solid black;");//background colour and font colour
    displayDataAnalysis();

    int x_size = 350;
    int y_size = 53;
    int x_begin = 30;
    int y_begin = 240;
    int gap=10;

    mean_button = new QPushButton("Mean value", this);
    mean_button->setFont(font);
    mean_button->setStyleSheet("color: yellow;");
    mean_button->setGeometry(x_begin, y_begin, x_size, y_size);
    connect(mean_button, &QPushButton::clicked, this, &stats1::count_mean);

    median_button = new QPushButton("Median", this);
    median_button->setFont(font);
    median_button->setStyleSheet("color: yellow;");
    median_button->setGeometry(x_begin, y_begin+gap+y_size, x_size, y_size);
    connect(median_button, &QPushButton::clicked, this, &stats1::count_median);

    variance_button = new QPushButton("Variance", this);
    variance_button->setFont(font);
    variance_button->setStyleSheet("color: yellow;");
    variance_button->setGeometry(x_begin, y_begin+2*gap+2*y_size, x_size, y_size);
    connect(variance_button, &QPushButton::clicked, this, &stats1::count_variance);

    standard_deviation_button = new QPushButton("Standard deviation", this);
    standard_deviation_button->setFont(font);
    standard_deviation_button->setStyleSheet("color: yellow;");
    standard_deviation_button->setGeometry(x_begin, y_begin+3*gap+3*y_size, x_size, y_size);
    connect(standard_deviation_button, &QPushButton::clicked, this, &stats1::count_standard_deviation);

    range_button = new QPushButton("Max - Min value", this);
    range_button->setFont(font);
    range_button->setStyleSheet("color: yellow;");
    range_button->setGeometry(x_begin, y_begin+4*gap+4*y_size, x_size, y_size);
    connect(range_button, &QPushButton::clicked, this, &stats1::count_range);

    min_button = new QPushButton("Min value", this);
    min_button->setFont(font);
    min_button->setStyleSheet("color: yellow;");
    min_button->setGeometry(x_begin, y_begin+5*gap+5*y_size, x_size, y_size);
    connect(min_button, &QPushButton::clicked, this, &stats1::count_min_value);

    max_button = new QPushButton("Max value", this);
    max_button->setFont(font);
    max_button->setStyleSheet("color: yellow;");
    max_button->setGeometry(x_begin, y_begin+6*gap+6*y_size, x_size, y_size);
    connect(max_button, &QPushButton::clicked, this, &stats1::count_max_value);

    amount_button = new QPushButton("Count amount of probes", this);
    amount_button->setFont(font);
    amount_button->setStyleSheet("color: yellow;");
    amount_button->setGeometry(x_begin, y_begin+7*gap+7*y_size, x_size, y_size);
    connect(amount_button, &QPushButton::clicked, this, &stats1::count_amount_of_numbers);

    clear_chat_button = new QPushButton("Clear...", this);
    clear_chat_button->setFont(font);
    clear_chat_button->setStyleSheet("color: yellow;");
    clear_chat_button->setGeometry(450, 770, 120, 70);
    connect(clear_chat_button, &QPushButton::clicked, this, &stats1::clear_chat);
}

void stats1::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, background);//Background
    QWidget::paintEvent(event);
}

void stats1::exitApp()
{
    this->close();//turn off app...
}

void stats1::mainPage()
{
    mainapp *appWindow = new mainapp();
    appWindow->show();
    this->close();
}

void stats1::displayDataAnalysis()//analisys about mode selection
{
    QString message;

    if (two_column_mode) {
        message = "Two column mode selected.\n";
        message += "Left column numerical type: " + QString(all_numbers_left ? "Yes" : "No") + "\n";
        message += "Right column numerical type: " + QString(all_numbers_right ? "Yes" : "No");
    } else {
        message = "Single column mode selected.\n";
        message += "Column numerical type: " + QString(all_numbers_left ? "Yes" : "No");
    }

    dataDisplay->setText(message);
}

void stats1::count_mean()
{
    if(two_column_mode == true)
    {
        if(all_numbers_left == true && all_numbers_right == true)
        {
            message1 += "Mean for 1st column: \n";
            message1 += "Mean for 2nd column: \n";
        }
        else if(all_numbers_left == true && all_numbers_right == false)
        {
            message1 += "Mean for 1st column: \n";
            message1 += "2nd column is not numerical. \n";
        }
        else if(all_numbers_left == false && all_numbers_right == true)
        {
            message1 += "1st column is not numerical. \n";
            message1 += "Mean for 2nd column: \n";
        }
        else
        {
            message1 += "1st and 2nd column is numerical value. \n";
        }
    }
    else
    {
        if(all_numbers_left == true)
        {
            message1 += "Mean for 1st column: \n";
        }
        else
        {
            message1 += "1st column is not numerical. \n";
        }
    }
    dataDisplay->setText(message1);
}

void stats1::count_median()
{
    if(two_column_mode == true)
    {
        if(all_numbers_left == true && all_numbers_right == true)
        {
            message1 += "Mean for 1st column: \n";
            message1 += "Mean for 2nd column: \n";
        }
        else if(all_numbers_left == true && all_numbers_right == false)
        {
            message1 += "Mean for 1st column: \n";
            message1 += "2nd column is not numerical. \n";
        }
        else if(all_numbers_left == false && all_numbers_right == true)
        {
            message1 += "1st column is not numerical. \n";
            message1 += "Mean for 2nd column: \n";
        }
        else
        {
            message1 += "1st and 2nd column is numerical value. \n";
        }
    }
    else
    {
        if(all_numbers_left == true)
        {
            message1 += "Mean for 1st column: \n";
        }
        else
        {
            message1 += "1st column is not numerical. \n";
        }
    }
    dataDisplay->setText(message1);
}

void stats1::count_variance()
{

}

void stats1::count_standard_deviation()
{

}

void stats1::count_range()
{

}

void stats1::count_min_value()
{

}

void stats1::count_max_value()
{

}

void stats1::count_amount_of_numbers()
{

}

void stats1::clear_chat()
{
    dataDisplay->clear();
}

