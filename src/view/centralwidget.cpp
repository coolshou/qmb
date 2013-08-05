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
#include "mibtreemodel.h"
#include "mibtreeproxymodel.h"
#include "snmpmanager.h"
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
View::CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    createWidgets();
    createConnections();
    loadMIBTree();
}

/**
 * @brief Destructor de CentralWidget
 */
View::CentralWidget::~CentralWidget()
{
    delete _mibTreeModel;
    delete _mibTreeProxyModel;
}

/**
 * @brief Invoca operacion SNMP
 */
void View::CentralWidget::invokeOperation()
{
    QModelIndex index = _mibTreeProxyModel -> mapToSource(_mibTreeView -> currentIndex());
    Model::SNMPNode *node = static_cast<Model::SNMPNode *>(index.internalPointer());
    QObject *sender = QObject::sender();

    //if(sender == _getPushButton)
        // Invoke SNMP GET
    //else if(sender == _getNextPushButton)
        // Invoke SNMP GET NEXT
    //else if(sender == _getBulkPushButton)
        // Invoke SNMP GET BULK
    //else if(sender == _setPushButton)
        // Invoke SNMP SET
}

/**
 * @brief Activa/Desactiva botones de operacion ante cambios en los otros widgets
 */
void View::CentralWidget::readyToInvoke()
{
    int row = _mibTreeView -> currentIndex().row();
    bool agent = !(_agentLineEdit -> text().isEmpty()) && _portSpinBox -> value();
    Model::SNMPVersion version = static_cast<Model::SNMPVersion>(_versionComboBox -> itemData(_versionComboBox -> currentIndex()).toInt());

    _getPushButton -> setEnabled(agent && row != -1);
    _getNextPushButton -> setEnabled(agent && row != -1);
    _getBulkPushButton -> setEnabled(agent && version != Model::SNMPv1 && row != -1);
    _setPushButton -> setEnabled(agent && row != -1);
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
    _mibTreeView -> setAlternatingRowColors(true);
    _mibTreeModel = new MIBTreeModel;
    _mibTreeProxyModel = new MIBTreeProxyModel;
    _mibTreeProxyModel -> setSourceModel(_mibTreeModel);
    _mibTreeView -> setModel(_mibTreeProxyModel);
    _mibTreeView -> setSortingEnabled(true);
    _mibTreeView -> sortByColumn(0, Qt::AscendingOrder);

    _getPushButton = new QPushButton(tr("Get"));
    _getPushButton -> setEnabled(false);
    _getNextPushButton = new QPushButton(tr("Get Next"));
    _getNextPushButton -> setEnabled(false);
    _getBulkPushButton = new QPushButton(tr("Get Bulk"));
    _getBulkPushButton -> setEnabled(false);
    _setPushButton = new QPushButton(tr("Set"));
    _setPushButton -> setEnabled(false);

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
    connect(_getPushButton, SIGNAL(clicked()), this, SLOT(invokeOperation()));
    connect(_getNextPushButton, SIGNAL(clicked()), this, SLOT(invokeOperation()));
    connect(_getBulkPushButton, SIGNAL(clicked()), this, SLOT(invokeOperation()));
    connect(_setPushButton, SIGNAL(clicked()), this, SLOT(invokeOperation()));
    connect(_agentLineEdit, SIGNAL(textChanged(QString)), this, SLOT(readyToInvoke()));
    connect(_portSpinBox, SIGNAL(valueChanged(int)), this, SLOT(readyToInvoke()));
    connect(_versionComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(readyToInvoke()));
    connect(_mibTreeView -> selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(readyToInvoke()));
}

/**
 * @brief Carga el arbol MIB en el modelo MIBTreeModel
 */
void View::CentralWidget::loadMIBTree()
{
    emit statusChanged(tr("Loading MIB Tree ..."));

    Model::SNMPNode *root = Model::SNMPManager::getMIBTree();

    _mibTreeModel -> setRoot(root);

    emit statusChanged(tr("MIB Tree loaded successfully"));
}
