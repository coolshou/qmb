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
 * @file snmpoid.cpp
 * @brief Implementacion de metodos de la clase SNMPOID
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Julio 2013
 */

#include "snmpoid.h"

/**
 * @brief Constructor de SNMPOID
 * @param stdOID OID en notacion textual
 * @param type Tipo de dato
 * @param value Valor del dato
 */
Model::SNMPOID::SNMPOID(const std::string& strOID, SNMPDataType type, void *value) : _strOID(strOID), _type(type), _value(value)
{
    _parseOID = new oid[MAX_OID_LEN];
    _parseOIDLength = MAX_OID_LEN;

    parse(); // Parseamos el OID para generar su notacion numerica
}

/**
 * @brief Destructor de SNMPOID
 */
Model::SNMPOID::~SNMPOID()
{
    delete _parseOID;

    if(_value)
        delete [] (char *) _value;
}

/**
 * @brief Obtiene el OID en notacion textual
 * @return OID en notacion textual
 */
const std::string& Model::SNMPOID::strOID() const
{
    return _strOID;
}

/**
 * @brief Establece el OID en notacion textual
 * @param strOID OID en notacion textual
 */
void Model::SNMPOID::setStrOID(const std::string& strOID) throw(SNMPOIDException)
{
    _strOID = strOID;

    parse();
}

/**
 * @brief Obtiene el OID en notacion numerica
 * @return OID en notacion numerica
 */
oid *Model::SNMPOID::parseOID() const
{
    return _parseOID;
}

/**
 * @brief Obtiene la longitud del OID en notacion numerica
 * @return Longitud del OID en notacion numerica
 */
size_t Model::SNMPOID::parseOIDLength() const
{
    return _parseOIDLength;
}

/**
 * @brief Obtiene el tipo de dato
 * @return Tipo de dato
 */
Model::SNMPDataType Model::SNMPOID::type() const
{
    return _type;
}

/**
 * @brief Establece el tipo de dato
 * @param type Tipo de dato
 */
void Model::SNMPOID::setType(SNMPDataType type)
{
    _type = type;
}

/**
 * @brief Obtiene el valor del dato
 * @return Valor del dato
 */
void *Model::SNMPOID::value() const
{
    return _value;
}

/**
 * @brief Establece el valor del dato
 * @param value Valor del dato
 */
void Model::SNMPOID::setValue(void *value)
{
    if(_value)
        delete [] (char *) _value;

    _value = value;
}

void Model::SNMPOID::parse() throw(SNMPOIDException)
{
    //if(!snmp_parse_oid(_strOID.c_str(), _parseOID, &_parseOIDLength))
    //    throw SNMPOIDException(_strOID ,"Error en la creacion de la PDU. OID mal formado.");
}
