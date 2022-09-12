#ifndef QTBOARD_H
#define QTBOARD_H

#include "qtcell.h"
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QPainter>

class QTBoard : public QGraphicsObject
{
  public:
    QTBoard();

    //! Our matrix of QTCell-s
    QTCell* celije[8][8];

    //! Generate size of our board
    QRectF boundingRect() const override;

    //! Method that
    void paint(QPainter* painter,
	       const QStyleOptionGraphicsItem* option,
	       QWidget* widget) override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void drawBoard();

  private:
    //! Colour of each cell that we are giving
    QColor color;
    //! Original color of each cell that we are giving
    QColor originalColor;
    //! Position for each cell
    qint32 _x, _y;
};

#endif // QTBOARD_H
