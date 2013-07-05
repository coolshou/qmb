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
#include "types.h"
#include "snmpexception.h"

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
         * @param type Tipo de dato
         * @param value Valor del dato
         */
        SNMPOID(const std::string& strOID, SNMPDataType type = SNMPDataNull, void *value = 0);

        /**
         * @brief Destructor de SNMPOID
         */
        ~SNMPOID();

        /**
         * @brief Obtiene el OID en notacion textual
         * @return OID en notacion textual
         */
        const std::string &strOID() const;

        /**
         * @brief Establece el OID en notacion textual
         * @param strOID OID en notacion textual
         */
        void setStrOID(const std::string &strOID) throw(SNMPOIDException);

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
         * @brief Obtiene el tipo de dato
         * @return Tipo de dato
         */
        SNMPDataType type() const;

        /**
         * @brief Establece el tipo de dato
         * @param type Tipo de dato
         */
        void setType(SNMPDataType type);

        /**
         * @brief Obtiene el valor del dato
         * @return Valor del dato
         */
        void *value() const;

        /**
         * @brief Establece el valor del dato
         * @param value Valor del dato
         */
        void setValue(void *value);
    private:
        /**
         * @brief Parsea el OID en notacion textual a notacion numerica
         * @throw SNMPOIDException
         */
        void parse() throw(SNMPOIDException);

        /**
         * @brief OID en notacion textual
         */
        std::string _strOID;
        /**
         * @brief OID en notacion numerica
         */
        oid *_parseOID;

        /**
         * @brief L
         */
        size_t _parseOIDLength;

        /**
         * @brief Tipo de dato
         */
        SNMPDataType _type;
        /**
         * @brief Valor del dato
         */
        void *_value;
    };
}

#endif // SNMPOID_H
