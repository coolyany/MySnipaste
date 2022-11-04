#include "CaptureScreen.h"
#include <QDebug>
#include <QMouseEvent>

CaptureScreen::CaptureScreen(QWidget* parent)
	:QWidget(parent),
	m_isPressed(false),
	m_state(NONE)
{
	initWindow();
	initStretchRect();

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

void CaptureScreen::initStretchRect()
{
	m_topLeftStretchRect = QRect(0, 0, 0, 0);
	m_topRightStretchRect = QRect(0, 0, 0, 0);
	m_bottomLeftStretchRect = QRect(0, 0, 0, 0);
	m_bottomRightStretchRect = QRect(0, 0, 0, 0);

	m_leftCenterStretchRect = QRect(0, 0, 0, 0);
	m_topCenterStretchRect = QRect(0, 0, 0, 0);
	m_rightCenterStretchRect = QRect(0, 0, 0, 0);
	m_bottomCenterStretchRect = QRect(0, 0, 0, 0);
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

bool CaptureScreen::isTooSmall(QRect rect)
{
	//当选择框小于10x10大小时，退出
	if (rect.width() < 10 || rect.height() < 10)
	{
		return true;
	}
	return false;
}

//void CaptureScreen::setSelectStretchRect(QRect rect)
//{
//	if (isTooSmall(rect))
//		return;
//
//	int adjust = 5;
//	QColor color = QColor(0, 174, 255);
//
//	QPoint topLeftPos = rect.topLeft();
//	QPoint topRightPos = rect.topRight();
//	QPoint bottomLeftPos = rect.bottomLeft();
//	QPoint bottomRightPos = rect.bottomRight();
//
//	m_topLeftStretchRect = QRect(topLeftPos.x() - adjust, topLeftPos.y() - adjust, 10, 10);
//	m_topRightStretchRect = QRect(topRightPos.x() + adjust, topRightPos.y() - adjust, 10, 10);
//	m_bottomLeftStretchRect = QRect(bottomLeftPos.x() - adjust, bottomLeftPos.y() + adjust, 10, 10);
//	m_bottomRightStretchRect = QRect(bottomRightPos.x() + adjust, bottomRightPos.y() + adjust, 10, 10);
//
//	m_leftCenterStretchRect = QRect(topLeftPos.x() - adjust, topLeftPos.y() + (rect.height() / 2) - adjust, 10, 10);
//	m_topCenterStretchRect = QRect(topLeftPos.x() + (rect.width() / 2) - adjust, topLeftPos.y() - adjust, 10, 10);
//	m_rightCenterStretchRect = QRect(topRightPos.x() - adjust, topRightPos.y() + (rect.height() / 2) - adjust, 10, 10);
//	m_bottomCenterStretchRect = QRect(bottomLeftPos.x() + (rect.width() / 2) - adjust, topLeftPos.y() - adjust, 10, 10);
//	
//	m_painter.fillRect(m_topLeftStretchRect, color);
//	m_painter.fillRect(m_topRightStretchRect, color);
//	m_painter.fillRect(m_bottomLeftStretchRect, color);
//	m_painter.fillRect(m_bottomRightStretchRect, color);
//	m_painter.fillRect(m_leftCenterStretchRect, color);
//	m_painter.fillRect(m_topCenterStretchRect, color);
//	m_painter.fillRect(m_rightCenterStretchRect, color);
//	m_painter.fillRect(m_bottomCenterStretchRect, color);
//}

bool CaptureScreen::isPointContains(QPoint curPos)
{
	QRect selectedRect = getRect(m_beginPoint, m_endPoint);
	if (selectedRect.contains(curPos))
	{
		return true;
	}
	return false;
}

//CursorStyle CaptureScreen::isStretchPointContains(QPoint curPos)
//{
//
//	QPoint topLeftPos = m_SelectRect.topLeft();
//	QPoint topRightPos = m_SelectRect.topRight();
//	QPoint bottomLeftPos = m_SelectRect.bottomLeft();
//	QPoint bottomRightPos = m_SelectRect.bottomRight();
//
//	if (qAbs(curPos.x() - topLeftPos.x()) < 5 && qAbs(curPos.y() - topLeftPos.y()) < 5 )
//	{
//		return LDIAGCUR;
//	}
//	if (m_topRightStretchRect.contains(curPos))
//		return RDIAGCUR;
//	if (m_bottomLeftStretchRect.contains(curPos))
//		return RDIAGCUR;
//	if (m_bottomRightStretchRect.contains(curPos))
//		return LDIAGCUR;
//
//	if (m_leftCenterStretchRect.contains(curPos))
//		return VERCUR;
//	if (m_topCenterStretchRect.contains(curPos))
//		return HORCUR;
//	if (m_rightCenterStretchRect.contains(curPos))
//		return VERCUR;
//	if (m_bottomCenterStretchRect.contains(curPos))
//		return HORCUR;
//
//	return NONECUR;
//}

CursorStyle CaptureScreen::getCursorStyle(QPoint curPos)
{
	/*QRect selectedRect = getRect(m_beginPoint, m_endPoint);
	if (selectedRect.contains(curPos))
	{
		return ALLCUR;
	}*/
	int adjust = 5;

	QPoint topLeftPos = m_SelectRect.topLeft();
	QPoint topRightPos = m_SelectRect.topRight();
	QPoint bottomLeftPos = m_SelectRect.bottomLeft();
	QPoint bottomRightPos = m_SelectRect.bottomRight();

	QPoint leftCenterPos = QPoint(topLeftPos.x(), topLeftPos.y() + (m_SelectRect.height() / 2));
	QPoint rightCenterPos = QPoint(topRightPos.x(), topRightPos.y() + (m_SelectRect.height() / 2));
	QPoint topCenterPos = QPoint(topLeftPos.x() + (m_SelectRect.width() / 2), topLeftPos.y());
	QPoint bottomCenterPos = QPoint(bottomLeftPos.x() + (m_SelectRect.width() / 2), bottomRightPos.y());

	int width = m_SelectRect.width();
	int height = m_SelectRect.height();

	QRect selectRect = getRect(QPoint(topLeftPos.x() + adjust, topLeftPos.y() + adjust), QPoint(bottomRightPos.x() + adjust, bottomRightPos.y() + adjust));

	//左对角
	if (qAbs(curPos.x() - topLeftPos.x()) < adjust && qAbs(curPos.y() - topLeftPos.y()) < adjust)
	{
		return LDIAGCUR;
	}
	else if (qAbs(curPos.x() - bottomRightPos.x()) < adjust && qAbs(curPos.y() - bottomRightPos.y()) < adjust)
	{
		return LDIAGCUR;
	}
	//右对角
	else if (qAbs(curPos.x() - topRightPos.x()) < adjust && qAbs(curPos.y() - topRightPos.y()) < adjust)
	{
		return RDIAGCUR;
	}
	else if (qAbs(curPos.x() - bottomLeftPos.x()) < adjust && qAbs(curPos.y() - bottomLeftPos.y()) < adjust)
	{
		return RDIAGCUR;
	}
	//水平
	else if (qAbs(curPos.x() - leftCenterPos.x()) < adjust && qAbs(curPos.y() - leftCenterPos.y()) < adjust)
	{
		return HORCUR;
	}
	else if (qAbs(curPos.x() - rightCenterPos.x()) < adjust && qAbs(curPos.y() - rightCenterPos.y()) < adjust)
	{
		return HORCUR;
	}
	//垂直
	else if (qAbs(curPos.x() - topCenterPos.x()) < adjust && qAbs(curPos.y() - topCenterPos.y()) < adjust)
	{
		return VERCUR;
	}
	else if (qAbs(curPos.x() - bottomCenterPos.x()) < adjust && qAbs(curPos.y() - bottomCenterPos.y()) < adjust)
	{
		return VERCUR;
	}
	else if (selectRect.contains(curPos))
	{
		return ALLCUR;
	}
	//中心
	//QRect centerRect = QRect(topLeftPos.x() + 5, topLeftPos.y() + 5, width - 10, height - 10);
	//QRect selectedRect = getRect(m_beginPoint., m_endPoint);
	//bool re = centerRect.contains(curPos);
	
	return NONECUR;
}

void CaptureScreen::drawMoveRect(QRect rect)
{
	int adjust = 5;

	int dx = m_curPressEndPoint.x() - m_curPressBeginPoint.x();
	int dy = m_curPressEndPoint.y() - m_curPressBeginPoint.y();
	//qDebug() << "dx :: " << dx << " dy :: " << dy;

	int curBeginX = rect.topLeft().x() + dx;
	int curBeginY = rect.topLeft().y() + dy;
	int curEndX = rect.bottomRight().x() + dx;
	int curEndY = rect.bottomRight().y() + dy;
	//左上方移动
	if (dx < 0 && dy < 0)
	{
		int press_dx = qAbs(rect.topLeft().x() - m_curPressBeginPoint.x());
		int press_dy = qAbs(rect.topLeft().y() - m_curPressBeginPoint.y());
		//边界情况
		if ((press_dx + qAbs(dx)) > m_curPressBeginPoint.x() + adjust)
		{
			curBeginX = 0;
			curEndX = rect.width();

		}
		if ((press_dy + qAbs(dy)) > m_curPressBeginPoint.y() + adjust)
		{
			curBeginY = 0;
			curEndY = rect.height();
		}
	}
	//左下方移动
	else if (dx < 0 && dy > 0)
	{
		int press_dx = qAbs(rect.topLeft().x() - m_curPressBeginPoint.x());
		int press_dy = qAbs(rect.bottomRight().y() - m_curPressBeginPoint.y());
		//边界情况
		if ((press_dx + qAbs(dx)) > m_curPressBeginPoint.x() + adjust)
		{
			curBeginX = 0;
			curEndX = rect.width();
		}
		if ((press_dy + qAbs(dy) + m_curPressBeginPoint.y()) > m_screenheight + adjust)
		{
			curEndY = m_screenheight;
			curBeginY = m_screenheight - rect.height();
		}
	}
	//右下方移动
	else if (dx > 0 && dy > 0)
	{
		int press_dx = qAbs(rect.bottomRight().x() - m_curPressBeginPoint.x());
		int press_dy = qAbs(rect.bottomRight().y() - m_curPressBeginPoint.y());

		//边界情况
		if ((press_dx + qAbs(dx) + m_curPressBeginPoint.x()) > m_screenwidth + adjust)
		{
			curEndX = m_screenwidth;
			curBeginX = m_screenwidth - rect.width();
		}
		if ((press_dy + qAbs(dy) + m_curPressBeginPoint.y()) > m_screenheight + adjust)
		{
			curEndY = m_screenheight;
			curBeginY = m_screenheight - rect.height();
		}
	}
	//右上方移动
	else if (dx > 0 && dy < 0)
	{
		int press_dx = qAbs(rect.bottomRight().x() - m_curPressBeginPoint.x());
		int press_dy = qAbs(rect.bottomRight().y() - m_curPressBeginPoint.y());

		//右边界
		if ((press_dx + qAbs(dx) + m_curPressBeginPoint.x()) > (m_screenwidth + adjust))
		{
			curEndX = m_screenwidth;
			curBeginX = m_screenwidth - rect.width();
		}
		//上边界
		if ((press_dy + qAbs(dy)) > (m_curPressBeginPoint.y() + adjust))
		{
			curBeginY = 0;
			curEndY = rect.height();
		}
	}
	m_beginPoint.setX(curBeginX);
	m_beginPoint.setY(curBeginY);
	m_endPoint.setX(curEndX);
	m_endPoint.setY(curEndY);
}

void CaptureScreen::drawinitStretchRect(QRect rect)
{
	if (isTooSmall(rect))
		return;

	int adjust = 5;
	QColor color = QColor(0, 174, 255);

	QPoint topLeftPos = rect.topLeft();
	QPoint topRightPos = rect.topRight();
	QPoint bottomLeftPos = rect.bottomLeft();
	QPoint bottomRightPos = rect.bottomRight();

	m_topLeftStretchRect = QRect(topLeftPos.x() - adjust, topLeftPos.y() - adjust, 10, 10);
	m_topRightStretchRect = QRect(topRightPos.x() - adjust, topRightPos.y() - adjust, 10, 10);
	m_bottomLeftStretchRect = QRect(bottomLeftPos.x() - adjust, bottomLeftPos.y() - adjust, 10, 10);
	m_bottomRightStretchRect = QRect(bottomRightPos.x() - adjust, bottomRightPos.y() - adjust, 10, 10);

	m_leftCenterStretchRect = QRect(topLeftPos.x() - adjust, topLeftPos.y() + (rect.height() / 2) - adjust, 10, 10);
	m_topCenterStretchRect = QRect(topLeftPos.x() + (rect.width() / 2) - adjust, topLeftPos.y() - adjust, 10, 10);
	m_rightCenterStretchRect = QRect(bottomRightPos.x() - adjust, bottomRightPos.y() - (rect.height() / 2) - adjust, 10, 10);
	m_bottomCenterStretchRect = QRect(bottomLeftPos.x() + (rect.width() / 2) - adjust, bottomLeftPos.y() - adjust, 10, 10);

	m_painter.fillRect(m_topLeftStretchRect, color);
	m_painter.fillRect(m_topRightStretchRect, color);
	m_painter.fillRect(m_bottomLeftStretchRect, color);
	m_painter.fillRect(m_bottomRightStretchRect, color);
	m_painter.fillRect(m_leftCenterStretchRect, color);
	m_painter.fillRect(m_topCenterStretchRect, color);
	m_painter.fillRect(m_rightCenterStretchRect, color);
	m_painter.fillRect(m_bottomCenterStretchRect, color);
}

void CaptureScreen::drawStretchRect(QRect rect)
{
	qDebug() << "stretch rect :: " << rect;
	QPoint topLeftPos = rect.topLeft();
	QPoint topRightPos = rect.topRight();
	QPoint bottomLeftPos = rect.bottomLeft();
	QPoint bottomRightPos = rect.bottomRight();

	int dy = m_curPressEndPoint.y() - m_curPressBeginPoint.y();
	int dx = m_curPressEndPoint.x() - m_curPressBeginPoint.x();

	//当垂直方向拉伸
	if (m_cursorStyle == VERCUR)
	{
		//向上拉伸
		if (qAbs(m_curPressBeginPoint.y() - topLeftPos.y()) < 5)
		{
			m_beginPoint.setY(topLeftPos.y() + dy);
		}
		//向下拉伸
		else if (qAbs(m_curPressBeginPoint.y() - bottomRightPos.y()) < 5)
		{
			m_endPoint.setY(bottomRightPos.y() + dy);

		}
	}
	//当水平方向拉伸
	else if (m_cursorStyle == HORCUR)
	{
		//向左拉伸
		if (qAbs(m_curPressBeginPoint.x() - topLeftPos.x()) < 5)
		{
			m_beginPoint.setX(topLeftPos.x() + dx);
		}
		//向右拉伸
		else if (qAbs(m_curPressBeginPoint.x() - bottomRightPos.x()) < 5)
		{
			m_endPoint.setX(bottomRightPos.x() + dx);
		}
	}
	//当左下角和右上角对角方向拉伸
	else if (m_cursorStyle == RDIAGCUR)
	{
		//向左下拉伸
		if (qAbs(m_curPressBeginPoint.x() - bottomLeftPos.x()) < 5 || 
			qAbs(m_curPressBeginPoint.y() - bottomLeftPos.y()) < 5)
		{
			m_beginPoint.setX(topLeftPos.x() + dx);
			m_endPoint.setY(bottomRightPos.y() + dy);
		}
		//向右上拉伸
		else if (qAbs(m_curPressBeginPoint.x() - topRightPos.x()) < 5 ||
				 qAbs(m_curPressBeginPoint.y() - topRightPos.y()) < 5)
		{
			m_beginPoint.setY(topLeftPos.y() + dy);
			m_endPoint.setX(bottomRightPos.x() + dx);
		}
	}
	//当左上角和右下角对角方向拉伸
	else if (m_cursorStyle == LDIAGCUR)
	{
		//向左上拉伸
		if (qAbs(m_curPressBeginPoint.x() - topLeftPos.x()) < 5 ||
			qAbs(m_curPressBeginPoint.y() - topLeftPos.y()) < 5)
		{
			m_beginPoint.setX(topLeftPos.x() + dx);
			m_beginPoint.setY(topLeftPos.y() + dy);
		}
		//向右下拉伸
		else if (qAbs(m_curPressBeginPoint.x() - bottomRightPos.x()) < 5 ||
				 qAbs(m_curPressBeginPoint.y() - bottomRightPos.y()) < 5)
		{
			m_endPoint.setY(bottomRightPos.y() + dy);
			m_endPoint.setX(bottomRightPos.x() + dx);
		}
	}
}

void CaptureScreen::mousePressEvent(QMouseEvent * event)
{
	qDebug() << "********** mousePressEvent ***********";
	if (event->button() == Qt::LeftButton)
	{
		//if (isPointContains(event->pos()))
		//{
		//	m_curPressBeginPoint = event->pos();
		//	m_curPressEndPoint = event->pos();
		//	m_state = MOVE;
		//}
		//else {
		//	m_beginPoint = event->pos();//记录当前位置
		//}
		//当为移动目标时
		if (m_cursorStyle == ALLCUR)
		{
			m_curPressBeginPoint = event->pos();
			m_curPressEndPoint = event->pos();
			m_state = MOVE;
		}
		else if (m_cursorStyle == VERCUR || 
				 m_cursorStyle == HORCUR || 
				 m_cursorStyle == RDIAGCUR || 
				 m_cursorStyle == LDIAGCUR
				)
		{
			m_curPressBeginPoint = event->pos();
			m_curPressEndPoint = event->pos();
			m_state = STRETCH;
		}
		else {
			m_beginPoint = event->pos();//记录当前位置
		}


		m_isPressed = true;
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
		m_curPressEndPoint = curPos;*/
		m_curPressEndPoint = event->pos();
		update();
	}
	//当鼠标移动时,设置鼠标样式
	else if (m_state == NONE)
	{
		CursorStyle style = getCursorStyle(event->pos());
		m_cursorStyle = style;
		if (style == ALLCUR)
		{
			this->setCursor(Qt::SizeAllCursor);
		}
		else if (style == VERCUR)
		{
			this->setCursor(Qt::SizeVerCursor);
		}
		else if (style == HORCUR)
		{
			this->setCursor(Qt::SizeHorCursor);
		}
		else if (style == RDIAGCUR)
		{
			this->setCursor(Qt::SizeBDiagCursor);
		}
		else if (style == LDIAGCUR)
		{
			this->setCursor(Qt::SizeFDiagCursor);
		}
		else {
			this->setCursor(Qt::ArrowCursor);
		}
	}
	//当拉伸大小时
	else if (m_isPressed && m_state == STRETCH)
	{
		m_curPressEndPoint = event->pos();;
		update();
	}
	return QWidget::mouseMoveEvent(event);
}

void CaptureScreen::mouseReleaseEvent(QMouseEvent * event)
{
	qDebug() << "********** mouseReleaseEvent ***********";
	if (m_state == NONE)
	{
		m_endPoint = event->pos();
		
	}
	else if (m_state == MOVE || m_state == STRETCH)
	{
		m_curPressEndPoint = event->pos();
	}
	m_initSelectRect = getRect(m_beginPoint, m_endPoint);

	//setSelectStretchRect(m_SelectRect);
	m_state = NONE;
	m_isPressed = false;

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

void CaptureScreen::paintEvent(QPaintEvent * event)
{
	Q_UNUSED(event);
	//重绘
	m_painter.begin(this);
	m_painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::FlatCap));	//设置画笔
	m_painter.drawPixmap(0, 0, m_screenPixmap);
	QColor shadowColor = QColor(0, 0, 0, 100);
	m_painter.fillRect(m_screenPixmap.rect(), shadowColor);//填充阴影


	//移动时
	if (m_isPressed && m_state == MOVE)
	{
		//画移动的截图框
		drawMoveRect(m_initSelectRect);
	}
	//拉伸时
	else if (m_isPressed && m_state == STRETCH)
	{
		drawStretchRect(m_initSelectRect);
	}

	QRect selectedRect = getRect(m_beginPoint, m_endPoint);
	m_SelectRect = selectedRect;
	qDebug() << "selectedRect  :: " << selectedRect;

	m_capturePixmap = m_screenPixmap.copy(selectedRect);
	m_painter.drawPixmap(selectedRect.topLeft(), m_capturePixmap);
	m_painter.drawRect(selectedRect);

	//初始化截图框边界的拉伸小框
	drawinitStretchRect(selectedRect);

	m_painter.end();
}