#include "gui.h"
#include "Logic.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository* userR = new Repository();
    Repository* aiR = new Repository();
    Validator* valid = new Validator;
    Logic* service = new Logic(userR, aiR, valid);
    GUI gui(service);
    gui.show();
    //delete gui;
    //gui = nullptr;
    return a.exec();
}
