#include "My_GraphicsScene.h"
#include "NSSharp.h"
#include "qdebug.h"
#include <qfile.h>
#include <QTextStream>
#include <qdesktopservices.h>
#include <QFileDialog>
#include <qstring.h>
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
             if (item->type() == QGraphicsItem::UserType + 2 && item->isSelected() == false) {
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
             if (itemToChange->b->length <= 80)     //实现自动放大
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

void My_GraphicsScene::DoWhileType()
{
      this->sharptype = NSDoWhile;
      qDebug() << "changed.";
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
      case(NSDoWhile):
            item = new NS_DoWhile(); break;
      default:
            break;
      }
      if (sharptype != MouseType) {
            item->setPos(xy.x() - item->length/2,xy.y()-item->width/2);
            addItem(item);
      }
      this->sharptype = MouseType;    
}
void My_GraphicsScene::translatingNS()
{
      QString path = QFileDialog::getOpenFileName(0, "Open", "./", "source(*.c);;source(*.cpp)");
      if (path.isEmpty() == false)
      {
            QFile* file = new QFile(path);
            if (file->open(QIODevice::ReadOnly) == true)
            {
                  QString str;

                  QTextStream* out = new QTextStream(file);
                  QTextStream* copy = out;
                  str = out->readLine();
                  str = out->readLine();
                  /*while (str.indexOf("#") != -1 && str.indexOf("main") != -1) {
                        qDebug() << (str.indexOf("main"));
                        copy = out;
                        str = out->readLine();
                  }*/
                  readC(0, &topitem, out);
                  file->close();
                  topitem = dynamic_cast<NSSharp*>(topitem->topLevelItem());
                  topitem->setPos(1430, 858);
                  topitem->update();
                  addItem(topitem);                 
            }
      }
}
void My_GraphicsScene::readC(NSSharp*parent, NSSharp** op, QTextStream* out)
{
      QString str;
      str=out->readLine();
      if (out->atEnd() == false) {
            int place = -1;
            if (str.indexOf("if(") >= 0) {
                  place = str.indexOf("if(");
                  *op = new NS_Judge(parent);
                  int tail = str.indexOf(")");
                  (*op)->a->setPlainText(str.mid(place + 3, tail - place - 3));
                  removeItem((*op)->b);
                  delete((*op)->b);
                  (*op)->b = nullptr;
                  NSSharp* opcopy = *op;
                  readC(*op, &(*op)->b, out);
                  QTextStream* copy = out;
                  str = out->readLine();
                  if (str.indexOf("else") >= 0) {
                        readC(opcopy, &(opcopy)->c, out);
                        readC(opcopy, &(opcopy)->exit, out);
                  }
                  else
                        readC(opcopy, &(opcopy)->exit, copy);
            }
            else if (str.indexOf("while(") >= 0) {
                  place = str.indexOf("while(");
                  *op = new NS_While(parent);
                  int tail = str.indexOf(")");
                  (*op)->a->setPlainText(str.mid(place + 6, tail - place - 6));
                  removeItem((*op)->b);
                  delete((*op)->b);
                  (*op)->b = nullptr;
                  NSSharp* opcopy = *op;
                  readC(*op, &(*op)->b, out);
                  readC(opcopy, &(opcopy)->exit, out);
            }
            else if (str.indexOf("do{") >= 0) {
                  place = str.indexOf("do{");
                  *op = new NS_DoWhile(parent);
                  removeItem((*op)->b);
                  delete((*op)->b);
                  (*op)->b = nullptr;
                  NSSharp* opcopy = *op;
                  readC(*op, &(*op)->b, out);
                  str = out->readLine();
                  if (str.indexOf("while (") >= 0) {
                        place = str.indexOf("while(");
                        int tail = str.indexOf(")");
                        (*op)->a->setPlainText(str.mid(place + 6, tail - place - 6));
                        readC(opcopy, &(opcopy)->exit, out);
                  }
            }
            else if (str.indexOf("}") >= 0) {
                  return;
            }
            else {
                  for (place = 0; place < str.length(); place++) {
                        if (str.at(place) != ' ') {
                              break;
                        }
                  }
                  if (place != str.length()) {
                        int tail = str.indexOf(";");
                        *op = new NS_Sequence(parent);
                        if (tail != -1)
                              (*op)->a->setPlainText(str.mid(place, tail - place));
                        removeItem((*op)->b);
                        delete((*op)->b);
                        (*op)->b = nullptr;
                        readC(*op, &(*op)->b, out);
                  }
                  else
                        readC(parent, op, out);
            }
      }
      else
            return;
}
void My_GraphicsScene::translatingC() {
      qDebug() << "buttonclick";
      QString path = QFileDialog::getSaveFileName(0, "Save", "./", "source(*.c);;source(*.cpp)");
      if (path.isEmpty() == false) {
            QFile* file = new QFile(path);
            if (!file->open(QIODevice::WriteOnly | QIODevice::Text)) {
                  qDebug() << "file open failed";
            }
            else {
                  QTextStream* out = new QTextStream(file);
                  //向文件中写入两行字符串
                  *out << "#include<stdio.h>" << "\n";
                  *out << "void main(){" << "\n";
                  if (topitem != nullptr) {
                        topitem->F_out(1, out);
                  }
                  *out << "}" << "\n";
                  file->close();
                  QDesktopServices::openUrl(QUrl::fromLocalFile("./NSDiagram.c"));
            }
      }
}



