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
 * @file snmpoid.h
 * @brief Declaracion de clase SNMPOID
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Julio 2013
 */

#ifndef SNMPOID_H
#define SNMPOID_H

#include <string>
#include "snmpdata.h"
#include "snmpexception.h"
#include "types.h"

namespace Model
{
    /**
     * @brief Clase SNMPOID que implementa el tratamiento de OIDs
     */
    class SNMPOID
    {
    public:
        /**
         * @brief Constructor de SNMPOID
         * @param strOID OID en notacion textual
         */
        SNMPOID(const std::string& strOID);

        /**
         * @brief Constructor de SNMPOID
         * @param parseOID OID en notacion numerica
         * @param parseOIDLength Longitud del OID en notacion numerica
         */
        SNMPOID(oid  *parseOID, size_t parseOIDLength);

        /**
         * @brief Constructor copia de SNMPOID
         * @param snmpOID Objeto origen
         */
        SNMPOID(const SNMPOID& snmpOID);

        /**
         * @brief Destructor de SNMPOID
         */
        ~SNMPOID();

        /**
         * @brief Redefinicion de operador de asignacion
         * @param snmpOID Objeto origen
         * @return Referencia a this
         */
        SNMPOID& operator=(const SNMPOID& snmpOID);

        /**
         * @brief Devuelve una instancia del OID actual referido por strOID.0
         * @return Instancia del OID actual
         */
        SNMPOID *getInstance() const;

        /**
         * @brief Obtiene el OID en notacion textual
         * @return OID en notacion textual
         */
        const std::string& strOID() const;

        /**
         * @brief Establece el OID en notacion textual
         * @param strOID OID en notacion textual
         */
        void setStrOID(const std::string& strOID) throw(SNMPOIDException);

        /**
         * @brief Obtiene el OID en notacion numerica
         * @return OID en notacion numerica
         */
        oid *parseOID() const;

        /**
         * @brief Obtiene la longitud del OID en notacion numerica
         * @return Longitud del OID en notacion numerica
         */
        size_t parseOIDLength() const;

        /**
         * @brief Obtiene el Dato SNMP
         * @return Dato SNMP
         */
        SNMPData *data() const;

        /**
         * @brief Obtiene el nombre del objeto
         * @return Nombre del objeto
         */
        const std::string& name() const;

        /**
         * @brief Establece el nombre del objeto
         * @param name Nombre del objeto
         */
        void setName(const std::string& name);

        /**
         * @brief obtiene el estado del objeto
         * @return Estado del objeto
         */
        MIBStatus status() const;

        /**
         * @brief Establece el estado del objeto
         * @param status Estado del objeto
         */
        void setStatus(MIBStatus status);

        /**
         * @brief Obtiene el modo de acceso del objeto
         * @return Modo de acceso del objeto
         */
        MIBAccess access() const;

        /**
         * @brief Establece el modo de acceso del objeto
         * @param access Modo de acceso del objeto
         */
        void setAccess(MIBAccess access);

        /**
         * @brief Obtiene la descripcion textual del objeto
         * @return Descripcion textual del objeto
         */
        const std::string& description() const;

        /**
         * @brief Establece la descripcion textual del objeto
         * @param description Descripcion textual del objeto
         */
        void setDescription(const std::string& description);

    private:
        /**
         * @brief Parsea el OID en notacion textual a notacion numerica
         * @throw SNMPOIDException
         */
        void parseOIDtoNumeric() throw(SNMPOIDException);

        /**
         * @brief Parsea el OID en notacion numerica a notacion textual
         */
        void parseOIDtoTextual();

        /**
         * @brief OID en notacion textual
         */
        std::string _strOID;

        /**
         * @brief OID en notacion numerica
         */
        oid *_parseOID;

        /**
         * @brief Longitud del OID en notacion numerica
         */
        size_t _parseOIDLength;

        /**
         * @brief Dato SNMP
         */
        SNMPData *_data;

        /**
         * @brief Nombre del objeto
         */
        std::string _name;

        /**
         * @brief Estado del objeto
         */
        MIBStatus _status;

        /**
         * @brief Modo de acceso del objeto
         */
        MIBAccess _access;

        /**
         * @brief Descripcion textual del objeto
         */
        std::string _description;
    };
}

#endif // SNMPOID_H
