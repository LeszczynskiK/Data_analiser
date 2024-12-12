#ifndef STATS2_H
#define STATS2_H

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

private:
     QPixmap background;//Background txt

};

#endif // STATS2_H
