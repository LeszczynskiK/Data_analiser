#ifndef MAINAPP_H
#define MAINAPP_H

#include "authorisation_page.h"
#include "stats1.h"
#include "stats2.h"
#include "plotter.h"

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
#include <vector>
using namespace std;

class mainapp : public QWidget {
    Q_OBJECT
public:
    mainapp(QWidget *parent = nullptr);
private slots:
    void paintEvent(QPaintEvent *event);//background setter
    void exitApp();//exit app
    void selectFile();//choose .csv
    void toggleDoubleColumn(bool var);//switch between 1 or 2 columns alalisys
    void displaySelectedData();//show data
    void stats1_page();//go to page stats1
    void stats2_page();//go to page stats2
    void plotter_page();//go to plotter
    void clear_chat();//clear chat
    void change_csv();//delete saved link do choosen csv to enable choose other one

private:
    QPixmap background;//Background txt
    QString filePath;//url for csv path
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
    QPushButton *plotterButton;//plotting
    QPushButton *stats1Button;//1st part of analisys
    QPushButton *stats2Button;//2nd part of analisys
    QPushButton *clear_chat_button;//button for chat clearing
    QPushButton *change_csv_button;
    bool all_numbers_left=false;//if data if numerical type
    bool all_numbers_right=false;//if data if numerical type
    bool two_column_mode;//if 2 columns mode, then true
    vector<double> left_column_vec;//keep double type data from column 1st
    vector<double> right_column_vec;//keep double type data from column 2nd

};


#endif // MAINAPP_H
