#ifndef _H_J_APPLICATION_H_
#define _H_J_APPLICATION_H_

class JAccountSvr;
class JApplication: public QApplication
{
	Q_OBJECT
private:
	JAccountSvr * m_pAccountSrv;
	QVector<QPair<QString, QString>> m_vtImport;

public:
	JApplication(int &argc, char **argv);
	//加载失败，直接退出
	void loadInfo(const QString & file);
	void saveInfo();
	QStringList getFileById(const QString & id) const;
	JAccountSvr * accountSvr();

protected:
	void loadInfo();
};

#define jApp ((JApplication*)QCoreApplication::instance())

#endif