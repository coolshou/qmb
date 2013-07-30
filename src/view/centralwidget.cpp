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
 * @file centralwidget.cpp
 * @brief Implementacion de metodos de la clase CentralWidget
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Julio 2013
 */

#include "centralwidget.h"
#include "types.h"
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>
#include <QTreeView>
#include <QTextEdit>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

/**
 * @brief Constructor de CentralWidget
 * @param parent Widget padre
 */
View::CentralWidget::CentralWidget(QWidget *parent)
{
    createWidgets();
    createConnections();
}

/**
 * @brief Crea los widgets
 */
void View::CentralWidget::createWidgets()
{
    _agentLabel = new QLabel(tr("&Agent: "));
    _agentLineEdit = new QLineEdit;
    _agentLabel -> setBuddy(_agentLineEdit);

    _portLabel = new QLabel(tr("&Port: "));
    _portSpinBox = new QSpinBox;
    _portSpinBox -> setRange(0, 65535);
    _portLabel -> setBuddy(_portSpinBox);

    _versionLabel = new QLabel(tr("&Version: "));
    _versionComboBox = new QComboBox;
    _versionComboBox -> addItem(tr("SNMPv1"), Model::SNMPv1);
    _versionComboBox -> addItem(tr("SNMPv2c"), Model::SNMPv2);
    _versionComboBox -> addItem(tr("SNMPv3"), Model::SNMPv3);
    _versionLabel -> setBuddy(_versionComboBox);

    _propertiesButton = new QPushButton(tr("Properties"));
    _propertiesButton -> setEnabled(false);

    QHBoxLayout *parametersLayout = new QHBoxLayout;
    parametersLayout -> addWidget(_agentLabel);
    parametersLayout -> addWidget(_agentLineEdit);
    parametersLayout -> addWidget(_portLabel);
    parametersLayout -> addWidget(_portSpinBox);
    parametersLayout -> addWidget(_versionLabel);
    parametersLayout -> addWidget(_versionComboBox);
    parametersLayout -> addWidget(_propertiesButton);

    QGroupBox *parametersGroupBox = new QGroupBox(tr("Parameters"));
    parametersGroupBox -> setLayout(parametersLayout);

    _mibTreeView = new QTreeView;

    _getPushButton = new QPushButton(tr("Get"));
    _getNextPushButton = new QPushButton(tr("Get Next"));
    _getBulkPushButton = new QPushButton(tr("Get Bulk"));
    _setPushButton = new QPushButton(tr("Set"));

    QHBoxLayout *operationsLayout = new QHBoxLayout;
    operationsLayout -> addWidget(_getPushButton);
    operationsLayout -> addWidget(_getNextPushButton);
    operationsLayout -> addWidget(_getBulkPushButton);
    operationsLayout -> addWidget(_setPushButton);

    QVBoxLayout *mibLayout = new QVBoxLayout;
    mibLayout -> addWidget(_mibTreeView);
    mibLayout -> addLayout(operationsLayout);

    QGroupBox *mibGroupBox = new QGroupBox(tr("MIB Tree"));
    mibGroupBox -> setLayout(mibLayout);

    _resultTextEdit = new QTextEdit;

    QHBoxLayout *resultLayout = new QHBoxLayout;
    resultLayout -> addWidget(_resultTextEdit);

    QGroupBox *resultGroupBox = new QGroupBox(tr("Results"));
    resultGroupBox -> setLayout(resultLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout -> addWidget(parametersGroupBox);
    mainLayout -> addWidget(mibGroupBox);
    mainLayout -> addWidget(resultGroupBox);

    setLayout(mainLayout);
}

/**
 * @brief Establece las conexiones
 */
void View::CentralWidget::createConnections()
{

}
