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
#include <sstream>

/**
 * @brief Constructor de SNMPOID
 * @param stdOID OID en notacion textual
 */
Model::SNMPOID::SNMPOID(const std::string& strOID) : _strOID(strOID)
{
    _parseOID = new oid[MAX_OID_LEN];
    _parseOIDLength = MAX_OID_LEN;
    _data = new SNMPData;

    parseOIDtoNumeric(); // Parseamos el OID para generar su notacion numerica
}

/**
 * @brief Constructor de SNMPOID
 * @param parseOID OID en notacion numerica
 * @param parseOIDLength Longitud del OID en notacion numerica
 */
Model::SNMPOID::SNMPOID(oid  *parseOID, size_t parseOIDLength)
    : _parseOID(parseOID), _parseOIDLength(parseOIDLength)
{
    _strOID = std::string();
    _data = new SNMPData;

    parseOIDtoTextual(); // Parseamos el OID para generar su notacion textual
}

/**
 * @brief Constructor copia de SNMPOID
 * @param snmpOID Objeto origen
 */
Model::SNMPOID::SNMPOID(const SNMPOID& snmpOID)
{
    _parseOID = 0;
    _data = 0;

    *this = snmpOID;
}

/**
 * @brief Destructor de SNMPOID
 */
Model::SNMPOID::~SNMPOID()
{
    if(_parseOID)
        delete [] _parseOID;
    if(_data)
        delete _data;
}

/**
 * @brief Redefinicion de operador de asignacion
 * @param snmpOID Objeto origen
 * @return Referencia a this
 */
Model::SNMPOID& Model::SNMPOID::operator=(const SNMPOID& snmpOID)
{
    _strOID = snmpOID.strOID();
    if(_parseOID)
        delete _parseOID;
    _parseOID = new oid[MAX_OID_LEN];
    _parseOIDLength = snmpOID.parseOIDLength();
    std::copy(snmpOID.parseOID(), snmpOID.parseOID() + snmpOID.parseOIDLength(), _parseOID);
    if(_data)
        delete _data;
    _data = new SNMPData(*snmpOID.data());
    _name = snmpOID.name();
    _status = snmpOID.status();
    _access = snmpOID.access();
    _description = snmpOID.description();

    return *this;
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
    _parseOIDLength = MAX_OID_LEN;

    parseOIDtoNumeric();
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
 * @brief Obtiene el Dato SNMP
 * @return Dato SNMP
 */
Model::SNMPData *Model::SNMPOID::data() const
{
    return _data;
}

/**
 * @brief Obtiene el nombre del objeto
 * @return Nombre del objeto
 */
const std::string& Model::SNMPOID::name() const
{
    return _name;
}

/**
 * @brief Establece el nombre del objeto
 * @param name Nombre del objeto
 */
void Model::SNMPOID::setName(const std::string& name)
{
    _name = name;
}

/**
 * @brief obtiene el estado del objeto
 * @return Estado del objeto
 */
Model::MIBStatus Model::SNMPOID::status() const
{
    return _status;
}

/**
 * @brief Establece el estado del objeto
 * @param status Estado del objeto
 */
void Model::SNMPOID::setStatus(MIBStatus status)
{
    _status = status;
}

/**
 * @brief Obtiene el modo de acceso del objeto
 * @return Modo de acceso del objeto
 */
Model::MIBAccess Model::SNMPOID::access() const
{
    return _access;
}

/**
 * @brief Establece el modo de acceso del objeto
 * @param access Modo de acceso del objeto
 */
void Model::SNMPOID::setAccess(MIBAccess access)
{
    _access = access;
}

/**
 * @brief Obtiene la descripcion textual del objeto
 * @return Descripcion textual del objeto
 */
const std::string& Model::SNMPOID::description() const
{
    return _description;
}

/**
 * @brief Establece la descripcion textual del objeto
 * @param description Descripcion textual del objeto
 */
void Model::SNMPOID::setDescription(const std::string& description)
{
    _description = description;
}

/**
 * @brief Parsea el OID en notacion textual a notacion numerica
 * @throw SNMPOIDException
 */
void Model::SNMPOID::parseOIDtoNumeric() throw(SNMPOIDException)
{
    if(!snmp_parse_oid(_strOID.c_str(), _parseOID, &_parseOIDLength))
        throw SNMPOIDException(_strOID ,"Error en la creacion del objeto. OID mal formado.");
}

/**
 * @brief Parsea el OID en notacion numerica a notacion textual
 */
void Model::SNMPOID::parseOIDtoTextual()
{
    std::stringstream ss;

    for(int k = 0; k < (int) _parseOIDLength; k++) {
        ss << _parseOID[k];
        if(k != ((int)_parseOIDLength - 1))
            ss << ".";
    }

    _strOID = ss.str();
}
