#ifndef BROWSER_H
#define BROWSER_H

#include <QtGui/QWidget>
#include "ui_browser.h"
#include <QtWebKit/QtWebKit>

class QLineEdit;
class QPushButton;
class QWebView;

class browser : public QWidget
{
	Q_OBJECT

public:
	browser(QWidget *parent = 0, Qt::WFlags flags = 0);
	~browser();

protected slots:
	void onLoadBtnClk();

private:
	Ui::browserClass ui;
	QLineEdit * m_edit;
	QPushButton * m_loadBtn;
	QWebView * m_webView;
};

#endif // BROWSER_H
