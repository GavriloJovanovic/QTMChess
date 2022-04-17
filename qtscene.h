#ifndef QTSCENE_H
#define QTSCENE_H

#include "qtboard.h"
#include <QGraphicsScene>

//! Dummy class that is need to assert QTBoard class for generating out custom board for chess
class QTScene : public QGraphicsScene {
public:
  QTScene(QTBoard *tabla, QObject *parent = nullptr);
  QTBoard *tabla;
};

#endif // QTSCENE_H
