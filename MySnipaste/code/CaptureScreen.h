#pragma once
#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QGuiApplication>
#include <QPoint>

enum PressState
{
	NONE,
	MOVE,

};

class CaptureScreen : public QWidget
{
	Q_OBJECT
public:
	CaptureScreen(QWidget* parent = Q_NULLPTR);
	~CaptureScreen();

	void initWindow();
	void loadBackgroundPixmap();
//方法函数
public:
	QRect getRect(const QPoint &beginPoint, const QPoint &endPoint);
	void close();
	bool isPointContains(QPoint curPos);
signals:
	void signalScreenQuit();
	void signalFinishedCapture(QPixmap cap);
protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent * event);
	void mouseReleaseEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent* event);
	void paintEvent(QPaintEvent *painter);

private:
	QPixmap m_screenPixmap, m_capturePixmap;
	int m_screenwidth, m_screenheight;
	QPainter m_painter;
	//QPoint m_moveStartPoint,m_moveEndPoint;
	QPoint m_beginPoint, m_endPoint;
	QPoint m_moveBeginPoint, m_moveEndPoint;
	//QPoint m_initBeginPoint, m_initEndPoint;
	QRect m_moveSelectRect;
	bool m_isPressed;
	//bool m_isFinished;
	PressState m_state;
};