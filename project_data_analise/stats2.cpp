#include "stats2.h"

stats2::stats2(const vector<double> left,const vector<double> right,bool allLeft, bool allRight, bool twoColumn,QWidget *parent)
    : QWidget(parent),
    left_column(left),
    right_column(right),
    all_numbers_left(allLeft),
    all_numbers_right(allRight),
    two_column_mode(twoColumn)
{
    setWindowTitle("Math stats II window");

    const int x =1920*0.8;//x window size
    const int y=1080*0.8;//y window size

    setFixedSize(x, y);//Set window size

    //Background image
    background = QPixmap("/home/krzysiek89/Desktop/QT_aplikacje/Data_analiser/stats2_background.png").scaled(x, y);

    QFont font;
    font.setPointSize(21);//Font size -all font size

    QFont font_stats;
    font_stats.setPointSize(16);//Font size -all font size

    exit_button = new QPushButton("Exit app...", this);//leave from app
    exit_button->setFont(font);
    exit_button->setStyleSheet("color: yellow;");
    exit_button->setGeometry(230, 770, 200, 70);
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
    main_button->setGeometry(10, 770, 200, 70);
    connect(main_button, &QPushButton::clicked, this, &stats2::mainPage);

    int x_size = 350;
    int y_size = 53;
    int x_begin = 30;
    int y_begin = 300;
    int gap=10;

    kurtosis_button = new QPushButton("Kurtosis", this);
    kurtosis_button->setFont(font);
    kurtosis_button->setStyleSheet("color: yellow;");
    kurtosis_button->setGeometry(x_begin, y_begin, x_size, y_size);
    connect(kurtosis_button, &QPushButton::clicked, this, &stats2::count_kurtosis);

    CV_button = new QPushButton("Coefficient of variation", this);
    CV_button->setFont(font);
    CV_button->setStyleSheet("color: yellow;");
    CV_button->setGeometry(x_begin, y_begin+gap+y_size, x_size, y_size);
    connect(CV_button, &QPushButton::clicked, this, &stats2::count_CV);

    skewness_button = new QPushButton("Skewness", this);
    skewness_button->setFont(font);
    skewness_button->setStyleSheet("color: yellow;");
    skewness_button->setGeometry(x_begin, y_begin+2*gap+2*y_size, x_size, y_size);
    connect(skewness_button, &QPushButton::clicked, this, &stats2::count_skewness);

    element_sum_button = new QPushButton("Sum of elements", this);
    element_sum_button->setFont(font);
    element_sum_button->setStyleSheet("color: yellow;");
    element_sum_button->setGeometry(x_begin, y_begin+3*gap+3*y_size, x_size, y_size);
    connect(element_sum_button, &QPushButton::clicked, this, &stats2::count_element_sum);

    min_max_diff_button = new QPushButton("Abs(min_value,max_value)", this);
    min_max_diff_button->setFont(font);
    min_max_diff_button->setStyleSheet("color: yellow;");
    min_max_diff_button->setGeometry(x_begin, y_begin+4*gap+4*y_size, x_size, y_size);
    connect(min_max_diff_button, &QPushButton::clicked, this, &stats2::count_min_max_diff);

    MAD_button = new QPushButton("Mean absolute deviation", this);
    MAD_button->setFont(font);
    MAD_button->setStyleSheet("color: yellow;");
    MAD_button->setGeometry(x_begin, y_begin+5*gap+5*y_size, x_size, y_size);
    connect(MAD_button, &QPushButton::clicked, this, &stats2::count_MAD);

    clear_chat_button = new QPushButton("Clear...", this);
    clear_chat_button->setFont(font);
    clear_chat_button->setStyleSheet("color: yellow;");
    clear_chat_button->setGeometry(450, 770, 120, 70);
    connect(clear_chat_button, &QPushButton::clicked, this, &stats2::clear_chat);

    //display data field(screen)
    dataDisplay = new QTextEdit(this);
    dataDisplay->setGeometry(600+10, 30+10, frame_x-20, frame_y-20);;
    dataDisplay->setFont(font_stats);
    dataDisplay->setReadOnly(true);//only to read
    dataDisplay->setStyleSheet("background-color: white;color:black;border: 1px solid black;");//background colour and font colour
    displayDataAnalysis();
}

void stats2::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, background);//Background
    QWidget::paintEvent(event);
}

void stats2::displayDataAnalysis()//analisys about mode selection
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


double stats2::sum_left_fun()
{
    sum_left=0;
    for(auto o1 : left_column)
    {
        sum_left+=o1;
    }
    return sum_left;
}

double stats2::sum_right_fun()
{
    sum_right=0;
    for(auto o1 : right_column)
    {
        sum_right+=o1;
    }
    return sum_right;
}
double stats2::mean_left_fun()
{
    size_left = left_column.size();
    double temp1 = sum_left_fun();
    avg_left = temp1/size_left;
    return avg_left;
}

double stats2::mean_right_fun()
{
    size_right = right_column.size();
    double temp2 = sum_right_fun();
    avg_right = temp2/size_right;
    return avg_right;
}

double stats2::variance_left_fun()
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

double stats2::variance_right_fun()
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

double stats2::std_dev_left_fun()
{
    variance_left=variance_left_fun();
    std_dev_left = sqrt(variance_left);
}

double stats2::std_dev_right_fun()
{
    variance_right=variance_right_fun();
    std_dev_right = sqrt(variance_right);
}

double stats2::kurtosis_left_fun()
{
    //calculate kurtosis
    kurtosis_left = 0;
    //(4th central moment / standard deviation) ^ 4, where 4th central moment is
    // number[i]-avg_numbers
    avg_left = mean_left_fun();
    std_dev_left = std_dev_left_fun();

    for (auto o1 : left_column)//for 1st column
    {
        kurtosis_left += pow((o1 - avg_left) / std_dev_left, 4);//normalized 4th moment
    }
    kurtosis_left = kurtosis_left / size_left;

    return kurtosis_left;
}

double stats2::kurtosis_right_fun()
{
    //calculate kurtosis
    kurtosis_right = 0;

    avg_right = mean_right_fun();
    std_dev_right = std_dev_right_fun();

    //(4th central moment / standard deviation) ^ 4, where 4th central moment is
    // number[i]-avg_numbers
    for (auto o2 : right_column)//for 2nd column
    {
        kurtosis_right += pow((o2 - avg_right) / std_dev_right, 4);//normalized 4th moment
    }
    kurtosis_right = kurtosis_right / size_right;
    return kurtosis_right;
}

void stats2::count_kurtosis()//count kurtosis
{
    kurtosis_left = kurtosis_left_fun();
    kurtosis_right = kurtosis_right_fun();

    if(two_column_mode == true)
    {
        if(all_numbers_left == true && all_numbers_right == true)
        {
            message1 += "kurtosis for 1st column: \n"+to_string(kurtosis_left)+"\n";
            message1 += "kurtosis for 2nd column: \n"+to_string(kurtosis_right)+"\n";
        }
        else if(all_numbers_left == true && all_numbers_right == false)
        {
            message1 += "kurtosis for 1st column: \n"+to_string(kurtosis_left)+"\n";
            message1 += "2nd column is not numerical. \n";
        }
        else if(all_numbers_left == false && all_numbers_right == true)
        {
            message1 += "1st column is not numerical. \n";
            message1 += "kurtosis for 2nd column: \n"+to_string(kurtosis_right)+"\n";
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
            message1 += "kurtosis for 1st column: \n"+to_string(kurtosis_left)+"\n";
        }
        else
        {
            message1 += "1st column is not numerical. \n";
        }
    }
    dataDisplay->setText(message1);

}

double stats2::CV_left_fun()
{
    std_dev_left = std_dev_left_fun();
    avg_left = mean_left_fun();

    CV_left = (std_dev_left / avg_left) * 100;
    return CV_left;
}

double stats2::CV_right_fun()
{
    std_dev_right = std_dev_right_fun();
    avg_right = mean_right_fun();

    CV_right = (std_dev_right / avg_right) * 100;
    return CV_right;
}

void stats2::count_CV()//coefficient of variation : standard_deviation/mean * 100%
{
    CV_left = CV_left_fun();
    CV_right = CV_right_fun();

    //display results
    if (two_column_mode == true)
    {
        if (all_numbers_left == true && all_numbers_right == true)
        {
            message1 += "Coefficient of Variation (CV) for 1st column: \n" + to_string(CV_left) + "%\n";
            message1 += "Coefficient of Variation (CV) for 2nd column: \n" + to_string(CV_right) + "%\n";
        }
        else if (all_numbers_left == true && all_numbers_right == false)
        {
            message1 += "Coefficient of Variation (CV) for 1st column: \n" + to_string(CV_left) + "%\n";
            message1 += "2nd column is not numerical. \n";
        }
        else if (all_numbers_left == false && all_numbers_right == true)
        {
            message1 += "1st column is not numerical. \n";
            message1 += "Coefficient of Variation (CV) for 2nd column: \n" + to_string(CV_right) + "%\n";
        }
        else
        {
            message1 += "1st and 2nd columns are NOT numerical values. \n";
        }
    }
    else
    {
        if (all_numbers_left == true)
        {
            message1 += "Coefficient of Variation (CV) for 1st column: \n" + to_string(CV_left) + "%\n";
        }
        else
        {
            message1 += "1st column is not numerical. \n";
        }
    }

    dataDisplay->setText(message1);
}

double stats2::skewness_left_fun()
{
    //calculate skewness
    skewness_left=0;
    avg_left=mean_left_fun();

    for (auto o1 : left_column)//skewness for 1st column
    {
        skewness_left += pow(o1 - avg_left, 3);
    }
    return skewness_left;
}

double stats2::skewness_right_fun()
{
    //calculate skewness
    skewness_right=0;
    avg_right = mean_right_fun();

    for (auto o2 : right_column)//skewness for 2nd column
    {
        skewness_right += pow(o2 - avg_right, 3);
    }
    return skewness_right;
}

void stats2::count_skewness()//count skewness: (x[i] - x_mean)^3 / (N-1)*standard_deviation^3
{

    skewness_left = skewness_left_fun();
    skewness_right = skewness_right_fun();

    if(two_column_mode == true)
    {
        if(all_numbers_left == true && all_numbers_right == true)
        {
            message1 += "Skewness for 1st column: \n"+to_string(skewness_left)+"\n";
            message1 += "Skewness for 2nd column: \n"+to_string(skewness_right)+"\n";
        }
        else if(all_numbers_left == true && all_numbers_right == false)
        {
            message1 += "Skewness for 1st column: \n"+to_string(skewness_left)+"\n";
            message1 += "2nd column is not numerical. \n";
        }
        else if(all_numbers_left == false && all_numbers_right == true)
        {
            message1 += "1st column is not numerical. \n";
            message1 += "Skewness for 2nd column: \n"+to_string(skewness_right)+"\n";
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
            message1 += "Skewness for 1st column: \n"+to_string(skewness_left)+"\n";
        }
        else
        {
            message1 += "1st column is not numerical. \n";
        }
    }
    dataDisplay->setText(message1);
}

void stats2::count_element_sum()//count element sum
{
    sum_left=0;
    sum_right=0;

    for(auto o1 : left_column)
    {
        sum_left+=o1;
    }

    for(auto o2 : right_column)
    {
        sum_right+=o2;
    }

    if(two_column_mode == true)
    {
        if(all_numbers_left == true && all_numbers_right == true)
        {
            message1 += "Sum for 1st column: \n"+to_string(sum_left) + "\n";
            message1 += "Sum for 2nd column: \n"+to_string(sum_right) + "\n";
        }
        else if(all_numbers_left == true && all_numbers_right == false)
        {
            message1 += "Sum for 1st column: \n"+to_string(sum_left) + "\n";
            message1 += "2nd column is not numerical. \n";
        }
        else if(all_numbers_left == false && all_numbers_right == true)
        {
            message1 += "1st column is not numerical. \n";
            message1 += "Sum for 2nd column: \n"+to_string(sum_right) + "\n";
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
            message1 += "Sum for 1st column: \n"+to_string(sum_left) + "\n";
        }
        else
        {
            message1 += "1st column is not numerical. \n";
        }
    }
    dataDisplay->setText(message1);
}

void stats2::count_min_max_diff()//count difference between  min max value
{
    //for 1 column mode
    range_min_left = *min_element(left_column.begin(), left_column.end());
    range_max_left = *max_element(left_column.begin(), left_column.end());
    left_diff = abs(range_max_left - range_min_left);

    if(two_column_mode == true)
    {
        range_min_right = *min_element(right_column.begin(), right_column.end());
        range_max_right = *max_element(right_column.begin(), right_column.end());
        right_diff = abs(range_max_right - range_min_right);

        if(all_numbers_left == true && all_numbers_right == true)
        {
            message1 += "abs(max_element,min_element) for 1st column: \n"+to_string(left_diff)+"\n";
            message1 += "abs(max_element,min_element) for 2nd column: \n"+to_string(right_diff)+"\n";
        }
        else if(all_numbers_left == true && all_numbers_right == false)
        {
            message1 += "abs(max_element,min_element) for 1st column: \n"+to_string(left_diff)+"\n";
            message1 += "2nd column is not numerical. \n";
        }
        else if(all_numbers_left == false && all_numbers_right == true)
        {
            message1 += "1st column is not numerical. \n";
            message1 += "abs(max_element,min_element) for 2nd column: \n"+to_string(right_diff)+"\n";
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
            message1 += "abs(max_element,min_element) for 1st column: \n"+to_string(left_diff)+"\n";
        }
        else
        {
            message1 += "1st column is not numerical. \n";
        }
    }
    dataDisplay->setText(message1);
}


double stats2::MAD_left_fun(){
    avg_left=mean_left_fun();
    //count MAD
    for (double val : left_column)
    {
        mad_left += abs(val - avg_left);
    }
    mad_left /= size_left;
    return mad_left;
}

double stats2::MAD_right_fun(){
    avg_right = mean_right_fun();
    //count MAD
    for (double val : right_column)
    {
        mad_right += abs(val - avg_right);
    }
    mad_right /= size_right;
    return mad_right;
}
void stats2::count_MAD()//count MAD- abs(xi - x_mean)/probe_amounts
{

    if(two_column_mode == true)
    {
        if(all_numbers_left == true && all_numbers_right == true)
        {
            message1 += "Mean Absolute Deviation for 1st column: \n"+to_string(mad_left)+"\n";
            message1 += "Mean Absolute Deviation for 2nd column: \n"+to_string(mad_right)+"\n";
        }
        else if(all_numbers_left == true && all_numbers_right == false)
        {
            message1 += "Mean Absolute Deviation for 1st column: \n"+to_string(mad_left)+"\n";
            message1 += "2nd column is not numerical. \n";
        }
        else if(all_numbers_left == false && all_numbers_right == true)
        {
            message1 += "1st column is not numerical. \n";
            message1 += "Mean Absolute Deviation for 2nd column: \n"+to_string(mad_right)+"\n";
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
            message1 += "Mean Absolute Deviation for 1st column: \n"+to_string(mad_left)+"\n";
        }
        else
        {
            message1 += "1st column is not numerical. \n";
        }
    }
    dataDisplay->setText(message1);

}

void stats2::clear_chat()//clear chat
{
    message1 = " ";
    dataDisplay->clear();
}

