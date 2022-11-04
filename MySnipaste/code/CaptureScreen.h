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
	STRETCH
};

enum CursorStyle 
{
	ALLCUR,
	VERCUR,
	HORCUR,
	RDIAGCUR,
	LDIAGCUR,
	NONECUR
};

class CaptureScreen : public QWidget
{
	Q_OBJECT
public:
	CaptureScreen(QWidget* parent = Q_NULLPTR);
	~CaptureScreen();

	void initWindow();
	void initStretchRect();
	void loadBackgroundPixmap();
//方法函数
public:
	QRect getRect(const QPoint &beginPoint, const QPoint &endPoint);
	void close();
	bool isTooSmall(QRect rect);
	//void setSelectStretchRect(QRect rect);

	bool isPointContains(QPoint curPos);//判断是否在截图框内
	//CursorStyle isStretchPointContains(QPoint curPos);//判断是否在截图框的边界
	CursorStyle getCursorStyle(QPoint curPos);//判断鼠标在截图框的位置
	
	void drawMoveRect(QRect rect);
	void drawinitStretchRect(QRect rect);
	void drawStretchRect(QRect rect);
signals:
	void signalScreenQuit();
	void signalFinishedCapture(QPixmap cap);
protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent * event);
	void mouseReleaseEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent* event);
	void paintEvent(QPaintEvent *event);

private:
	QPixmap m_screenPixmap, m_capturePixmap;
	int m_screenwidth, m_screenheight;
	QPainter m_painter;
	//QPoint m_moveStartPoint,m_moveEndPoint;
	QPoint m_beginPoint, m_endPoint;
	QPoint m_curPressBeginPoint, m_curPressEndPoint;
	//QPoint m_initBeginPoint, m_initEndPoint;
	QRect m_SelectRect;//当前选中的截图框
	QRect m_initSelectRect;
	bool m_isPressed;
	//bool m_isFinished;
	PressState m_state;

	QRect m_topLeftStretchRect;
	QRect m_topRightStretchRect;
	QRect m_bottomLeftStretchRect;
	QRect m_bottomRightStretchRect;
	QRect m_leftCenterStretchRect;
	QRect m_topCenterStretchRect;
	QRect m_rightCenterStretchRect;
	QRect m_bottomCenterStretchRect;

	CursorStyle m_cursorStyle = NONECUR;
};