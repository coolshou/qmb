/**
 *  This file is part of QMB.
 *
 *  Copyright (c) 2013 Juan Jose Salazar Garcia jjslzgc@gmail.com
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

/**
 * @file mainwindow.h
 * @brief Declaracion de clase MainWindow
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Julio 2013
 */

#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QSpinBox;
class QComboBox;
class QPushButton;
class QTreeView;
class QTextEdit;
QT_END_NAMESPACE

namespace View
{
    class CentralWidget : public QWidget
    {
        Q_OBJECT
    public:
        CentralWidget(QWidget *parent = 0);
    private:
        void createWidgets();
        void createConnections();
        QLabel *_agentLabel;
        QLineEdit *_agentLineEdit;
        QLabel *_portLabel;
        QSpinBox *_portSpinBox;
        QLabel *_versionLabel;
        QComboBox *_versionComboBox;
        QPushButton *_propertiesButton;
        QTreeView *_mibTreeView;
        QPushButton *_getPushButton;
        QPushButton *_getNextPushButton;
        QPushButton *_getBulkPushButton;
        QPushButton *_setPushButton;
        QTextEdit *_resultTextEdit;
    };
}

#endif // CENTRALWIDGET_H
