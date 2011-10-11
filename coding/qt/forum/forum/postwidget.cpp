/********************************************************************
	created:	31:7:2011   17:40
	file base:	postwidget.cpp
	author:		zhzengj
	
*********************************************************************/

#include "stdafx.h"
#include "postwidget.h"
#include "ui_post.h"

JPostWidget::JPostWidget(QWidget * parent/*= NULL*/)
:QWidget(parent), m_ui(new Ui::JPostWidget())
{
	m_ui->setupUi(this);
}