#include "MyOtherItems.h"
#include <QPainter>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
MyTextItem::MyTextItem(QGraphicsItem *parent)
	: QGraphicsTextItem(parent)
{
	setFlag(ItemIsSelectable, false);
	setFlag(ItemIsMovable, false);
}

int MyTextItem::type() const
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
