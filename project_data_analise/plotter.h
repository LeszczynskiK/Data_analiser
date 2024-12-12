#ifndef PLOTTER_H
#define PLOTTER_H


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

private:
     QPixmap background;//Background txt

};

#endif // PLOTTER_H
