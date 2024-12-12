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

class stats2 : public QWidget {
    Q_OBJECT
public:
    stats2(QWidget *parent = nullptr);

private slots:
    void paintEvent(QPaintEvent *event);//background setter
    void exitApp();//exit app
    void mainPage();//go to main page

private:
    QPixmap background;//Background txt
    QPushButton *exit_button;//exit app
    QPushButton *main_button;//go to main page
    QLabel *frame;//frame for display screen
    QTextEdit *dataDisplay;//place to display data from .csv
};

#endif // STATS2_H
