#include "mainform.h"
#include <QtDebug>
#include <qpainter.h>
#include <qmovie.h>
#include <qbitmap.h>
#include <cstdlib>
#include <cctype>
#include <strstream>
#include <sstream>


MainForm::MainForm(QWidget *parent)
	: QMainWindow(parent)
{
	//UI Setup
	ui.setupUi(this);
	setFixedSize(geometry().width(), geometry().height());
	ui.Label_Battlefield->setStyleSheet("border: 1px solid black");
	ui.Label_Map->setFixedSize(MAP_WIDTH, MAP_HEIGHT);
	ui.Label_Battlefield->setFixedSize(MAP_WIDTH, MAP_HEIGHT);

	//Label_Map Setup
	QImage Image_Map("./Resources/image.jpg");
	Image_Map = Image_Map.scaled(MAP_WIDTH, MAP_HEIGHT);// add Qt::KeepAspectRatio in argument to keep the picture ratio.
	ui.Label_Map->setPixmap(QPixmap::fromImage(Image_Map));
		
	//BAK
	QPixmap bkgnd("./Resources/background.png");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Background, bkgnd);
	this->setPalette(palette);
	//

	//LABEL
	ui.Label_CommandA->setStyleSheet("QLabel{color: white; }");
	ui.Label_CommandB->setStyleSheet("QLabel{color: white; }");
	ui.Label_GameTime->setStyleSheet("QLabel{color: white; }");
	ui.Label_BattleLog->setStyleSheet("QLabel{color: white; }");
	//======
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
	for (int i = 0, j = BF.BattleLog_TEXT.size(); i < j; i++) {
		ui.TextBox_BattleLog->append((TIME_MESSAGE + BF.BattleLog_TEXT[i]).c_str());
	}
	BF.BattleLog_TEXT.clear();
}

void  MainForm::on_startButton_clicked() {

	if (ui.TextBox_CommandA->toPlainText().length() != 0) {
		qDebug() << "A have content:\n" << ui.TextBox_CommandA->toPlainText();
		//分析
		analyze(ui.TextBox_CommandA->toPlainText().toStdString(),0);
	}
	if (ui.TextBox_CommandB->toPlainText().length() != 0) {
		qDebug() << "B have content:\n"<< ui.TextBox_CommandB->toPlainText();
		analyze(ui.TextBox_CommandB->toPlainText().toStdString(), 1);
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
		QPen circle_pen;
		circle_pen.setColor("red");
		circle_pen.setWidth(3);
		painter.setPen(circle_pen);
		double WarningRadius = Distance_2D(ms.Location.to_2D(), ms.Destination.to_2D());
		if (WarningRadius > 3.0) { WarningRadius = 3.0; }

		painter.drawEllipse(
			ms.Destination.x* (MAP_WIDTH / MAP_INTERVALS)- WarningRadius/2* (MAP_WIDTH / MAP_INTERVALS),
			ms.Destination.y* (MAP_WIDTH / MAP_INTERVALS)- WarningRadius/2* (MAP_WIDTH / MAP_INTERVALS),
			WarningRadius* (MAP_WIDTH / MAP_INTERVALS), WarningRadius* (MAP_WIDTH / MAP_INTERVALS)
		);

	}

//Pen Resume
	painter.setPen(pen_saved);
}

inline void MainForm::renderEffects(QPainter& painter) {
	QPen  pen_saved = painter.pen();

	//LINE
	QPen pen_lazer;
	for (int i = 0, j = BF.EFFECT[EFFECTS::EF_LINE].size(); i < j; i++) {
		LineEffect & ef = *(LineEffect*)BF.EFFECT[EFFECTS::EF_LINE][i];
		pen_lazer.setWidth(ef.width);
		pen_lazer.setColor(ef.color);
		painter.setPen(pen_lazer);
		painter.drawLine(
			ef.Location.x*(MAP_WIDTH / MAP_INTERVALS),
			ef.Location.y*(MAP_HEIGHT / MAP_INTERVALS),
			ef.Destination.x*(MAP_WIDTH / MAP_INTERVALS),
			ef.Destination.y*(MAP_HEIGHT / MAP_INTERVALS));
	}


	//ROUND SHRINK
	for (int i = 0, j = BF.EFFECT[EFFECTS::EF_ROUND_SHRINK].size(); i < j; i++) {

	    RoundShrink & ef = *(RoundShrink*)BF.EFFECT[EFFECTS::EF_ROUND_SHRINK][i];

		QPixmap cp_ex = ARRAY_PICS[ef.PicSerial()]->scaled(
			ef.radius * 2 * (MAP_WIDTH / MAP_INTERVALS),
			ef.radius * 2 * (MAP_HEIGHT / MAP_INTERVALS)
		);
	

		double width_deviation = cp_ex.width() / 2.0;
		double height_deviation = cp_ex.height() / 2.0;

		painter.drawPixmap(ef.Location.x * (MAP_WIDTH / MAP_INTERVALS) - width_deviation,
					       ef.Location.y * (MAP_HEIGHT / MAP_INTERVALS) - height_deviation,
						   cp_ex);
	}

	//ROUND EXPAND
	for (int i = 0, j = BF.EFFECT[EFFECTS::EF_ROUND_EXPAND].size(); i < j; i++) {

		RoundExpand & ef = *(RoundExpand*)BF.EFFECT[EFFECTS::EF_ROUND_EXPAND][i];

		QPixmap cp_ex = ARRAY_PICS[ef.PicSerial()]->scaled(
			ef.radius * 2 * (MAP_WIDTH / MAP_INTERVALS),
			ef.radius * 2 * (MAP_HEIGHT / MAP_INTERVALS)
		);


		double width_deviation = cp_ex.width() / 2.0;
		double height_deviation = cp_ex.height() / 2.0;

		painter.drawPixmap(ef.Location.x * (MAP_WIDTH / MAP_INTERVALS) - width_deviation,
			ef.Location.y * (MAP_HEIGHT / MAP_INTERVALS) - height_deviation,
			cp_ex);
	}
	painter.setPen(pen_saved);
}

inline void MainForm::renderLine(QPainter& painter) {
//Setup Pen for line
	QPen  pen_saved = painter.pen();
	painter.setPen(QColor(0, 0, 0, 60));
	
	double per_width = MAP_WIDTH / MAP_INTERVALS;
	double per_height = MAP_HEIGHT / MAP_INTERVALS;
	for (int i = 1; i < MAP_INTERVALS; i++) {
		painter.drawLine(
			0,
			i*per_height,
			MAP_WIDTH,
			i*per_height
		);
	}
	for (int i = 1; i < MAP_INTERVALS; i++) {
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


//分析功能
void MainForm::analyze(string textBox_String,int team) {
	stringstream in(textBox_String);
	string buffer;
	while (getline(in, buffer))
	{
		setBuffer(buffer);
		stringstream command(buffer);
		string mod;
		command >> mod;
		 if (mod == COMMAND_SET) {
			string vessel_name, vessel_type;
			double twoDx, twoDy;
			command >> vessel_name >> vessel_type>>twoDx>>twoDy;

			if (twoDx == 20.0)twoDx = 19.9; else if (twoDx == 0.0) twoDx = 0.1;
			if (twoDy == 20.0)twoDy = 19.9; else if (twoDy == 0.0) twoDy = 0.1;
			_2D loc{ twoDx,twoDy };
			BF.addVessel(team,vessel_type,vessel_name,loc);
		}
		else if (mod == COMMAND_FIRE) {
			string trigger, atkType;
			command >> trigger >> atkType;

			if (atkType == ATTACK_MISSILE) {
				double x = -1; command >> x;
				double y = -1; command >> y;
				_2D loc(x, y);
				BF.fireMissile(team, trigger, atkType, loc);
			}
			else if (atkType == ATTACK_TRACKER) {
				string target;
				command >> target;
				BF.fireMissile(team, trigger, atkType, target);
			}
			else {
				///////
			}
		}
		else if (mod == COMMAND_DEFENSE) {
			string trigger, defType;
			command >> trigger >> defType;

			if (defType == DEFENSE_LAZER) {
				string shellname;
				command >> shellname;
				BF.defenseMissile(team, trigger, defType, shellname);
			}
			else if (defType == DEFENSE_NOVA) {
				BF.defenseMissile(team, trigger, defType);
			}
			else {
				///
			}
		}
		else if (mod == COMMAND_TAG) {
			string  Pname, Nname;
			command >> Pname>> Nname;
			BF.tagVessel(team,Pname,Nname);
		}
		else if (mod == COMMAND_MOVE) {
			string vessel_name;
			double speed, angle;
			command >> vessel_name >> speed >> angle;
			BF.moveVessel(team,vessel_name,angle,speed);
		}
		else if (mod == COMMAND_ULT) {
			string V_name;
			command >> V_name;
			BF.ULT(team, V_name);
		}
		else if (mod == COMMAND_SPECIAL) {
			BF.Special(team);
		}
		else {
		}
	}
}



inline void MainForm::createPics() {

	//remember to set pic size
	ARRAY_PICS[PICS::PIC_NON] = new QPixmap("./Resources/NON.png");
	ARRAY_PICS[PICS::PIC_BB] = new QPixmap("./Resources/BB.png"); *(ARRAY_PICS[PICS::PIC_BB]) = ARRAY_PICS[PICS::PIC_BB]->scaled(BATTLE_SHIP_WIDTH, BATTLE_SHIP_HEIGHT);
	ARRAY_PICS[PICS::PIC_CV] = new QPixmap("./Resources/CV.png"); *(ARRAY_PICS[PICS::PIC_CV]) = ARRAY_PICS[PICS::PIC_CV]->scaled(BATTLE_SHIP_WIDTH, BATTLE_SHIP_HEIGHT);
	ARRAY_PICS[PICS::PIC_DD] = new QPixmap("./Resources/DD.png"); *(ARRAY_PICS[PICS::PIC_DD]) = ARRAY_PICS[PICS::PIC_DD]->scaled(BATTLE_SHIP_WIDTH, BATTLE_SHIP_HEIGHT);
	ARRAY_PICS[PICS::PIC_CG] = new QPixmap("./Resources/CG.png"); *(ARRAY_PICS[PICS::PIC_CG]) = ARRAY_PICS[PICS::PIC_CG]->scaled(BATTLE_SHIP_WIDTH, BATTLE_SHIP_HEIGHT);
	ARRAY_PICS[PICS::PIC_ATK_MS] = new QPixmap("./Resources/MS.png"); *(ARRAY_PICS[PICS::PIC_ATK_MS]) = ARRAY_PICS[PICS::PIC_ATK_MS]->scaled(MISSILE_WIDTH, MISSILE_HEIGHT);
	ARRAY_PICS[PICS::PIC_ATK_TRACKER] = new QPixmap("./Resources/TRACKER.png");  *(ARRAY_PICS[PICS::PIC_ATK_TRACKER]) = ARRAY_PICS[PICS::PIC_ATK_TRACKER]->scaled(MISSILE_WIDTH, MISSILE_HEIGHT);

	ARRAY_PICS[PICS::PIC_MS_EX] = new QPixmap("./Resources/EX.png");
	ARRAY_PICS[PICS::PIC_DEF_NOVA] = new QPixmap("./Resources/NOVA.png");
}