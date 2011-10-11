#ifndef _H_ACCOUNTS_H_
#define _H_ACCOUNTS_H_

class JAccounts;

class JAccount
{
private:
	QString m_name;
	QString m_pwd;
	int		m_nState;
	enum {
		JAC_Enabled = 0
	};

public:
	void setEnable(bool isEnable);
	QString nickName();
	QString plainPwd();
	bool isEnable();

protected:
	bool hasState(int en);
	void setState(int en);
	void clearState(int en);

	friend JAccounts;
};

//һ����̳�������û�
class JAccounts
{
private:
	QString m_forumName;//��ʾ����
	QString m_id; //�ڲ�ʹ����
	//name, account
	QMap<QString, JAccount*> m_accounts;
	QList<QString> m_accNames;

public:
	~JAccounts();
	void clear();
	void loadInfo(const QDomElement & e);
	void saveInfo(QXmlStreamWriter & s);

	QString getForumName();
	int count();
	JAccount * at(int index);
	void removeAccount(const QString & name);
	bool isExist(const QString & name);
	bool addAccount(const QString & name, const QString & plainPwd, bool isEnable = true);
	bool modifyAccount(const QString & name, const QString & plainPwd, bool isEnable = true);
};



#endif
