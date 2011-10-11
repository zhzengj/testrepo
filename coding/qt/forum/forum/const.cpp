/********************************************************************
	created:	13:6:2011   21:18
	file base:	const.cpp
	author:		zhzengj
	
*********************************************************************/

#include "stdafx.h"
#include "const.h"

namespace ZJ
{
	const wchar_t * XmlAccountId = L"account";
	const wchar_t * XmlTianyaForumId = L"tianya";

	//pub func
	bool openXml(QDomDocument & doc, const QString & fileName)
	{
		QFile file(fileName);
		QString errStr;
		if (!file.open(QIODevice::ReadOnly))
		{
			qCritical() << "Open file failure\n";
			return FALSE;
		}
		if (!doc.setContent(&file, &errStr))
		{
			file.close();
			qCritical() << "xml set content failure : " << errStr << endl;
			return FALSE;
		}
		file.close();
		return TRUE;
	}
}