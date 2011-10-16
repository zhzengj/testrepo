#include "stdafx.h"
#include "weather.h"
#include <QtGui/QtGui>
#include "net.h"

const wchar_t * WURL_TAG = L"url";
const wchar_t * WWeek = L"day_of_week";
const wchar_t * WLow = L"low";
const wchar_t * WHigh = L"high";
int PIC_WIDTH = 40;
int PIC_HEIGHT = 40;
//struct
//tray icon -> tips, data
//tips -> title, detail, future
//title -> string, right corner
QIcon ZWeatherData::icon(const QString & url)
{
	return *m_icons[url];
}

QIcon ZWeatherData::detailIcon()
{
	QString urlIcon = m_details[QString::fromUtf16(WURL_TAG)];
	return *m_icons[urlIcon];
}

//////////////////////////////////////////////////////////////////////////
ZWeatherTipsTitle::ZWeatherTipsTitle(const QString & title, QWidget * parent, Qt::WFlags flags)
: QWidget(parent, flags)
{
	QHBoxLayout * hLy = new QHBoxLayout(this);
	hLy->setMargin(1);
	hLy->setSpacing(1);
	QLabel * lbl = new QLabel(title);
	hLy->addWidget(lbl);
}
//////////////////////////////////////////////////////////////////////////
ZWeatherDetails::ZWeatherDetails(const QIcon & icon, const ZWProp & prop, QWidget * parent /* = NULL */, Qt::WFlags flags /* = 0 */)
: QWidget(parent, flags)
{
	QHBoxLayout * hLy = new QHBoxLayout(this);
	hLy->setMargin(2);
	hLy->setSpacing(4);

	QLabel * pic = new QLabel(this);
	pic->setPixmap(icon.pixmap(QSize(PIC_WIDTH, PIC_WIDTH)));
	hLy->addWidget(pic);

	QVBoxLayout * vLy = new QVBoxLayout(this);
	vLy->setMargin(1);
	vLy->setSpacing(2);
	foreach(const QString & tags, prop.keys())
	{
		if (tags == QString::fromUtf16(WURL_TAG))
			continue;
		QLabel * lbl = new QLabel(QString("%1: %2").arg(tags).arg(prop.value(tags)));
		vLy->addWidget(lbl);
	}
	hLy->addLayout(vLy);
}
//////////////////////////////////////////////////////////////////////////
ZWeatherFuture::ZWeatherFuture(const QIcon & icon, const ZWProp & prop, QWidget * parent /* = NULL */, Qt::WFlags flags /* = 0 */)
: QWidget(parent, flags)
{
	QVBoxLayout * vLy = new QVBoxLayout(this);
	vLy->setMargin(1);
	vLy->setSpacing(2);

	QLabel * dweek = new QLabel(prop.value(QString::fromUtf16(WWeek)));
	vLy->addWidget(dweek);

	QLabel * pic = new QLabel();
	pic->setPixmap(icon.pixmap(QSize(PIC_WIDTH, PIC_WIDTH)));
	vLy->addWidget(pic);

	QLabel * lowHigh = new QLabel(QString("%1 | %2").arg(prop.value(QString::fromUtf16(WLow)))
		.arg(QString::fromUtf16(WHigh)));
	vLy->addWidget(lowHigh);
}
//////////////////////////////////////////////////////////////////////////
ZWeatherFutures::ZWeatherFutures(const ZFutureLst & lst, ZWeatherTips * parent /* = NULL */, Qt::WFlags flags /* = 0 */)
:m_tips(parent), QWidget(parent, flags)
{
	QHBoxLayout * hLy = new QHBoxLayout(this);
	hLy->setMargin(1);
	hLy->setSpacing(2);
	foreach(const ZWProp & prop, lst)
	{
		QIcon icon = m_tips->icon(prop.value(QString::fromUtf16(WURL_TAG)));
		ZWeatherFuture * future = new ZWeatherFuture(icon, prop, this);
		hLy->addWidget(future);
	}
}
//////////////////////////////////////////////////////////////////////////
ZWeatherTips::ZWeatherTips(ZWeatherData * pData, QWidget *parent /* = 0 */, Qt::WFlags flags /* = 0 */)
: QWidget(parent, flags), m_pData(pData)
{
	ui.setupUi(this);
	init();
}

ZWeatherTips::~ZWeatherTips()
{

}

void ZWeatherTips::init()
{
	m_netHelper = new ZWeatherNetHelper(m_pData, this);
	if (!m_netHelper->updateData())
		return;

	m_title = new ZWeatherTipsTitle(m_pData->m_city, this);
	m_details = new ZWeatherDetails(m_pData->detailIcon(), m_pData->m_details, this);
	m_futures = new ZWeatherFutures(m_pData->m_futures, this);

	QVBoxLayout * vLy = new QVBoxLayout(this);
	vLy->setSpacing(2);
	vLy->setMargin(0);
	vLy->addWidget(m_title);
	vLy->addWidget(m_details);
	vLy->addWidget(m_futures);
}

QIcon ZWeatherTips::icon(const QString & url)
{
	return m_pData->icon(url);
}

void ZWeatherTips::updateWeatherData()
{

}
//////////////////////////////////////////////////////////////////////////
ZWeatherTrayIcon::ZWeatherTrayIcon(QObject *parent /* = 0 */)
:QSystemTrayIcon(parent)
{
	setIcon(QIcon(":/weather/Resources/weather.gif"));
	connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		this, SLOT(onActivated(QSystemTrayIcon::ActivationReason)));
}

void ZWeatherTrayIcon::onActivated(QSystemTrayIcon::ActivationReason reason)
{
	QRect rt = geometry();
	QWidget * tips = new ZWeatherTips(&m_data, NULL, Qt::Popup);
	tips->setAttribute(Qt::WA_DeleteOnClose);
	tips->move(rt.left(), rt.top() - tips->height());
	tips->show();
}

bool ZWeatherTrayIcon::event(QEvent *e)
{
	if (e->type() == QEvent::ToolTip)
	{
		QHelpEvent * he = dynamic_cast<QHelpEvent*> (e);
		if (he)
		{
			QWidget * tips = new ZWeatherTips(&m_data, NULL, Qt::Popup);
			tips->setAttribute(Qt::WA_DeleteOnClose);
			tips->move(he->globalPos());
			tips->show();
		}
		return true;
	}
	return false;
}


