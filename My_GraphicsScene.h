#pragma once
#ifndef MY_GRAPHICSSCENE_H
#define MY_GRAPHICSSCENE_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "NSSharp.h"
class My_GraphicsScene  : public QGraphicsScene
{
	Q_OBJECT

public:
	NSSharp* topitem;
	My_GraphicsScene(QObject *parent);
	~My_GraphicsScene();
	enum SharpType			//ö�ٱ���������Ӧ�ô�������Item
	{			
		MouseType = 0,		//��Ӧ���
		NSSequence,			//˳��
		NSJudge,			//�ж�
		NSWhile,			//ѭ��
		NSStandard,			//����	
		NSDoWhile
	};
	SharpType sharptype;
	//QGraphicsSceneMouseEvent* mouseEvent;
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
	
signals:
	void SendClickMassage(QPointF xy, SharpType sharptype);

public slots:
	void translatingC();
	void SequenceType();
	void JudgeType();
	void WhileType();
	void DoWhileType();
	void ReceiveClickMassage(QPointF xy, SharpType sharptype);
};

#endif
