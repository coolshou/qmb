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
 * @file snmpdata.h
 * @brief Declaracion de clase SNMPData
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Julio 2013
 */

#ifndef SNMPDATA_H
#define SNMPDATA_H

#include <string>
#include "types.h"

namespace Model
{
    /**
     * @brief Clase SNMPData que implementa la representacion de datos en SNMP
     */
    class SNMPData
    {
    public:
        /**
         * @brief Constructor de SNMPData
         * @param type Tipo de dato
         * @param value Valor del dato
         */
        SNMPData(SNMPDataType type = SNMPDataNull, void *value = 0);

        /**
         * @brief Constructor copia de SNMPData
         * @param snmpData Objeto origen
         */
        SNMPData(const SNMPData& snmpData);

        /**
         * @brief Destructor de SNMPData
         */
        ~SNMPData();

        /**
         * @brief Redefinicion de operador de asignacion
         * @param snmpData Objeto origen
         * @return
         */
        SNMPData& operator=(const SNMPData& snmpData);

        /**
         * @brief Devuelve el valor del dato
         * @return Valor del dato
         */
        void *value() const;

        /**
         * @brief Establece el valor del dato
         * @param value Valor del dato
         */
        void setValue(void *value);

        /**
         * @brief Establece el valor del dato
         * @param value Valor del dato
         */
        void setValue(const SNMPValue &value);

        /**
         * @brief Devuelve el tipo del dato
         * @return Tipo del dato
         */
        SNMPDataType type() const;

        /**
         * @brief Establece el tipo del dato
         * @param type Tipo del dato
         */
        void setType(SNMPDataType type);

        /**
         * @brief Obtiene representacion textual del valor del dato
         * @return Representacion textual del valor del dato
         */
        std::string toString() const;
    private:
        /**
         * @brief Inicializa el valor del dato
         * @param value Valor del dato
         */
        void initValue(void *value);

        /**
         * @brief Libera memoria del valor del dato
         */
        void deleteValue();

        /**
         * @brief Valor del dato
         */
        SNMPValue _value;

        /**
         * @brief Tipo del dato
         */
        SNMPDataType _type;
    };
}

#endif // SNMPDATA_H
