#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MySnipaste.h"
//#include "capturing_dialog.h"
//#include "CaptureDlg.h"
#include "CaptureScreen.h"

class MySnipaste : public QMainWindow
{
    Q_OBJECT

public:
    MySnipaste(QWidget *parent = Q_NULLPTR);
	~MySnipaste();

//public slots:
	void onStart();
	void onRecvCapture(QPixmap capmap);
	void onRecvQuitCapture();
private:
    Ui::MySnipasteClass ui;

	//CapturingDialog* capDlg;
	//CaptureDlg* capDlg = nullptr;
	CaptureScreen* capScn = nullptr;
};
