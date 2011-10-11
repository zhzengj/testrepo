#ifndef _H_POST_WIDGET_H__
#define _H_POST_WIDGET_H__

namespace Ui {
	class JPostWidget;
} 

class JPostWidget : public QWidget
{
private:
	Ui::JPostWidget * m_ui;
public:
	JPostWidget(QWidget * parent = NULL);
};

#endif