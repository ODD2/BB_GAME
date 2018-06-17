#include "mainform.h"
#include <QtDebug>
#include <qpainter.h>
#include <qmovie.h>
#include <qbitmap.h>
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
	QImage Image_Map("./Resources/image.png");
	Image_Map = Image_Map.scaled(MAP_WIDTH, MAP_HEIGHT);// add Qt::KeepAspectRatio in argument to keep the picture ratio.
	ui.Label_Map->setPixmap(QPixmap::fromImage(Image_Map));
		
	
	//GameTime(Recorder) Setup
	GameTime = new QTime(0, 0, 0, 0);



	//GameTimer Setup
	GameTimer = new QTimer(this);
	connect(GameTimer, SIGNAL(timeout()), this, SLOT(Tick()));
	GameTimer->setInterval(UPDATE_PER_MS);

	//Picture Setup
	createPics();
}

void MainForm::paintEvent(QPaintEvent *event) {

//Initialize Canvas
		QPixmap Canvas_Battlefield(MAP_WIDTH, MAP_HEIGHT);
		Canvas_Battlefield.fill(QColor("transparent"));

//Initialize Painter
		QPainter painter(&Canvas_Battlefield);

	
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
		renderVessle(painter);
		//missle
		renderMissile(painter);
		//effect
		renderEffects(painter);

		//line
		renderLine(painter);
	

//Render Canvas
		ui.Label_Battlefield->setPixmap(Canvas_Battlefield);
}

void MainForm::Tick() {
//BattleField TickEvent
	BF.Tick();


//update GameTime
	*GameTime = GameTime->addMSecs(PER_SECOND_IN_GAME*UPDATE_PER_MS);
	ui.Label_GameTime->setText(GameTime->toString("hh:mm:ss"));

//Battle Log Update
	string TIME_MESSAGE = "[" + GameTime->toString("hh:mm:ss").toStdString() + "]";
	while (BF.BattleLog_TEXT.size()) {
		ui.TextBox_BattleLog->append(  (TIME_MESSAGE + BF.BattleLog_TEXT.back()).c_str() );
		BF.BattleLog_TEXT.pop_back();
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

inline void MainForm::renderVessle(QPainter& painter) {
//Setup Pen for TEXT
	QPen pen_text;
	pen_text.setWidth(TEXT_PIXEL);
	pen_text.setBrush(QBrush("black"));
	QPen pen_saved = painter.pen();
	painter.setPen(pen_text);

//Object Render + Text Render
	for (int i = 0; i < NUM_TEAM; i++) {
		map<string, vessel*>::iterator it = BF.TEAM[i].begin();
		for (; it != BF.TEAM[i].end(); it++) {
			//picture modification.
			QMatrix rm;
			vessel& vs = *(it->second);
			rm.rotate(-1 * vs.angle);
			QPixmap px_tmp = ARRAY_PICS[vs.PicSerial()]->transformed(rm);

			//string modification.
			string vessel_location = vs.Location.operator std::string();


			double width_deviation = (double)px_tmp.width() / 2;
			double height_deviation = (double)px_tmp.height() / 2;

			//draw vessel
			painter.drawPixmap(
				vs.Location.x * (MAP_WIDTH / MAP_INTERVALS) - width_deviation,
				vs.Location.y * (MAP_HEIGHT / MAP_INTERVALS) - height_deviation,
				px_tmp
			);


			////write vessel name
			//painter.drawText(
			//	vs.Location.x * (MAP_WIDTH / MAP_INTERVALS) - width_deviation,
			//	vs.Location.y * (MAP_HEIGHT / MAP_INTERVALS) - height_deviation,
			//	vs.name.c_str()
			//);


			//


			////write vessel location
			//painter.drawText(
			//	vs.Location.x * (MAP_WIDTH / MAP_INTERVALS) - width_deviation,
			//	vs.Location.y * (MAP_HEIGHT / MAP_INTERVALS) + height_deviation + TEXT_PIXEL,
			//	vessel_location.c_str()
			//);

		}
	}

//Pen Resume
	painter.setPen(pen_saved);
}

inline void MainForm::renderMissile(QPainter& painter) {
//Setup Pen for TEXT
	QPen pen_text;
	pen_text.setWidth(TEXT_PIXEL);
	pen_text.setBrush(QBrush("black"));
	QPen pen_saved = painter.pen();
	painter.setPen(pen_text);

//Object Render + Text Render
	for (int i = 0, limit = BF.MISSILE.size(); i < limit; i++) {
		//picture modification.
		QMatrix rm;
		missile & ms = *(BF.MISSILE[i]);
		rm.rotate(-1 * ms.angle);
		QPixmap px_tmp = ARRAY_PICS[ms.PicSerial()]->transformed(rm);


		//string modification.
		string missile_location = ms.Location.to_2D().operator std::string();


		double width_deviation = (double)px_tmp.width() / 2;
		double height_deviation = (double)px_tmp.height() / 2;


		//draw  missile
		painter.drawPixmap(
			ms.Location.x * (MAP_WIDTH / MAP_INTERVALS) - width_deviation,
			ms.Location.y * (MAP_HEIGHT / MAP_INTERVALS) - height_deviation,
			px_tmp);

		////write vessel location
		//painter.drawText(
		//	ms.Location.x * (MAP_WIDTH / MAP_INTERVALS) - width_deviation,
		//	ms.Location.y * (MAP_HEIGHT / MAP_INTERVALS) + height_deviation + TEXT_PIXEL,
		//	missile_location.c_str());

	}

//Pen Resume
	painter.setPen(pen_saved);
}

inline void MainForm::renderEffects(QPainter& painter) {

	for (int i = 0, j = BF.EFFECT.size(); i < j; i++) {

	    explosion & exp = *(BF.EFFECT[i]);

		QPixmap cp_ex = ARRAY_PICS[exp.PicSerial()]->scaled(
			exp.radius * 2 * (MAP_WIDTH / MAP_INTERVALS),
			exp.radius * 2 * (MAP_HEIGHT / MAP_INTERVALS)
		);
	

		double width_deviation = cp_ex.width() / 2.0;
		double height_deviation = cp_ex.height() / 2.0;

		painter.drawPixmap(exp.Location.x * (MAP_WIDTH / MAP_INTERVALS) - width_deviation,
					       exp.Location.y * (MAP_HEIGHT / MAP_INTERVALS) - height_deviation,
						   cp_ex);
	}

}

inline void MainForm::renderLine(QPainter& painter) {
//Setup Pen for line
	QPen  pen_saved = painter.pen();
	painter.setPen(QColor(0, 0, 0, 60));
	
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

//Pen Resume
	painter.setPen(pen_saved);
}

inline void MainForm::createPics() {

	//remember to set pic size
	ARRAY_PICS[PICS::PIC_NON] = new QPixmap("./Resources/NON.png");
	ARRAY_PICS[PICS::PIC_BB] = new QPixmap("./Resources/BB.png"); *(ARRAY_PICS[PICS::PIC_BB]) = ARRAY_PICS[PICS::PIC_BB]->scaled(BATTLE_SHIP_WIDTH, BATTLE_SHIP_HEIGHT);
	ARRAY_PICS[PICS::PIC_MS] = new QPixmap("./Resources/MS.png"); *(ARRAY_PICS[PICS::PIC_MS]) = ARRAY_PICS[PICS::PIC_MS]->scaled(MISSILE_WIDTH, MISSILE_HEIGHT);
	ARRAY_PICS[PICS::PIC_EX] = new QPixmap("./Resources/EX.png");
}