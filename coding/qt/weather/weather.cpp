#include "stdafx.h"
#include "weather.h"
#include <QtGui/QtGui>

weather::weather(QWidget *parent, Qt::WFlags flags)
: QWidget(parent, flags)
{
	ui.setupUi(this);
}

weather::~weather()
{

}

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
	QWidget * tips = new weather(NULL, Qt::Popup);
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
			QWidget * tips = new weather(NULL, Qt::Popup);
			tips->setAttribute(Qt::WA_DeleteOnClose);
			tips->move(he->globalPos());
			tips->show();
		}
		return true;
	}
	return false;
}


