/********************************************************************
	created:	26:6:2011   21:04
	file base:	jtabwidget.cpp
	author:		zhzengj
	
*********************************************************************/

#include "stdafx.h"
#include "jtabwidget.h"

JTabWidget::JTabWidget(QListWidget * lw, QStackedWidget * sw, QObject *parent /* = 0 */)
:QObject(parent), m_lw(lw), m_sw(sw)
{
	m_lw->setViewMode(QListView::IconMode);
	m_lw->setMovement(QListView::Static);
	m_lw->setMaximumWidth(100);
	m_lw->setIconSize(QSize(64, 64));
	m_lw->setSpacing(12);
	m_lw->setUniformItemSizes(true);
	connect(m_lw, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(itemClicked(QListWidgetItem*)));
}

void JTabWidget::addTab(QWidget * w, const QString & n, const QIcon & icon)
{
	if (-1 == m_sw->indexOf(w))
	{
		QListWidgetItem * item = new QListWidgetItem(m_lw);
		item->setText(n);
		item->setIcon(icon);
		item->setTextAlignment(Qt::AlignHCenter);
		item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		m_lw->addItem(item);
		m_sw->addWidget(w);

		if (1 == m_lw->count())
		{
			m_lw->setCurrentItem(item);
			m_sw->setCurrentIndex(m_lw->currentRow());
		}
	}
}

void JTabWidget::itemClicked(QListWidgetItem* item)
{
	m_lw->setCurrentItem(item);
	m_sw->setCurrentIndex(m_lw->currentRow());
}
