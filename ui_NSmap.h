/********************************************************************************
** Form generated from reading UI file 'NSmappUlGJP.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef NSMAPPULGJP_H
#define NSMAPPULGJP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NSmapClass
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_as;
    QWidget *centralWidget;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPushButton *SequenceButton;
    QPushButton *JudgeButton;
    QPushButton *WhileButton;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *NSmapClass)
    {
        if (NSmapClass->objectName().isEmpty())
            NSmapClass->setObjectName(QString::fromUtf8("NSmapClass"));
        NSmapClass->resize(826, 599);
        actionNew = new QAction(NSmapClass);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionOpen = new QAction(NSmapClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(NSmapClass);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave_as = new QAction(NSmapClass);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        centralWidget = new QWidget(NSmapClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setEnabled(true);
        scrollArea->setGeometry(QRect(0, 0, 191, 1021));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 189, 1019));
        SequenceButton = new QPushButton(scrollAreaWidgetContents);
        SequenceButton->setObjectName(QString::fromUtf8("SequenceButton"));
        SequenceButton->setEnabled(true);
        SequenceButton->setGeometry(QRect(10, 0, 81, 61));
        SequenceButton->setStyleSheet(QString::fromUtf8("border-image: url(:/NSmap/NS_order.png);"));
        SequenceButton->setCheckable(false);
        JudgeButton = new QPushButton(scrollAreaWidgetContents);
        JudgeButton->setObjectName(QString::fromUtf8("JudgeButton"));
        JudgeButton->setEnabled(true);
        JudgeButton->setGeometry(QRect(100, 0, 81, 61));
        JudgeButton->setStyleSheet(QString::fromUtf8("border-image: url(:/NSmap/Judge.png);"));
        WhileButton = new QPushButton(scrollAreaWidgetContents);
        WhileButton->setObjectName(QString::fromUtf8("WhileButton"));
        WhileButton->setEnabled(true);
        WhileButton->setGeometry(QRect(10, 70, 81, 61));
        WhileButton->setStyleSheet(QString::fromUtf8("border-image: url(:/NSmap/While.png);"));
        scrollArea->setWidget(scrollAreaWidgetContents);
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setEnabled(true);
        graphicsView->setGeometry(QRect(200, 0, 1051, 731));
        NSmapClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(NSmapClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 826, 22));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        NSmapClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(NSmapClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        NSmapClass->addToolBar(Qt::LeftToolBarArea, mainToolBar);
        statusBar = new QStatusBar(NSmapClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        NSmapClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actionNew);
        menu->addAction(actionOpen);
        menu->addAction(actionSave);
        menu->addAction(actionSave_as);

        retranslateUi(NSmapClass);

        QMetaObject::connectSlotsByName(NSmapClass);
    } // setupUi

    void retranslateUi(QMainWindow *NSmapClass)
    {
        NSmapClass->setWindowTitle(QCoreApplication::translate("NSmapClass", "NSmap", nullptr));
        actionNew->setText(QCoreApplication::translate("NSmapClass", "New", nullptr));
        actionOpen->setText(QCoreApplication::translate("NSmapClass", "Open", nullptr));
        actionSave->setText(QCoreApplication::translate("NSmapClass", "Save", nullptr));
        actionSave_as->setText(QCoreApplication::translate("NSmapClass", "Save as", nullptr));
        SequenceButton->setText(QString());
        JudgeButton->setText(QString());
        WhileButton->setText(QString());
        menu->setTitle(QCoreApplication::translate("NSmapClass", "\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NSmapClass: public Ui_NSmapClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // NSMAPPULGJP_H
