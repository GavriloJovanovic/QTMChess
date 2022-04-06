#ifndef QTBOARD_H
#define QTBOARD_H

#include "qtcell.h"
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QPainter>

class QTBoard : public QGraphicsObject {
public:
  QTBoard();

  QTCell *celije[8][8];

  QRectF boundingRect() const override;

  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget) override;

  void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
  void drawBoard();

private:
  QColor color;
  QColor originalColor;
  qint32 _x, _y;
};

#endif // QTBOARD_H
