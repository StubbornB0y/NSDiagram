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
	void MouseSelect();				//选择子项时自动递归选择其parent函数
	virtual void show();				//更新绘制
	virtual void update();				//递归更新其子项
	virtual int count(int number);		//统计NS_JUDGE的子项的个数以便计算宽度
	int type() const;
	virtual void textshow();
	virtual void F_out(int indent, QTextStream* out);	//递归输出
protected:
	//void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);//item内部画画

	// Shift+左键：进行选择  Alt：准备缩放
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	// Alt+拖拽：进行缩放  移动
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
	//void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
	// 使item可使用qgraphicsitem_cast
	

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
class NS_Sequence :public NSSharp //用于显示基本顺序结构
{
public:
	void update();
	int count(int number);
	NS_Sequence(QGraphicsItem* parent = 0);
	void F_out(int indent, QTextStream* out);
	void show();
};
class NS_Judge :public NSSharp //基本判断结构 if。。。else
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

