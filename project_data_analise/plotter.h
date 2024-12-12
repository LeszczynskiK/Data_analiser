#ifndef PLOTTER_H
#define PLOTTER_H

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

class plotter : public QWidget {
    Q_OBJECT
public:
    plotter(QWidget *parent = nullptr);
private slots:
    void paintEvent(QPaintEvent *event);//background setter
    void exitApp();//exit app
    void mainPage();//go to main page

    //plotters types connected with buttons
    void Plot1();
    void Plot2();
    void Plot3();
    void Plot4();
    void Plot5();
    void Plot6();

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

};

#endif // PLOTTER_H
