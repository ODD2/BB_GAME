#pragma once

#include <QtWidgets/QMainWindow>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <Qtime>
#include <qtimer.h>
#include "GLOBALSETTINGS.h"
#include "VESSELHEADER.h"
#include "ui_mainform.h"
#include "battlefield.h"
#include "ResourceClass.h"
#define COMMAND_TYPES 6  //6種功能 在analyze用到


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
	QPixmap * ARRAY_PICS[PICS::PIC_END];
	inline void createPics();
//render functions
	inline void renderVessle(QPainter&);
	inline void renderMissile(QPainter&);
	inline void renderEffects(QPainter&);
	inline void renderLine(QPainter&);
	//inline void renderTerrain();

	

//功能
	void analyze(string,int);//分析 command+team
	
};
