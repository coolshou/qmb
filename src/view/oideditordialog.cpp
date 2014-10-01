/**
 *  This file is part of QMB.
 *
 *  Copyright (c) 2013 2014 Juan Jose Salazar Garcia jjslzgc@gmail.com
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

#include "oideditordialog.h"
//#include "snmpoid.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtNetSNMP/qsnmpoid.h>
#include <QtNetSNMP/qsnmpdata.h>

View::OIDEditorDialog::OIDEditorDialog(QtNetSNMP::QSNMPObject *object, QWidget *parent) : QDialog(parent), _object(object)
{
    createWidgets();
    createConnections();
    setWindowTitle(tr("OID Editor"));
    setFixedSize(sizeHint());
    loadObject();
}

void View::OIDEditorDialog::done(int result)
{
    if(result)
        saveObject();

    QDialog::done(result);
}

void View::OIDEditorDialog::textChangedOnValueLineEdit(QString text)
{
    _okPushButton -> setEnabled(!text.isEmpty());
}

void View::OIDEditorDialog::createWidgets()
{
    _nameLabel = new QLabel(tr("Name:"));
    _nameValue = new QLabel;

    _oidLabel = new QLabel(tr("OID:"));
    _oidValue = new QLabel;

    _typeLabel = new QLabel("Type:");
    _typeValue = new QLabel;

    _valueLabel = new QLabel(tr("&Value:"));
    _valueLineEdit = new QLineEdit;
    _valueLabel -> setBuddy(_valueLineEdit);

    _okPushButton = new QPushButton(tr("Ok"));
    _okPushButton -> setDefault(true);
    _okPushButton -> setEnabled(false);

    _cancelPushButton = new QPushButton(tr("Cancel"));

    QGridLayout *topLayout = new QGridLayout;

    topLayout -> addWidget(_nameLabel, 0, 0, 1, 1);
    topLayout -> addWidget(_nameValue, 0, 1, 1, 1);
    topLayout -> addWidget(_oidLabel, 1, 0, 1, 1);
    topLayout -> addWidget(_oidValue, 1, 1, 1, 3);
    topLayout -> addWidget(_typeLabel, 2, 0, 1, 1);
    topLayout -> addWidget(_typeValue, 2, 1, 1, 3);
    topLayout -> addWidget(_valueLabel, 3, 0, 1, 1);
    topLayout -> addWidget(_valueLineEdit, 3, 1, 1, 3);

    QHBoxLayout *bottomLayout = new QHBoxLayout;

    bottomLayout -> addStretch();
    bottomLayout -> addWidget(_okPushButton);
    bottomLayout -> addWidget(_cancelPushButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout -> addLayout(topLayout);
    mainLayout -> addLayout(bottomLayout);

    setLayout(mainLayout);
}

void View::OIDEditorDialog::createConnections()
{
    connect(_valueLineEdit, SIGNAL(textChanged(QString)), this, SLOT(textChangedOnValueLineEdit(QString)));
    connect(_okPushButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_cancelPushButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void View::OIDEditorDialog::loadObject()
{
    QString type;

    switch(_object -> data() -> type()) {
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
    case QtNetSNMP::SNMPDataNull:        type = "NULL";     break;
    default:                             type = "UNKNOWN";   break;
    }

    _nameValue -> setText(_object -> name());
    _oidValue -> setText(_object -> objID() -> textOID());
    _typeValue -> setText(type);
}

void View::OIDEditorDialog::saveObject()
{
    QtNetSNMP::SNMPDataType type = _object -> data() -> type();

    switch(type) {
    case QtNetSNMP::SNMPDataInteger:
    case QtNetSNMP::SNMPDataUnsigned:
    case QtNetSNMP::SNMPDataBits:
    case QtNetSNMP::SNMPDataCounter:
    case QtNetSNMP::SNMPDataTimeTicks: {
        long value = _valueLineEdit -> text().toLong();
        _object -> data() -> setValue(type, &value, sizeof(long));
    } break;
    case QtNetSNMP::SNMPDataCounter64: {
        QtNetSNMP::SNMPCounter64 value;
        value.high = 0;
        value.low = _valueLineEdit -> text().toLong();
        _object -> data() -> setValue(type, &value, sizeof(QtNetSNMP::SNMPCounter64));
    } break;
    case QtNetSNMP::SNMPDataBitString:
    case QtNetSNMP::SNMPDataOctetString:
    case QtNetSNMP::SNMPDataIPAddress: {
        QString value = _valueLineEdit -> text();
        _object -> data() -> setValue(type, const_cast<char *>(value.toStdString().c_str()), sizeof(char) * value.length());
    } break;
    //case QtNetSNMP::SNMPDataObjectId:
    //    break;
    default:
        _object -> data()->setValue(QtNetSNMP::SNMPDataUnknown, 0);
    }
}
