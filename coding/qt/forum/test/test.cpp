#include "test.h"
#include <QtGui/QtGui>
#include <QNetworkAccessManager>
#include <QWebView>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QWebFrame>

class JCookieJar : public QNetworkCookieJar
{
public:
	void output()
	{
		QList<QNetworkCookie> pList = allCookies();/*pCookieJar->cookiesForUrl(QUrl("passport.tianya.cn"));*/
		qDebug() << "cookie number " << pList.count() << endl;
		for (int i = 0 ; i < pList.count(); ++i)
		{
			QNetworkCookie tmp = pList.at(i);
			qDebug() << "domain " << tmp.domain()  << endl
				<< "path " << tmp.path() << endl
				<< "name " << QString(tmp.name()) << endl
				<< "value " << QString(tmp.value()) << endl
				<< "date " << tmp.expirationDate().toString() << endl;
		}
	}
};

test::test(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
	,m_pData(NULL)
	,m_pNetMan(NULL)
	,m_pWebView(NULL)
{
	ui.setupUi(this);

	m_pNetMan = new QNetworkAccessManager(this);
	m_pWebView = new QWebView();

	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

	connect(ui.postBtn, SIGNAL(clicked()), this, SLOT(onPost()));
	connect(m_pNetMan, SIGNAL(finished(QNetworkReply*)), this, SLOT(onPostFinished(QNetworkReply*)));
	connect(m_pWebView, SIGNAL(loadFinished(bool)), this, SLOT(onWebViewLoadFinished(bool)));
}

test::~test()
{
	if (NULL != m_pData)
		delete m_pData;
}

// vwriter:
// vpassword:
// returnURL: 可以为空
// forwardURL: 可以为空
JCookieJar * jar;
void test::onPost()
{
	QUrl urlData;
	urlData.addQueryItem("vwriter", QString::fromUtf16(L"都被注册了有没有"));
	urlData.addQueryItem("vpassword", "testtest");
	urlData.addQueryItem("rmflag", "1");
	urlData.addQueryItem("returnURL", "");
	urlData.addQueryItem("forwardURL", "");

	if (NULL != m_pData)
		delete m_pData;
	m_pData = new QByteArray(urlData.encodedQuery());
	QNetworkRequest req(QUrl("http://passport.tianya.cn:80/login?from=index"));
	req.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

	//m_pWebView->load(req, QNetworkAccessManager::PostOperation, *m_pData);
	jar = new JCookieJar();
	m_pNetMan->setCookieJar(jar);
	m_pNetMan->post(req, *m_pData);
	//m_pNetMan->get(QNetworkRequest(QUrl("http://www.baidu.com")));

}

void test::onPostFinished(QNetworkReply * reply)
{
	QString data (reply->readAll());
	data = data.trimmed();
	qDebug() << "recv data: \n"
		<< data << endl;
	qDebug() << "post finish\n";

// 	QWebPage * page = new QWebPage();
// 	
// 	QNetworkAccessManager * pNetMan = page->networkAccessManager();
// 	pNetMan->setCookieJar(jar);
// 
// 	page->mainFrame()->setHtml(data);
	
	//QNetworkCookieJar * pCookieJar = pNetMan->cookieJar();
	jar->output();
	int i = 0;
	++i;
	
}

void test::onWebViewLoadFinished(bool ok)
{
	if (ok)
	{
		qDebug() << "web view load finished \n";
		QWebPage * page = m_pWebView->page();
		QNetworkAccessManager * pNetMan = page->networkAccessManager();
		QNetworkCookieJar * pCookieJar = pNetMan->cookieJar();
		QList<QNetworkCookie> pList = pCookieJar->cookiesForUrl(QUrl("passport.tianya.cn"));
		qDebug() << "cookie number " << pList.count() << endl;
		for (int i = 0 ; i < pList.count(); ++i)
		{
			QNetworkCookie tmp = pList.at(i);
			qDebug() << "domain " << tmp.domain()  << endl
				<< "path " << tmp.path() << endl
				<< "name " << QString(tmp.name()) << endl
				<< "value " << QString(tmp.value()) << endl
				<< "date " << tmp.expirationDate().toString() << endl;
		}
	}
	else
	{
		qDebug() << "web view load failure\n";
	}
}
