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

#ifndef SNMPEXCEPTION_H
#define SNMPEXCEPTION_H

#include <string>
#include "types.h"

namespace Model
{
    class SNMPException
    {
    public:
        SNMPException(const std::string& message = "SNMP : Error desconocido") : _message(message) {}
        const std::string& message() const
        {
            return _message;
        }
    protected:
        const std::string _message;
    };

    class SNMPSessionException : public SNMPException
    {
    public:
        SNMPSessionException(const SNMPSession& session, const std::string& message = "SNMP : Error en sesion") : SNMPException(message), _session(session) {}
        const SNMPSession& session() const
        {
            return _session;
        }
    private:
        SNMPSession _session;
    };

    class SNMPOIDException : public SNMPException
    {
    public:
        SNMPOIDException(const std::string& badOID, const std::string& message = "SNMP : Error en OID ") : SNMPException(message), _badOID(badOID) {}
        const std::string& badOID() const
        {
            return _badOID;
        }
    private:
        std::string _badOID;
    };

    class SNMPPacketException : public SNMPException
    {
    public:
        SNMPPacketException(const std::string& error, const std::string& message = "SNMP : Error en mensaje de respuesta") : SNMPException(message), _error(error) {}
        const std::string& error() const
        {
            return _error;
        }
    private:
        std::string _error;
    };
}

#endif // SNMPEXCEPTION_H
