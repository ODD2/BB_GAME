#include "mainform.h"
#include <QtDebug>
#include <qpainter.h>
#include <qmovie.h>
#include <qbitmap.h>
#include<strstream>


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
void MainForm::analyze(string command,int team) {
	strstream in;
	in << command;
	string buffer;
	string type[COMMAND_TYPES] = { "SET","FIRE","DEFENSE","TAG","MOVE","ULT"};
	while (getline(in,buffer))
	{
		int mod=-1,at=-1,at2=-1;
		while (buffer[0] == ' ')buffer.erase(0, 1);
		while (buffer[buffer.length()-1] == ' ')buffer.pop_back();
		int white = buffer.find("  ");
		while (white!=-1) {
			buffer.erase(white, 1);
			white = buffer.find("  ");
		}
		for (int i = 0; i < COMMAND_TYPES; i++) {
			at = buffer.find(type[i]);
			if (at == 0) {
				mod = i;
				break;
			}			
		}
		if (mod == 0) {
			string vessel_name, vessel_type, twoDX, twoDY;
			at = buffer.find(' ');
			at2 = buffer.find(' ', at + 1);
			if (!checkText(at, at2))break;
			vessel_name.assign(buffer.begin() + at + 1, buffer.begin() + at2);
			at = buffer.find('(', at2 + 1);
			if (!checkText(at, at2))break;
			vessel_type.assign(buffer.begin() + at2 + 1, buffer.begin() + at - 1);
			at = buffer.find('(');
			at2 = buffer.find(',');
			if (!checkText(at, at2))break;
			twoDX.assign(buffer.begin() + at + 1, buffer.begin() + at2);
			at = buffer.find(')', at2 + 1);
			if (!checkText(at, at2))break;
			twoDY.assign(buffer.begin() + at2 + 1, buffer.begin() + at);
			double x = stod(twoDX);
			if (x == 20.0)x = 19.9; else if (x == 0.0) x = 0.1;
			double y=stod(twoDY);
			if (y == 20.0)y = 19.9; else if (y == 0.0) y = 0.1;
			_2D loc{x,y};
			string log = "Team";
			log.push_back(team + 'A');
			if (BF.addVessel(team, vessel_type, vessel_name, loc)) {
				log += " SET " + vessel_name + " with " + vessel_type + " at(" + twoDX + "," + twoDY + ")->Success";
			}
			else {
				log += " SET " + vessel_name + " with " + vessel_type + " at(" + twoDX + "," + twoDY + ")->Fail";
			}
			BF.BattleLog_TEXT.push_back(log);
#ifdef Edebug
			string x = "##" + vessel_name + "##" + vessel_type + "##" + twoDX + "##" + twoDY + "##";
			ui.Label_debug->setText(QString::fromStdString(x));
#endif // Edebug
		}
		else if (mod == 1) {
			string vessel_name, twoDX, twoDY;
			at = buffer.find(' ');
			at2 = buffer.find(' ',at+1);
			if (!checkText(at, at2))break;
			vessel_name.assign(buffer.begin() + at + 1, buffer.begin() + at2);
			at = buffer.find('(', at2 + 1);
			at2 = buffer.find(',',at+1);
			if (!checkText(at, at2))break;
			twoDX.assign(buffer.begin() + at + 1, buffer.begin() + at2);
			at = buffer.find(')', at2 + 1);
			if (!checkText(at, at2))break;
			twoDY.assign(buffer.begin() + at2+1, buffer.begin() + at);
			_2D loc{ stod(twoDX),stod(twoDY) };
			if (!BF.fireMissile(team,vessel_name, loc,team)) {
				string log = "Team";
				log.push_back(team + 'A');
				log += " " + vessel_name + " Fire to (" + twoDX + "," + twoDY + ")-> Fail"  ;
				BF.BattleLog_TEXT.push_back(log);
			}
			
#ifdef Edebug
			string x = "##" + vessel_name + "##" + twoDX + "##"+twoDY+"##";
			ui.Label_debug->setText(QString::fromStdString(x));

#endif // Edebug
		}
		else if (mod == 2) {
			string vessel_name,shellname;
			at = buffer.find(' ');
			at2 = buffer.find(' ', at + 1);
			if (!checkText(at, at2))break;
			vessel_name.assign(buffer.begin() + at + 1, buffer.begin() + at2);
			shellname.assign(buffer.begin() + at2 + 1, buffer.end());
			if (BF.defenseMissile(team,vessel_name, shellname)) {
				string log = vessel_name+" DEFENSE "+shellname+" -> Hit" ;
				BF.BattleLog_TEXT.push_back(log);
			}
			else {
				string log = vessel_name + " DEFENSE " + shellname + " -> Fail";
				BF.BattleLog_TEXT.push_back(log);
			}
			
#ifdef Edebug
			string x = "##" + vessel_name + "##" + shellname + "##";
			ui.Label_debug->setText(QString::fromStdString(x));
#endif // Edebug
		}
		else if (mod == 3) {
			string log = "Team";
			log.push_back(team + 'A');
			string vessel_name, newname;
			at = buffer.find(' ');
			at2 = buffer.find(' ', at + 1);
			if (!checkText(at, at2))break;
			vessel_name.assign(buffer.begin() + at + 1, buffer.begin() + at2);
			newname.assign(buffer.begin()+at2+1,buffer.end());
			if (BF.tagVessel(team,vessel_name, newname)) {
				log += " RENAME " + vessel_name + " to " + newname + " -> Success";
			}
			else {
				log += " RENAME " + vessel_name + " to " + newname + " -> Fail";
			}
			BF.BattleLog_TEXT.push_back(log);
#ifdef Edebug
			string x = "##" + vessel_name + "##" + newname + "##" ;
			ui.Label_debug->setText(QString::fromStdString(x));
#endif // Edebug
		}
		else if (mod==4) {
			string vessel_name,speed,angle;
			at = buffer.find(' ');
			at2 = buffer.find(' ', at + 1);
			if (!checkText(at, at2))break;
			vessel_name.assign(buffer.begin() + at + 1, buffer.begin() + at2);
			at = buffer.find(' ', at2 + 1);
			if (!checkText(at, at2))break;
			speed.assign(buffer.begin()+at2+1, buffer.begin()+at);
			angle.assign(buffer.begin()+at+1  , buffer.end());
			string log = "Team";
			log.push_back(team + 'A');
			if (BF.moveVessel(team,vessel_name, stod(angle), stod(speed))) {
				log += " " + vessel_name + " MOVE to " + angle + " as " + speed + "->Success";	
			}
			else {
				log += " " + vessel_name + " MOVE to " + angle + " as " + speed + "->Fail";
			}
			BF.BattleLog_TEXT.push_back(log);
#ifdef Edebug
			string x = "##" + vessel_name + "##" + speed + "##"+angle+"##";
			ui.Label_debug->setText(QString::fromStdString(x));
#endif // Edebug
		}
		else if (mod == 5) {
			at = buffer.find(' ');
			if (!checkText(at,0))break;
			string V_name;
			V_name.assign(buffer.begin()+at+1,buffer.end());
			BF.ULT(team,V_name);
			string log = V_name + " use ULT";
			BF.BattleLog_TEXT.push_back(log);
		}else{

#ifdef Edebug
			string x = "COMMAND FAIL";
			ui.Label_debug->setText(QString::fromStdString(x));
#endif // Edebug
		}
	}
}

bool MainForm::checkText(int at, int at2) {
	if (at == -1) {
		return false;
	}
	else if (at2 == -1) {
		return false;
	}
	return true;
}

inline void MainForm::createPics() {

	//remember to set pic size
	ARRAY_PICS[PICS::PIC_NON] = new QPixmap("./Resources/NON.png");
	ARRAY_PICS[PICS::PIC_BB] = new QPixmap("./Resources/BB.png"); *(ARRAY_PICS[PICS::PIC_BB]) = ARRAY_PICS[PICS::PIC_BB]->scaled(BATTLE_SHIP_WIDTH, BATTLE_SHIP_HEIGHT);
	ARRAY_PICS[PICS::PIC_CV] = new QPixmap("./Resources/CV.png"); *(ARRAY_PICS[PICS::PIC_CV]) = ARRAY_PICS[PICS::PIC_CV]->scaled(BATTLE_SHIP_WIDTH, BATTLE_SHIP_HEIGHT);
	ARRAY_PICS[PICS::PIC_DD] = new QPixmap("./Resources/DD.png"); *(ARRAY_PICS[PICS::PIC_DD]) = ARRAY_PICS[PICS::PIC_DD]->scaled(BATTLE_SHIP_WIDTH, BATTLE_SHIP_HEIGHT);
	ARRAY_PICS[PICS::PIC_CG] = new QPixmap("./Resources/CG.png"); *(ARRAY_PICS[PICS::PIC_CG]) = ARRAY_PICS[PICS::PIC_CG]->scaled(BATTLE_SHIP_WIDTH, BATTLE_SHIP_HEIGHT);
	ARRAY_PICS[PICS::PIC_MS] = new QPixmap("./Resources/MS.png"); *(ARRAY_PICS[PICS::PIC_MS]) = ARRAY_PICS[PICS::PIC_MS]->scaled(MISSILE_WIDTH, MISSILE_HEIGHT);
	ARRAY_PICS[PICS::PIC_MS_EX] = new QPixmap("./Resources/EX.png");
}