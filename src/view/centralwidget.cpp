/**
 *  This file is part of QMB.
 *
 *  Copyright (c) 2013-2015 Juan Jose Salazar Garcia jjslzgc@gmail.com
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

#include "centralwidget.h"
#include "mibtreemodel.h"
#include "mibtreeproxymodel.h"
#include "propertiesdialog.h"
#include "oideditordialog.h"
#include "global.h"
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTreeView>
#include <QTextEdit>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QtNetSNMP/qsnmpmanager.h>
#include <QtNetSNMP/qmibtree.h>
#include <QtNetSNMP/qsnmpobject.h>
#include <QtNetSNMP/qsnmpoid.h>
#include <QtNetSNMP/qsnmpdata.h>

View::CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    createWidgets();
    createConnections();
    loadMIBTree();
    loadProperties();
}

View::CentralWidget::~CentralWidget()
{
    delete _mibTreeModel;
    delete _mibTreeProxyModel;
}

void View::CentralWidget::loadMIBTree()
{
    emit statusChanged(tr("Loading MIB Tree ..."));

    QtNetSNMP::QSNMPManager *snmpManager = QtNetSNMP::QSNMPManager::instance();
    QtNetSNMP::QMIBTree *mibTree = snmpManager->getMIBModule();

    _mibTreeModel -> setRoot(mibTree);

    emit statusChanged(tr("MIB Tree loaded successfully"));
}

void View::CentralWidget::invokeOperation()
{
    QObject *sender = QObject::sender();
    QModelIndex index = _mibTreeProxyModel -> mapToSource(_mibTreeView -> currentIndex());
    QtNetSNMP::QSNMPManager *snmpManager = QtNetSNMP::QSNMPManager::instance();
    QtNetSNMP::QMIBTree *node = static_cast<QtNetSNMP::QMIBTree *>(index.internalPointer());
    QtNetSNMP::QSNMPObject *object = new QtNetSNMP::QSNMPObject(*node -> object());
    QString agent = _agentLineEdit -> text();
    QtNetSNMP::SNMPVersion version = static_cast<QtNetSNMP::SNMPVersion>(_versionComboBox -> itemData(_versionComboBox -> currentIndex()).toInt());
    QVector<QtNetSNMP::QSNMPObject *> objs;
    objs.push_back(object);

    _resultTextEdit -> clear();
    _resultTextEdit -> append(tr("### SNMP Operation to %1 invoked ###").arg(agent));

    try {
        if(sender == _getPushButton)
            snmpManager -> snmpget(version, _community, agent, objs);
        else if(sender == _getNextPushButton)
            snmpManager -> snmpgetnext(version, _community, agent, objs);
        else if(sender == _getBulkPushButton)
            snmpManager -> snmpgetbulk(version, _community, agent, objs, _nonRepeaters, _maxRepetitions);
        else if(sender == _setPushButton) {
            if(object -> access() == QtNetSNMP::MIBAccessReadOnly) {
                QMessageBox::critical(this, tr("SNMP Exception"), tr("Object is not writable"), QMessageBox::Ok);
                delete object;
                return;
            }

            OIDEditorDialog editorDialog(object, this);

            if(editorDialog.exec() == QDialog::Rejected) {
                delete object;
                return;
            }

            snmpManager -> snmpset(version, _community, agent, objs);
        }

        foreach(QtNetSNMP::QSNMPObject *object, objs) {
            QString type;

            switch(object -> data() -> type()) {
            case QtNetSNMP::SNMPDataInteger:     type = "INTEGER";   break;
            case QtNetSNMP::SNMPDataUnsigned:    type = "UNSIGNED";  break;
            case QtNetSNMP::SNMPDataBits:        type = "BITS";      break;
            case QtNetSNMP::SNMPDataCounter:     type = "COUNTER";   break;
            case QtNetSNMP::SNMPDataTimeTicks:   type = "TIMETICKS"; break;
            case QtNetSNMP::SNMPDataCounter64:   type = "COUNTER64"; break;
            case QtNetSNMP::SNMPDataBitString:   type = "BITSTRING"; break;
            case QtNetSNMP::SNMPDataOctetString: type = "STRING";    break;
            case QtNetSNMP::SNMPDataIPAddress:   type = "IPADDRESS"; break;
            case QtNetSNMP::SNMPDataObjectId:    type = "OBJID";     break;
            case QtNetSNMP::SNMPDataNull:        type = "NULL";      break;
            default:                             type = "UNKNOWN";   break;
            }

            _resultTextEdit -> append(QString("%1 = %2 : %3").arg(object -> objID() -> textOID()).arg(type).arg(""));
        }

        _resultTextEdit -> append(tr("### SNMP Operation finished ###"));
    } catch(QtNetSNMP::QSNMPException& exception) {
        QMessageBox::critical(this, tr("SNMP Exception"), exception.message(), QMessageBox::Ok);
    }
}

void View::CentralWidget::properties()
{
    PropertiesDialog dialog(_community, _nonRepeaters, _maxRepetitions, this);

    if(dialog.exec() == QDialog::Accepted) {
        _community = dialog.community();
        _nonRepeaters = dialog.nonRepeaters();
        _maxRepetitions = dialog.maxRepetitions();
    }
}

void View::CentralWidget::readyToInvoke()
{
    QModelIndex index;
    QtNetSNMP::QMIBTree *node;
    bool internalNode = true;
    int row = _mibTreeView -> currentIndex().row();
    bool agent = !(_agentLineEdit -> text().isEmpty());
    QtNetSNMP::SNMPVersion version = static_cast<QtNetSNMP::SNMPVersion>(_versionComboBox -> itemData(_versionComboBox -> currentIndex()).toInt());

    if(row != -1) {
        index = _mibTreeProxyModel -> mapToSource(_mibTreeView -> currentIndex());
        node = static_cast<QtNetSNMP::QMIBTree *>(index.internalPointer());
        internalNode = !node -> childs().isEmpty();
    }

    _getPushButton -> setEnabled(agent && row != -1 && !internalNode);
    _getNextPushButton -> setEnabled(agent && row != -1);
    _getBulkPushButton -> setEnabled(agent && version != QtNetSNMP::SNMPv1 && row != -1);
    _setPushButton -> setEnabled(agent && row != -1 && !internalNode);
}

void View::CentralWidget::createWidgets()
{
    _agentLabel = new QLabel(tr("&Agent: "));
    _agentLineEdit = new QLineEdit;
    _agentLabel -> setBuddy(_agentLineEdit);

    _versionLabel = new QLabel(tr("&Version: "));
    _versionComboBox = new QComboBox;
    _versionComboBox -> addItem(tr("v1"), QtNetSNMP::SNMPv1);
    _versionComboBox -> addItem(tr("v2C"), QtNetSNMP::SNMPv2);
    //_versionComboBox -> addItem(tr("v3"), QtNetSNMP::SNMPv3);
    _versionLabel -> setBuddy(_versionComboBox);

    _propertiesButton = new QPushButton(tr("Properties"));

    QHBoxLayout *parametersLayout = new QHBoxLayout;
    parametersLayout -> addWidget(_agentLabel);
    parametersLayout -> addWidget(_agentLineEdit);
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
    _resultTextEdit -> setReadOnly(true);

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

void View::CentralWidget::createConnections()
{
    connect(_propertiesButton, SIGNAL(clicked()), this, SLOT(properties()));
    connect(_getPushButton, SIGNAL(clicked()), this, SLOT(invokeOperation()));
    connect(_getNextPushButton, SIGNAL(clicked()), this, SLOT(invokeOperation()));
    connect(_getBulkPushButton, SIGNAL(clicked()), this, SLOT(invokeOperation()));
    connect(_setPushButton, SIGNAL(clicked()), this, SLOT(invokeOperation()));
    connect(_agentLineEdit, SIGNAL(textChanged(QString)), this, SLOT(readyToInvoke()));
    connect(_versionComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(readyToInvoke()));
    connect(_mibTreeView -> selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this, SLOT(readyToInvoke()));
}

void View::CentralWidget::loadProperties()
{
    _community = DEFAULT_COMMUNITY_NAME;
    _nonRepeaters = DEFAULT_NON_REPEATERS;
    _maxRepetitions = DEFAULT_MAX_REPETITIONS;
}
