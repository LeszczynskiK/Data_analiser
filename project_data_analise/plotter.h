#ifndef PLOTTER_H
#define PLOTTER_H

#include "mainapp.h"

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
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


class plotter : public QWidget {
    Q_OBJECT
public:
    plotter(const vector<double> left,const vector<double> right,bool allLeft, bool allRight, bool twoColumn,QWidget *parent=nullptr);
private slots:
    void paintEvent(QPaintEvent *event);//background setter
    void exitApp();//exit app
    void mainPage();//go to main page
    void displayDataAnalysis();//information about data

    //plotters types connected with buttons
    void Plot1();
    void Plot2();
    void Plot3();
    void Plot4();
    void Plot5();
    void Plot6();

    void error_inform();//if something is wrong with data,inform
    void clearPlot();

private:
     QPixmap background;//Background txt
     QPushButton *exit_button;//exit app
     QPushButton *main_button;//go to main page
     QLabel *frame;//frame for display screen
     QWidget *drawing_area; //white rectangle for drawing or stats
     //column1 is x, column2 is y
     QPushButton *plot1;//x y
     QPushButton *plot2;//y x
     QPushButton *plot3;//time x
     QPushButton *plot4;//time y
     QPushButton *plot5;//x time
     QPushButton *plot6;//y time
     QPushButton *clear_screen;//clear screan(delete plot)
     QChartView *chartView;//to see
     QChart *chart;//to draw
     vector<double> left_column;
     vector<double> right_column;
     bool all_numbers_left;//if all numeric on left column
     bool all_numbers_right;//if all numeric on the right column
     bool two_column_mode;//mode 1 or 2 column
     QString message1;//initialise space for messages
     QLabel *dataAnalysisLabel;
};

#endif // PLOTTER_H
