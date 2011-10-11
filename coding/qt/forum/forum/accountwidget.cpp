/********************************************************************
	created:	26:6:2011   21:18
	file base:	accountwidget.cpp
	author:		zhzengj
	
*********************************************************************/

#include "stdafx.h"
#include "accountwidget.h"
#include "accountsvr.h"
#include "accounts.h"
#include "useropwidget.h"

JAccountWidget::JAccountWidget(JAccountSvr * svr, QWidget * parent /* = 0 */)
:QWidget(parent)
,m_svr(svr), m_model(NULL)
{
	m_ui.setupUi(this);
	setupTable();
	connect(m_ui.acAddBtn, SIGNAL(clicked()), this, SLOT(onAddAccount()));
	connect(m_ui.acModifyBtn, SIGNAL(clicked()), this, SLOT(onModifyAccount()));
	connect(m_ui.acDelBtn, SIGNAL(clicked()), this, SLOT(onDeleteAccount()));
	QShortcut * sc = new QShortcut(QKeySequence(QKeySequence::Delete), m_ui.tableView);
	connect(sc, SIGNAL(activated()), this, SLOT(onDeleteAccount()));
	m_UserOp = new JUserOpWidget(this);
}

JAccountWidget::~JAccountWidget()
{
}

void JAccountWidget::setupTable()
{
	m_model = new QStandardItemModel(this);
	m_model->setColumnCount(5);
	m_model->setHeaderData(0, Qt::Horizontal, QString::fromUtf16(L"启用"));
	m_model->setHeaderData(1, Qt::Horizontal, QString::fromUtf16(L"论坛"));
	m_model->setHeaderData(2, Qt::Horizontal, QString::fromUtf16(L"用户名"));
	m_model->setHeaderData(3, Qt::Horizontal, QString::fromUtf16(L"密码"));
	m_model->setHeaderData(4, Qt::Horizontal, QString::fromUtf16(L"状态"));

	m_ui.tableView->setModel(m_model);
	m_ui.tableView->horizontalHeader()->setStretchLastSection(true);
	m_ui.tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
	m_ui.tableView->setShowGrid(true);
	m_ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	connect(m_model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(onItemChged(QStandardItem*)));

	//add data
	if (NULL != m_svr)
	{
		JAccounts * acs;
		int rows = 0;
		QStandardItem * pItem;
		for (int i = 0; i < m_svr->forumCount(); ++i)
		{
			acs = m_svr->getForumAccounts(i);
			for (int j = 0; j < acs->count(); ++j)
			{
				m_model->insertRow(rows);

				pItem = createItem("", false, true);
				pItem->setCheckState(acs->at(j)->isEnable() ? Qt::Checked : Qt::Unchecked);
				m_model->setItem(rows, 0, pItem);

				m_model->setItem(rows, 1, createItem(acs->getForumName()));
				m_model->setItem(rows, 2, createItem(acs->at(j)->nickName()));
				m_model->setItem(rows, 3, createItem(acs->at(j)->plainPwd()));
				m_model->setItem(rows, 4, createItem("VA"));
				++rows;
			}
		}
	}
	m_ui.tableView->resizeColumnsToContents();
}

QStandardItem * JAccountWidget::createItem(const QString & text, bool isEdit /* = false */, bool isChk /* = false */)
{
	QStandardItem* pItem = new QStandardItem();
	pItem->setText(text);
	pItem->setEditable(isEdit);
	pItem->setCheckable(isChk);
	return pItem;
}

void JAccountWidget::onItemChged(QStandardItem * item)
{
	qDebug() << "item change\n";
}

void JAccountWidget::onAddAccount()
{
	JAccounts * acs;
	UserOpData data;
	data.m_forumName = m_svr->forumNames();
	if (QDialog::Accepted == m_UserOp->showModal(data))
	{
		acs = m_svr->forumAccounts(m_UserOp->forum());
		if (acs)
		{
			if (acs->isExist(m_UserOp->name()))
			{
				QString str = QString("用户 %1 已经存在").arg(m_UserOp->name());
				QMessageBox::warning(m_UserOp, "提示", str);
			}
			else
			{
				m_svr->setDirty(true);
				acs->addAccount(m_UserOp->name(), m_UserOp->pwd(), m_UserOp->isUserEnable());

				int rows = m_model->rowCount();
				m_model->insertRow(rows);

				QStandardItem * pItem = createItem("", false, true);
				pItem->setCheckState(m_UserOp->isUserEnable() ? Qt::Checked : Qt::Unchecked);
				m_model->setItem(rows, 0, pItem);

				m_model->setItem(rows, 1, createItem(m_UserOp->forum()));
				m_model->setItem(rows, 2, createItem(m_UserOp->name()));
				m_model->setItem(rows, 3, createItem(m_UserOp->pwd()));
				m_model->setItem(rows, 4, createItem("VA"));
			}
		}
	}
}

void JAccountWidget::onModifyAccount()
{
	int selRow = m_ui.tableView->currentIndex().row();
	if (selRow < 0)
	{		
		QMessageBox::warning(this, "提示", "请先选择一个用户");
		return;
	}

	UserOpData data;
	QString oldForumName = m_model->data(m_model->index(selRow, 1)).toString();
	
	data.m_bEnabled = m_model->item(selRow, 0)->checkState();//m_model->data(m_model->index(selRow, 0)).toInt();
	data.m_forumName = m_svr->forumNames();
	data.m_name = m_model->data(m_model->index(selRow, 2)).toString();
	data.m_pwd = m_model->data(m_model->index(selRow, 3)).toString();

	JAccounts * acs;
	if (QDialog::Accepted == m_UserOp->showModal(data))
	{
		if (oldForumName == m_UserOp->forum() && data.m_name == m_UserOp->name()
			&& data.m_pwd == m_UserOp->pwd() && data.m_bEnabled == m_UserOp->isUserEnable())
			return;

		m_svr->setDirty(true);
		acs = m_svr->forumAccounts(m_UserOp->forum());
		if (oldForumName != m_UserOp->forum())
		{
			m_svr->forumAccounts(oldForumName)->removeAccount(data.m_name);
			acs->addAccount(m_UserOp->name(), m_UserOp->pwd(), m_UserOp->isUserEnable());
		}
		else
			acs->modifyAccount(m_UserOp->name(), m_UserOp->pwd(), m_UserOp->isUserEnable());

		m_model->item(selRow, 0)->setCheckState(m_UserOp->isUserEnable() ? Qt::Checked : Qt::Unchecked);
		m_model->item(selRow, 1)->setText(m_UserOp->forum());
		m_model->item(selRow, 2)->setText(m_UserOp->name());
		m_model->item(selRow, 3)->setText(m_UserOp->pwd());
	}
}

void JAccountWidget::onDeleteAccount()
{
	int selRow = m_ui.tableView->currentIndex().row();
	if (selRow < 0)
	{		
		QMessageBox::warning(this, "提示", "请先选择一个用户");
		return;
	}

	QString oldForumName = m_model->data(m_model->index(selRow, 1)).toString();
	QString oldName = m_model->data(m_model->index(selRow, 2)).toString();

	m_svr->forumAccounts(oldForumName)->removeAccount(oldName);
	m_model->removeRow(selRow);
	m_svr->setDirty(true);
}
