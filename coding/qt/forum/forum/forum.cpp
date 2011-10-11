#include "stdafx.h"
#include "forum.h"
#include "jtabwidget.h"
#include "accountwidget.h"
#include "japplication.h"
#include "postwidget.h"

forum::forum(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	ui.mainToolBar->setVisible(false);
	ui.statusBar->setVisible(false);

	m_tabWidget = new JTabWidget(ui.listWidget, ui.stackedWidget, this);
	m_accountWidget = new JAccountWidget(jApp->accountSvr(), this);
	m_postWidget = new JPostWidget(this);

	init();
}

forum::~forum()
{

}

void forum::init()
{
	m_tabWidget->addTab(m_accountWidget, QString::fromUtf16(L"用户管理"), QIcon(":/forum/icon/users.png"));
	m_tabWidget->addTab(m_postWidget, QString::fromUtf16(L"发帖"), QIcon(":/forum/icon/post.png"));
	m_tabWidget->addTab(new QWidget(), QString::fromUtf16(L"回帖"), QIcon(":/forum/icon/reply.png"));
}
