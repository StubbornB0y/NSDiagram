#pragma once
#ifndef MY_GRAPHICSSCENE_H
#define MY_GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
class My_GraphicsScene  : public QGraphicsScene
{
	Q_OBJECT

public:
	My_GraphicsScene(QObject *parent);
	~My_GraphicsScene();
	enum SharpType			//枚举变量，发送应该创造哪类Item
	{			
		MouseType = 0,		//对应鼠标
		NSSequence,			//顺序
		NSJudge,			//判断
		NSWhile,			//循环
		NSStandard			//基本		
	};
	SharpType sharptype;
	//QGraphicsSceneMouseEvent* mouseEvent;
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);


signals:
	void SendClickMassage(QPointF xy, SharpType sharptype);

public slots:
	void SequenceType();
	void JudgeType();
	void WhileType();
	void ReceiveClick();
	void ReceiveClickMassage(QPointF xy, SharpType sharptype);
};
#endif
