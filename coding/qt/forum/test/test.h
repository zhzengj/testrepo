#ifndef TEST_H
#define TEST_H

#include <QtGui/QWidget>
#include "ui_test.h"

class QByteArray;
class QNetworkAccessManager;
class QWebView;
class QNetworkReply;
class test : public QWidget
{
	Q_OBJECT
private:
	QByteArray * m_pData;
	QNetworkAccessManager * m_pNetMan;
	QWebView * m_pWebView;

public:
	test(QWidget *parent = 0, Qt::WFlags flags = 0);
	~test();

protected slots:
	void onPost();
	void onPostFinished(QNetworkReply * reply);
	void onWebViewLoadFinished(bool ok);

private:
	Ui::testClass ui;
};

#endif // TEST_H
