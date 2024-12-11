#include "authorisation_page.h"

authorisation_page::authorisation_page(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Authorisation window");

    const int x =1920*0.8;//x window size
    const int y=1080*0.8;//y window size

    setFixedSize(x, y);//Set window size

    //Background image
    background = QPixmap("/home/krzysiek89/Desktop/QT_aplikacje/Data_analiser/background.png").scaled(x, y);

    QFont font;
    font.setPointSize(21);//Font size -all font size

    QFont font_status;
    font_status.setPointSize(25);//Font size -all font size

    //Text inputs (login and password)
    loginInput = new QLineEdit(this);//login
    loginInput->setGeometry(60, 120, 500, 60);
    loginInput->setFont(font);
    loginInput->setStyleSheet("color: yellow;");
    loginInput->setPlaceholderText("Enter login");

    passwordInput = new QLineEdit(this);//password
    passwordInput->setGeometry(60, 200, 500, 60);
    passwordInput->setFont(font);
    passwordInput->setStyleSheet("color: yellow;");
    passwordInput->setPlaceholderText("Enter password");
    passwordInput->setEchoMode(QLineEdit::Password);//dont show password, show only *****

    //login status(logged or not)
    statusLogin = new QLabel("Not logged...", this);
    statusLogin->setFont(font_status);
    statusLogin->setStyleSheet("color: yellow;");
    statusLogin->setGeometry(30, 30, 650, 70);

    //Initialize buttons
    login_to_session_button = new QPushButton("Login to app...", this);//login to app
    login_to_session_button->setFont(font);
    login_to_session_button->setStyleSheet("color: yellow;");
    login_to_session_button->setGeometry(70, 500, 360, 70);
    connect(login_to_session_button, &QPushButton::clicked, this, &authorisation_page::handleLoginAttempt);

    turn_on_button = new QPushButton("Turn on app...", this);//turn on app
    turn_on_button->setFont(font);
    turn_on_button->setStyleSheet("color: yellow;");
    turn_on_button->setGeometry(70, 600, 360, 70);
    turn_on_button->setVisible(false);//if login and password are not ok, button is not visible
    connect(turn_on_button, &QPushButton::clicked, this, &authorisation_page::openApp);//if clicked, open server-client view

    exit_button = new QPushButton("Exit app...", this);//leave from app
    exit_button->setFont(font);
    exit_button->setStyleSheet("color: yellow;");
    exit_button->setGeometry(70, 700, 360, 70);
    connect(exit_button, &QPushButton::clicked, this, &authorisation_page::exitApp);

}

void authorisation_page::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, background);//Background
    QWidget::paintEvent(event);
}

QString authorisation_page::hashPassword(const QString &password) {

    //Hash the password using SHA-256
    return QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
}

QString authorisation_page::hashLogin(const QString &login) {

    //Hash the password using SHA-256
    return QString(QCryptographicHash::hash(login.toUtf8(), QCryptographicHash::Sha256).toHex());
}

void authorisation_page::handleLoginAttempt() {//check correctivity of typped data...
    userLogin = loginInput->text();
    userPassword = passwordInput->text();


    //predefined hashed password
    QString hashedCorrectPassword = hashPassword("123");
    QString hashedCorrectLogin = hashLogin("admin");


    if (hashLogin(userLogin) == hashedCorrectLogin && hashPassword(userPassword) == hashedCorrectPassword) {//check validation of login and password
        isLoggedIn = true;//let login - bool variable
        statusLogin->setText("Login successful! Ready to proceed...");//new status of data
        turn_on_button->setVisible(true);
    } else {
        isLoggedIn = false;//deny login - frong data written
        statusLogin->setText("Incorrect login or password. Try again.");//new status of data
        turn_on_button->setVisible(false);
    }
}

void authorisation_page::exitApp()
{
    this->close();//turn off app...
}

void authorisation_page::openApp()
{
    if (isLoggedIn) {
        //open main page of app
        mainapp *appWindow = new mainapp();
        appWindow->show();

        this->close();
    }
}
