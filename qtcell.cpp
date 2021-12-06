#include "qtcell.h"
#include <iostream>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QString>
#include <QDrag>
#include <QMimeData>
#include <QGraphicsSceneEvent>

QTCell::QTCell(QGraphicsObject* parent,int x,int y) : QGraphicsObject(parent),x(x),y(y)
{

}

QRectF QTCell::boundingRect() const
{
    return QRectF(0, 0, 80, 80);
}

void QTCell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(color);
    painter->drawRect(0, 0, 80, 80);
    if(this->number != '0')
    {
        painter->setPen(Qt::red);
        painter->setFont(QFont("Segoe UI", 16));
        painter->drawText(15,15,QString(this->number));

//        NumberKnight* tmp = new NumberKnight(1);
//        tmp->setPixmap(number);
//        tmp->drawNumberKnight();
//        this->receiveUnit(tmp);

    }

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

bool QTCell::event(QEvent* ev)
{
    if (ev->type() == QEvent::GraphicsSceneMousePress) {
        if (color == Qt::red) {
            color = originalColor;
        }
        else
            color = Qt::red;
        this->update();

        emit clicked(this->x,this->y);
        return true;
    }
    // Make sure the rest of events are handled
    // FIX

    return true;
}
void QTCell::setColor(QColor color)
{
    this->color = color;
}

void QTCell::setOriginalColor(QColor originalColor)
{
    this->originalColor = originalColor;
}

void QTCell::refresh() {
    if (color == Qt::red) {
        color = originalColor;
    }
    this->update();
}
