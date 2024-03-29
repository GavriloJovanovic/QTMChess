#include "qtboard.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>
#include <QStyleOption>

QTBoard::QTBoard() {}

QRectF
QTBoard::boundingRect() const
{
    return QRectF(0, 0, QTCell::cellSideLen() * 8, QTCell::cellSideLen() * 8);
}

//! Method that sets out board with current position and looks for the display
//! of cells
void
QTBoard::drawBoard()
{
    int altPocetak= 1;
    for (auto i= 0; i < 8; i++) {
	int alt= altPocetak;
	for (auto j= 0; j < 8; j++) {
	    // we need to extract information from m_board
	    celije[i][j]= new QTCell(this, i, j);
	    QTCell* cell= celije[i][j];
	    cell->moveBy(x() + QTCell::cellSideLen() * i,
			 y() + QTCell::cellSideLen() * j);
	    cell->setColor(color);
	    cell->setOriginalColor(originalColor);
	    if (alt == 1) {
		cell->setOriginalColor(QColor(255, 255, 255));
		cell->setColor(QColor(255, 255, 255));
	    } else {
		cell->setOriginalColor(QColor(128, 128, 128));
		cell->setColor(QColor(128, 128, 128));
	    }
	    alt*= -1;
	}
	altPocetak*= -1;
    }
}

//! Coloring of board
void
QTBoard::paint(QPainter* painter,
	       const QStyleOptionGraphicsItem* option,
	       QWidget*)
{
    Q_UNUSED(option)

    painter->setBrush(color);
    painter->drawRect(
      0, 0, QTCell::cellSideLen() * 8, QTCell::cellSideLen() * 8);
}

//! Event for board that is happening when we click on cell, it turns red!
void
QTBoard::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

    Q_UNUSED(event)

    if (color == Qt::red)
	color= originalColor;
    else
	color= Qt::red;

    this->update();
}
