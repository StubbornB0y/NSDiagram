#ifndef NSSHARP_H
#define NSSHARP_H
#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include "My_GraphicsScene.h"
#include "MyOtherItems.h"
using namespace std;
class NSSharp  : public QGraphicsRectItem
{
	
public:
	int length;
	int width;
	//string a;
	NSSharp *b;
	NSSharp *c;
	NSSharp *exit;
	NSSharp(QGraphicsItem* parent = 0);
	void MouseSelect();				//ѡ������ʱ�Զ��ݹ�ѡ����parent����
	virtual void show();
	virtual void update();				//�ݹ����������
	virtual int count(int number);				//ͳ��NS_JUDGE��cָ���ĸ����Ա������
	My_GraphicsScene::SharpType Sharptype;
	int type() const;

protected:
	//void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);//item�ڲ�����

	// Shift+���������ѡ��  Alt��׼������
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	// Alt+��ק����������  �ƶ�
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
	//void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
	// ʹitem��ʹ��qgraphicsitem_cast
	
	QPolygonF mysharp;
	
	QPointF m_centerPointF;
	bool m_bResizing;
private:
	
};

class NS_Standard :public NSSharp {
public:
	NS_Standard(QGraphicsItem* parent = 0);
	void show();
	void update();
	int count(int number);
	int type() const
	{
		return UserType + 2;
	}
};
class NS_Sequence :public NSSharp //������ʾ����˳��ṹ
{
public:
	void update();
	int count(int number);
	NS_Sequence(QGraphicsItem* parent = 0);
	void show();
};
class NS_Judge :public NSSharp //�����жϽṹ if������else
{
public:
	int maxwidth;
	int count(int number);
	void update();
	NS_Judge(QGraphicsItem* parent = 0);
	void show();
private:	
	MyLineItem* Leftline;
	MyLineItem* Rightline;
	MyTextItem* T;
	MyTextItem* F;
};
class NS_While :public NSSharp {
public:
	int childwidth;
	int count(int number);
	void update();
	NS_While(QGraphicsItem* parent = 0);
	void show();
};

#endif

