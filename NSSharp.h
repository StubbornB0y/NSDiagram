#ifndef NSSHARP_H
#define NSSHARP_H
#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include "My_GraphicsScene.h"
using namespace std;
class NSSharp  : public QGraphicsPolygonItem
{
	
public:
	int length;
	int width;
	string a;
	std::shared_ptr<NSSharp> b;
	std::shared_ptr<NSSharp> c;
	std::shared_ptr<NSSharp> exit;
	NSSharp(QGraphicsItem* parent = 0);
	virtual void show();
protected:
	// Shift+���������ѡ��  Alt��׼������
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	// Alt+��ק����������  �ƶ�
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
	// ʹitem��ʹ��qgraphicsitem_cast
	int type() const;
	QPolygonF mysharp;
	My_GraphicsScene::SharpType Sharptype;
	QPointF m_centerPointF;
	bool m_bResizing;
private:
	
};

class NS_Standard :public NSSharp {
public:
	NS_Standard(QGraphicsItem* parent = 0);
	void show();
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

