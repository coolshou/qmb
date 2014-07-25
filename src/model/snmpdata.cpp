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

#include "snmpdata.h"
#include <algorithm>
#include <sstream>

Model::SNMPData::SNMPData(SNMPDataType type, void *value, size_t length) : _type(type), _length(length)
{
    initValue(value);
}

Model::SNMPData::SNMPData(const SNMPData& snmpData)
{
    _type = SNMPDataUnknown;
    _length = 0;

    initValue(0);

    *this = snmpData;
}

Model::SNMPData::~SNMPData()
{
    deleteValue();
}

Model::SNMPData& Model::SNMPData::operator=(const SNMPData& snmpData)
{
    _type = snmpData.type();
    _length = snmpData.length();
    setValue(snmpData.value());

    return *this;
}

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

void Model::SNMPData::setValue(void *value)
{
    deleteValue();

    if(!value || _length <= 0) {
        initValue(0);
        return;
    }

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
        _value.bitstring = new unsigned char[_length + 1];
        std::copy(((unsigned char *) value), ((unsigned char *) value) + _length, _value.bitstring);
        _value.bitstring[_length] = '\0';
        break;
    case SNMPDataOctetString:
    case SNMPDataIPAddress:
        _value.string = new unsigned char[_length + 1];
        std::copy(((unsigned char *) value), ((unsigned char *) value) + _length, _value.string);
        _value.string[_length] = '\0';
        break;
    case SNMPDataObjectId:
        _value.objid = new oid[MAX_OID_LEN];
        std::copy(((oid *) value), ((oid *) value)+ MAX_OID_LEN, _value.objid);
        break;
    default:
        _value.integer = 0;
        _value.counter64 = 0;
        _value.bitstring = 0;
        _value.string = 0;
        _value.objid = 0;
    }
}

void Model::SNMPData::setValue(const SNMPValue &value)
{
    switch(_type) {
    case SNMPDataInteger:
    case SNMPDataUnsigned:
    case SNMPDataBits:
    case SNMPDataCounter:
    case SNMPDataTimeTicks:
        setValue(value.integer);
        break;
    case SNMPDataCounter64:
        setValue(value.counter64);
        break;
    case SNMPDataBitString:
        setValue(value.bitstring);
        break;
    case SNMPDataOctetString:
    case SNMPDataIPAddress:
        setValue(value.string);
        break;
    case SNMPDataObjectId:
        setValue(value.objid);
        break;
    default:
        _value.integer = 0;
        _value.counter64 = 0;
        _value.bitstring = 0;
        _value.string = 0;
        _value.objid = 0;
    }
}

size_t Model::SNMPData::length() const
{
    return _length;
}

void Model::SNMPData::setLength(size_t length)
{
    _length = length;
}

Model::SNMPDataType Model::SNMPData::type() const
{
    return _type;
}

void Model::SNMPData::setType(SNMPDataType type)
{
    _type = type;
}

std::string Model::SNMPData::toString() const
{
    std::stringstream ss;

    switch(_type) {
    case SNMPDataInteger:
    case SNMPDataUnsigned:
    case SNMPDataBits:
    case SNMPDataCounter:
    case SNMPDataTimeTicks:
        ss << *_value.integer;
        break;
    case SNMPDataCounter64:
        ss << _value.counter64 -> high << _value.counter64 -> low;
        break;
    case SNMPDataBitString:
        ss << _value.bitstring;
        break;
    case SNMPDataOctetString:
    case SNMPDataIPAddress:
        ss << _value.string;
        break;
    case SNMPDataObjectId:
        for(int k = 0; k < MAX_OID_LEN && _value.objid[k]; k++)
            ss << _value.objid[k]
               << (((k+1) < MAX_OID_LEN && _value.objid[k+1]) ? "." : "");
        break;
    default:
        ss << 0;
    }

    return ss.str();
}

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

void Model::SNMPData::deleteValue()
{   
    switch(_type) {
    case SNMPDataInteger:
    case SNMPDataUnsigned:
    case SNMPDataBits:
    case SNMPDataCounter:
    case SNMPDataTimeTicks:
        if(_value.integer) {
            delete _value.integer;
            _value.integer = 0;
        }
        break;
    case SNMPDataCounter64:
        if(_value.counter64) {
            delete _value.counter64;
            _value.counter64 = 0;
        }
        break;
    case SNMPDataBitString:
        if(_value.bitstring) {
            delete _value.bitstring;
            _value.bitstring = 0;
        }
        break;
    case SNMPDataOctetString:
    case SNMPDataIPAddress:
        if(_value.string) {
            delete _value.string;
            _value.string = 0;
        }
        break;
    case SNMPDataObjectId:
        if(_value.objid) {
            delete _value.objid;
            _value.objid = 0;
        }
        break;
    default:
        _value.integer = 0;
        _value.counter64 = 0;
        _value.bitstring = 0;
        _value.string = 0;
        _value.objid = 0;
    }
}
