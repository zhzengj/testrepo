#include "stdafx.h"
#include "net.h"
#include "weather.h"
#include <QtNetwork/QtNetwork>

ZWeatherNetHelper::ZWeatherNetHelper(ZWeatherData * pData, QObject * parent)
:QObject(parent), m_pData(pData)
{
	m_postalNet = new QNetworkAccessManager(this);
	m_iconNet = new QNetworkAccessManager(this);
	m_weatherNet = new QNetworkAccessManager(this);


}

bool ZWeatherNetHelper::updateData()
{
	//get postal
	if (m_pData->m_postal.isEmpty())
		m_pData->m_postal = postal();

	//weather data
	//weather icon
}

QString ZWeatherNetHelper::ipAddress()
{
	foreach(const QHostAddress & addr, QNetworkInterface::allAddresses())
	{
		if (addr != QHostAddress::LocalHost && addr != QHostAddress::LocalHostIPv6 &&
			!addr.isNull())
			return addr.toString();
	}
	return QString();
}

QString ZWeatherNetHelper::postal()
{
	QString strPostal;
	return strPostal;
}