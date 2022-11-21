#include "NSSharp.h"
#include "MyOtherItems.h"
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
      width = 0;
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

void NSSharp::update()
{
}

int NSSharp::count(int number)
{
      return number++;
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
            /*
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
            else {*/
            qDebug() << "Custom item left clicked.";
            QGraphicsItem::mousePressEvent(event);
            MouseSelect();
            qDebug() << pos();
            if(b!=nullptr)
            qDebug() << (b->count(0));
            if(c!=nullptr)
            qDebug() << (c->count(0));
            event->accept();
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
      show();
}

void NS_Standard::show()
{
      setRect(0,0, this->length, this->width);
}

void NS_Standard::update()
{
      show();
}

int NS_Standard::count(int number)
{
      return (++number);
}

NS_Sequence::NS_Sequence(QGraphicsItem* parent)
      :NSSharp(parent) 
{
      Sharptype = My_GraphicsScene::NSSequence;
      
      this->width = 50;
      this->length = 200;
      b = new NS_Standard(this);
      b->setPos(0,this->width);
      b->width = this->width;
      b->length = this->length;
      b->setRect(0,0,this->length, this->width);
      show();
}
void NS_Sequence::show()
{
      setRect(0, 0, this->length, this->width);
}

void NS_Sequence::update()
{
      show();
      if (b != nullptr){
            b->length = this->length;
            b->width = this->width;
            b->setPos(0, this->width);
            b->update();
      }
}

int NS_Sequence::count(int number)
{
      if (b != nullptr) {
            return (b->count(++number));
      }
      else
            return ++number;//一定要++number 一定要++number 一定要++number 要不就加括号
}

NS_Judge::NS_Judge(QGraphicsItem* parent)
      :NSSharp(parent)
{
      Sharptype = My_GraphicsScene::NSJudge;
      this->width = 50;
      this->length = 200;
      Leftline = new MyLineItem(this);
      Rightline = new MyLineItem(this);
      T = new MyTextItem(this);
      F = new MyTextItem(this);
      b = new NS_Standard(this);
      b->setPos(0, this->width);
      b->width = this->width;
      b->length = this->length/2;
      b->setRect(0, 0, b->length, b->width);
      c = new NS_Standard(this);
      c->setPos(this->length/2, this->width);
      c->width = this->width;
      c->length = this->length / 2;
      c->setRect(0, 0, c->length, c->width);
      exit = new NS_Standard(this);
      exit->setPos(0, this->width*2);
      exit->width = this->width;
      exit->length = this->length;
      exit->setRect(0, 0, exit->length, exit->width);
      show();
}


void NS_Judge::show()
{
      setRect(0, 0, this->length, this->width);
      Leftline->setLine(0, 0, this->length / 2, this->width);
      Rightline->setLine(this->length / 2, this->width, this->length, 0);
      T->setPlainText("T");
      T->setPos(5,this->width-25);
      F->setPlainText("F");
      F->setPos(this->length-20, this->width - 25);
      
     // setPolygon(mysharp);
}

void NS_Judge::update()
{
      show();
      int bnumber = 0, cnumber = 0;
      if (b != nullptr) {
            bnumber = b->count(0);
      }
      if (c != nullptr) {
            cnumber = c->count(0);
      }
      if (bnumber >= cnumber) {
            if (b != nullptr) {
                  b->setPos(0, this->width);
                  b->width = this->width;
                  b->length = this->length / 2;
                  b->update();
                  maxwidth =( (b->boundingRect()).united(b->childrenBoundingRect() ) ).height()-2 ;
                  //注:united函数和childrenBoundingRect分别会多框1格 所以-2 下同      
            }
            if (c != nullptr) {
                  c->setPos(this->length / 2, this->width);
                  c->width = maxwidth/cnumber;
                  c->length = this->length / 2;
                  c->update();
            }
      }     
      else if(bnumber<cnumber){
            if (c != nullptr) {
                  c->setPos(this->length / 2, this->width);
                  c->width = this->width;
                  c->length = this->length / 2;
                  c->update();
                  maxwidth = ((c->boundingRect()).united(c->childrenBoundingRect())).height()-2;
            }
            if (b != nullptr) {
                  b->setPos(0, this->width);
                  b->width = maxwidth / bnumber;
                  b->length = this->length / 2;
                  b->update();
            }
      }
      if (exit != nullptr) {
            exit->length = this->length;
            exit->width = this->width;
            exit->setPos(0, this->width+maxwidth);
            exit->update();
      }
}

int NS_Judge::count(int number)
{
      int bnumber=0, cnumber=0;
      if (b != nullptr) {
            bnumber = b->count(0);
      }
      if (c != nullptr) {
            cnumber = c->count(0);
      }
      if (bnumber > cnumber) {
            if (exit != nullptr) {
                  return exit->count(bnumber+(++number));
            }
            else {
                  return bnumber + (++number);
            }
      }
      else {
            if (exit != nullptr) {
                  return exit->count(cnumber + (++number));
            }
            else {
                  return cnumber + (++number);
            }
      }
}



NS_While::NS_While(QGraphicsItem* parent)
{
      Sharptype = My_GraphicsScene::NSWhile;
      this->width = 50;
      this->length = 200;
      b = new NS_Standard(this);
      b->setPos(20, this->width);
      b->width = this->width;
      b->length = this->length-20;
      b->setRect(0, 0, b->length, b->width);
      childwidth = (b->childrenBoundingRect()).width() + b->width;
      exit = new NS_Standard(this);
      exit->setPos(0, this->width + this->childwidth);
      exit->width = this->width;
      exit->length = this->length;
      exit->setRect(0, 0, exit->length, exit->width);
      show();
      
}

void NS_While::show()
{
      setRect(0, 0, this->length, this->width + this->childwidth);
}

int NS_While::count(int number)
{
      int bnumber = 0;
      if (b != nullptr) {
            bnumber = b->count(0);
      }
      if (exit != nullptr) {
            return exit->count(bnumber + (++number));
      }
      else {
            return bnumber + (++number);
      }
}

void NS_While::update() {
      
      if (b != nullptr) {
            b->length = this->length-20;
            b->width = this->width;
            b->setPos(20, this->width);
            b->update();
            childwidth = ((b->boundingRect()).united(b->childrenBoundingRect())).height()-2;
      }
      show();
      if (exit != nullptr) {
            exit->length = this->length;
            exit->width = this->width;
            exit->setPos(0, this->width + childwidth);
            exit->update();
      }
      
}
