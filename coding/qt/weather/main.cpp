#include "stdafx.h"
#include "weather.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setQuitOnLastWindowClosed(true);

	ZWeatherTrayIcon trayIcon;
	trayIcon.show();
	return a.exec();
}
