#ifndef _H_NET_H_
#define _H_NET_H_

class ZWeatherData;
class ZWeatherNetHelper: public QObject
{
private:
	ZWeatherData * m_pData;
	QNetworkAccessManager * m_postalNet;
	QNetworkAccessManager * m_iconNet;
	QNetworkAccessManager * m_weatherNet;

public:
	ZWeatherNetHelper(ZWeatherData * pData, QObject * parent);
	bool updateData();

protected:
	QString idAddress();
	QString postal();
};

#endif