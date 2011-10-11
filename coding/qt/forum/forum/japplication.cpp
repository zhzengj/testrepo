/********************************************************************
	created:	12:6:2011   22:46
	file base:	japplication.cpp
	author:		zhzengj
	
*********************************************************************/

#include "stdafx.h"
#include "japplication.h"
#include "accountsvr.h"

JApplication::JApplication(int &argc, char **argv)
:QApplication(argc, argv)
{
	QTextCodec *codec = QTextCodec::codecForName("GB2312");
	QTextCodec::setCodecForCStrings(codec);
	m_pAccountSrv = new JAccountSvr(this);
}

void JApplication::loadInfo(const QString & file)
{
	m_vtImport.clear();
	QDomDocument doc;
	if (!ZJ::openXml(doc, applicationDirPath() + "/" + file))
	{
		QString str = "加载配置文件 " + applicationDirPath() + "/" + file + " 失败!";
		QMessageBox::critical(NULL, "错误", str);
		::exit(-1);
	}

	QDomElement root = doc.documentElement();
	QDomElement e = root.firstChildElement("import");
	for (; !e.isNull(); e = e.nextSiblingElement())
	{
		if (e.hasAttribute("id") && e.hasAttribute("file"))
			m_vtImport.push_back(QPair<QString, QString>(e.attribute("id"), applicationDirPath() + "/" + e.attribute("file")));
	}
	loadInfo();
}

void JApplication::loadInfo()
{	
	try 
	{
		//load xml
		m_pAccountSrv->loadInfo(getFileById(QString::fromUtf16(ZJ::XmlAccountId)));
	}
	catch (QString err)
	{
		qCritical() << "loadInfo error : " << err << endl;
	}
	catch (...)
	{
		qCritical() << "loadInfo error\n";
	}
}

void JApplication::saveInfo()
{
	QStringList lst = getFileById(QString::fromUtf16(ZJ::XmlAccountId));
	if (!lst.isEmpty())
		m_pAccountSrv->SaveInfo(lst[0]);
}

QStringList JApplication::getFileById(const QString & id) const
{//加载时，一个id可以有多个xml，但保存时，仅有一个。。
	QStringList strList;
	for (int i = 0; i < m_vtImport.count(); ++i)
	{
		if (m_vtImport[i].first == id)
			strList << m_vtImport[i].second;
	}
	return strList;
}

JAccountSvr * JApplication::accountSvr()
{
	return m_pAccountSrv;
}
