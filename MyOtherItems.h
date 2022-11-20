#pragma once

#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
class MyTextItem  : public QGraphicsTextItem
{
public:
	MyTextItem(QGraphicsItem *parent=0);
	int type() const;
};
class MyLineItem :public QGraphicsLineItem {
public:
	MyLineItem(QGraphicsItem* parent = 0);
	int type() const;
};

