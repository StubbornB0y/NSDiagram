#include "MyOtherItems.h"
#include <QPainter>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <qtextcursor.h>
#include<qtextformat.h>
#include <QGraphicsSceneMouseEvent>
MySimpleTextItem::MySimpleTextItem(QGraphicsItem *parent)
	: QGraphicsSimpleTextItem(parent)
{
	setFlag(ItemIsSelectable, false);
	setFlag(ItemIsMovable, false);
}

int MySimpleTextItem::type() const
{
	return UserType + 8;	//杂项 防止被选中
}


MyLineItem::MyLineItem(QGraphicsItem* parent)
	: QGraphicsLineItem(parent)
{
	QPen p = pen();
	p.setWidth(2);
	p.setColor(QColor(0, 0, 0));
	setPen(p);
	setFlag(ItemIsSelectable, false);
	setFlag(ItemIsMovable, false);
}

int MyLineItem::type() const
{
	return UserType + 8;	//杂项 防止被选中
}

MyTextItem::MyTextItem(QGraphicsItem* parent)
	:QGraphicsTextItem(parent)
{
	
	setFlag(ItemIsSelectable, false);
	//设置字体
	QFont font; font.setBold(true); 
	font.setFamily("SimHei"); 
	font.setPointSize(20); 
	this->setFont(font);
}

int MyTextItem::type() const
{
	return UserType+8;
}

void MyTextItem::mousePressEvent(QGraphicsSceneMouseEvent* event){

	if (event->button() == Qt::LeftButton) {
		if (event->modifiers() == Qt::AltModifier) {
			setTextInteractionFlags(Qt::TextEditorInteraction);
			setFocus();
			QGraphicsItem::mousePressEvent(event);
		}
		else{
			event->ignore();
		}

	}
	else {//其他按键正常流程    	
		QGraphicsTextItem::mousePressEvent(event);
	}
}

void MyTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsItem::mouseDoubleClickEvent(event);
}




