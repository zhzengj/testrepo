#ifndef _H_JTABWIDGET_H_
#define _H_JTABWIDGET_H_

class QListWidget;
class QStackedWidget;
class QWidget;
class QListWidgetItem;
class QIcon;

class JTabWidget : public QObject
{
	Q_OBJECT
private:
	QListWidget * m_lw;
	QStackedWidget * m_sw;

public:
	explicit JTabWidget(QListWidget * lw, QStackedWidget * sw, QObject *parent = 0);
	void addTab(QWidget * w, const QString & n, const QIcon & icon);

protected slots:
	void itemClicked(QListWidgetItem* item);
};

#endif