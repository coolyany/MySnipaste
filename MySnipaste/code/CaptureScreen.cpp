#include "CaptureScreen.h"
#include <QDebug>
#include <QMouseEvent>

CaptureScreen::CaptureScreen(QWidget* parent)
	:QWidget(parent),
	m_isPressed(false),
	m_state(NONE)
{
	initWindow();
}

CaptureScreen::~CaptureScreen()
{
}

void CaptureScreen::initWindow()
{
	this->setMouseTracking(true);
	this->setWindowFlags(Qt::FramelessWindowHint);//设置无边框
	setWindowState(Qt::WindowActive | Qt::WindowFullScreen);//全屏

	loadBackgroundPixmap();
}

void CaptureScreen::loadBackgroundPixmap()
{
	QDesktopWidget* desk = QApplication::desktop();
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
	m_screenPixmap = QPixmap::grabWindow(desk->winId());
#else if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
	QScreen *screen = QGuiApplication::primaryScreen();
	m_screenPixmap = screen->grabWindow(desk->winId());
#endif
	m_screenwidth = m_screenPixmap.width();
	m_screenheight = m_screenPixmap.height();

	qDebug() << "m_screenwidth :: " << m_screenwidth
		<< "m_screenheight :: " << m_screenheight;
}

QRect CaptureScreen::getRect(const QPoint &beginPoint, const QPoint &endPoint)
{
	int x, y, width, height;
	//获取大小
	width = qAbs(beginPoint.x() - endPoint.x());
	height = qAbs(beginPoint.y() - endPoint.y());
	//获取左上角坐标
	x = beginPoint.x() < endPoint.x() ? beginPoint.x() : endPoint.x();
	y = beginPoint.y() < endPoint.y() ? beginPoint.y() : endPoint.y();
	//获取rect
	QRect selectedRect = QRect(x, y, width, height);

	//避免宽、高为零时出错
	if (selectedRect.width() == 0)
	{
		selectedRect.setWidth(1);
	}
	if (selectedRect.height() == 0)
	{
		selectedRect.setHeight(1);
	}

	return selectedRect;
}

void CaptureScreen::close()
{

}

bool CaptureScreen::isPointContains(QPoint curPos)
{
	QRect selectedRect = getRect(m_beginPoint, m_endPoint);
	if (selectedRect.contains(curPos))
	{
		return true;
	}
	return false;
}

void CaptureScreen::mousePressEvent(QMouseEvent * event)
{
	qDebug() << "********** mousePressEvent ***********";
	if (event->button() == Qt::LeftButton)
	{
		if (isPointContains(event->pos()))
		{
			m_moveBeginPoint = event->pos();
			m_moveEndPoint = event->pos();
			m_state = MOVE;

			//qDebug() << "event->pos() :: " << event->pos();
			//qDebug() << "event->globalPos() :: " << event->globalPos();
			qDebug() << "m_moveBeginPoint  :: " << m_moveBeginPoint;

		}
		else {
			m_beginPoint = event->pos();//记录当前位置
		}
		m_isPressed = true;
		qDebug() << "m_beginPoint :: " << m_beginPoint;
	}
	return QWidget::mousePressEvent(event);
}

void CaptureScreen::mouseMoveEvent(QMouseEvent * event)
{
	//qDebug() << "*********** mouseMoveEvent ***********";
	if (m_isPressed && m_state == NONE)
	{
		m_endPoint = event->pos();
		
		update();
	}
	//当移动时
	else if (m_isPressed && m_state == MOVE)
	{
		/*QPoint curPos = event->pos();
		m_moveEndPoint = curPos;*/
		m_moveEndPoint = event->pos();
		qDebug() << "$$$$$$$$$$$$$$$$$$$$$$$$$$$";
		qDebug() << "event->pos() :: " << event->pos();
		qDebug() << "m_moveEndPoint :: " << m_moveEndPoint;

		//qDebug() << "****************************************";
		//qDebug() << "event->pos() :: " << event->pos();
		//qDebug() << "event->globalPos() :: " << event->globalPos();
		//qDebug() << "m_moveEndPoint :: " << m_moveEndPoint;
		update();
	}
	else if (m_state == NONE)
	{
		if (isPointContains(event->pos()))
		{
			this->setCursor(Qt::SizeAllCursor);
		}
		else {
			this->setCursor(Qt::ArrowCursor);
		}
	}
	return QWidget::mouseMoveEvent(event);
}

void CaptureScreen::mouseReleaseEvent(QMouseEvent * event)
{
	qDebug() << "********** mouseReleaseEvent ***********";
	if (m_state == NONE)
	{
		m_endPoint = event->pos();
		m_isPressed = false;
		qDebug() << "mouseReleaseEvent  m_beginPoint :: " << m_beginPoint;
		qDebug() << "mouseReleaseEvent  m_endPoint :: " << m_endPoint;
		
	}
	else if (m_state == MOVE)
	{
		m_moveEndPoint = event->pos();
		//qDebug() << "m_moveEndPoint :: " << m_moveEndPoint;
		//qDebug() << "m_endPoint :: " << m_endPoint;

		m_isPressed = false;
		m_state = NONE;
	}
	//m_initBeginPoint = m_beginPoint;
	//m_initEndPoint = m_endPoint;
	m_moveSelectRect = getRect(m_beginPoint, m_endPoint);

	return QWidget::mouseReleaseEvent(event);
}

void CaptureScreen::keyPressEvent(QKeyEvent * event)
{
	//退出
	if (event->key() == Qt::Key_Escape)
	{
		emit signalScreenQuit();
	}
	//回车确定
	else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
	{
		emit signalFinishedCapture(m_capturePixmap);
	}
}

void CaptureScreen::paintEvent(QPaintEvent * painter)
{
	//重绘
	m_painter.begin(this);
	m_painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::FlatCap));	//设置画笔
	m_painter.drawPixmap(0, 0, m_screenPixmap);
	QColor shadowColor = QColor(255, 255, 255, 100);
	m_painter.fillRect(m_screenPixmap.rect(), shadowColor);//填充阴影

	//if (m_isPressed && m_state == NONE)
	//{
	//	QRect selectedRect = getRect(m_beginPoint, m_endPoint);
	//	m_capturePixmap = m_screenPixmap.copy(selectedRect);
	//	m_painter.drawPixmap(selectedRect.topLeft(), m_capturePixmap);
	//	m_painter.drawRect(selectedRect);
	//}
	if (m_isPressed && m_state == MOVE)
	{
		int dx = m_moveEndPoint.x() - m_moveBeginPoint.x();
		int dy = m_moveEndPoint.y() - m_moveBeginPoint.y();
		//qDebug() << "dx :: " << dx << " dy :: " << dy;

		int curBeginX = m_moveSelectRect.topLeft().x() + dx;
		int curBeginY = m_moveSelectRect.topLeft().y() + dy;
		int curEndX = m_moveSelectRect.bottomRight().x() + dx;
		int curEndY = m_moveSelectRect.bottomRight().y() + dy;
		//左上方移动
		if (dx < 0 && dy < 0)
		{
			int press_dx = qAbs(m_moveSelectRect.topLeft().x() - m_moveBeginPoint.x());
			int press_dy = qAbs(m_moveSelectRect.topLeft().y() - m_moveBeginPoint.y());
			//边界情况
			if ((press_dx + qAbs(dx)) >= m_moveBeginPoint.x())
			{
				curBeginX = 0;
				curEndX = m_moveSelectRect.width();

			}
			if ((press_dy + qAbs(dy)) >= m_moveBeginPoint.y())
			{
				curBeginY = 0;
				curEndY = m_moveSelectRect.height();
			}
		}
		//左下方移动
		else if (dx < 0 && dy > 0)
		{
			int press_dx = qAbs(m_moveSelectRect.topLeft().x() - m_moveBeginPoint.x());
			int press_dy = qAbs(m_moveSelectRect.bottomRight().y() - m_moveBeginPoint.y());
			//边界情况
			if ((press_dx + qAbs(dx)) >= m_moveBeginPoint.x())
			{
				curBeginX = 0;
				curEndX = m_moveSelectRect.width();
			}
			if ((press_dy + qAbs(dy) + m_moveBeginPoint.y()) >= m_screenheight)
			{
				curEndY = m_screenheight;
				curBeginY = m_screenheight - m_moveSelectRect.height();
			}
		}
		//右下方移动
		else if (dx > 0 && dy > 0)
		{
			int press_dx = qAbs(m_moveSelectRect.bottomRight().x() - m_moveBeginPoint.x());
			int press_dy = qAbs(m_moveSelectRect.bottomRight().y() - m_moveBeginPoint.y());

			//边界情况
			if ((press_dx + qAbs(dx) + m_moveBeginPoint.x()) >= m_screenwidth)
			{
				curEndX = m_screenwidth;
				curBeginX = m_screenwidth - m_moveSelectRect.width();
			}
			if ((press_dy + qAbs(dy) + m_moveBeginPoint.y()) >= m_screenheight)
			{
				curEndY = m_screenheight;
				curBeginY = m_screenheight - m_moveSelectRect.height();
			}
		}
		//右上方移动
		else if (dx > 0 && dy < 0)
		{
			int press_dx = qAbs(m_moveSelectRect.bottomRight().x() - m_moveBeginPoint.x());
			int press_dy = qAbs(m_moveSelectRect.bottomRight().y() - m_moveBeginPoint.y());

			//边界情况
			if ((press_dx + qAbs(dx) + m_moveBeginPoint.x()) >= m_screenwidth)
			{
				curEndX = m_screenwidth;
				curBeginX = m_screenwidth - m_moveSelectRect.width();
			}
			if ((press_dy + qAbs(dy)) >= m_moveBeginPoint.y())
			{
				curBeginY = 0;
				curEndY = m_moveSelectRect.height();
			}
		}
		m_beginPoint.setX(curBeginX);
		m_beginPoint.setY(curBeginY);
		m_endPoint.setX(curEndX);
		m_endPoint.setY(curEndY);
		QPoint tempBegin, tempEnd;
		tempBegin.setX(curBeginX);
		tempBegin.setY(curBeginY);
		tempEnd.setX(curEndX);
		tempEnd.setY(curEndY);
		m_beginPoint = tempBegin;
		m_endPoint = tempEnd;
		QRect tempSelectRect = getRect(tempBegin, tempEnd);

		qDebug() << "****************************************";
		qDebug() << "moved dx :: " << dx;
		qDebug() << "moved dy :: " << dy;

		qDebug() << "moved m_moveBeginPoint :: " << m_moveBeginPoint;
		qDebug() << "moved m_moveEndPoint :: " << m_moveEndPoint;
		qDebug() << "moved 后 tempBegin :: " << tempBegin;
		qDebug() << "moved 后 tempEnd :: " << tempEnd;
		qDebug() << "moved tempSelectRect  :: " << tempSelectRect;
		qDebug() << "moved m_beginPoint  :: " << m_beginPoint;
		qDebug() << "moved m_endPoint  :: " << m_endPoint;

	}

	//qDebug() << "paintEvent  m_beginPoint :: " << m_beginPoint;
	//qDebug() << "paintEvent  m_endPoint :: " << m_endPoint;

	QRect selectedRect = getRect(m_beginPoint, m_endPoint);
	qDebug() << "selectedRect  :: " << selectedRect;

	m_capturePixmap = m_screenPixmap.copy(selectedRect);
	m_painter.drawPixmap(selectedRect.topLeft(), m_capturePixmap);
	m_painter.drawRect(selectedRect);

	m_painter.end();
}