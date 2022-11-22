#pragma once

#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QKeyEvent>
class MySimpleTextItem  : public QGraphicsSimpleTextItem
{
public:
	MySimpleTextItem(QGraphicsItem *parent=0);
	int type() const;
};
class MyLineItem :public QGraphicsLineItem {
public:
	MyLineItem(QGraphicsItem* parent = 0);
	int type() const;
};
class MyTextItem:public QGraphicsTextItem
{
public:
	MyTextItem(QGraphicsItem* parent = 0);
	int type() const;
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void keyPressEvent(QKeyEvent* event) override {
		if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
		{
			//����س�ʧȥ���㣬�༭��ɣ�������FocusOutEvent����
			clearFocus();
		}
		else {
			QGraphicsTextItem::keyPressEvent(event);
		}
	}
	void focusOutEvent(QFocusEvent* event) override {
		setTextInteractionFlags(Qt::NoTextInteraction);
		QGraphicsTextItem::focusOutEvent(event);
	}
};