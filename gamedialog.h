#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include <QDialog>
#include "Logic.h"

namespace Ui {
class GameDialog;
}

class GameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameDialog(Logic* serv, QWidget *parent = nullptr);
    ~GameDialog();
    void game();
    void updateAfterHit();

private slots:
    void on_guessButton_clicked();

private:
    Ui::GameDialog* m_ui;
    Logic* m_serv;
};

#endif // GAMEDIALOG_H
