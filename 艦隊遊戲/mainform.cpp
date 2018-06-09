#include "mainform.h"
#include <QtDebug>
#include <qpainter.h>

MainForm::MainForm(QWidget *parent)
	: QMainWindow(parent)
{
	//UI Setup
	ui.setupUi(this);
	setFixedSize(geometry().width(), geometry().height());
	ui.Label_Battlefield->setStyleSheet("");
	ui.Label_Map->setFixedSize(MAP_WIDTH, MAP_HEIGHT);
	ui.Label_Battlefield->setFixedSize(MAP_WIDTH, MAP_HEIGHT);


	//Label_Map Setup
	QImage Image_Map(":/Resources/image.jpg");
	Image_Map = Image_Map.scaled(QSize(MAP_WIDTH, MAP_HEIGHT),Qt::KeepAspectRatio);// add Qt::KeepAspectRatio in argument to keep the picture ratio.
	ui.Label_Map->setPixmap(QPixmap::fromImage(Image_Map));
		
	
	//GameTime(Recorder) Setup
	GameTime = new QTime(0, 0, 0, 0);



	//GameTimer Setup
	GameTimer = new QTimer(this);
	connect(GameTimer, SIGNAL(timeout()), this, SLOT(Tick()));
	GameTimer->setInterval(UPDATE_PER_MS);

	test.move(-30, 18);
}

void MainForm::paintEvent(QPaintEvent *event) {



//Initialize Canvas
		QPixmap Canvas_Battlefield(MAP_WIDTH, MAP_HEIGHT);
		Canvas_Battlefield.fill(QColor("transparent"));

//Initialize Painter
		QPainter painter(&Canvas_Battlefield);
		painter.setPen(QColor("green"));



//Modifications to Canvas
		/*
		static int h = 0;
		static int s = 255;
		static int v = 120;
		if (h >= 360) h = 0;
		QColor test;
		test.setHsl(h += 1, s, v);*/



		//ground




		//vessel

			/*test*/
			QPixmap pixmap(":/Resources/BB.png");
			pixmap = pixmap.scaled(BATTLE_SHIP_WIDTH, BATTLE_SHIP_HEIGHT);
			QMatrix rm;
			rm.rotate(-1*this->test.angle);
			pixmap = pixmap.transformed(rm);
			painter.drawPixmap(this->test.Location.x * (MAP_WIDTH / MAP_INTERVALS) - BATTLE_SHIP_WIDTH/2, this->test.Location.y * (MAP_HEIGHT / MAP_INTERVALS) - BATTLE_SHIP_HEIGHT/2, pixmap);
			/*test*/


		//missle







		//Draw Line
		painter.setPen(QColor("white"));
		double per_width = MAP_WIDTH / MAP_INTERVALS;
		double per_height = MAP_HEIGHT / MAP_INTERVALS;
		for (int i = 0; i < MAP_INTERVALS; i++) {
			painter.drawLine(
				0,
				i*per_height,
				MAP_WIDTH,
				i*per_height
			);
		}
		for (int i = 0; i < MAP_INTERVALS; i++) {
			painter.drawLine(
				i*per_width,
				0,
				i*per_width,
				MAP_HEIGHT
			);
		}


//Render Canvas+
		ui.Label_Battlefield->setPixmap(Canvas_Battlefield);
}

void MainForm::Tick() {
	round += 1;
	//map.tick();
	test.tick();
	if (round == (1000.0 / UPDATE_PER_MS)) {
		round = 0;
		//update GameTime
		*GameTime = GameTime->addSecs(15);
		qDebug() << GameTime->toString("hh:mm:ss");
		ui.Label_GameTime->setText(GameTime->toString("hh:mm:ss"));
		//map.render();
	}
	
}

void  MainForm::on_startButton_clicked() {

	if (ui.TextBox_CommandA->toPlainText().length() != 0) {
		qDebug() << "A have content:\n" << ui.TextBox_CommandA->toPlainText();
	}
	if (ui.TextBox_CommandB->toPlainText().length() != 0) {
		qDebug() << "B have content:\n"<< ui.TextBox_CommandB->toPlainText();
	}

	//Reset TextBox_Commands
	ui.TextBox_CommandA->clear();
	ui.TextBox_CommandA->setEnabled(false);
	ui.TextBox_CommandB->clear();
	ui.TextBox_CommandB->setEnabled(false);

	GameTimer->start();
}

void  MainForm::on_stopButton_clicked() {
	GameTimer->stop();
	ui.TextBox_CommandB->setEnabled(true);
	ui.TextBox_CommandA->setEnabled(true);
}