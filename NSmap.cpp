#include "NSmap.h"
#include "My_GraphicsScene.h"
#include "qpushbutton.h"
#include <iostream>
#include <iomanip>
#include "qdebug.h"
using namespace std;

NSmap::NSmap(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);
	createsence();
	
}

NSmap::~NSmap()
{}

void NSmap::createsence()	
{
	My_GraphicsScene* scene = new My_GraphicsScene(this);
	scene->setSceneRect(1280, 720, 2360,1440);
	ui.graphicsView->setScene(scene);
	qDebug() << "created.";
	connect(ui.SequenceButton,&QPushButton::clicked,scene,&My_GraphicsScene::SequenceType);
	connect(ui.JudgeButton, &QPushButton::clicked, scene, &My_GraphicsScene::JudgeType);
	connect(ui.WhileButton, &QPushButton::clicked, scene, &My_GraphicsScene::WhileType);
	connect(ui.DoWhileButton, &QPushButton::clicked, scene, &My_GraphicsScene::DoWhileType);
	connect(scene,&My_GraphicsScene::SendClickMassage,scene,&My_GraphicsScene::ReceiveClickMassage);
	connect(ui.actionSave_as, &QAction::triggered,scene,&My_GraphicsScene::translatingC);
}


/*class NSSharp {
public:
	NSSharp(int length,int width) {
		this->length = length;
		this->width = width;
	}
	int length;
	int width;
	string a;
	std::shared_ptr<NSSharp> b;
	std::shared_ptr<NSSharp> c;
	
	NSSharp(int ind) {
		indent = 1;
	}
	virtual void F_cout() {
		
	}
	virtual void show() {

	}
};
class NS_Standard :public NSSharp {
public:
	void F_cout() {
		std::cout << setw(indent * 4) << a << endl;
	}
	void show()
	{
		
	}
};
class NS_Sequence:public NSSharp //用于显示基本顺序结构
{
public:
	void F_cout() {
		
		std::cout << setw(indent*4) << a << endl;
		if (b != nullptr)
			b->F_cout();
	}

};

class NS_Judge :NSSharp //基本判断结构 if。。。else
{
public:
	std::shared_ptr<NSSharp> exit;
	void F_cout() {
		std::cout << setw(indent * 4) << "if(" << a << "){" << endl;
		indent++;
		if (b != nullptr)
			b->F_cout();
		indent--;
		std::cout << setw(indent * 4) <<  "}" << endl;
		std::cout << setw(indent * 4) << "else{" << endl;
		indent++;
		if (c != nullptr)  
			c->F_cout();
		indent--;
		std::cout << setw(indent * 4) << "}" << endl;
		if (exit != nullptr)
			exit->F_cout();
	 }
};

class NS_While :NSSharp
{
public:
	std::shared_ptr<NSSharp> exit;
	void F_cout() {

	}
};*/