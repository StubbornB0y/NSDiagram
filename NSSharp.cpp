#include "NSSharp.h"
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

NSSharp::NSSharp(QGraphicsItem* parent)
      : QGraphicsPolygonItem(parent)
{

      // 画笔 - 边框色
      QPen p = pen();
      p.setWidth(2);
      p.setColor(QColor(0, 0, 0));

      setPen(p);
      

      // 可选择、可移动
      setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
}

void NSSharp::show()
{
}

      

void NSSharp::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
      if (event->button() == Qt::LeftButton) {
            if (event->modifiers() == Qt::ShiftModifier) {
                  qDebug() << "Custom item left clicked with shift key.";// 选中 item
                  setSelected(true);
            }
            else if (event->modifiers() == Qt::AltModifier) {
                  qDebug() << "Custom item left clicked with alt key.";// 重置 item 大小
                  double radius = boundingRect().width() / 2.0;
                  QPointF topLeft = boundingRect().topLeft();
                  m_centerPointF = QPointF(topLeft.x() + pos().x() + radius, topLeft.y() + pos().y() + radius);
                  QPointF pos = event->scenePos();
                  qDebug() << boundingRect() << radius << this->pos() << pos << event->pos();
                  double dist = sqrt(pow(m_centerPointF.x() - pos.x(), 2) + pow(m_centerPointF.y() - pos.y(), 2));
                  if (dist / radius > 0.8) {
                        qDebug() << dist << radius << dist / radius;
                        m_bResizing = true;
                  }
                  else {
                        m_bResizing = false;
                  }
            }
            else {
            qDebug() << "Custom item left clicked.";
            QGraphicsItem::mousePressEvent(event);
            event->accept();
            }
      }
      else if (event->button() == Qt::RightButton) {
            qDebug() << "Custom item right clicked.";
            event->ignore();
      }
}

void NSSharp::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
      if ((event->modifiers() == Qt::AltModifier) && m_bResizing) {
            QPointF pos = event->scenePos();
            double dist = sqrt(pow(m_centerPointF.x() - pos.x(), 2) + pow(m_centerPointF.y() - pos.y(), 2));
            //setRect(m_centerPointF.x() - this->pos().x() - dist, m_centerPointF.y() - this->pos().y() - dist, dist * 2, dist * 2);
      }
      else if (event->modifiers() != Qt::AltModifier) {
            qDebug() << "Custom item moved.";
            QGraphicsItem::mouseMoveEvent(event);
            qDebug() << "moved" << pos();
      }
}

void NSSharp::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
      if ((event->modifiers() == Qt::AltModifier) && m_bResizing) {
            m_bResizing = false;
      }
      else {
            QGraphicsItem::mouseReleaseEvent(event);
      }
}

int NSSharp::type() const
{
      return UserType + 1;
}

NS_Standard::NS_Standard(QGraphicsItem* parent)
      :NSSharp(parent)
{
      Sharptype = My_GraphicsScene::NSStandard;
      show();
}

void NS_Standard::show()
{
      mysharp << QPointF(-100, -50) << QPointF(100, -50)
            << QPointF(100, 50) << QPointF(-100, 50)
            << QPointF(-100, -50);
      setPolygon(mysharp);
}

NS_Sequence::NS_Sequence(QGraphicsItem* parent)
      :NSSharp(parent) 
{
      Sharptype = My_GraphicsScene::NSSequence;
      show();
}
void NS_Sequence::show()
{
      mysharp << QPointF(-100, -50) << QPointF(100, -50)
            << QPointF(100, 50) << QPointF(-100, 50)
            << QPointF(-100, -50);
      setPolygon(mysharp);
}

NS_Judge::NS_Judge(QGraphicsItem* parent)
      :NSSharp(parent)
{
      Sharptype = My_GraphicsScene::NSJudge;
      show();
}

void NS_Judge::show()
{
      mysharp << QPointF(-100, -50) << QPointF(100, -50)
            << QPointF(100, 50) << QPointF(-100, 50)
            << QPointF(-100, -50) << QPointF(0, 49)
            << QPointF(99, -49);
      setPolygon(mysharp);
}

NS_While::NS_While(QGraphicsItem* parent)
{
      Sharptype = My_GraphicsScene::NSWhile;
      show();
      
}

void NS_While::show()
{
      mysharp << QPointF(-100, -50) << QPointF(100, -50)
            << QPointF(100, -25) << QPointF(-75, -25)
            << QPointF(-75, 50) << QPointF(-100, 50)<< QPointF(-100, -50);
      setPolygon(mysharp);
}
