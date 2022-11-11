#pragma once
#include"My_GraphicsScene.h"
#include <QtWidgets/QMainWindow>
#include "ui_NSmap.h"
#include "NSSharp.h"
using namespace std;
class NSmap : public QMainWindow
{
    Q_OBJECT

public:
    NSmap(QWidget *parent = nullptr);
    ~NSmap();
    My_GraphicsScene* scene;
private:
	void createsence();
	
    Ui::NSmapClass ui;

};
