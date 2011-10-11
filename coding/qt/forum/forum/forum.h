#ifndef FORUM_H
#define FORUM_H

#include <QtGui/QMainWindow>
#include "ui_forum.h"
class JTabWidget;
class JAccountWidget;
class JPostWidget;

class forum : public QMainWindow
{
	Q_OBJECT

public:
	forum(QWidget *parent = 0, Qt::WFlags flags = 0);
	~forum();

protected:
	void init();

private:
	Ui::forumClass ui;
	JTabWidget * m_tabWidget;
	JAccountWidget * m_accountWidget;
	JPostWidget * m_postWidget;
};

#endif // FORUM_H
