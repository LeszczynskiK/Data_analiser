#ifndef MAINAPP_H
#define MAINAPP_H

#include "authorisation_page.h"

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
#include <QTextStream>
#include <QStringList>
#include <QMessageBox>
#include <QRegularExpression>



class mainapp : public QWidget {
    Q_OBJECT
public:
    mainapp(QWidget *parent = nullptr);

private slots:
    void paintEvent(QPaintEvent *event);//background setter
    void exitApp();
    void selectFile();
    void displaySelectedData();
private:
    QPixmap background;//Background txt
    QPushButton *exit_button;//exit app
    QPushButton *selectFileButton;//choose .csv file button
    QString csvFilePath;//path to csv file
    int selectedColumn;//Number of choosen column
    int selectedRowStart;//row start in column
    int selectedRowEnd;//row end in column
    QLineEdit *columnInput;//columnt input
    QLineEdit *rowStartInput;//start row input
    QLineEdit *rowEndInput;//end row input
    QTextEdit *dataDisplay;//place to display data from .csv
};


#endif // MAINAPP_H
