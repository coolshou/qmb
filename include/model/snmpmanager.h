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
 * @file snmpmanager.h
 * @brief Declaracion de clase SNMPManager
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Junio 2013
 */

#ifndef SNMPMANAGER_H
#define SNMPMANAGER_H

#include <string>
#include <vector>
#include "types.h"
#include "global.h"
#include "snmpoid.h"
#include "snmpnode.h"
#include "snmpexception.h"

namespace Model
{
    /**
     * @brief Clase SNMPManager que implementa la funcionalidad del gestor SNMP
     */
    class SNMPManager
    {
    public:
        /**
         * @brief Inicializa la libreria SNMP
         */
        static void initSNMP();

        /**
         * @brief Establece parametros de configuracion para una sesion SNMP
         * @param remotePort Numero de puerto del agente SNMP remoto
         * @param retries Numero de reintentos
         * @param timeout Numero de uSegundos para producirse un timeout
         */
        static void configSNMP(unsigned short remotePort = DEFAULT_REMOTE_PORT,
                               unsigned short retries = DEFAULT_RETRIES,
                               long timeout = DEFAULT_TIMEOUT);

        /**
         * @brief Envia mensaje de peticion SNMP GET y recibe mensaje de respuesta.
         * @param version Version de SNMP utilizada.
         * @param community Nombre de la comunidad.
         * @param agent Dirección IP o nombre de dominio del agente SNMP.
         * @param oids Lista de OIDs
         * @throw SNMPException
         */
        static void snmpget(SNMPVersion version,
                            const std::string& community,
                            const std::string& agent,
                            std::vector<SNMPOID *>& oids) throw(SNMPException);

        /**
         * @brief Envia mensaje de peticion SNMP GETNEXT y recibe mensaje de respuesta.
         * @param version Version de SNMP utilizada.
         * @param community Nombre de la comunidad.
         * @param agent Dirección IP o nombre de dominio del agente SNMP.
         * @param oids Lista de OIDs
         * @throw SNMPException
         */
        static void snmpgetnext(SNMPVersion version,
                                const std::string& community,
                                const std::string& agent,
                                std::vector<SNMPOID *> &oids) throw(SNMPException);

        /**
         * @brief Envia mensaje de peticion SNMP GET BULK y recibe mensaje de respuesta.
         * @param version Version de SNMP utilizada.
         * @param community Nombre de la comunidad.
         * @param agent Dirección IP o nombre de dominio del agente SNMP.
         * @param oids Lista de OIDs
         * @param nrepeaters Numero de variables sobre las que no se iterara
         * @param mrepetitions Numero de iteraciones sobre cada variable
         * @throw SNMPException
         */
        static void snmpgetbulk(SNMPVersion version,
                                const std::string& community,
                                const std::string& agent,
                                std::vector<SNMPOID *>& oids,
                                unsigned short nrepeaters = DEFAULT_NON_REPEATERS,
                                unsigned short mrepetitions = DEFAULT_MAX_REPETITIONS) throw(SNMPException);

        /**
         * @brief Envia mensaje de peticion SNMP SET y recibe mensaje de respuesta.
         * @param version Version de SNMP utilizada.
         * @param community Nombre de la comunidad.
         * @param oids Lista de OIDs con su tipo y valor
         * @throw SNMPException
         */
        static void snmpset(SNMPVersion version,
                            const std::string& community,
                            const std::string& agent,
                            std::vector<SNMPOID *> &oids) throw(SNMPException);

    private:
        /**
         * @brief Crea, inicializa y abre una session SNMP Agente-Gestor
         * @param version Version de SNMP utilizada.
         * @param community Nombre de la comunidad.
         * @param agent Dirección IP o nombre de dominio del agente SNMP.
         * @throw SNMPException
         * @return Sesion SNMP Agente-Gestor inicializada y abierta.
         */
        static SNMPSession *createSession(SNMPVersion version,
                                          const std::string& community,
                                          const std::string& agent) throw(SNMPException);

        /**
         * @brief Crea una PDU SNMP de peticion
         * @param type Tipo de PDU SNMP
         * @param oids Lista de OIDs
         * @param nrepeaters Numero de variables sobre las que no se iterara
         * @param mrepetitions Numero de iteraciones sobre cada variable
         * @throw SNMPException
         * @return PDU SNMP
         */
        static SNMPPDU *createPDU(SNMPPDUType type,
                                  const std::vector<SNMPOID *> &oids,
                                  unsigned short nrepeaters = DEFAULT_NON_REPEATERS,
                                  unsigned short mrepetitions = DEFAULT_MAX_REPETITIONS) throw(SNMPException);

        /**
         * @brief Envia la PDU SNMP de peticion a traves de una sesion Gestor-Agente
         * @param session Gestion SNMP Gestor-Agente
         * @param pdu PDU SNMP de peticion
         * @throw SNMPException
         * @return PDU de respuesta
         */
        static SNMPPDU *sendPDU(SNMPSession *session, SNMPPDU *pdu) throw(SNMPException);

        /**
         * @brief Procesa la PDU SNMP de respuesta del agente
         * @param pdu PDU SNMP de respuesta
         * @param oids Lista de OIDs
         */
        static void processResponse(SNMPPDU *pdu, std::vector<SNMPOID *>& oids, SNMPPDUType type);

        /**
         * @brief Busca el OID correspondiente a una variable de una PDU SNMP de respuesta
         * @param oids Lista de OIDs
         * @param var Variable de la lista de variables de una PDU SNMP de respuesta
         * @throw SNMPException
         * @return OID correspondiente a la variable si se encuentra en el vector o 0 en caso contrario
         */
        static SNMPOID *findOID(const std::vector<SNMPOID *>& oids, SNMPVariableList *var);

        /**
         * @brief Invoca una operacion SNMP de consulta (GET, GETNEXT, GET BULK) o modificacion (SET)
         * @param type Tipo de PDU de peticion
         * @param version Version de SNMP utilizada.
         * @param community Nombre de la comunidad.
         * @param agent Dirección IP o nombre de dominio del agente SNMP.
         * @param oids Lista de OIDs
         * @param nrepeaters Numero de variables sobre las que no se iterara
         * @param mrepetitions Numero de iteraciones sobre cada variable
         * @throw SNMPException
         */
        static void snmpoperation(SNMPPDUType type,
                                  SNMPVersion version,
                                  const std::string& community,
                                  const std::string& agent,
                                  std::vector<SNMPOID *> &oids,
                                  unsigned short nrepeaters = DEFAULT_NON_REPEATERS,
                                  unsigned short mrepetitions = DEFAULT_MAX_REPETITIONS);

        static SNMPNode *getMIBTree();

        static void snmpParseMIB(SNMPNode *node, SNMPTree *tree);

        /**
         * @brief Especifica si la libreria SNMP ha sido inicializada
         */
        static bool _initialized;

        /**
         * @brief Numero de puerto del agente SNMP remoto
         */
        static unsigned short _remotePort;

        /**
         * @brief Numero de reintentos
         */
        static unsigned short _retries;

        /**
         * @brief Numero de uSegundos para producirse un timeout
         */
        static long _timeout;
    };
}

#endif // SNMPMANAGER_H
