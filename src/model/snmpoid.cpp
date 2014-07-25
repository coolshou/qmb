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

#include "snmpoid.h"
#include <sstream>

Model::SNMPOID::SNMPOID(const std::string& strOID) : _strOID(strOID)
{
    _parseOID = new oid[MAX_OID_LEN];
    _parseOIDLength = MAX_OID_LEN;
    _data = new SNMPData;

    parseOIDtoNumeric(); // Parseamos el OID para generar su notacion numerica
}

Model::SNMPOID::SNMPOID(oid  *parseOID, size_t parseOIDLength) : _parseOIDLength(parseOIDLength)
{
    _parseOID = new oid[MAX_OID_LEN];
    std::copy(parseOID, parseOID + _parseOIDLength, _parseOID);
    _data = new SNMPData;

    parseOIDtoTextual(); // Parseamos el OID para generar su notacion textual
}

Model::SNMPOID::SNMPOID(const SNMPOID& snmpOID)
{
    _parseOID = 0;
    _data = 0;

    *this = snmpOID;
}

Model::SNMPOID::~SNMPOID()
{
    if(_parseOID)
        delete [] _parseOID;
    if(_data)
        delete _data;
}

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

Model::SNMPOID *Model::SNMPOID::getInstance() const
{
    SNMPOID *instance = new SNMPOID(*this);

    if(_parseOID[_parseOIDLength - 1])
        instance -> setStrOID(_strOID + ".0");

    return instance;
}

const std::string& Model::SNMPOID::strOID() const
{
    return _strOID;
}

void Model::SNMPOID::setStrOID(const std::string& strOID) throw(SNMPOIDException)
{
    _strOID = strOID;
    _parseOIDLength = MAX_OID_LEN;

    parseOIDtoNumeric();
}

oid *Model::SNMPOID::parseOID() const
{
    return _parseOID;
}

size_t Model::SNMPOID::parseOIDLength() const
{
    return _parseOIDLength;
}

Model::SNMPData *Model::SNMPOID::data() const
{
    return _data;
}

const std::string& Model::SNMPOID::name() const
{
    return _name;
}

void Model::SNMPOID::setName(const std::string& name)
{
    _name = name;
}

Model::MIBStatus Model::SNMPOID::status() const
{
    return _status;
}

void Model::SNMPOID::setStatus(MIBStatus status)
{
    _status = status;
}

Model::MIBAccess Model::SNMPOID::access() const
{
    return _access;
}

void Model::SNMPOID::setAccess(MIBAccess access)
{
    _access = access;
}

const std::string& Model::SNMPOID::description() const
{
    return _description;
}

void Model::SNMPOID::setDescription(const std::string& description)
{
    _description = description;
}

void Model::SNMPOID::parseOIDtoNumeric() throw(SNMPOIDException)
{
    if(!snmp_parse_oid(_strOID.c_str(), _parseOID, &_parseOIDLength))
        throw SNMPOIDException(_strOID ,"Error en la creacion del objeto. OID mal formado.");
}

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
