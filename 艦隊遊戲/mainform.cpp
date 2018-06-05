#include "mainform.h"
#include <QtDebug>

MainForm::MainForm(QWidget *parent)
	: QMainWindow(parent)
{
	//UI Setup
	ui.setupUi(this);
	setFixedSize(geometry().width(), geometry().height());

	//Label_Map Setup
	QImage Image_Map(":/Resources/image.jpg");
	Image_Map = Image_Map.scaled(QSize(ui.Label_Map->width(), ui.Label_Map->height()),Qt::KeepAspectRatio);
	ui.Label_Map->setPixmap(QPixmap::fromImage(Image_Map));


	
	//GameTime(Recorder) Setup
	GameTime = new QTime(0, 0, 0, 0);





	//GameTimer Setup
	GameTimer = new QTimer(this);
	connect(GameTimer, SIGNAL(timeout()), this, SLOT(Tick()));
	GameTimer->setInterval(1000);
}


void MainForm::Tick() {
	//update GameTime
	*GameTime = GameTime->addSecs(15);
	qDebug() << GameTime->toString("hh:mm:ss");
	ui.Label_GameTime->setText(GameTime->toString("hh:mm:ss"));

	//map.tick();
	
	//map.render();
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