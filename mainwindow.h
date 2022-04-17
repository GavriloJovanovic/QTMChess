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
//! Main class that generates chess game
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
  //!Class that has all logic-based board characteristics
  CBoard board;
  //!AI class that plays game for you
  AI ai;
  Ui::MainWindow *ui;
  //!Helping atribute for terminal comand
  std::string command;
  void addToScene(QTCell *cell);
  void refreshBoardSelect();
  QTBoard *tabla;
  QTScene *s;
  //!Atribute that represent how much has user clicked on the board
  int num_click = 0;
  //!Atributes that represent position where user has clicked
  std::string x1, x2;
  //!Atributes that represent position of clicked cells
  int y1, y2;
  std::string vertical = "abcdefgh";
};
#endif // MAINWINDOW_H
