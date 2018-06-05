#pragma once

#include <QtWidgets/QMainWindow>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <qtimer.h>
#include <Qtime>
#include "ui_mainform.h"

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

private slots:
	void on_startButton_clicked();
	void on_stopButton_clicked();
	void Tick();


};
