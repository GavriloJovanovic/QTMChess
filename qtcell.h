#ifndef QTCELL_H
#define QTCELL_H

#include <QObject>

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QString>

class QTCell : public QGraphicsObject
{
    Q_OBJECT

  signals:
    //! Signal for clicked cell,
    //!@param x @param y are postion of cell
    void clicked(int x, int y);
  public
    Q_SLOT
      :
      // void MousePressEvent(QGraphicsSceneMouseEvent * event);
      bool event(QEvent* ev) override;

  public:
    QTCell(QGraphicsObject* parent, int i, int j);
    QRectF boundingRect() const override;

    void paint(QPainter* painter,
	       const QStyleOptionGraphicsItem* option,
	       QWidget* widget) override;

    void setColor(QColor color);
    void setOriginalColor(QColor originalColor);
    //! Lentht of each cell
    static qint32 cellSideLen() { return 96; }
    char number{ '0' };
    void setPicture(const QString & imageAdress);
    void refresh();
    //! Position of our cell
    int x, y;
    //! Picture that is attached to certan cell
    QPixmap picture;
    ~QTCell() {}

  private:
    QColor color;
    QColor originalColor;
    QString karakter;
};

#endif // QTCELL_H
