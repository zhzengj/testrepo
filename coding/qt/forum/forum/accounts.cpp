/********************************************************************
	created:	14:6:2011   21:20
	file base:	accounts.cpp
	author:		zhzengj
	
*********************************************************************/
#include "stdafx.h"
#include "accounts.h"

void JAccount::setEnable(bool isEnable)
{
	if (isEnable)
		setState(JAC_Enabled);
	else
		clearState(JAC_Enabled);
}

QString JAccount::nickName()
{
	return m_name;
}

QString JAccount::plainPwd()
{
	return m_pwd;
}

bool JAccount::isEnable()
{
	return hasState(JAC_Enabled);
}

JAccounts::~JAccounts()
{
	clear();
}

bool JAccount::hasState(int en)
{
	return m_nState & (1 << en);
}

void JAccount::setState(int en)
{
	m_nState |= (1 << en);
}

void JAccount::clearState(int en)
{
	m_nState = (m_nState | (1 << en)) - (1 << en);
}

void JAccounts::loadInfo(const QDomElement & e)
{
	m_forumName = e.attribute("name");
	m_id = e.attribute("id");

	JAccount * ptr, *tmp;
	QMap<QString, JAccount*>::Iterator itr;
	QDomElement child = e.firstChildElement();
	for (; !child.isNull(); child = child.nextSiblingElement())
	{
		ptr = new JAccount();
		ptr->setEnable(child.attribute("enable").toInt());
		ptr->m_name = child.attribute("name");
		ptr->m_pwd = child.attribute("pwd");
		
		itr = m_accounts.find(ptr->m_name);
		if (itr != m_accounts.end())
		{
			tmp = itr.value();
			delete tmp;
		}
		else
			m_accNames.append(ptr->m_name);
		m_accounts[ptr->m_name] = ptr;
	}
}

void JAccounts::saveInfo(QXmlStreamWriter & s)
{
	s.writeStartElement("forum");
	s.writeAttribute("name", m_forumName);
	s.writeAttribute("id", m_id);

	QMap<QString, JAccount*>::Iterator itr;
	for (itr = m_accounts.begin(); itr != m_accounts.end(); ++itr)
	{
		s.writeStartElement("account");
		s.writeAttribute("name", (*itr)->nickName());
		s.writeAttribute("pwd", (*itr)->plainPwd());
		s.writeAttribute("enable", (*itr)->isEnable() ? "1": "0");
		s.writeEndElement();
	}

	s.writeEndElement();
}

void JAccounts::clear()
{
	JAccount * ptr;
	QMap<QString, JAccount*>::Iterator itr;
	for (itr = m_accounts.begin(); itr != m_accounts.end(); ++itr)
	{
		ptr = itr.value();
		delete ptr;
	}
	m_accounts.clear();
}

int JAccounts::count()
{
	return m_accounts.count();
}

QString JAccounts::getForumName()
{
	return m_forumName;
}

JAccount * JAccounts::at(int index)
{
	if (index < 0 || index >= m_accounts.count())
		return NULL;
	return m_accounts.find(m_accNames.at(index)).value();
}

void JAccounts::removeAccount(const QString & name)
{
	m_accNames.removeAt(m_accNames.indexOf(name));
	JAccount * ptr =  m_accounts.take(name);
	delete ptr;
}

bool JAccounts::isExist(const QString & name)
{
	QMap<QString, JAccount*>::Iterator itr;
	itr = m_accounts.find(name);
	return itr != m_accounts.end();
}

bool JAccounts::addAccount(const QString & name, const QString & plainPwd, bool isEnable /* = true */)
{
	if (isExist(name))
		return false;

	JAccount * ptr = new JAccount();
	ptr->setEnable(isEnable);
	ptr->m_name = name;
	ptr->m_pwd = plainPwd;
	m_accounts[ptr->m_name] = ptr;
	return true;
}

bool JAccounts::modifyAccount(const QString & name, const QString & plainPwd, bool isEnable /* = true */)
{
	QMap<QString, JAccount*>::Iterator itr;
	itr = m_accounts.find(name);
	if (itr == m_accounts.end())
		return false;

	(*itr)->m_name = name;
	(*itr)->m_pwd = plainPwd;
	(*itr)->setEnable(isEnable);
	return true;
}
