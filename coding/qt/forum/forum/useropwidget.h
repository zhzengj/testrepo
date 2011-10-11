#ifndef _H_USER_OP_WIDGET_
#define _H_USER_OP_WIDGET_

namespace Ui {
	class userop;
}

class JAccountSvr;

struct UserOpData
{
	QStringList m_forumName;
	int			m_nSelected;
	QString		m_name;
	QString		m_pwd;
	bool		m_bEnabled;
	UserOpData()
		:m_nSelected(0), m_bEnabled(true)
	{}
	UserOpData(const QStringList & forums, const QString & name, const QString & pwd, 
		bool enabled = true, int selected = 0)
		:m_forumName(forums), m_name(name), m_pwd(pwd), m_bEnabled(enabled), m_nSelected(selected)
	{}
};

class JUserOpWidget : public QDialog
{
	Q_OBJECT
private:
	class Ui::userop * m_ui;

public:
	JUserOpWidget(QWidget * parent = 0);
	int showModal(const UserOpData & data);
	QString forum();
	QString name();
	QString pwd();
	bool isUserEnable();

protected slots:
	void onOkBtnClicked();
};

#endif