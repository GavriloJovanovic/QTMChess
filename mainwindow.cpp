#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <stdlib.h>
#include "CBoard.h"
#include "ai.h"
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ai(board)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    tabla = new QTBoard();
    s = new QTScene(tabla);

    ui->graphicsView->setScene(s);
    tabla->drawBoard();

    for(int i = 0; i < 8; i++) {
        int j = 0;
        for(j=0;j<8;j++) {
            s->addItem(tabla->celije[i][j]);
            connect(tabla->celije[i][j],&QTCell::clicked,this,&MainWindow::turn);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addToScene(QTCell *cell) {
    ui->graphicsView->scene()->addItem(cell);
}

void MainWindow::refreshBoardSelect() {
    std::cout << "Refreshujem" << std::endl;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            tabla->celije[i][j]->refresh();
        }
    }
}

void MainWindow::displayBoard() {
    // Display board
    // We need to make a QT object for this one, but for now it's in the terminal
    std::cout << board;
    static const char pieces[] = "kqrbnp.PNBRQK";
    QDir d = QFileInfo("").absoluteDir();
    QString absolute=d.absolutePath();
    static const std::vector<QString> adrese = {
        "/../QTMChess/Figure/CrniKralj.png",
        "/../QTMChess/Figure/CrnaKraljica.png",
        "/../QTMChess/Figure/CrniTop.png",
        "/../QTMChess/Figure/CrniLovac.png",
        "/../QTMChess/Figure/CrniKonj.png",
        "/../QTMChess/Figure/CrniPiun.png",
        "/../QTMChess/Figure/PraznoPolje.png",
        "/../QTMChess/Figure/BeliPiun.png",
        "/../QTMChess/Figure/BeliKonj.png",
        "/../QTMChess/Figure/BeliLovac.png",
        "/../QTMChess/Figure/BeliTop.png",
        "/../QTMChess/Figure/BelaKraljica.png",
        "/../QTMChess/Figure/BeliKralj.png"

    };
    std::vector<int8_t> boardTable = board.getMBoard();
    for (int row=8, row2 =1; row>=1; --row, ++row2)
    {
        for (int col=1, col2 =8; col<=8; ++col, --col2)
        {
            int number = (col+1)*10+row;
            int piece = board.m_board[number];
            if (piece != IV)
            {
                this->tabla->celije[row - 1][col2-1]->setPicture(absolute + adrese[piece+6]);
            }
        }
        std::cout << std::endl;
    }
}

void MainWindow::turn(int x, int y) {
    // We shall convert the input of QString
    /*
         std::string str;
         getline(std::cin, str);
         std::cout << std::endl;
    */
    if(num_click == 0) {

        x1 = vertical[x];
        y1 = 8 - y;
        num_click += 1;
        std::cout << "Selekt" << x1 << " " << y1 << std::endl;
    }
    else {
        x2 = vertical[x];
        y2 = 8 - y;
        std::cout << "Move " << x1 << y1 << x2 << y2 << std::endl;
        num_click = 0;

        /*
        QString inputLine = ui->lineEdit->text();
        ui->lineEdit->clear();
        this->command = inputLine.toStdString();
        std::cout << "You inputed: " << this->command << std::endl;
        */

        this->command = "move " + x1 + std::to_string(y1) + x2 + std::to_string(y2);


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
                 refreshBoardSelect();
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
                     refreshBoardSelect();
                     return;
                 }

                 std::cout << "You move : " << move << std::endl;
                 board.make_move(move);
             }
             else
             {
                 std::cout << "Move " << move << " is not legal." << std::endl;
                 refreshBoardSelect();
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
             refreshBoardSelect();
             return;
         }

         this->displayBoard();
         refreshBoardSelect();
    }
}
