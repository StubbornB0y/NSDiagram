#include "My_GraphicsScene.h"
#include "NSSharp.h"
#include "qdebug.h"
#include <qfile.h>
#include <QTextStream>

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
            }
            else if (event->button() == Qt::RightButton) {
                  // 检测光标下是否有 item
                  QGraphicsItem* itemToRemove = NULL;
                  foreach(QGraphicsItem * item, items(event->scenePos())) {
                        if (item->type() != QGraphicsItem::UserType + 2 && item->type() != QGraphicsItem::UserType + 8) {
                              itemToRemove = item;
                              break;
                        }
                  }
                  // 从 Scene 上移除 item
                  if (itemToRemove != NULL) {
                        NSSharp* theparent = dynamic_cast<NSSharp*>(itemToRemove->parentItem());
                        if (theparent != nullptr) {
                              //判断parent中哪个指针指向itemtoremove
                              if (theparent->b != nullptr && theparent->b == itemToRemove) {
                                    theparent->b = nullptr;
                              }
                              else if (theparent->c != nullptr && theparent->c == itemToRemove) {
                                    theparent->c = nullptr;
                              }
                              else if (theparent->exit != nullptr && theparent->exit == itemToRemove) {
                                    theparent->exit = nullptr;
                              }

                              topitem = dynamic_cast<NSSharp*>(itemToRemove->topLevelItem());
                              removeItem(itemToRemove);
                              delete(itemToRemove);
                              topitem->update();
                        }
                        else {
                              removeItem(itemToRemove);
                              delete(itemToRemove);
                              topitem = nullptr;
                        }
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
             if (item->type() != QGraphicsItem::UserType + 2 && item->isSelected()==true && item->type() != QGraphicsItem::UserType + 8) {
                   itemToChange = dynamic_cast<NSSharp*> (item);
                   break;
             }
       }
       //由于NS——While中的NS_Standard完全包含在其图形中，在点击while中的b指针项时Release事件依然会满足条件从而引发bug，所以再写
       if (itemToRemove != NULL && itemToChange != NULL && itemToRemove->topLevelItem() != itemToChange->topLevelItem())                      //进行一系列修改
       {
             NSSharp* theparent = dynamic_cast<NSSharp*>(itemToRemove->parentItem());
             //图形层面修改
             itemToChange = dynamic_cast<NSSharp*>(itemToChange->topLevelItem());
             itemToChange->setParentItem(theparent);
             theparent->setSelected(true);
             itemToChange->setPos(itemToRemove->pos().x(), itemToRemove->pos().y());
             itemToChange->width = itemToRemove->width;
             itemToChange->length = itemToRemove->length;
             //qDebug() << itemToChange->width;
             //qDebug() << itemToChange->b;
             //以下是数据层面修改
             //判断parent中哪个指针指向itemtoremove
             if (theparent->b != nullptr && theparent->b == itemToRemove) {
                   theparent->b = itemToChange;
             }
             else if (theparent->c != nullptr && theparent->c == itemToRemove) {
                   theparent->c = itemToChange;
             }
             else if (theparent->exit != nullptr && theparent->exit == itemToRemove) {
                   theparent->exit = itemToChange;
             }
             topitem = dynamic_cast<NSSharp*>(itemToChange->topLevelItem());
             topitem->update();
             if (itemToChange->b->length <= 70)     //实现自动放大
             {
                   topitem->length = topitem->length * 2;
                   topitem->update();
             }
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
void My_GraphicsScene::translatingC() {
      qDebug() << "buttonclick";
      QFile* file = new QFile("./NSDiagram.c");
      if (!file->open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "file open failed";
      }
      QTextStream* out=new QTextStream (file);
      //向文件中写入两行字符串
      *out << "#include<stdio.h>"<< "\n";
      *out << "void main(){" << "\n";
      if (topitem != nullptr) {
            topitem->F_out(1,out);
      }
      *out << "}" << "\n";
      file->close();
}
