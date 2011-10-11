#include "stdafx.h"
#include "browser.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	browser w;
	w.show();
	return a.exec();
}
