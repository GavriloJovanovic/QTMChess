#include "qtboard.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QRandomGenerator>


QTBoard::QTBoard()
    : color(QColor(135,206,250))
    , originalColor(QColor(135,206,250))
{

}

QRectF QTBoard::boundingRect() const
{
    return QRectF(0, 0, QTCell::cellSideLen()*8, QTCell::cellSideLen()*8);

}

void QTBoard::drawBoard()
{

    for (auto i = 0; i < 8; i++) {
        for (auto j = 0; j < 8; j++) {
            celije[i][j] = new QTCell(this,i,j);
            QTCell* cell = celije[i][j];
            cell->moveBy(x() + QTCell::cellSideLen()*i, y() + QTCell::cellSideLen()*j);
            cell->setColor(color);
            cell->setOriginalColor(originalColor);
        }
    }
}


void QTBoard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    Q_UNUSED(option)

    painter->setBrush(color);
    painter->drawRect(0, 0, QTCell::cellSideLen()*8, QTCell::cellSideLen()*8);

}

void QTBoard::mousePressEvent(QGraphicsSceneMouseEvent * event)
{

    Q_UNUSED(event)

    if (color == Qt::red)
        color = originalColor;
    else
        color = Qt::red;

    this->update();

}

