#ifndef QTCELL_H
#define QTCELL_H

#include <QObject>

#include <QGraphicsItem>
#include <QPainter>
#include <QString>
#include <QObject>

class QTCell : public QGraphicsObject
{
    Q_OBJECT

signals:
    void clicked(int x, int y);
public Q_SLOT:
    // void MousePressEvent(QGraphicsSceneMouseEvent * event);

    bool event(QEvent* ev) override;

public:
    QTCell(QGraphicsObject* parent,int i, int j);
    QRectF boundingRect() const override;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;


    void setColor(QColor color);
    void setOriginalColor(QColor originalColor);
    static qint32 cellSideLen() {return 96;}
    char number{'0'};
    void setPicture(QString imageAdress);
    void refresh();
    int x,y;
    QPixmap *picture;
    ~QTCell() {}
private:
    QColor color;
    QColor originalColor;
    QString karakter;
};

#endif // QTCELL_H
