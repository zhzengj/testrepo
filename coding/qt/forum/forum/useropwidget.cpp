/********************************************************************
	created:	10:7:2011   10:58
	file base:	useropwidget.cpp
	author:		zhzengj
	
*********************************************************************/

#include "stdafx.h"
#include "useropwidget.h"
#include "ui_userop.h"


JUserOpWidget::JUserOpWidget(QWidget * parent /* = 0 */)
:QDialog(parent)
{
	m_ui = new Ui::userop();
	m_ui->setupUi(this);
	connect(m_ui->okBtn, SIGNAL(clicked()), this, SLOT(onOkBtnClicked()));
	connect(m_ui->cancelBtn, SIGNAL(clicked()), this, SLOT(reject()));
}

int JUserOpWidget::showModal(const UserOpData & data)
{
	//clear
	m_ui->forumName->clear();

	m_ui->forumName->addItems(data.m_forumName);
	m_ui->forumName->setCurrentIndex(data.m_nSelected);
	m_ui->name->setText(data.m_name);
	m_ui->password->setText(data.m_pwd);
	m_ui->enableRbtn->setChecked(data.m_bEnabled);
	m_ui->disableRbtn->setChecked(!data.m_bEnabled);

	return exec();
}

QString JUserOpWidget::forum()
{
	return m_ui->forumName->currentText();
}

QString JUserOpWidget::name()
{
	return m_ui->name->text();
}

QString JUserOpWidget::pwd()
{
	return m_ui->password->text();
}

bool JUserOpWidget::isUserEnable()
{
	return m_ui->enableRbtn->isChecked();
}

void JUserOpWidget::onOkBtnClicked()
{
	if (m_ui->name->text().isEmpty() || m_ui->password->text().isEmpty())
	{
		QMessageBox::warning(this, "提示", "用户名或者密码不能为空!");
		return;
	}
	accept();
}
