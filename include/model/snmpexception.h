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
 * @file snmpexception.h
 * @brief Declaracion de clase SNMPException
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Junio 2013
 */

#ifndef SNMPEXCEPTION_H
#define SNMPEXCEPTION_H

#include <string>
#include "types.h"

namespace Model
{
    /**
     * @brief Clase SNMPException que implementa la notificacion de errores SNMP
     */
    class SNMPException
    {
    public:
        /**
         * @brief Constructor de SNMPException
         * @param message Mensaje descriptivo del error producido
         */
        SNMPException(const std::string& message = "SNMP : Error desconocido") : _message(message) {}

        /**
         * @brief Obtiene el mensaje de error
         * @return Mensaje de error
         */
        const std::string& message() const
        {
            return _message;
        }
    protected:
        /**
         * @brief Mensaje descriptivo del error producido
         */
        const std::string _message;
    };

    /**
     * @brief Clase SNMPSessionException que implementa la notificacion de errores con sesiones SNMP
     */
    class SNMPSessionException : public SNMPException
    {
    public:
        /**
         * @brief Constructor de SNMPSessionException
         * @param session Sesion SNMP erronea
         * @param message Mensaje descriptivo del error producido
         */
        SNMPSessionException(const SNMPSession& session, const std::string& message = "SNMP : Error en sesion") : SNMPException(message), _session(session) {}

        /**
         * @brief Obtiene la sesion que ha producido el error
         * @return Sesion SNMP erronea
         */
        const SNMPSession& session() const
        {
            return _session;
        }
    private:
        /**
         * @brief Sesion SNMP erronea
         */
        SNMPSession _session;
    };

    /**
     * @brief Clase SNMPOIDException que implementa la notificacion de errores con OIDs
     */
    class SNMPOIDException : public SNMPException
    {
    public:
        /**
         * @brief Constructor de SNMPOIDException
         * @param oid OID erroneo
         * @param message Mensaje descriptivo del error producido
         */
        SNMPOIDException(const std::string& badOID, const std::string& message = "SNMP : Error en OID ") : SNMPException(message), _badOID(badOID) {}

        /**
         * @brief Obtiene el OID que ha producido el error
         * @return OID erroneo
         */
        const std::string& badOID() const
        {
            return _badOID;
        }
    private:
        /**
         * @brief OID erroneo
         */
        std::string _badOID;
    };

    /**
     * @brief Clase SNMPPacketException que implementa la notificacion de errores en los mensajes SNMP
     */
    class SNMPPacketException : public SNMPException
    {
    public:
        /**
         * @brief Constructor de SNMPPacketException
         * @param error Error del mensaje SNMP
         * @param message Mensaje descriptivo del error producido
         */
        SNMPPacketException(const std::string& error, const std::string& message = "SNMP : Error en mensaje de respuesta") : SNMPException(message), _error(error) {}
        /**
         * @brief Obtiene el error del mensaje SNMP
         * @return Error del mensaje SNMP
         */
        const std::string& error() const
        {
            return _error;
        }
    private:
        /**
         * @brief Error del mensaje SNMP
         */
        std::string _error;
    };
}

#endif // SNMPEXCEPTION_H
