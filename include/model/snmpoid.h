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

#ifndef SNMPOID_H
#define SNMPOID_H

#include <string>
#include "snmpdata.h"
#include "snmpexception.h"
#include "types.h"

namespace Model
{
    class SNMPOID
    {
    public:
        SNMPOID(const std::string& strOID);
        SNMPOID(oid  *parseOID, size_t parseOIDLength);
        SNMPOID(const SNMPOID& snmpOID);
        ~SNMPOID();
        SNMPOID& operator=(const SNMPOID& snmpOID);
        SNMPOID *getInstance() const;
        const std::string& strOID() const;
        void setStrOID(const std::string& strOID) throw(SNMPOIDException);
        oid *parseOID() const;
        size_t parseOIDLength() const;
        SNMPData *data() const;
        const std::string& name() const;
        void setName(const std::string& name);
        MIBStatus status() const;
        void setStatus(MIBStatus status);
        MIBAccess access() const;
        void setAccess(MIBAccess access);
        const std::string& description() const;
        void setDescription(const std::string& description);
    private:
        void parseOIDtoNumeric() throw(SNMPOIDException);
        void parseOIDtoTextual();

        std::string _strOID;
        oid *_parseOID;
        size_t _parseOIDLength;
        SNMPData *_data;
        std::string _name;
        MIBStatus _status;
        MIBAccess _access;
        std::string _description;
    };
}

#endif // SNMPOID_H
