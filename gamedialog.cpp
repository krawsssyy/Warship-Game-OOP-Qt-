#include "gamedialog.h"
#include "ui_gamedialog.h"

const QString warshipPath = ":/files/textures/warship.jpg";
const QString yachtPath = ":/files/textures/yacht.jpg";
const QString submarinePath = ":/files/textures/submarine.jpg";
const QString hitPath = ":/files/textures/hit.png";
const QString clearPath = ":/files/textures/clear.png";
const QString audioUrl = "qrc:/files/audio/audio.mp3";

GameDialog::GameDialog(Logic* serv, QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::GameDialog),
    m_serv(serv),
    m_music(new QMediaPlayer)
{
    this->m_ui->setupUi(this);
    //setup music
    this->m_music->setMedia(QUrl(audioUrl));
    this->m_music->setVolume(25);

    //removing edit triggers
    this->m_ui->playerTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->m_ui->guessTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //should also setup table to depend on N
    //this->m_ui->playerTable->setRowCount(N);
    //this->m_ui->playerTable->setColumnCount(N);
    //also find a formula for the cell size
    //

    //start game
    this->game();
}

GameDialog::~GameDialog()
{
    if(this->m_ui) {
        delete this->m_ui;
        this->m_ui = nullptr;
    }
    if(this->m_music) {
        delete this->m_music;
        this->m_music = nullptr;
    }
}

void GameDialog::on_guessButton_clicked()
{
    QString guess = this->m_ui->lineEdit->text();
    this->m_ui->lineEdit->clear();
    std::string actGuess = guess.toStdString();
    bool resUser = this->m_serv->hitReg(actGuess, 'u');
    if(resUser)
       //draw the result on guessTable
    {
        std::pair<int, int> gue = this->m_serv->guessDecoder(actGuess);
        QPixmap p(hitPath);
        QPixmap newP = p.scaled(QSize(35,35), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QBrush b(newP);
        QTableWidgetItem* item = new QTableWidgetItem;
        item->setBackground(b);
        this->m_ui->guessTable->setItem(gue.first - 1, gue.second - 1, item);

    }
    else {
        std::pair<int, int> gue = this->m_serv->guessDecoder(actGuess);
        QPixmap p(clearPath);
        QPixmap newP = p.scaled(QSize(25,25), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QBrush b(newP);
        QTableWidgetItem* item = new QTableWidgetItem;
        item->setBackground(b);
        this->m_ui->guessTable->setItem(gue.first - 1, gue.second - 1, item);
    }
    std::string aiGuess = this->m_serv->aiGuess();
    bool resAI = this->m_serv->hitReg(aiGuess, 'a');
    //verify if we need to update a hit element
    if(resAI)
        updateAfterHit();
    std::string text;
    if(resUser){
       if(resAI)
           text = "Hit!\n AI Guess was " + aiGuess + ", which was a hit!\n";
       else
           text = "Hit!\n AI Guess was " + aiGuess + ", which missed!\n";
    }
    else {
        if(resAI)
            text = "Clear!\n AI Guess was " + aiGuess + ", which was a hit!\n";
        else
            text = "Clear!\n AI Guess was " + aiGuess + ", which missed!\n";
    }
    QString toShow = QString::fromStdString(text);
    this->m_ui->label->setText(toShow);
    //weird flex but ok
    int gameState = this->m_serv->getGameStatus();
    if(gameState == -1)
        throw Exc("The AI won!");
    else if (gameState == 1)
        throw Exc("You won!");
    //
}

void GameDialog::game() {
    //start music
    this->m_music->play();
    //draw board headers with letters
   for(int i=0;i<this->m_ui->playerTable->columnCount();++i) {
   //expensive but no other solution found
         char s = 97 + i;
         std::string str(1, s);
         QString strr = QString::fromStdString(str);
         this->m_ui->playerTable->setHorizontalHeaderItem(i, new QTableWidgetItem);
         Q_ASSUME(this->m_ui->playerTable->model()->setHeaderData(i,Qt::Horizontal,strr));

    }
    for(int i=0;i<this->m_ui->guessTable->columnCount();++i) {
         char s = 97 + i;
         std::string str(1, s);
         QString strr = QString::fromStdString(str);
         this->m_ui->guessTable->setHorizontalHeaderItem(i, new QTableWidgetItem);
         Q_ASSUME(this->m_ui->guessTable->model()->setHeaderData(i,Qt::Horizontal,strr));
    }
   //doing checks for correctly loading images
    QImage img;
    bool loadedWarships = img.load(warshipPath);
    bool loadedYachts = img.load(yachtPath);
    bool loadedSubmarines = img.load(submarinePath);
    bool loadedHit = img.load(hitPath);
    bool loadedClear = img.load(clearPath);
    if(!loadedWarships || !loadedYachts || !loadedSubmarines || !loadedHit || !loadedClear)
        throw Exc("Some images haven't loaded correctly!");
    //load ai board
    this->m_serv->aiStart();
    //drawing player board
    for(auto elem : this->m_serv->getAllUser()) {
        //drawing for warships
        if(dynamic_cast<Warship*>(elem) != nullptr) {
            QPixmap p(warshipPath);
            QPixmap newP = p.scaled(QSize(60,60), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            QBrush b(newP);
            if(elem->getOrientation() == 1)
            {
                for(int i = 0; i < dynamic_cast<Warship*>(elem)->getLength(); i++ )
                {
                    QTableWidgetItem* imgg = new QTableWidgetItem;
                    imgg->setBackground(b);
                    this->m_ui->playerTable->setItem(elem->getStartX() + i - 1 , elem->getStartY() - 1, imgg);
                    //delete imgg;
                    //imgg = nullptr;

                }
            }
            else {
                for(int i = 0; i < dynamic_cast<Warship*>(elem)->getLength(); i++ )
                {
                    QTableWidgetItem* imgg = new QTableWidgetItem;
                    imgg->setBackground(b);
                    this->m_ui->playerTable->setItem(elem->getStartX() - 1 , elem->getStartY() + i - 1, imgg);
                    //delete imgg;
                    //imgg = nullptr;
                }
            }
        }
        //drawing for yachts
        if(dynamic_cast<Yacht*>(elem) != nullptr) {
            QPixmap p(yachtPath);
            QPixmap newP = p.scaled(QSize(60,60), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            QBrush b(newP);
            if(elem->getOrientation() == 1)
            {
                for(int i = 0; i < dynamic_cast<Yacht*>(elem)->getLength(); i++ )
                {
                    QTableWidgetItem* imgg = new QTableWidgetItem;
                    imgg->setBackground(b);
                    this->m_ui->playerTable->setItem(elem->getStartX() + i - 1 , elem->getStartY() - 1, imgg);
                    //delete imgg;
                    //imgg = nullptr;
                }
            }
            else {
                for(int i = 0; i < dynamic_cast<Yacht*>(elem)->getLength(); i++)
                {
                    QTableWidgetItem* imgg = new QTableWidgetItem;
                    imgg->setBackground(b);
                    this->m_ui->playerTable->setItem(elem->getStartX() - 1 , elem->getStartY() + i - 1, imgg);
                    //delete imgg;
                    //imgg = nullptr;
                }
            }
        }
        //drawing for submarines
        if(dynamic_cast<Submarine*>(elem) != nullptr) {
            QPixmap p(submarinePath);
            QPixmap newP = p.scaled(QSize(60,60), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            QBrush b(newP);
            if(elem->getOrientation() == 1)
            {

                for(int i = 0; i < dynamic_cast<Submarine*>(elem)->getLength(); i++ )
                {
                    QTableWidgetItem* imgg = new QTableWidgetItem;
                    imgg->setBackground(b);
                    this->m_ui->playerTable->setItem(elem->getStartX() + i - 1 , elem->getStartY() - 1, imgg);
                    //delete imgg;
                    //imgg = nullptr;
                }
            }
            else {
                for(int i = 0; i < dynamic_cast<Submarine*>(elem)->getLength(); i++ )
                {
                    QTableWidgetItem* imgg = new QTableWidgetItem;
                    imgg->setBackground(b);
                    this->m_ui->playerTable->setItem(elem->getStartX() - 1 , elem->getStartY() + i - 1, imgg);
                    //delete imgg;
                    //imgg = nullptr;
                }
            }
        }
    }
    //end of drawing
}

void GameDialog::updateAfterHit() {
    for(auto elem: this->m_serv->getAllUser()) {
        if(elem->getHidden() == false)
        {
            QPixmap p(hitPath);
            QPixmap newP = p.scaled(QSize(35,35), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            QBrush b(newP);
            auto getElementLength = [](IE* elem) {
                if(dynamic_cast<Warship*>(elem) != nullptr)
                    return dynamic_cast<Warship*>(elem)->getLength();
                if(dynamic_cast<Yacht*>(elem) != nullptr)
                   return dynamic_cast<Yacht*>(elem)->getLength();
                if(dynamic_cast<Submarine*>(elem) != nullptr)
                    return dynamic_cast<Submarine*>(elem)->getLength();
            };
            int elemLength = getElementLength(elem);
            if(elem->getOrientation() == 1) {
                for(int i = 0; i < elemLength; i++)
                {
                    QTableWidgetItem* imgg = new QTableWidgetItem;
                    imgg->setBackground(b);
                    this->m_ui->playerTable->setItem(elem->getStartX() + i - 1 , elem->getStartY() - 1, imgg);
                }
            }
            else {
                for(int i = 0; i < elemLength; i++)
                {
                QTableWidgetItem* imgg = new QTableWidgetItem;
                imgg->setBackground(b);
                this->m_ui->playerTable->setItem(elem->getStartX() - 1 , elem->getStartY() + i - 1, imgg);
                }
            }
        }
    }
}
