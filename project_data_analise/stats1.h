#ifndef STATS1_H
#define STATS1_H

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

class stats1 : public QWidget {
    Q_OBJECT
public:
    stats1(QWidget *parent = nullptr);

private slots:
    void paintEvent(QPaintEvent *event);//background setter

private:
     QPixmap background;//Background txt

};

#endif // STATS1_H
