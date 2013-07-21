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
 * @file snmpdata.cpp
 * @brief Implementacion de metodos de la clase SNMPData
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Julio 2013
 */

#include "snmpdata.h"
#include <algorithm>
#include <cstring>

/**
 * @brief Constructor de SNMPData
 * @param type Tipo de dato
 * @param value Valor del dato
 */
Model::SNMPData::SNMPData(SNMPDataType type, void *value) : _type(type)
{
    initValue(value);
}

/**
 * @brief Constructor copia de SNMPData
 * @param snmpData Objeto origen
 */
Model::SNMPData::SNMPData(const SNMPData& snmpData)
{
    *this = snmpData;
}

/**
 * @brief Destructor de SNMPData
 */
Model::SNMPData::~SNMPData()
{
    deleteValue();
}

/**
 * @brief Redefinicion de operador de asignacion
 * @param snmpData Objeto origen
 * @return
 */
Model::SNMPData& Model::SNMPData::operator=(const SNMPData& snmpData)
{
    _type = snmpData.type();
    newValue(snmpData.value());

    return *this;
}

/**
 * @brief Devuelve el valor del dato
 * @return Valor del dato
 */
void *Model::SNMPData::value() const
{
    void *vp;

    switch(_type) {
    case SNMPDataInteger:
    case SNMPDataUnsigned:
    case SNMPDataBits:
    case SNMPDataCounter:
    case SNMPDataTimeTicks:
        vp = _value.integer;
        break;
    case SNMPDataCounter64:
        vp = _value.counter64;
        break;
    case SNMPDataBitString:
        vp = _value.bitstring;
        break;
    case SNMPDataOctetString:
    case SNMPDataIPAddress:
        vp = _value.string;
        break;
    case SNMPDataObjectId:
        vp = _value.objid;
        break;
    default:
        vp = 0;
    }

    return vp;
}

/**
 * @brief Establece el valor del dato
 * @param value Valor del dato
 */
void Model::SNMPData::setValue(void *value)
{
    newValue(value);
}

/**
 * @brief Devuelve el tipo del dato
 * @return Tipo del dato
 */
Model::SNMPDataType Model::SNMPData::type() const
{
    return _type;
}

/**
 * @brief Asigna memoria para el valor del dato
 * @param value Nuevo valor del dato
 */
void Model::SNMPData::newValue(void *value)
{
    deleteValue();

    switch(_type) {
    case SNMPDataInteger:
    case SNMPDataUnsigned:
    case SNMPDataBits:
    case SNMPDataCounter:
    case SNMPDataTimeTicks:
        _value.integer = new long;
        *_value.integer = *((long *) value);
        break;
    case SNMPDataCounter64:
        _value.counter64 = new SNMPCounter64;
        *_value.counter64 = *((SNMPCounter64 *) value);
        break;
    case SNMPDataBitString:
        _value.bitstring = new unsigned char;
        std::copy(((unsigned char *) value),
                  ((unsigned char *) value)+ strlen(((const char *) value)),
                  _value.bitstring);
        break;
    case SNMPDataOctetString:
    case SNMPDataIPAddress:
        _value.string = new unsigned char;
        std::copy(((unsigned char *) value),
                  ((unsigned char *) value)+ strlen(((const char *) value)),
                  _value.string);
        break;
    case SNMPDataObjectId:
        _value.objid = new oid;
        std::copy(((unsigned char *) value),
                  ((unsigned char *) value)+ MAX_OID_LEN,
                  _value.objid);
        break;
    default:
        _value.integer = 0;
        _value.counter64 = 0;
        _value.bitstring = 0;
        _value.string = 0;
        _value.objid = 0;
    }
}

/**
 * @brief Inicializa el valor del dato
 * @param value Valor del dato
 */
void Model::SNMPData::initValue(void *value)
{
    switch(_type) {
    case SNMPDataInteger:
    case SNMPDataUnsigned:
    case SNMPDataBits:
    case SNMPDataCounter:
    case SNMPDataTimeTicks:
        _value.integer = (long *) value;
        break;
    case SNMPDataCounter64:
        _value.counter64 = (SNMPCounter64 *) value;
        break;
    case SNMPDataBitString:
        _value.bitstring = (unsigned char *) value;
        break;
    case SNMPDataOctetString:
    case SNMPDataIPAddress:
        _value.string = (unsigned char *) value;
        break;
    case SNMPDataObjectId:
        _value.objid = (oid *) value;
        break;
    default:
        _value.integer = 0;
        _value.counter64 = 0;
        _value.bitstring = 0;
        _value.string = 0;
        _value.objid = 0;
    }
}

/**
 * @brief Libera memoria del valor del dato
 */
void Model::SNMPData::deleteValue()
{
    switch(_type) {
    case SNMPDataInteger:
    case SNMPDataUnsigned:
    case SNMPDataBits:
    case SNMPDataCounter:
    case SNMPDataTimeTicks:
        delete _value.integer;
        _value.integer = 0;
        break;
    case SNMPDataCounter64:
        delete _value.counter64;
        _value.counter64 = 0;
        break;
    case SNMPDataBitString:
        delete _value.bitstring;
        _value.bitstring = 0;
        break;
    case SNMPDataOctetString:
    case SNMPDataIPAddress:
        delete _value.string;
        _value.string = 0;
        break;
    case SNMPDataObjectId:
        delete _value.objid;
        _value.objid = 0;
        break;
    default:
        _value.integer = 0;
        _value.counter64 = 0;
        _value.bitstring = 0;
        _value.string = 0;
        _value.objid = 0;
    }
}
