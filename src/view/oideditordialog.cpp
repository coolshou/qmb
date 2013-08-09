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
 * @file oideditordialog.cpp
 * @brief Implementacion de metodos de la clase OIDEditorDialog
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Agosto 2013
 */

#include "oideditordialog.h"
#include "snmpoid.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

/**
 * @brief Constructor de OIDEditorDialog
 * @param object OID al que asignar el valor
 * @param parent Widget padre
 */
View::OIDEditorDialog::OIDEditorDialog(Model::SNMPOID *object, QWidget *parent) : QDialog(parent), _object(object)
{
    createWidgets();
    createConnections();
    setWindowTitle(tr("OID Editor"));
    setFixedSize(sizeHint());
    loadObject();
}

/**
 * @brief Establece el resultado de Aceptado/Rechazado del cuadro de dialogo
 * @param result Resultado del cuadro de dialogo
 */
void View::OIDEditorDialog::done(int result)
{
    if(result)
        saveObject();

    QDialog::done(result);
}

/**
 * @brief Ranura en habilita/inhabilita el boton ok
 * @param text Texto en QLineEdit
 */
void View::OIDEditorDialog::textChangedOnValueLineEdit(QString text)
{
    _okPushButton -> setEnabled(!text.isEmpty());
}

/**
 * @brief Crea los widgets
 */
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

/**
 * @brief Establece las conexiones
 */
void View::OIDEditorDialog::createConnections()
{
    connect(_valueLineEdit, SIGNAL(textChanged(QString)), this, SLOT(textChangedOnValueLineEdit(QString)));
    connect(_okPushButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_cancelPushButton, SIGNAL(clicked()), this, SLOT(reject()));
}

/**
 * @brief Carga el OID en el cuadro de dialogo
 */
void View::OIDEditorDialog::loadObject()
{
    QString type;

    switch(_object -> data() -> type()) {
    case Model::SNMPDataInteger:     type = "INTEGER";   break;
    case Model::SNMPDataUnsigned:    type = "UNSIGNED";  break;
    case Model::SNMPDataBits:        type = "BITS";      break;
    case Model::SNMPDataCounter:     type = "COUNTER";   break;
    case Model::SNMPDataTimeTicks:   type = "TIMETICKS"; break;
    case Model::SNMPDataCounter64:   type = "COUNTER64"; break;
    case Model::SNMPDataBitString:   type = "BITSTRING"; break;
    case Model::SNMPDataOctetString: type = "STRING";    break;
    case Model::SNMPDataIPAddress:   type = "IPADDRESS"; break;
    case Model::SNMPDataObjectId:    type = "OBJID";     break;
    case Model::SNMPDataNull:        type = "NULL";     break;
    default:                         type = "UNKNOWN";   break;
    }

    _nameValue -> setText(_object -> name().c_str());
    _oidValue -> setText(_object -> strOID().c_str());
    _typeValue -> setText(type);
}
#include <QDebug>
/**
 * @brief Guarda el valor introducido en el OID
 */
void View::OIDEditorDialog::saveObject()
{
    switch(_object -> data() -> type()) {
    case Model::SNMPDataInteger:
    case Model::SNMPDataUnsigned:
    case Model::SNMPDataBits:
    case Model::SNMPDataCounter:
    case Model::SNMPDataTimeTicks: {
        long value = _valueLineEdit -> text().toLong();
        _object -> data() -> setLength(sizeof(long));
        _object -> data() -> setValue(&value);
    } break;
    case Model::SNMPDataCounter64: {
        Model::SNMPCounter64 value;
        value.high = 0;
        value.low = _valueLineEdit -> text().toLong();
        _object -> data() -> setLength(sizeof(Model::SNMPCounter64));
        _object -> data() -> setValue(&value);
    } break;
    case Model::SNMPDataBitString:
    case Model::SNMPDataOctetString:
    case Model::SNMPDataIPAddress: {
        QString value = _valueLineEdit -> text();
        _object -> data() -> setLength(sizeof(char) * value.length());
        _object -> data() -> setValue((char *) value.toStdString().c_str());
    } break;
    //case Model::SNMPDataObjectId:
    //    break;
    default:
        _object -> data() -> setValue(0);
    }
}
