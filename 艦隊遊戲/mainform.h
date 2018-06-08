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

using namespace std;

class MainForm : public QMainWindow
{
	Q_OBJECT

public:
	MainForm(QWidget *parent = Q_NULLPTR);
	QTimer * GameTimer;
private:
	
	Ui::MainFormClass ui;
	QTime * GameTime;
	int round;
	BB test;

protected:
	void paintEvent(QPaintEvent *event) override;

private slots:
	void on_startButton_clicked();
	void on_stopButton_clicked();
	void Tick();


};
