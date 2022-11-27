#include "NSSharp.h"
#include "MyOtherItems.h"
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <qtextcursor.h>
#include<qtextformat.h>
#include <iostream>
#include <iomanip>
using namespace std;

NSSharp::NSSharp(QGraphicsItem* parent)
      : QGraphicsRectItem(parent)
{
      b = nullptr;
      c = nullptr;
      exit = nullptr;
      length = 200;
      width = 50;
      // ���� - �߿�ɫ
      QPen p = pen();
      p.setWidth(2);
      p.setColor(QColor(0, 0, 0));

      setPen(p);
      //��ʼ��a�����þ���
      a = new MyTextItem(this);

      // ��ѡ�񡢿��ƶ�
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
      if (parentItem()!=nullptr) {
            dynamic_cast<NSSharp*>(parentItem())->MouseSelect();
      }
}

void NSSharp::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
      if (event->button() == Qt::LeftButton) {
            qDebug() << "Custom item left clicked.";
            QGraphicsItem::mousePressEvent(event);
            MouseSelect();
            qDebug() << pos();
            if(b!=nullptr)
            if(c!=nullptr)
            event->accept();
      }
      else if (event->button() == Qt::RightButton) {
            event->ignore();
      }
}

void NSSharp::F_out(int indent, QTextStream* out)
{

}

void NSSharp::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
      
      qDebug() << "Custom item moved.";
      QGraphicsItem::mouseMoveEvent(event);
      qDebug() << "moved" << pos();    
}

void NSSharp::textshow()
{
      //a->setPlainText("test");
      a->setTextWidth(this->length - 20);
      a->setPos(10, this->width/2-20);
      QTextBlockFormat format;
      format.setAlignment(Qt::AlignCenter);
      QTextCursor cursor = a->textCursor();
      cursor.select(QTextCursor::Document);
      cursor.mergeBlockFormat(format);
      cursor.clearSelection();
      a->setTextCursor(cursor);
}

int NSSharp::type() const
{
      return UserType + 1;
}



NS_Standard::NS_Standard(QGraphicsItem* parent)
      :NSSharp(parent)
{
      //setFlag(QGraphicsItem::ItemIsMovable,false);
      //setFlag(QGraphicsItem::ItemIsSelectable, false);
      //Sharptype = My_GraphicsScene::NSStandard;
      
      show();
}

void NS_Standard::show()
{
      setRect(0,0, this->length, this->width);
      textshow();
}

void NS_Standard::update()
{
      show();
}

void NS_Standard::F_out(int indent, QTextStream* out)
{
      for (int i = 0; i < indent; i++)
            *out << "   ";
      *out << a->toPlainText() <<";" << "\n";
}

int NS_Standard::count(int number)
{
      return (++number);
}



NS_Sequence::NS_Sequence(QGraphicsItem* parent)
      :NSSharp(parent) 
{
     // Sharptype = My_GraphicsScene::NSSequence;
      //this->width = 50;
      //this->length = 200;
      
      b = new NS_Standard(this);
      b->setPos(0,this->width);
      b->width = this->width;
      b->length = this->length;
      b->setRect(0,0,this->length, this->width);
      b->textshow();
      show();
}

void NS_Sequence::show()
{
      setRect(0, 0, this->length, this->width);
      textshow();
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
            return ++number;//һ��Ҫ++number һ��Ҫ++number һ��Ҫ++number Ҫ���ͼ�����
}

void NS_Sequence::F_out(int indent, QTextStream* out) {
      for (int i = 0; i < indent; i++)
            *out << "   ";
      *out<< a->toPlainText() <<";"<< "\n";
      if (b != nullptr)
            b->F_out(indent, out);
}



NS_Judge::NS_Judge(QGraphicsItem* parent)
      :NSSharp(parent)
{
      //Sharptype = My_GraphicsScene::NSJudge;
      //this->width = 50;
      //this->length = 200;
      Leftline = new MyLineItem(this);
      Rightline = new MyLineItem(this);
      T = new MySimpleTextItem(this);
      F = new MySimpleTextItem(this);
      QFont font = a->font();
      font.setPointSize(15);
      a->setFont(font);
      b = new NS_Standard(this);
      b->setPos(0, this->width);
      b->width = this->width;
      b->length = this->length/2;
      b->setRect(0, 0, b->length, b->width);
      b->textshow();
      c = new NS_Standard(this);
      c->setPos(this->length/2, this->width);
      c->width = this->width;
      c->length = this->length / 2;
      c->setRect(0, 0, c->length, c->width);
      c->textshow();
      exit = new NS_Standard(this);
      exit->setPos(0, this->width*2);
      exit->width = this->width;
      exit->length = this->length;
      exit->setRect(0, 0, exit->length, exit->width);
      exit->textshow();
      show();
}

void NS_Judge::show()
{
      setRect(0, 0, this->length, this->width);
      Leftline->setLine(0, 0, this->length / 2, this->width);
      Rightline->setLine(this->length / 2, this->width, this->length, 0);
      T->setText("T");
      T->setPos(5,this->width-25);
      F->setText("F");
      F->setPos(this->length-20, this->width - 25);
      textshow();
     // setPolygon(mysharp);
}

void NS_Judge::update()
{
      show();
      a->setPos(10, 5);
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
                  //ע:united������childrenBoundingRect�ֱ����1�� ����-2 ��ͬ      
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

void NS_Judge::F_out(int indent, QTextStream* out)
{
      for (int i = 0; i < indent; i++)
            *out << "   ";
      *out <<  "if(" << a->toPlainText() << "){" << "\n";
      indent++;
      if (b != nullptr)
            b->F_out(indent,out);
      indent--;
      for (int i = 0; i < indent; i++)
            *out << "   ";
      *out <<  "}" << "\n";
      for (int i = 0; i < indent; i++)
            *out << "   ";
      *out << "else{" << "\n";
      indent++;
      if (c != nullptr)
            c->F_out(indent,out);
      indent--;
      for (int i = 0; i < indent; i++)
            *out << "   ";
      *out << "}" <<"\n";
      if (exit != nullptr)
            exit->F_out(indent,out);
}



NS_While::NS_While(QGraphicsItem* parent)
{
      //Sharptype = My_GraphicsScene::NSWhile;
      //this->width = 50;
      //this->length = 200;
      b = new NS_Standard(this);
      b->setPos(20, this->width);
      b->width = this->width;
      b->length = this->length-20;
      b->setRect(0, 0, b->length, b->width);
      b->textshow();
      childwidth = ((b->boundingRect()).united(b->childrenBoundingRect())).height() - 2;
      exit = new NS_Standard(this);
      exit->setPos(0, this->width + this->childwidth);
      exit->width = this->width;
      exit->length = this->length;
      exit->setRect(0, 0, exit->length, exit->width);
      exit->textshow();
      show();
      
}

void NS_While::show()
{
      setRect(0, 0, this->length, this->width + this->childwidth);
      textshow();
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

void NS_While::F_out(int indent, QTextStream *out)
{
      for (int i = 0; i < indent; i++)
            *out << "   ";
      *out << "while(" << a->toPlainText() << "){" << "\n";
      indent++;
      if (b != nullptr)
            b->F_out(indent, out);
      indent--;
      for (int i = 0; i < indent; i++)
            *out << "   ";
      *out << "}" << "\n";
      if (exit != nullptr)
            exit->F_out(indent, out);
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



NS_DoWhile::NS_DoWhile(QGraphicsItem* parent)
{
      //Sharptype = My_GraphicsScene::NSWhile;
      //this->width = 50;
      //this->length = 200;
      b = new NS_Standard(this);
      b->setPos(0, 0);
      b->width = this->width;
      b->length = this->length - 20;
      b->setRect(0, 0, b->length, b->width);
      b->textshow();
      childwidth = ((b->boundingRect()).united(b->childrenBoundingRect())).height() - 2;
      exit = new NS_Standard(this);
      exit->setPos(0, this->width + this->childwidth);
      exit->width = this->width;
      exit->length = this->length;
      exit->setRect(0, 0, exit->length, exit->width);
      exit->textshow();
      show();

}

void NS_DoWhile::show()
{
      setRect(0, 0, this->length, this->width + this->childwidth);
      textshow();
}

int NS_DoWhile::count(int number)
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

void NS_DoWhile::F_out(int indent, QTextStream* out)
{
      for (int i = 0; i < indent; i++)
            *out << "   ";
      *out << "do{" << "\n";
      indent++;
      if (b != nullptr)
            b->F_out(indent, out);
      indent--;
      for (int i = 0; i < indent; i++)
            *out << "   ";
      *out << "}" << "\n";
      for (int i = 0; i < indent; i++)
            *out << "   ";
      *out << "while(" << a->toPlainText() << ");" << "\n";
      if (exit != nullptr)
            exit->F_out(indent, out);
}

void NS_DoWhile::update() {

      if (b != nullptr) {
            b->length = this->length - 20;
            b->width = this->width;
            b->setPos(0, 0);
            b->update();
            childwidth = ((b->boundingRect()).united(b->childrenBoundingRect())).height() - 2;
      }
      show();
      if (exit != nullptr) {
            exit->length = this->length;
            exit->width = this->width;
            exit->setPos(0, this->width + childwidth);
            exit->update();
      }

}

void NS_DoWhile::textshow() {
      a->setTextWidth(this->length - 20);
      a->setPos(10, (this->width / 2 - 20)+childwidth);
      QTextBlockFormat format;
      format.setAlignment(Qt::AlignCenter);
      QTextCursor cursor = a->textCursor();
      cursor.select(QTextCursor::Document);
      cursor.mergeBlockFormat(format);
      cursor.clearSelection();
      a->setTextCursor(cursor);
}