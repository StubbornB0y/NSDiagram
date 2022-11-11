#include "My_GraphicsScene.h"
#include "NSSharp.h"
#include "qdebug.h"

My_GraphicsScene::My_GraphicsScene(QObject *parent)
	: QGraphicsScene(parent)
{
      sharptype = MouseType;
}

My_GraphicsScene::~My_GraphicsScene()
{}

void My_GraphicsScene::SequenceType()
{
	this->sharptype = NSSequence;
      qDebug() << "changed.";
}

void My_GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
      qDebug() << "Custom scene clicked.";
      QGraphicsScene::mousePressEvent(event);
      if (!event->isAccepted()) {
            if (event->button() == Qt::LeftButton) {
                  // �� Scene �����һ���Զ��� item
                  if (sharptype != MouseType) {
                        QPointF point = event->scenePos();
                        emit this->SendClickMassage(point, sharptype);
                        qDebug() << "sent";
                  }
                 /* NSSharp* item = new NSSharp();                            //���ϴ���
                  item->setRect(point.x() - 25, point.y() - 25, 60, 60);
                  addItem(item);
                  */
            }
            else if (event->button() == Qt::RightButton) {
                  // ��������Ƿ��� item
                  QGraphicsItem* itemToRemove = NULL;
                  foreach(QGraphicsItem * item, items(event->scenePos())) {
                        if (item->type() == QGraphicsItem::UserType + 1) {
                              itemToRemove = item;
                              break;
                        }
                  }
                  // �� Scene ���Ƴ� item
                  if (itemToRemove != NULL)
                        removeItem(itemToRemove);
            }
      }
}

void My_GraphicsScene::JudgeType()
{
	this->sharptype = NSJudge;
      qDebug() << "changed.";
}

void My_GraphicsScene::WhileType()
{
	this->sharptype = NSWhile;
      qDebug() << "changed.";
}

void My_GraphicsScene::ReceiveClick()
{
/*
	mousePressEvent(this->mouseEvent);
	QPointF xy=mouseEvent->pos();
	emit this->SendClickMassage(xy,this->sharptype);*/
}

void My_GraphicsScene::ReceiveClickMassage(QPointF xy, SharpType sharptype)
{
      NSSharp* item = nullptr;
      switch (sharptype) {
      case(NSSequence):
            item = new NS_Sequence(); break;                           //���ϴ���
      case(NSJudge):
            item = new NS_Judge(); break;
      case(NSWhile):
            item = new NS_While(); break;
      default:
            break;
      }
      if (sharptype != MouseType) {
            item->setPos(xy);
            addItem(item);
      }
      this->sharptype = MouseType;
      qDebug() << "set";
      
}
