#ifndef NSSHARP_H
#define NSSHARP_H
#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include "My_GraphicsScene.h"
using namespace std;
class NSSharp  : public QGraphicsRectItem
{
	
public:
	int length;
	int width;
	string a;
	NSSharp *b;
	NSSharp *c;
	NSSharp *exit;
	NSSharp(QGraphicsItem* parent = 0);
	void MouseSelect();				//选择子项时自动递归选择其parent函数
	virtual void show();
	My_GraphicsScene::SharpType Sharptype;


protected:
	//void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);//item内部画画

	// Shift+左键：进行选择  Alt：准备缩放
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	// Alt+拖拽：进行缩放  移动
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
	//void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
	// 使item可使用qgraphicsitem_cast
	int type() const;
	QPolygonF mysharp;
	
	QPointF m_centerPointF;
	bool m_bResizing;
private:
	
};

class NS_Standard :public NSSharp {
public:
	NS_Standard(QGraphicsItem* parent = 0);
	void show();
	int type() const
	{
		return UserType + 2;
	}
};
class NS_Sequence :public NSSharp //用于显示基本顺序结构
{
public:
	NS_Sequence(QGraphicsItem* parent = 0);
	void show();
};
class NS_Judge :public NSSharp //基本判断结构 if。。。else
{
public:
	NS_Judge(QGraphicsItem* parent = 0);
	void show();
};
class NS_While :public NSSharp {
public:
	NS_While(QGraphicsItem* parent = 0);
	void show();
};

#endif

