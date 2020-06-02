#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <gamedialog.h>

QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QMainWindow
{
    Q_OBJECT

public:
    GUI(Logic* service, QWidget *parent = nullptr);
    ~GUI();
private slots:
    void handleWarships();
    void handleYachts();
    void handleSubmarines();
    void handleGame();
private:
    Ui::GUI* m_ui;
    Logic* m_serv;
    bool m_warOk, m_yaOk, m_subOk;
    int m_warCount , m_yaCount, m_subCount;
};
#endif // GUI_H
