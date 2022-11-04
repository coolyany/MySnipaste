#include "MySnipaste.h"
#include <QDebug>

MySnipaste::MySnipaste(QWidget *parent)
	: QMainWindow(parent)
	  //capDlg(nullptr)
{
    ui.setupUi(this);

	//QMetaObject::connectSlotsByName(this);
	//capScn = new CaptureScreen();
	connect(ui.pushButton, &QPushButton::clicked, this, &MySnipaste::onStart);
	//connect(capScn, &CaptureScreen::signalFinishedCapture, this, &MySnipaste::onRecvCapture);
}



MySnipaste::~MySnipaste()
{
	if (capScn)
	{
		delete capScn;
		capScn = nullptr;
	}
}

void MySnipaste::onStart()
{
	//if (capDlg)
	//{
	//	capDlg->show();
	//}
	//else {
	//	capDlg = new CaptureDlg(this);

	//	capDlg->show();
	//}
	if (capScn)
	{
		capScn->show();
	}
	else {
		capScn = new CaptureScreen();
		connect(capScn, &CaptureScreen::signalFinishedCapture, this, &MySnipaste::onRecvCapture);
		capScn->show();
	}

}

void MySnipaste::onRecvCapture(QPixmap capmap)
{
	capmap.scaled(ui.label->size(), Qt::KeepAspectRatio);
	ui.label->setScaledContents(true);
	ui.label->setPixmap(capmap);
	capScn->hide();
	disconnect(capScn, &CaptureScreen::signalFinishedCapture, this, &MySnipaste::onRecvCapture);
	delete capScn;
	capScn = nullptr;
}
