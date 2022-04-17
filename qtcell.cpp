#include "qtcell.h"
#include <QDrag>
#include <QGraphicsScene>
#include <QGraphicsSceneEvent>
#include <QMimeData>
#include <QPainter>
#include <QString>
#include <QStyleOption>
#include <iostream>

QTCell::QTCell(QGraphicsObject *parent, int x, int y)
    : QGraphicsObject(parent), x(x), y(y) {}

//! Defenition of size for each cell
QRectF QTCell::boundingRect() const { return QRectF(0, 0, 80, 80); }

//! Painting each cell on it's own position acordingly
void QTCell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);
  painter->setBrush(color);
  painter->drawRect(0, 0, 80, 80);
  painter->drawPixmap(0, 0, picture->width(), picture->height(), *picture);
  if (this->number != '0') {
    painter->setPen(Qt::red);
    painter->setFont(QFont("Segoe UI", 16));
    painter->drawText(15, 15, QString(this->number));

    //        NumberKnight* tmp = new NumberKnight(1);
    //        tmp->setPixmap(number);
    //        tmp->drawNumberKnight();
    //        this->receiveUnit(tmp);
  }
}

//!Method that puts figures on the positon
void QTCell::setPicture(QString imageAdress) { // NAPRAVI DELEETE
  delete this->picture;
  this->picture = new QPixmap(imageAdress);
  this->update();
}
/*
void Celija::MousePressEvent(QGraphicsSceneMouseEvent * event)
{
    Q_UNUSED(event)

    if (color == Qt::red)
        color = originalColor;
    else
        color = Qt::red;
    this->update();
    std::cout << "Pozicija: " << this->x << " " << this->y << std::endl;
    emit clicked();
}
*/

//! What is happening when we click on the cell in exact postion
bool QTCell::event(QEvent *ev) {
  if (ev->type() == QEvent::GraphicsSceneMousePress) {
    if (color == Qt::red) {
      color = originalColor;
    } else
      color = Qt::red;
    this->update();

    emit clicked(this->x, this->y);
    return true;
  }
  // Make sure the rest of events are handled
  // FIX

  return true;
}

//! Method for seting color
void QTCell::setColor(QColor color) {
  this->color = color;
  this->update();
}


//! Revert to original color of each cells, it's eather gray or white
void QTCell::setOriginalColor(QColor originalColor) {
  this->originalColor = originalColor;
  this->update();
}

//! Refresh cell to it's original color
void QTCell::refresh() {
  this->color = this->originalColor;
  this->update();
}
