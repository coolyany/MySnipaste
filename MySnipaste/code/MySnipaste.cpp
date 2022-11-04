#include "MySnipaste.h"
#include <QDebug>

MySnipaste::MySnipaste(QWidget *parent)
	: QMainWindow(parent)
	  //capDlg(nullptr)
{
    ui.setupUi(this);

	this->setWindowTitle("MySnipaste");
	this->setWindowIcon(QIcon(":/MySnipaste/resource/title.png"));
	//ui.label_tip->setText(QStringLiteral("回车键（Enter）确定\n"));
	this->statusBar()->setStyleSheet("QStatusBar::item{border: 0px}");
	//this->statusBar->setToolTip(QStringLiteral("回车键（Enter）确定截图"));
	this->statusBar()->addPermanentWidget(new QLabel("回车键（Enter）确定截图/退出键（Escape）退出截图"));//设置statusBar永久提示部件
	//this->statusBar()->addPermanentWidget(new QLabel("退出键（Escape）退出截图"));//设置statusBar永久提示部件

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
	if (capScn)
	{
		capScn->show();
	}
	else {
		capScn = new CaptureScreen();
		connect(capScn, &CaptureScreen::signalFinishedCapture, this, &MySnipaste::onRecvCapture);
		connect(capScn, &CaptureScreen::signalScreenQuit, this, &MySnipaste::onRecvQuitCapture);

		capScn->show();
	}

}

void MySnipaste::onRecvCapture(QPixmap capmap)
{
	capmap.scaled(ui.label->size(), Qt::KeepAspectRatio);
	ui.label->setScaledContents(true);//铺满label
	ui.label->setPixmap(capmap);
	//capScn->hide();
	disconnect(capScn, &CaptureScreen::signalFinishedCapture, this, &MySnipaste::onRecvCapture);
	delete capScn;
	capScn = nullptr;
}

void MySnipaste::onRecvQuitCapture()
{
	//capScn->hide();
	disconnect(capScn, &CaptureScreen::signalFinishedCapture, this, &MySnipaste::onRecvCapture);
	delete capScn;
	capScn = nullptr;
}
