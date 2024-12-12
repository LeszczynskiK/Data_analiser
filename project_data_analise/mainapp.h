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
#include <QRadioButton>


class mainapp : public QWidget {
    Q_OBJECT
public:
    mainapp(QWidget *parent = nullptr);

private slots:
    void paintEvent(QPaintEvent *event);//background setter
    void exitApp();
    void selectFile();
    void toggleDoubleColumn(bool var);
    void displaySelectedData();
private:
    QPixmap background;//Background txt
    QPushButton *exit_button;//exit app
    QPushButton *selectFileButton;//choose .csv file button
    QString csvFilePath;//path to csv file
    QLabel *frame;//frame for display screen
    QLabel *columnLabel;//1st column number
    QLabel *rowStartLabel;//number of 1st element in row
    QLabel *rowEndLabel;//number of last element in row
    QLabel *secondColumnLabel;//if option yes - number of 2nd column
    QLineEdit *columnInput;//columnt input
    QLineEdit *rowStartInput;//start row input
    QLineEdit *rowEndInput;//end row input
    QTextEdit *dataDisplay;//place to display data from .csv
    QRadioButton *singleColumnRadio;//switch to 1 columnt data management
    QRadioButton *doubleColumnRadio;//switch do 2 column data management
    QLineEdit *secondColumnInput;//number of column number two
    QPushButton *showDataButton;//display selected data

};


#endif // MAINAPP_H
