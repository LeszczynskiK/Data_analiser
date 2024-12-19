#include <QApplication>
#include "authorisation_page.h"
#include "mainapp.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    //display authorisation window
    authorisation_page startWindow;
    startWindow.show();

    return app.exec();
}
