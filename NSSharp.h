#ifndef NSSHARP_H
#define NSSHARP_H
#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsScene>
//#include "My_GraphicsScene.h"
#include "MyOtherItems.h"
#include <qtextstream.h>

class NSSharp  : public QGraphicsRectItem
{
	
public:
	int length;
	int width;
	MyTextItem *a;
	NSSharp *b;
	NSSharp *c;
	NSSharp *exit;
	NSSharp(QGraphicsItem* parent = 0);
	void MouseSelect();				//ѡ������ʱ�Զ��ݹ�ѡ����parent����
	virtual void show();				//���»���
	virtual void update();				//�ݹ����������
	virtual int count(int number);		//ͳ��NS_JUDGE������ĸ����Ա������
	int type() const;
	virtual void textshow();
	virtual void F_out(int indent, QTextStream* out);	//�ݹ����
protected:
	//void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);//item�ڲ�����

	// Shift+���������ѡ��  Alt��׼������
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	// Alt+��ק����������  �ƶ�
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
	//void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
	// ʹitem��ʹ��qgraphicsitem_cast
	

private:
	
};

class NS_Standard :public NSSharp {
public:
	NS_Standard(QGraphicsItem* parent = 0);
	void show();
	void update();
	int count(int number);
	void F_out(int indent, QTextStream* out);
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
	void F_out(int indent, QTextStream* out);
	void show();
};
class NS_Judge :public NSSharp //�����жϽṹ if������else
{
public:
	int maxwidth;
	int count(int number);
	void update();
	void F_out(int indent, QTextStream* out);
	NS_Judge(QGraphicsItem* parent = 0);
	void show();
private:	
	MyLineItem* Leftline;
	MyLineItem* Rightline;
	MySimpleTextItem* T;
	MySimpleTextItem* F;
};
class NS_While :public NSSharp {
public:
	int childwidth;
	int count(int number);
	void F_out(int indent, QTextStream* out);
	void update();
	NS_While(QGraphicsItem* parent = 0);
	void show();
};
class NS_DoWhile :public NSSharp {
public:
	int childwidth;
	int count(int number);
	void F_out(int indent, QTextStream* out);
	void update();
	NS_DoWhile(QGraphicsItem* parent = 0);
	void show();
	void textshow()override;
};

#endif

