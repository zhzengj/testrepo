/********************************************************************
	created:	13:6:2011   20:55
	file base:	accountsvr.cpp
	author:		zhzengj
	
*********************************************************************/
#include "stdafx.h"
#include "accountsvr.h"
#include "accounts.h"
#include <QPair>

JAccountSvr::JAccountSvr(QObject *parent /* = 0 */)
:QObject(parent), m_isDirty(false)
{

}

JAccountSvr::~JAccountSvr()
{
	clear();
}

void JAccountSvr::loadInfo(const QStringList & strList)
{
	JAccounts * pAccount;
	for (int i = 0; i < strList.count(); ++i)
	{
		QDomDocument doc;
		if (!ZJ::openXml(doc, strList[i]))
			throw QString("load accounts xml erro");

		QDomElement root = doc.documentElement();
		QDomElement e = root.firstChildElement("forum");//forum
		for (; !e.isNull(); e = e.nextSiblingElement())
		{
			pAccount = getForumAccounts(e.attribute("id"));
			if (NULL == pAccount)
				pAccount = new JAccounts();
			pAccount->loadInfo(e);
			m_accounts.push_back(QPair<QString, JAccounts*>(e.attribute("id"), pAccount));
		}
	}
}

bool JAccountSvr::SaveInfo(const QString & strFile)
{
	if (!m_isDirty)
		return true;

	QFile file(strFile);
	if (file.open(QIODevice::WriteOnly))
	{
		QXmlStreamWriter s(&file);
		s.setAutoFormatting(true);
		s.writeStartDocument();
		s.writeStartElement("accounts");

		for (int i = 0; i < m_accounts.count(); ++i)
			m_accounts[i].second->saveInfo(s);

		s.writeEndElement();
		s.writeEndDocument();
		file.flush();
		file.close();
		m_isDirty = false;
	}
	else
	{
		qWarning("save account server info failure");
		return false;
	}
	return true;
}

void JAccountSvr::clear()
{
	JAccounts * ptr;
	for (int i = 0; i < m_accounts.count(); ++i)
	{
		ptr = m_accounts[i].second;
		delete ptr;
	}
	m_accounts.clear();
}

void JAccountSvr::setDirty(bool isDirty)
{
	m_isDirty = isDirty;
}

JAccounts * JAccountSvr::getForumAccounts(const QString & forumId)
{
	for (int i = 0; i < m_accounts.count(); ++i)
	{
		if (forumId == m_accounts[i].first)
			return m_accounts[i].second;
	}
	return NULL;
}

JAccounts * JAccountSvr::forumAccounts(const QString & forumName)
{
	if (forumName.isEmpty())
		return NULL;
	for (int i = 0; i < m_accounts.count(); ++i)
	{
		if (m_accounts[i].second->getForumName() == forumName)
			return m_accounts[i].second;
	}
	return NULL;
}

QString JAccountSvr::forumName(int index)
{
	if (index < 0 || index >= m_accounts.count())
		return NULL;
	return m_accounts[index].second->getForumName();
}

QStringList JAccountSvr::forumNames()
{
	QStringList lst;
	for (int i = 0; i < m_accounts.count(); ++i)
		lst << m_accounts[i].second->getForumName();
	lst << "²âÊÔ";
	return lst;
}

int JAccountSvr::forumCount()
{
	return m_accounts.count();
}

JAccounts * JAccountSvr::getForumAccounts(int index)
{
	if (index < 0 || index >= m_accounts.count())
		return NULL;
	return m_accounts[index].second;
}
