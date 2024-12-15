#ifndef STATS1_H
#define STATS1_H

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

class stats1 : public QWidget {
    Q_OBJECT
public:
    stats1(const vector<double> left,const vector<double> right,bool allLeft, bool allRight, bool twoColumn,QWidget *parent=nullptr);//share variables from mainapp

private slots:
    void paintEvent(QPaintEvent *event);//background setter
    void exitApp();//exit app
    void mainPage();//go to main page

    //methods to count stats
    void displayDataAnalysis();//information about data
    void count_mean();//mean value
    void count_median();//median value display
    double calculateMedian(std::vector<double> &data);//median value calculate
    void count_variance();//variance value
    void count_standard_deviation();//standard deviation value
    void count_range();//range(max-min) value
    void count_min_value();//min value
    void count_max_value();//max value
    void count_amount_of_numbers();//how many numbers
    void clear_chat();

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
    QPushButton *mean_button;
    QPushButton *median_button;
    QPushButton *variance_button;
    QPushButton *standard_deviation_button;
    QPushButton *range_button;
    QPushButton *min_button;
    QPushButton *max_button;
    QPushButton *amount_button;
    QPushButton *clear_chat_button;


};

#endif // STATS1_H
