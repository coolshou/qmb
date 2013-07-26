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
 * @file testsnmpmanager.h
 * @brief Declaracion de clase TestSNMPManager
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Julio 2013
 */

#ifndef TESTSNMPMANAGER_H
#define TESTSNMPMANAGER_H

#include "snmpmanager.h"
#include "types.h"
#include <string>
#include <vector>

namespace Test
{
    /**
     * @brief Clase TestSNMPManager que implementa las pruebas de la clase SNMPManager
     */
    class TestSNMPManager
    {
    public:
        /**
         * @brief Realiza una prueba de la operacion SNMP GET.
         * @param version Version de SNMP utilizada.
         * @param community Nombre de la comunidad.
         * @param agent Dirección IP o nombre de dominio del agente SNMP.
         * @param oids Lista de OIDs
         * @param verbose Muestra mensajes por la salida estandar
         * @return true si la prueba fue exitosa o false en caso contrario.
         */
        static bool testGet(Model::SNMPVersion version,
                            const std::string& community,
                            const std::string& agent,
                            std::vector<Model::SNMPOID *> oids,
                            bool verbose = false);

        /**
         * @brief Realiza una prueba de la operacion SNMP GETNEXT.
         * @param version Version de SNMP utilizada.
         * @param community Nombre de la comunidad.
         * @param agent Dirección IP o nombre de dominio del agente SNMP.
         * @param oids Lista de OIDs
         * @param verbose Muestra mensajes por la salida estandar
         * @return true si la prueba fue exitosa o false en caso contrario.
         */
        static bool testGetNext(Model::SNMPVersion version,
                                const std::string& community,
                                const std::string& agent,
                                std::vector<Model::SNMPOID *> oids,
                                bool verbose = false);
        /**
         * @brief Realiza una prueba de la operacion SNMP GET BULK.
         * @param version Version de SNMP utilizada.
         * @param community Nombre de la comunidad.
         * @param agent Dirección IP o nombre de dominio del agente SNMP.
         * @param oids Lista de OIDs
         * @param nrepeaters Numero de variables sobre las que no se iterara
         * @param mrepetitions Numero de iteraciones sobre cada variable
         * @param verbose Muestra mensajes por la salida estandar
         * @return true si la prueba fue exitosa o false en caso contrario.
         */
        static bool testGetBulk(Model::SNMPVersion version,
                                const std::string& community,
                                const std::string& agent,
                                std::vector<Model::SNMPOID *> oids,
                                unsigned short nrepeaters = DEFAULT_NON_REPEATERS,
                                unsigned short mrepetitions = DEFAULT_MAX_REPETITIONS,
                                bool verbose = false);

        /**
         * @brief Realiza una prueba de la operacion SNMP SET.
         * @param version Version de SNMP utilizada.
         * @param community Nombre de la comunidad.
         * @param agent Dirección IP o nombre de dominio del agente SNMP.
         * @param oids Lista de OIDs con su tipo y valor
         * @param verbose Muestra mensajes por la salida estandar
         * @return true si la prueba fue exitosa o false en caso contrario.
         */
        static bool testSet(Model::SNMPVersion version,
                            const std::string& community,
                            const std::string& agent,
                            std::vector<Model::SNMPOID *> oids,
                            bool verbose = false);

    private:

        /**
         * @brief Realiza una prueba de una operacion SNMP.
         * @param operation Operacion de prueba
         * @param version Version de SNMP utilizada.
         * @param community Nombre de la comunidad.
         * @param agent Dirección IP o nombre de dominio del agente SNMP.
         * @param oids Lista de OIDs
         * @param nrepeaters Numero de variables sobre las que no se iterara
         * @param mrepetitions Numero de iteraciones sobre cada variable
         * @param verbose Muestra mensajes por la salida estandar
         * @return true si la prueba fue exitosa o false en caso contrario.
         */
        static bool test(TestOperation operation,
                         Model::SNMPVersion version,
                         const std::string& community,
                         const std::string& agent,
                         std::vector<Model::SNMPOID *> oids,
                         unsigned short nrepeaters = DEFAULT_NON_REPEATERS,
                         unsigned short mrepetitions = DEFAULT_MAX_REPETITIONS,
                         bool verbose = false);
    };
}

#endif // TESTSNMPMANAGER_H
