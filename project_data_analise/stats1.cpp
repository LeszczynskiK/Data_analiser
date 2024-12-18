#include "stats1.h"

stats1::stats1(const vector<double> left,const vector<double> right,bool allLeft, bool allRight, bool twoColumn,QWidget *parent)
    : QWidget(parent),
    left_column(left),
    right_column(right),
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
    dataDisplay->setGeometry(600+10, 30+10, frame_x-20, frame_y-20);
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

    range_button = new QPushButton("Range (min,max) value", this);
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
     qDebug() << "two_column_mode in displayDataAnalysis: " << two_column_mode;
    if (two_column_mode==true) {
        message += "Two column mode selected.\n";
        message += "Left column numerical type: " + QString(all_numbers_left ? "Yes" : "No") + "\n";
        message += "Right column numerical type: " + QString(all_numbers_right ? "Yes" : "No")+"\n";
        if(left_column.empty())
        {
            message += "Vector of 1st column data is empty! \n";
        }
        if(right_column.empty())
        {
            message += "Vector of 2nd column data is empty! \n";
        }
    } else {
        message += "Single column mode selected.\n";
        message += "Column numerical type: " + QString(all_numbers_left ? "Yes" : "No")+"\n";
        if(left_column.empty())
        {
            message += "Vector of 1st column data is empty! \n";
        }
    }
    dataDisplay->setText(message);
}

double stats1::sum_left_fun()
{
    sum_left=0;
    for(auto o1 : left_column)
    {
        sum_left+=o1;
    }
    return sum_left;
}

double stats1::sum_right_fun()
{
    sum_right=0;
    for(auto o1 : right_column)
    {
        sum_right+=o1;
    }
    return sum_right;
}
double stats1::mean_left_fun()
{
    size_left = left_column.size();
    double temp1 = sum_left_fun();
    avg_left = temp1/size_left;
    return avg_left;
}

double stats1::mean_right_fun()
{
    size_right = right_column.size();
    double temp2 = sum_right_fun();
    avg_right = temp2/size_right;
    return avg_right;
}

void stats1::count_mean()
{
    avg_left = mean_left_fun();
    avg_right = mean_right_fun();

    if(two_column_mode == true)
    {
        if(all_numbers_left == true && all_numbers_right == true)
        {
            message1 += "Mean for 1st column: \n"+to_string(avg_left) + "\n";
            message1 += "Mean for 2nd column: \n"+to_string(avg_right) + "\n";
        }
        else if(all_numbers_left == true && all_numbers_right == false)
        {
            message1 += "Mean for 1st column: \n"+to_string(avg_left) + "\n";
            message1 += "2nd column is not numerical. \n";
        }
        else if(all_numbers_left == false && all_numbers_right == true)
        {
            message1 += "1st column is not numerical. \n";
            message1 += "Mean for 2nd column: \n"+to_string(avg_right) + "\n";
        }
        else
        {
            message1 += "1st and 2nd column is NOT numerical value. \n";
        }
    }
    else
    {
        if(all_numbers_left == true)
        {
            message1 += "Mean for 1st column: \n"+to_string(avg_left) + "\n";
        }
        else
        {
            message1 += "1st column is not numerical. \n";
        }
    }
    dataDisplay->setText(message1);
}

double stats1::calculateMedian(vector<double> &data)
{
    if (data.empty())
        return 0.0;

    sort(data.begin(), data.end());//median is based on sorted increasily number set

    int n = data.size();
    if (n % 2 == 0)//if even number of elements
    {
        //return average of the two middle numbers
        return (data[n / 2 - 1] + data[n / 2]) / 2.0;
    }
    else//odd number of elements
    {
        return data[n / 2];//return the middle element
    }
}

void stats1::count_median()
{
    median_left = calculateMedian(left_column);
    median_right = calculateMedian(right_column);
    if(two_column_mode == true)
    {
        if(all_numbers_left == true && all_numbers_right == true)
        {
            message1 += "Median for 1st column: \n"+to_string(median_left)+" \n";
            message1 += "Median for 2nd column: \n"+to_string(median_right)+" \n";
        }
        else if(all_numbers_left == true && all_numbers_right == false)
        {
            message1 += "Median for 1st column: \n"+to_string(median_left)+" \n";
            message1 += "2nd column is not numerical. \n";
        }
        else if(all_numbers_left == false && all_numbers_right == true)
        {
            message1 += "1st column is not numerical. \n";
            message1 += "Median for 2nd column: \n"+to_string(median_right)+" \n";
        }
        else
        {
            message1 += "1st and 2nd column is NOT numerical value. \n";
        }
    }
    else
    {
        if(all_numbers_left == true)
        {
            message1 += "Mean for 1st column: \n"+to_string(median_left)+" \n";
        }
        else
        {
            message1 += "1st column is not numerical. \n";
        }
    }
    dataDisplay->setText(message1);
}

double stats1::variance_left_fun()
{
    avg_left = mean_left_fun();
    variance_left = 0;
    for (auto o1 : left_column)//variance for 1st column
    {
        variance_left += pow(o1 - avg_left, 2);
    }
    variance_left = variance_left/size_left;
    return variance_left;
}

double stats1::variance_right_fun()
{
    avg_right = mean_right_fun();
    variance_right = 0;
    for (auto o2 : right_column)//variance for 2nd column
    {
        variance_right += pow(o2 - avg_right, 2);
    }
    variance_right = variance_right/size_right;
    return variance_right;
}

void stats1::count_variance()
{
    variance_left = variance_left_fun();
    variance_right = variance_right_fun();

    if(two_column_mode == true)
    {
        if(all_numbers_left == true && all_numbers_right == true)
        {
            message1 += "Variance for 1st column: \n"+to_string(variance_left)+"\n";
            message1 += "Variance for 2nd column: \n"+to_string(variance_right)+"\n";
        }
        else if(all_numbers_left == true && all_numbers_right == false)
        {
            message1 += "Variance for 1st column: \n"+to_string(variance_left)+"\n";
            message1 += "2nd column is not numerical. \n";
        }
        else if(all_numbers_left == false && all_numbers_right == true)
        {
            message1 += "1st column is not numerical. \n";
            message1 += "Variance for 2nd column: \n"+to_string(variance_right)+"\n";
        }
        else
        {
            message1 += "1st and 2nd column is NOT numerical value. \n";
        }
    }
    else
    {
        if(all_numbers_left == true)
        {
            message1 += "Variance for 1st column: \n"+to_string(variance_left)+"\n";
        }
        else
        {
            message1 += "1st column is not numerical. \n";
        }
    }
    dataDisplay->setText(message1);
}

double stats1::std_dev_left_fun()
{
    variance_left=variance_left_fun();
    std_dev_left = sqrt(variance_left);
}

double stats1::std_dev_right_fun()
{
    variance_right=variance_right_fun();
    std_dev_right = sqrt(variance_right);
}

void stats1::count_standard_deviation()
{
    std_dev_left = std_dev_left_fun();
    std_dev_right = std_dev_right_fun();
    if(two_column_mode == true)
    {
        if(all_numbers_left == true && all_numbers_right == true)
        {
            message1 += "Standard deviation for 1st column: \n"+to_string(std_dev_left)+"\n";
            message1 += "Standard deviation for 2nd column: \n"+to_string(std_dev_right)+"\n";
        }
        else if(all_numbers_left == true && all_numbers_right == false)
        {
            message1 += "Standard deviation for 1st column: \n"+to_string(std_dev_left)+"\n";
            message1 += "2nd column is not numerical. \n";
        }
        else if(all_numbers_left == false && all_numbers_right == true)
        {
            message1 += "1st column is not numerical. \n";
            message1 += "Standard deviation for 2nd column: \n"+to_string(std_dev_right)+"\n";
        }
        else
        {
            message1 += "1st and 2nd column is NOT numerical value. \n";
        }
    }
    else
    {
        if(all_numbers_left == true)
        {
            message1 += "Standard deviation for 1st column: \n"+to_string(std_dev_left)+"\n";
        }
        else
        {
            message1 += "1st column is not numerical. \n";
        }
    }
    dataDisplay->setText(message1);
}

void stats1::count_range()
{
    range_min_left=0;//preinitialisation, becouse there is error withoud this
    range_min_right=0;
    range_max_left=0;
    range_max_right=0;

    if(two_column_mode == true)
    {
        if(all_numbers_left == true && all_numbers_right == true)
        {
            range_min_left=*min_element(left_column.begin(),left_column.end());
            range_max_left=*max_element(left_column.begin(),left_column.end());
            range_min_right=*min_element(right_column.begin(),right_column.end());
            range_max_right=*max_element(right_column.begin(),right_column.end());
            message1 += "Range for 1st column: \n"+to_string(range_min_left)+" to: "+to_string(range_max_left)+"\n";
            message1 += "Range for 2nd column: \n"+to_string(range_min_right)+" to: "+to_string(range_max_right)+"\n";
        }
        else if(all_numbers_left == true && all_numbers_right == false)
        {
            range_min_left=*min_element(left_column.begin(),left_column.end());
            range_max_left=*max_element(left_column.begin(),left_column.end());
            message1 += "Range for 1st column: \n"+to_string(range_min_left)+" to: "+to_string(range_max_left)+"\n";
            message1 += "2nd column is not numerical. \n";
        }
        else if(all_numbers_left == false && all_numbers_right == true)
        {
            range_min_right=*min_element(right_column.begin(),right_column.end());
            range_max_right=*max_element(right_column.begin(),right_column.end());
            message1 += "1st column is not numerical. \n";
            message1 += "Range for 2nd column: \n"+to_string(range_min_right)+" to: "+to_string(range_max_right)+"\n";
        }
        else
        {
            message1 += "1st and 2nd column is NOT numerical value. \n";
        }
    }
    else
    {
        if(all_numbers_left == true)
        {
            range_min_left=*min_element(left_column.begin(),left_column.end());
            range_max_left=*max_element(left_column.begin(),left_column.end());
            message1 += "Range for 1st column: \n"+to_string(range_min_left)+" to: "+to_string(range_max_left)+"\n";
        }
        else
        {
            message1 += "1st column is not numerical. \n";
        }
    }
    dataDisplay->setText(message1);
}

void stats1::count_min_value()
{
    min_left =0;//preinitialisation, becouse there is error without this
    min_right=0;

    if(two_column_mode == true)
    {
        if(all_numbers_left == true && all_numbers_right == true)
        {
             min_left=*min_element(left_column.begin(),left_column.end());
             min_right=*min_element(right_column.begin(),right_column.end());
            message1 += "Min element for 1st column: \n"+to_string(min_left)+" \n";
            message1 += "Min element for 2nd column: \n"+to_string(min_right)+" \n";
        }
        else if(all_numbers_left == true && all_numbers_right == false)
        {
             min_left=*min_element(left_column.begin(),left_column.end());
            message1 += "Min element for 1st column: \n"+to_string(min_left)+" \n";
            message1 += "2nd column is not numerical. \n";
        }
        else if(all_numbers_left == false && all_numbers_right == true)
        {
             min_right=*min_element(right_column.begin(),right_column.end());
            message1 += "1st column is not numerical. \n";
            message1 += "Min element for 2nd column: \n"+to_string(min_right)+" \n";
        }
        else
        {
            message1 += "1st and 2nd column is NOT numerical value. \n";
        }
    }
    else
    {
        if(all_numbers_left == true)
        {
             min_left=*min_element(left_column.begin(),left_column.end());
            message1 += "Min element for 1st column: \n"+to_string(min_left)+" \n";
        }
        else
        {
            message1 += "1st column is not numerical. \n";
        }
    }
    dataDisplay->setText(message1);
}

void stats1::count_max_value()
{
    max_left =0;//preinitialisation, becouse there is error without this
    max_right=0;

    if(two_column_mode == true)
    {
        if(all_numbers_left == true && all_numbers_right == true)
        {
                max_left=*max_element(left_column.begin(),left_column.end());
            max_right=*max_element(right_column.begin(),right_column.end());
            message1 += "Max element for 1st column: \n"+to_string(max_left)+" \n";
            message1 += "Max element for 2nd column: \n"+to_string(max_right)+" \n";
        }
        else if(all_numbers_left == true && all_numbers_right == false)
        {
                max_left=*max_element(left_column.begin(),left_column.end());
            message1 += "Max element for 1st column: \n"+to_string(max_left)+" \n";
            message1 += "2nd column is not numerical. \n";
        }
        else if(all_numbers_left == false && all_numbers_right == true)
        {
            max_right=*max_element(right_column.begin(),right_column.end());
            message1 += "1st column is not numerical. \n";
            message1 += "Max element for 2nd column: \n"+to_string(max_right)+" \n";
        }
        else
        {
            message1 += "1st and 2nd column is NOT numerical value. \n";
        }
    }
    else
    {
        if(all_numbers_left == true)
        {
                max_left=*max_element(left_column.begin(),left_column.end());
            message1 += "Max element for 1st column: \n"+to_string(max_left)+" \n";
        }
        else
        {
            message1 += "1st column is not numerical. \n";
        }
    }
    dataDisplay->setText(message1);
}

void stats1::count_amount_of_numbers()
{
    size_left = left_column.size();
    size_right = right_column.size();
    if(two_column_mode == true)
    {
        if(all_numbers_left == true && all_numbers_right == true)
        {
            message1 += "Amount for 1st column: \n"+to_string(size_left)+" \n";
            message1 += "Amount for 2nd column: \n"+to_string(size_right)+" \n";
        }
        else if(all_numbers_left == true && all_numbers_right == false)
        {
            message1 += "Amount for 1st column: \n"+to_string(size_left)+" \n";
            message1 += "2nd column is not numerical. \n";
        }
        else if(all_numbers_left == false && all_numbers_right == true)
        {
            message1 += "1st column is not numerical. \n";
            message1 += "Amount for 2nd column: \n"+to_string(size_right)+" \n";
        }
        else
        {
            message1 += "1st and 2nd column is NOT numerical value. \n";
        }
    }
    else
    {
        if(all_numbers_left == true)
        {
            message1 += "Amount for 1st column: \n"+to_string(size_left)+" \n";
        }
        else
        {
            message1 += "1st column is not numerical. \n";
        }
    }
    dataDisplay->setText(message1);
}

void stats1::clear_chat()
{
    message1 = " ";
    dataDisplay->clear();
}

