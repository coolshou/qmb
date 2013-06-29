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

#ifndef SNMPMANAGER_H
#define SNMPMANAGER_H

#include <string>
#include "types.h"
#include "snmpexception.h"

namespace Model
{
    class SNMPManager
    {
    public:
        static bool snmpget(SNMPVersion version, const std::string& community, const std::string& address, const std::string& oid) throw(SNMPException);
        static bool snmpgetnext(SNMPVersion version, const std::string& community, const std::string& address, const std::string& oid) throw(SNMPException);
        static bool snmpget(SNMPVersion version, const std::string& community, const std::string& address, const std::string& oid) throw(SNMPException);
        static bool snmpgetbulk(SNMPVersion version, const std::string& community, const std::string& address, const std::string& oid) throw(SNMPException);
    };
}

#endif // SNMPMANAGER_H
