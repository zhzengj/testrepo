#include "stdafx.h"
#include "browser.h"
#include <QtGui/QtGui>

browser::browser(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);

	m_edit = new QLineEdit(this);
	m_loadBtn = new QPushButton("load", this);
	m_webView = new QWebView(this);
	m_webView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	QHBoxLayout * hly = new QHBoxLayout();
	hly->addWidget(m_edit);
	hly->addWidget(m_loadBtn);

	QVBoxLayout * vly = new QVBoxLayout(this);
	vly->addLayout(hly);
	vly->addWidget(m_webView);

	connect(m_loadBtn, SIGNAL(clicked()), this, SLOT(onLoadBtnClk()));
}

browser::~browser()
{

}

void browser::onLoadBtnClk()
{
	m_webView->load(m_edit->text());
}
