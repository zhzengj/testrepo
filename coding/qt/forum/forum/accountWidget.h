#ifndef _H_ACCOUNT_WIDGET_H_
#define _H_ACCOUNT_WIDGET_H_

#include "ui_account.h"

class JAccountSvr;
class JUserOpWidget;
class QStandardItemModel;
class JAccountWidget : public QWidget
{
	Q_OBJECT
private:
	Ui::Account m_ui;
	JAccountSvr * m_svr;
	JUserOpWidget * m_UserOp;
	QStandardItemModel * m_model;

public:
	explicit JAccountWidget(JAccountSvr * svr, QWidget * parent = 0);
	~JAccountWidget();

protected slots:
	void onItemChged(QStandardItem * item);
	void onAddAccount();
	void onModifyAccount();
	void onDeleteAccount();

protected:
	void setupTable();
	QStandardItem * createItem(const QString & text, bool isEdit = false, bool isChk = false);
};

#endif