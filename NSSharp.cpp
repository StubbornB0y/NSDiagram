#include "NSSharp.h"

#include <QPainter>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

NSSharp::NSSharp(QGraphicsItem* parent)
      : QGraphicsRectItem(parent)
{
      b = nullptr;
      c = nullptr;
      exit = nullptr;
      length = 0;
     // width = 0;
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

void NSSharp::MouseSelect()
{     
      setSelected(true);
      if (parentItem()!=0) {
            static_cast<NSSharp*>(parentItem())->MouseSelect();
      }
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
                  MouseSelect();
                  qDebug() << pos();
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
      
      qDebug() << "Custom item moved.";
      QGraphicsItem::mouseMoveEvent(event);
      qDebug() << "moved" << pos();    
}

/*void NSSharp::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
      if ((event->modifiers() == Qt::AltModifier) && m_bResizing) {
            m_bResizing = false;
      }
      else {
            QGraphicsItem::mouseReleaseEvent(event);
      }
      qDebug() << "MouseRelease";
}
*/
int NSSharp::type() const
{
      return UserType + 1;
}

/*void NSSharp::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
      Q_UNUSED(option)
      Q_UNUSED(widget)
      painter->drawLine(-this->length / 2, -this->width / 2, 0, this->width/2);

}*/

NS_Standard::NS_Standard(QGraphicsItem* parent)
      :NSSharp(parent)
{
      //setFlag(QGraphicsItem::ItemIsMovable,false);
      //setFlag(QGraphicsItem::ItemIsSelectable, false);
      Sharptype = My_GraphicsScene::NSStandard;
      setRect(0,0, this->length, this->width);
      show();
}

void NS_Standard::show()
{
      
}

NS_Sequence::NS_Sequence(QGraphicsItem* parent)
      :NSSharp(parent) 
{
      Sharptype = My_GraphicsScene::NSSequence;
      show();
      b = new NS_Standard(this);
      b->setPos(0,this->width);
      b->width = this->width;
      b->length = this->length;
      b->setRect(0,0,this->length, this->width);
}
void NS_Sequence::show()
{
      this->width = 50;
      this->length = 120;
      setRect(0, 0, this->length, this->width);
}

NS_Judge::NS_Judge(QGraphicsItem* parent)
      :NSSharp(parent)
{
      
      Sharptype = My_GraphicsScene::NSJudge;
      this->width = 50;
      this->length = 120;
      setRect(-this->length / 2, -this->width / 2, this->length, this->width);
      
      show();
}


void NS_Judge::show()
{

     // setPolygon(mysharp);
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
     // setPolygon(mysharp);
}
