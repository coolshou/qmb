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
 * @file testsnmpmanager.cpp
 * @brief Implementacion de metodos de la clase TestSNMPManager
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Julio 2013
 */

#include "testsnmpmanager.h"
#include <iostream>

/**
 * @brief Realiza una prueba de la operacion SNMP GET.
 * @param version Version de SNMP utilizada.
 * @param community Nombre de la comunidad.
 * @param agent Dirección IP o nombre de dominio del agente SNMP.
 * @param oids Lista de OIDs
 * @param verbose Muestra mensajes por la salida estandar
 * @return true si la prueba fue exitosa o false en caso contrario.
 */
bool Test::TestSNMPManager::testGet(Model::SNMPVersion version,
                    const std::string& community,
                    const std::string& agent,
                    std::vector<Model::SNMPOID *> oids,
                    bool verbose)
{
    return test(TestGet, version, community, agent, oids, DEFAULT_NON_REPEATERS, DEFAULT_MAX_REPETITIONS, verbose);
}

/**
 * @brief Realiza una prueba de la operacion SNMP GETNEXT.
 * @param version Version de SNMP utilizada.
 * @param community Nombre de la comunidad.
 * @param agent Dirección IP o nombre de dominio del agente SNMP.
 * @param oids Lista de OIDs
 * @param verbose Muestra mensajes por la salida estandar
 * @return true si la prueba fue exitosa o false en caso contrario.
 */
bool Test::TestSNMPManager::testGetNext(Model::SNMPVersion version,
                        const std::string& community,
                        const std::string& agent,
                        std::vector<Model::SNMPOID *> oids,
                        bool verbose)
{
    return test(TestGetNext, version, community, agent, oids, DEFAULT_NON_REPEATERS, DEFAULT_MAX_REPETITIONS, verbose);
}

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
bool Test::TestSNMPManager::testGetBulk(Model::SNMPVersion version,
                        const std::string& community,
                        const std::string& agent,
                        std::vector<Model::SNMPOID *> oids,
                        unsigned short nrepeaters,
                        unsigned short mrepetitions,
                        bool verbose)
{
    return test(TestGetBulk, version, community, agent, oids, nrepeaters, mrepetitions, verbose);
}

/**
 * @brief Realiza una prueba de la operacion SNMP SET.
 * @param version Version de SNMP utilizada.
 * @param community Nombre de la comunidad.
 * @param agent Dirección IP o nombre de dominio del agente SNMP.
 * @param oids Lista de OIDs con su tipo y valor
 * @param verbose Muestra mensajes por la salida estandar
 * @return true si la prueba fue exitosa o false en caso contrario.
 */
bool Test::TestSNMPManager::testSet(Model::SNMPVersion version,
                    const std::string& community,
                    const std::string& agent,
                    std::vector<Model::SNMPOID *> oids,
                    bool verbose)
{
    return test(TestSet, version, community, agent, oids, DEFAULT_NON_REPEATERS, DEFAULT_MAX_REPETITIONS, verbose);
}

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
bool Test::TestSNMPManager::test(TestOperation operation,
                                 Model::SNMPVersion version,
                                 const std::string& community,
                                 const std::string& agent,
                                 std::vector<Model::SNMPOID *> oids,
                                 unsigned short nrepeaters,
                                 unsigned short mrepetitions,
                                 bool verbose)
{
    Model::SNMPManager::initSNMP();

    try {
        switch(operation) {
        case TestGet:
            if(verbose)
                std::cout << "Testing SNMP GET" << std::endl;

            Model::SNMPManager::snmpget(version, community, agent, oids);
        break;
        case TestGetNext:
            if(verbose)
                std::cout << "Testing SNMP GET NEXT" << std::endl;

            Model::SNMPManager::snmpgetnext(version, community, agent, oids);
        break;
        case TestGetBulk:
            if(verbose)
                std::cout << "Testing SNMP GET BULK" << std::endl;

            Model::SNMPManager::snmpgetbulk(version, community, agent, oids, nrepeaters, mrepetitions);
        break;
        case TestSet:
            if(verbose)
                std::cout << "Testing SNMP SET" << std::endl;

            Model::SNMPManager::snmpset(version, community, agent, oids);
        break;
        }

        if(verbose && operation != TestSet) {
            for(std::vector<Model::SNMPOID *>::iterator vi = oids.begin(); vi != oids.end(); ++vi)
                std::cout << (*vi) -> strOID() << " := "
                          <<  (*vi) -> data() -> toString() << std::endl;
        }
    } catch (Model::SNMPSessionException& exception) {
        if(verbose) {
            std::cout << exception.message() << std::endl;
            std::cout << "Agent : " << exception.session().peername << ":" << exception.session().remote_port << " "
                      << "Community: " << exception.session().community << std::endl;
        }

        return false;
    } catch (Model::SNMPOIDException& exception) {
        if(verbose) {
            std::cout << exception.message() << std::endl;
            std::cout << "OID : " << exception.badOID() << std::endl;
        }

        return false;
    } catch (Model::SNMPPacketException& exception) {
        if(verbose) {
            std::cout << exception.message() << std::endl;
            std::cout << "Packet Error : " << exception.error() << std::endl;
        }

        return false;
    } catch (Model::SNMPException& exception) {
        if(verbose)
            std::cout << exception.message() << std::endl;

        return false;
    }

    return true;
}