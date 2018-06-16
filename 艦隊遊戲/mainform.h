#pragma once

#include <QtWidgets/QMainWindow>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <Qtime>
#include <qtimer.h>
#include "ui_mainform.h"
#include "GLOBALSETTINGS.h"
#include "VESSELHEADER.h"
#include "battlefield.h"
#define command_types 5  //五種功能 在analyze用到
using namespace std;

class MainForm : public QMainWindow
{
	Q_OBJECT

public:
	MainForm(QWidget *parent = Q_NULLPTR);
	QTimer * GameTimer;
private:
//objects
	Ui::MainFormClass ui;
	QTime * GameTime;
	BattleField BF;


protected:
	void paintEvent(QPaintEvent *event) override;

private slots:
	void on_startButton_clicked();
	void on_stopButton_clicked();
	void Tick();


private:
//picures
	QPixmap pm_vessel = QPixmap("./Resources/BB.png").scaled(BATTLE_SHIP_WIDTH, BATTLE_SHIP_HEIGHT);
	QPixmap pm_missile =  QPixmap("./Resources/MS.png").scaled(MISSILE_WIDTH, MISSILE_HEIGHT);
	QPixmap pm_explode = QPixmap("./Resources/EX.png");

//render functions
	inline void renderVessle(QPainter&);
	inline void renderMissile(QPainter&);
	inline void renderEffects(QPainter&);
	inline void renderLine(QPainter&);
	//inline void renderTerrain();
	void analyze(string,int);//分析 command+team
};
