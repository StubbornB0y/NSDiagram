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
	void MouseSelect();				//ѡ������ʱ�Զ��ݹ�ѡ����parent����
	virtual void show();
	My_GraphicsScene::SharpType Sharptype;


protected:
	//void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);//item�ڲ�����

	// Shift+���������ѡ��  Alt��׼������
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	// Alt+��ק����������  �ƶ�
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
	//void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
	// ʹitem��ʹ��qgraphicsitem_cast
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
class NS_Sequence :public NSSharp //������ʾ����˳��ṹ
{
public:
	NS_Sequence(QGraphicsItem* parent = 0);
	void show();
};
class NS_Judge :public NSSharp //�����жϽṹ if������else
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

