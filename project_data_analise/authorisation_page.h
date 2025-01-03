#ifndef AUTHORISATION_PAGE_H
#define AUTHORISATION_PAGE_H

#include "mainapp.h"

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QTextEdit>
#include <QPainter>
#include <QPaintEvent>
#include <QCryptographicHash>//For password hashing

class authorisation_page :  public QWidget {
    Q_OBJECT
public:
    authorisation_page(QWidget *parent = nullptr);

private slots:
    void paintEvent(QPaintEvent *event);//background setter
    void exitApp();
    void openApp();
    void handleLoginAttempt();

private:
    QPixmap background;//Background txt
    QLineEdit *loginInput;//type login
    QLineEdit *passwordInput;//type password
    QPushButton *login_to_session_button;//login to app
    QPushButton *turn_on_button;//open app
    QPushButton *exit_button;//exit app
    QLabel *statusLogin;//Label to show status of login to app

    QString userLogin;//Store typped login
    QString userPassword;//Store typped password
    bool isLoggedIn = false;//If password and login are typped correctly

    QString hashPassword(const QString &password);//function to hash a password
    QString hashLogin(const QString &login);//function to hash a password
};
#endif // AUTHORISATION_PAGE_H
