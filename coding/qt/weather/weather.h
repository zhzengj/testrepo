#ifndef WEATHER_H
#define WEATHER_H

#include <QtGui/QWidget>
#include <QtGui/QSystemTrayIcon>
#include "ui_weather.h"

typedef QHash<QString, QString> ZWProp;
typedef QList<ZWProp> ZFutureLst;

class ZWeatherData : public QObject
{
public:
	QDate				m_date;
	QString				m_city;
	QString				m_postal;
	QCache<QString, QIcon>	m_icons;
	ZWProp				m_details;
	ZFutureLst			m_futures;
public:
	QIcon detailIcon();
	QIcon icon(const QString & url);
};

class ZWeatherTipsTitle : public QWidget
{
public:
	ZWeatherTipsTitle(const QString & title,
		QWidget * parent = NULL, Qt::WFlags flags = 0);
};

class ZWeatherDetails : public QWidget
{
public:
	ZWeatherDetails(const QIcon & icon, const ZWProp & prop,
		QWidget * parent = NULL, Qt::WFlags flags = 0);
};

class ZWeatherFuture : public QWidget
{
public:
	ZWeatherFuture(const QIcon & icon, const ZWProp & prop,
		QWidget * parent = NULL, Qt::WFlags flags = 0);
};

class ZWeatherTips;
class ZWeatherFutures : public QWidget
{
private:
	ZWeatherTips * m_tips;

public:
	ZWeatherFutures(const ZFutureLst & lst,
		ZWeatherTips * parent = NULL, Qt::WFlags flags = 0);
};

class ZWeatherNetHelper;
class ZWeatherTips : public QWidget
{
	Q_OBJECT
private:
	ZWeatherData * m_pData;
	ZWeatherTipsTitle * m_title;
	ZWeatherDetails * m_details;
	ZWeatherFutures * m_futures;
	ZWeatherNetHelper * m_netHelper;

public:
	ZWeatherTips(ZWeatherData * pData, QWidget *parent = 0, Qt::WFlags flags = 0);
	~ZWeatherTips();
	QIcon icon(const QString & url);

protected:
	void init();
	void updateWeatherData();

private:
	Ui::weatherClass ui;
};

class ZWeatherTrayIcon: public QSystemTrayIcon
{
	Q_OBJECT
private:
	ZWeatherData m_data;

public:
	ZWeatherTrayIcon(QObject *parent = 0);

protected slots:
	void onActivated(QSystemTrayIcon::ActivationReason reason);

protected:
	virtual bool event(QEvent *e);
};
#endif // WEATHER_H
