/********************************************************************************
** Form generated from reading UI file 'mainform.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainFormClass
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QFrame *line;
    QVBoxLayout *VL_Command;
    QLabel *Label_CommandA;
    QPlainTextEdit *TextBox_CommandA;
    QLabel *Label_CommandB;
    QPlainTextEdit *TextBox_CommandB;
    QHBoxLayout *horizontalLayout;
    QLabel *Label_GameTime;
    QPushButton *startButton;
    QPushButton *stopButton;
    QVBoxLayout *VL_BattleLog;
    QLabel *Label_BattleLog;
    QTextEdit *TextBox_BattleLog;
    QLabel *Label_Map;
    QLabel *Label_Battlefield;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainFormClass)
    {
        if (MainFormClass->objectName().isEmpty())
            MainFormClass->setObjectName(QStringLiteral("MainFormClass"));
        MainFormClass->resize(1298, 715);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainFormClass->sizePolicy().hasHeightForWidth());
        MainFormClass->setSizePolicy(sizePolicy);
        MainFormClass->setDocumentMode(false);
        MainFormClass->setDockNestingEnabled(false);
        MainFormClass->setUnifiedTitleAndToolBarOnMac(false);
        centralWidget = new QWidget(MainFormClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(610, 0, 681, 661));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        line = new QFrame(layoutWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(2);
        sizePolicy1.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy1);
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 1, 0, 1, 1);

        VL_Command = new QVBoxLayout();
        VL_Command->setSpacing(6);
        VL_Command->setObjectName(QStringLiteral("VL_Command"));
        VL_Command->setContentsMargins(10, 10, 10, 10);
        Label_CommandA = new QLabel(layoutWidget);
        Label_CommandA->setObjectName(QStringLiteral("Label_CommandA"));

        VL_Command->addWidget(Label_CommandA);

        TextBox_CommandA = new QPlainTextEdit(layoutWidget);
        TextBox_CommandA->setObjectName(QStringLiteral("TextBox_CommandA"));
        TextBox_CommandA->setEnabled(true);

        VL_Command->addWidget(TextBox_CommandA);

        Label_CommandB = new QLabel(layoutWidget);
        Label_CommandB->setObjectName(QStringLiteral("Label_CommandB"));

        VL_Command->addWidget(Label_CommandB);

        TextBox_CommandB = new QPlainTextEdit(layoutWidget);
        TextBox_CommandB->setObjectName(QStringLiteral("TextBox_CommandB"));

        VL_Command->addWidget(TextBox_CommandB);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        Label_GameTime = new QLabel(layoutWidget);
        Label_GameTime->setObjectName(QStringLiteral("Label_GameTime"));
        Label_GameTime->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(Label_GameTime);

        startButton = new QPushButton(layoutWidget);
        startButton->setObjectName(QStringLiteral("startButton"));

        horizontalLayout->addWidget(startButton);

        stopButton = new QPushButton(layoutWidget);
        stopButton->setObjectName(QStringLiteral("stopButton"));

        horizontalLayout->addWidget(stopButton);


        VL_Command->addLayout(horizontalLayout);


        gridLayout->addLayout(VL_Command, 1, 1, 1, 1);

        VL_BattleLog = new QVBoxLayout();
        VL_BattleLog->setSpacing(6);
        VL_BattleLog->setObjectName(QStringLiteral("VL_BattleLog"));
        VL_BattleLog->setContentsMargins(10, 10, 10, 10);
        Label_BattleLog = new QLabel(layoutWidget);
        Label_BattleLog->setObjectName(QStringLiteral("Label_BattleLog"));
        Label_BattleLog->setFrameShape(QFrame::NoFrame);

        VL_BattleLog->addWidget(Label_BattleLog);

        TextBox_BattleLog = new QTextEdit(layoutWidget);
        TextBox_BattleLog->setObjectName(QStringLiteral("TextBox_BattleLog"));
        TextBox_BattleLog->setReadOnly(true);

        VL_BattleLog->addWidget(TextBox_BattleLog);


        gridLayout->addLayout(VL_BattleLog, 1, 2, 1, 1);

        Label_Map = new QLabel(centralWidget);
        Label_Map->setObjectName(QStringLiteral("Label_Map"));
        Label_Map->setGeometry(QRect(20, 40, 570, 570));
        Label_Map->setAutoFillBackground(false);
        Label_Map->setStyleSheet(QStringLiteral("QLabel{background-color: gray}"));
        Label_Map->setFrameShadow(QFrame::Plain);
        Label_Battlefield = new QLabel(centralWidget);
        Label_Battlefield->setObjectName(QStringLiteral("Label_Battlefield"));
        Label_Battlefield->setGeometry(QRect(20, 40, 570, 570));
        Label_Battlefield->setStyleSheet(QStringLiteral("QLabel{background-color: green}"));
        MainFormClass->setCentralWidget(centralWidget);
        Label_Map->raise();
        Label_Battlefield->raise();
        layoutWidget->raise();
        menuBar = new QMenuBar(MainFormClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1298, 21));
        MainFormClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainFormClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainFormClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainFormClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainFormClass->setStatusBar(statusBar);

        retranslateUi(MainFormClass);

        QMetaObject::connectSlotsByName(MainFormClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainFormClass)
    {
        MainFormClass->setWindowTitle(QApplication::translate("MainFormClass", "BattleShip", nullptr));
        Label_CommandA->setText(QApplication::translate("MainFormClass", "CommandA:", nullptr));
        Label_CommandB->setText(QApplication::translate("MainFormClass", "CommandB:", nullptr));
        Label_GameTime->setText(QApplication::translate("MainFormClass", "00:00:00", nullptr));
        startButton->setText(QApplication::translate("MainFormClass", "START", nullptr));
        stopButton->setText(QApplication::translate("MainFormClass", "STOP", nullptr));
        Label_BattleLog->setText(QApplication::translate("MainFormClass", "BattleLog:", nullptr));
        Label_Map->setText(QString());
        Label_Battlefield->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainFormClass: public Ui_MainFormClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
