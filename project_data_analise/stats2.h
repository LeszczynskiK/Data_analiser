#ifndef STATS2_H
#define STATS2_H

#include "mainapp.h"

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QTextEdit>
#include <QPainter>
#include <QPaintEvent>
#include <QFileDialog>
#include <QTextEdit>
#include <QFile>
#include <vector>
#include <algorithm>
using namespace std;

class stats2 : public QWidget {
    Q_OBJECT
public:
    stats2(const vector<double> left,const vector<double> right,bool allLeft, bool allRight, bool twoColumn,QWidget *parent=nullptr);//share variables from mainapp

private slots:
    void paintEvent(QPaintEvent *event);//background setter
    void exitApp();//exit app
    void mainPage();//go to main page

    //methods to display stats
    void displayDataAnalysis();//information about data
    void count_kurtosis();//count kurtosis
    void count_CV();//count coefficient of variation
    void count_skewness();//count skewness
    void count_element_sum();//count element sum
    void count_min_max_diff();//count difference between  min max value
    void count_MAD();//count MAD
    void clear_chat();//clear chat

private:
    QPixmap background;//Background txt
    QPushButton *exit_button;//exit app
    QPushButton *main_button;//go to main page
    QLabel *frame;//frame for display screen
    QTextEdit *dataDisplay;//place to display data from .csv
    vector<double> left_column;
    vector<double> right_column;
    bool all_numbers_left;//if all numeric on left column
    bool all_numbers_right;//if all numeric on the right column
    bool two_column_mode;//mode 1 or 2 column
    QString message1;//initialise space for messages

    //buttons to do statistics methods
    QPushButton *kurtosis_button;//kurtosis button
    QPushButton *CV_button;//Coefficient of Variation button
    QPushButton *skewness_button;//asymetry level button
    QPushButton *element_sum_button;//sum of elements button
    QPushButton *min_max_diff_button;//abs(min-max) button
    QPushButton *MAD_button;//mean absolute deviation
    QPushButton *clear_chat_button;//clear chat

    //variables to stats counting
    int size_left;
    int size_right;
    double sum_left;
    double sum_right;
    double avg_left;
    double avg_right;
    double median_left;
    double median_right;
    double variance_left;
    double variance_right;
    double std_dev_left;
    double std_dev_right;
    double kurtosis_left;
    double kurtosis_right;
    double CV_left;
    double CV_right;
    long double skewness_left;
    long double skewness_right;
    double range_min_left;
    double range_max_left;
    double left_diff;
    double range_min_right;
    double range_max_right;
    double right_diff;
    double mad_left;
    double mad_right;

    //methods to count stats
    //functions to count stats
    double sum_left_fun();
    double sum_right_fun();
    double mean_left_fun();
    double mean_right_fun();
    double variance_left_fun();
    double variance_right_fun();
    double std_dev_left_fun();
    double std_dev_right_fun();
    double kurtosis_left_fun();
    double kurtosis_right_fun();
    double CV_left_fun();
    double CV_right_fun();
    long double skewness_left_fun();
    long double skewness_right_fun();
    double MAD_left_fun();
    double MAD_right_fun();
};

#endif // STATS2_H
