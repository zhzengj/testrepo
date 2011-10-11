#include "stdafx.h"
#include "forum.h"
#include "japplication.h"

int main(int argc, char *argv[])
{
	JApplication a(argc, argv);
	a.loadInfo("data/load.xml");

	forum w;
	w.show();
	int res = a.exec();
	a.saveInfo();
	return res;
}
