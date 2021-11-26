#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <stdlib.h>
#include "CBoard.h"
#include "ai.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ai(board)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(
        ui->pushButton,
        &QPushButton::clicked,
        this,
        &MainWindow::turn
    );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayBoard() {
    // Display board
    // We need to make a QT object for this one, but for now it's in the terminal
    std::cout << board;
    std::cout << "Input command : ";
}

void MainWindow::turn() {
    // We shall convert the input of QString
    /*
         std::string str;
         getline(std::cin, str);
         std::cout << std::endl;
    */
        QString inputLine = ui->lineEdit->text();
        ui->lineEdit->clear();
        this->command = inputLine.toStdString();
        std::cout << "You inputed: " << this->command << std::endl;



         // Parse input from player
         if (this->command == "quit")
         {
             exit(1);
             return;
         }

         if (this->command.compare(0, 5, "move ") == 0)
         {
             CMove move;

             if (move.FromString(this->command.c_str()+5) == NULL)
             {
                 // Could not parse move.
                 std::cout << "Try again. Use long notation, e.g. e2e4" << std::endl;
                 return; // Go back to beginning
             }

             if (board.IsMoveValid(move))
             {
                 board.make_move(move);
                 bool check = board.isOtherKingInCheck();
                 board.undo_move(move);
                 if (check)
                 {
                     std::cout << "You are in CHECK. Play another move." << std::endl;
                     return;
                 }

                 std::cout << "You move : " << move << std::endl;
                 board.make_move(move);
             }
             else
             {
                 std::cout << "Move " << move << " is not legal." << std::endl;
                 return;
             }
         } // end of "move "

         else if (this->command.compare(0, 2, "go") == 0)
         {
             CMove best_move = ai.find_best_move();

             std::cout << "bestmove " << best_move << std::endl;

             board.make_move(best_move);
         } // end of "go"

         else if (this->command == "show")
         {
             CMoveList moves;
             board.find_legal_moves(moves);

             //            std::cout << moves.ToShortString() << std::endl;
             std::cout << moves << std::endl;
         }

         else
         {
             std::cout << "Unknown command" << std::endl;
             std::cout << "Valid commands are: quit, move, go, show" << std::endl;
             return;
         }
         this->displayBoard();
}
