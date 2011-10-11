#ifndef _H_ACCOUNT_SVR_H_
#define _H_ACCOUNT_SVR_H_

#include <QObject>
class QDomElement;
class JAccounts;
class JAccountSvr : public QObject
{
	Q_OBJECT
private:
	QStringList m_fileList;
	QVector<QPair<QString, JAccounts*>> m_accounts;
	bool m_isDirty;

public:
	JAccountSvr(QObject *parent = 0);
	~JAccountSvr();
	void loadInfo(const QStringList & strList) throw (QString);
	bool SaveInfo(const QString & file);
	void clear();

	void setDirty(bool isDirty);

	int forumCount();
	JAccounts * getForumAccounts(int index);
	JAccounts * forumAccounts(const QString & forumName);
	QString forumName(int index);
	QStringList forumNames();

protected:
	JAccounts * getForumAccounts(const QString & forumId);
};

#endif