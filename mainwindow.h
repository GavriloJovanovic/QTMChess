#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CBoard.h"
#include "ai.h"
#include <string>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void displayBoard();
    CBoard board;
    AI ai;
private:
    Ui::MainWindow *ui;
    std::string command;
public Q_SLOTS:
    void turn();
};
#endif // MAINWINDOW_H
