#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "CBoard.h"
#include "ai.h"
#include "qtboard.h"
#include "qtcell.h"
#include "qtscene.h"
#include <QMainWindow>
#include <string>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT
public
  Q_SLOT : void turn(int x, int y);

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void displayBoard();
  CBoard board;
  AI ai;
  Ui::MainWindow *ui;
  std::string command;
  void addToScene(QTCell *cell);
  void refreshBoardSelect();
  QTBoard *tabla;
  QTScene *s;
  int num_click = 0;
  std::string x1, x2;
  int y1, y2;
  std::string vertical = "abcdefgh";
};
#endif // MAINWINDOW_H
