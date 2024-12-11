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

class mainapp : public QWidget {
    Q_OBJECT
public:
    mainapp(QWidget *parent = nullptr);

private slots:
    void paintEvent(QPaintEvent *event);//background setter
    void exitApp();
private:
    QPixmap background;//Background txt
    QPushButton *exit_button;//exit app
};


#endif // MAINAPP_H
