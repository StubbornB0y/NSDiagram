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
      
      QGraphicsScene::mousePressEvent(event);
      qDebug() << "Custom scene clicked."<<event->scenePos();
      if (!event->isAccepted()) {
            if (event->button() == Qt::LeftButton) {
                  // 在 Scene 上添加一个自定义 item
                  if (sharptype != MouseType) {
                        QPointF point = event->scenePos();
                        emit this->SendClickMassage(point, sharptype);
                        qDebug() << "sent";
                  }
                 /* NSSharp* item = new NSSharp();                            //网上代码
                  item->setRect(point.x() - 25, point.y() - 25, 60, 60);
                  addItem(item);
                  */
            }
            else if (event->button() == Qt::RightButton) {
                  // 检测光标下是否有 item
                  QGraphicsItem* itemToRemove = NULL;
                  foreach(QGraphicsItem * item, items(event->scenePos())) {
                        if (item->type() == QGraphicsItem::UserType + 1) {
                              itemToRemove = item;
                              break;
                        }
                  }
                  // 从 Scene 上移除 item
                  if (itemToRemove != NULL) {
                        removeItem(itemToRemove);
                  }
            }
      }
}

 void My_GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
       NSSharp* itemToRemove = NULL;
       NSSharp* itemToChange = NULL;
       foreach(QGraphicsItem * item, items(event->scenePos()))                //寻找嵌入对象
       {
             if (item->type() == QGraphicsItem::UserType + 2) {
                   itemToRemove = dynamic_cast<NSSharp*> (item);
                   break;
             }
       }
       foreach(QGraphicsItem* item, items(event->scenePos()))                 //寻找被嵌入对象
       {
             if (item->type() != QGraphicsItem::UserType + 2 && item->isSelected()==true) {
                   itemToChange = dynamic_cast<NSSharp*> (item);
                   break;
             }
       }
       if (itemToRemove != NULL && itemToChange != NULL)                      //进行一系列修改
       {
             itemToChange->setParentItem(itemToRemove->parentItem());
             itemToChange->parentItem()->setSelected(true);
             itemToChange->setPos(itemToRemove->pos().x(), itemToRemove->pos().y());
             qDebug() << itemToChange->width;
             qDebug() << itemToChange->b;
             removeItem(itemToRemove);
             itemToChange->setSelected(false);
             delete(itemToRemove);
             qDebug() << "changed.";
             QGraphicsScene::mouseReleaseEvent(event);
       }
       else {
             QGraphicsScene::mouseReleaseEvent(event);
             qDebug() << "notchanged.";
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
            item = new NS_Sequence(); break;                           //网上代码
      case(NSJudge):
            item = new NS_Judge(); break;
      case(NSWhile):
            item = new NS_While(); break;
      default:
            break;
      }
      if (sharptype != MouseType) {
            item->setPos(xy.x() - item->length/2,xy.y()-item->width/2);
            addItem(item);

      }
      this->sharptype = MouseType;    
}
