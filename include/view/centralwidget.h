/**
 *  This file is part of QMB.
 *
 *  Copyright (c) 2013-2014 Juan Jose Salazar Garcia jjslzgc@gmail.com
 *
 *  QMB is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  QMB is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with QMB.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QComboBox;
class QPushButton;
class QTreeView;
class QTextEdit;
QT_END_NAMESPACE

namespace View
{
    class MIBTreeModel;
    class MIBTreeProxyModel;

    class CentralWidget : public QWidget
    {
        Q_OBJECT
    public:
        CentralWidget(QWidget *parent = 0);
        ~CentralWidget();
    signals:
        void statusChanged(const QString& status);
    public slots:
        void loadMIBTree();
    private slots:
        void invokeOperation();
        void properties();
        void readyToInvoke();
    private:
        void createWidgets();
        void createConnections();
        void loadProperties();

        QLabel *_agentLabel;
        QLineEdit *_agentLineEdit;
        QLabel *_versionLabel;
        QComboBox *_versionComboBox;
        QPushButton *_propertiesButton;
        QTreeView *_mibTreeView;
        MIBTreeModel *_mibTreeModel;
        MIBTreeProxyModel *_mibTreeProxyModel;
        QPushButton *_getPushButton;
        QPushButton *_getNextPushButton;
        QPushButton *_getBulkPushButton;
        QPushButton *_setPushButton;
        QTextEdit *_resultTextEdit;

        QString _community;
        unsigned short _nonRepeaters;
        unsigned short _maxRepetitions;
    };
}

#endif // CENTRALWIDGET_H
