#ifndef WEATHER_H
#define WEATHER_H

#include <QtGui/QWidget>
#include <QtGui/QSystemTrayIcon>
#include "ui_weather.h"

class weather : public QWidget
{
	Q_OBJECT

public:
	weather(QWidget *parent = 0, Qt::WFlags flags = 0);
	~weather();

private:
	Ui::weatherClass ui;
};

class ZWeatherTrayIcon: public QSystemTrayIcon
{
	Q_OBJECT
public:
	ZWeatherTrayIcon(QObject *parent = 0);

protected slots:
	void onActivated(QSystemTrayIcon::ActivationReason reason);

protected:
	virtual bool event(QEvent *e);
};
#endif // WEATHER_H
