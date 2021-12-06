#ifndef QTSCENE_H
#define QTSCENE_H

#include <QGraphicsScene>
#include "qtboard.h"

class QTScene : public QGraphicsScene
{
public:
    QTScene(QTBoard *tabla,QObject *parent = nullptr);
    QTBoard *tabla;
};

#endif // QTSCENE_H
