#include "gui.h"
#include "ui_gui.h"
#include <QApplication>
#include <QInputDialog>
#include <QDir>
#include <QMessageBox>

const QString bgPath = ":/files/textures/background.jpg";

GUI::GUI(Logic* service, QWidget *parent) : QMainWindow(parent),  m_ui(new Ui::GUI), m_serv(service){

    this->m_ui->setupUi(this);
    //setup connections
    connect(this->m_ui->addWarship, SIGNAL(released()), this, SLOT(handleWarships()));
    connect(this->m_ui->addYacht, SIGNAL(released()), this, SLOT(handleYachts()));
    connect(this->m_ui->addSubmarine, SIGNAL(released()), this, SLOT(handleSubmarines()));
    connect(this->m_ui->handleGame, SIGNAL(released()), this, SLOT(handleGame()));
    connect(this->m_ui->handleExit, SIGNAL(released()), this, SLOT(close()));
    //setup background
    QPixmap bkgnd(bgPath);
    int widWidth = this->width();
    int widHeight = this->height();
    bkgnd = bkgnd.scaled(widWidth, widHeight, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    //setup values
    this->m_warOk = false;
    this->m_yaOk = false;
    this->m_subOk = false;
    this->m_warCount = 0;
    this->m_yaCount = 0;
    this->m_subCount = 0;

}

GUI::~GUI() {
    if(this->m_ui) {
        delete this->m_ui;
        this->m_ui = nullptr;
    }
    if(this->m_serv) {
        delete this->m_serv;
        this->m_serv = nullptr;
    }
}

void GUI::handleWarships() {
    try {
   if(this->m_warOk == true)
       throw Exc("You already added the warships!");
   for(int i = this->m_warCount; i < k; i++) {
       int startX = 0, startY = 0, orientation = -1;
       bool ok;
       //Starting row dialog and conversion
       QString startx = QInputDialog::getText(this, tr("Give warship starting row"),
                                               tr("Starting row(1 to N):"), QLineEdit::Normal,
                                               tr("1"),&ok);
       if(ok && !startx.isEmpty())
           startX = startx.toInt();
       //Starting column dialog and conversion
       QString starty = QInputDialog::getText(this, tr("Give warship starting column"),
                                               tr("Starting column(1 to N):"), QLineEdit::Normal,
                                               tr("1"),&ok);
       if(ok && !starty.isEmpty())
           startY = starty.toInt();
       //Orientation dialog and conversion
       QString orient = QInputDialog::getText(this, tr("Give warship orientation"),
                                               tr("Orientation(0-horizontal, 1-vertical):"), QLineEdit::Normal,
                                               tr("0"),&ok);
       if(ok && !orient.isEmpty())
           orientation = orient.toInt();
       //Adding to service
       this->m_serv->addElem(startX, startY, orientation, "Warship");
       this->m_warCount++;
    }
   if(this->m_warCount == k)
       this->m_warOk = true;
    }
    catch(Exc& exc) {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Error!"));
        msgBox.setText(exc.what());
        msgBox.exec();
    }
    catch(...) {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Error!"));
        msgBox.setText("Unhandled exception!");
        msgBox.exec();    }

}

void GUI::handleYachts() {
    try {
   if(this->m_yaOk == true)
       throw Exc("You already added the yachts!");
   for(int i = this->m_yaCount; i < p; i++) {
       int startX = 0, startY= 0, orientation = -1;
       bool ok;
       //Starting row dialog and conversion
       QString startx = QInputDialog::getText(this, tr("Give yacht warship starting row"),
                                               tr("Starting row(1 to N):"), QLineEdit::Normal,
                                               tr("1"),&ok);
       if(ok && !startx.isEmpty())
           startX = startx.toInt();
       //Starting column dialog and conversion
       QString starty = QInputDialog::getText(this, tr("Give yacht starting column"),
                                               tr("Starting column(1 to N):"), QLineEdit::Normal,
                                               tr("1"),&ok);
       if(ok && !starty.isEmpty())
           startY = starty.toInt();
       //Orientation dialog and conversion
       QString orient = QInputDialog::getText(this, tr("Give yacht orientation"),
                                               tr("Orientation(0-horizontal, 1-vertical):"), QLineEdit::Normal,
                                               tr("0"),&ok);
       if(ok && !orient.isEmpty())
           orientation = orient.toInt();
       //Adding to service
       this->m_serv->addElem(startX, startY, orientation, "Yacht");
       this->m_yaCount++;
    }
   if(this->m_yaCount == p)
       this->m_yaOk = true;
    }
    catch(Exc& exc) {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Error!"));
        msgBox.setText(exc.what());
        msgBox.exec();
    }
    catch(...) {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Error!"));
        msgBox.setText("Unhandled exception!");
        msgBox.exec();
    }
}

void GUI::handleSubmarines() {
    try {
   if(this->m_subOk == true)
       throw Exc("You already added the submarines!");
   for(int i = this->m_subCount; i < q; i++) {
       int startX = 0, startY = 0, orientation = -1;
       //bool value to get the result of the getText()
       bool ok;
       //Starting row dialog and conversion
       QString startx = QInputDialog::getText(this, tr("Give submarine starting row"),
                                               tr("Starting row(1 to N):"), QLineEdit::Normal,
                                               tr("1"),&ok);
       if(ok && !startx.isEmpty())
           startX = startx.toInt();
       //Starting column dialog and conversion
       QString starty = QInputDialog::getText(this, tr("Give submarine starting column"),
                                               tr("Starting column(1 to N):"), QLineEdit::Normal,
                                               tr("1"),&ok);
       if(ok && !starty.isEmpty())
           startY = starty.toInt();
       //Orientation dialog and conversion
       QString orient = QInputDialog::getText(this, tr("Give submarine orientation"),
                                               tr("Orientation(0-horizontal, 1-vertical):"), QLineEdit::Normal,
                                              tr("0"),&ok);
       if(ok && !orient.isEmpty())
           orientation = orient.toInt();
       //Adding to service
       this->m_serv->addElem(startX, startY, orientation, "Submarine");
       this->m_subCount++;
    }
   if(this->m_subCount == q)
       this->m_subOk = true;
    }
    catch(Exc& exc) {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Error!"));
        msgBox.setText(exc.what());
        msgBox.exec();
    }
    catch(...) {
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Error!"));
        msgBox.setText("Unhandled exception!");
        msgBox.exec();
    }
}

void GUI::handleGame() {
    try {
        if(!this->m_warOk || !this->m_yaOk || !this->m_subOk)
            throw Exc("You haven't added all the pieces!");
        GameDialog game(this->m_serv);
        game.setModal(true);
        game.exec();
    }
    catch(Exc& exc) {
        QMessageBox msgBox;
        if(strstr(exc.what(), "won") != nullptr)
            msgBox.setWindowTitle(tr("Result"));
        else
            msgBox.setWindowTitle(tr("Error!"));
        msgBox.setText(exc.what());
        msgBox.exec();
    }
    catch(...){
        QMessageBox msgBox;
        msgBox.setWindowTitle(tr("Error!"));
        msgBox.setText("Unhandled exception!");
        msgBox.exec();
    }
}
