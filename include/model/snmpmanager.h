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
#include <map>
#include "types.h"
#include "global.h"
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
         * @brief Envia mensaje de peticion SNMP GET y recibe mensaje de respuesta.
         * @param version Version de SNMP utilizada.
         * @param community Nombre de la comunidad.
         * @param agent Dirección IP o nombre de dominio del agente SNMP.
         * @param oids Lista de OIDs
         * @throw SNMPException
         * @return Pares (OID, valor) resultado de la consulta.
         */
        static std::map<std::string, void *> *snmpget(SNMPVersion version,
                                                      const std::string& community,
                                                      const std::string& agent,
                                                      const std::vector<std::string>& oids) throw(SNMPException);

        /**
         * @brief Envia mensaje de peticion SNMP GETNEXT y recibe mensaje de respuesta.
         * @param version Version de SNMP utilizada.
         * @param community Nombre de la comunidad.
         * @param agent Dirección IP o nombre de dominio del agente SNMP.
         * @param oids Lista de OIDs
         * @throw SNMPException
         * @return Pares (OID, valor) resultado de la consulta.
         */
        static std::map<std::string, void *> *snmpgetnext(SNMPVersion version,
                                                          const std::string& community,
                                                          const std::string& agent,
                                                          const std::vector<std::string>& oids) throw(SNMPException);

        /**
         * @brief Envia mensaje de peticion SNMP GET BULK y recibe mensaje de respuesta.
         * @param version Version de SNMP utilizada.
         * @param community Nombre de la comunidad.
         * @param agent Dirección IP o nombre de dominio del agente SNMP.
         * @param oids Lista de OIDs
         * @param nrepeaters Numero de variables sobre las que no se iterara
         * @param mrepetitions Numero de iteraciones sobre cada variable
         * @throw SNMPException
         * @return Pares (OID, valor) resultado de la consulta.
         */
        static std::map<std::string, void *> *snmpgetbulk(SNMPVersion version,
                                                          const std::string& community,
                                                          const std::string& agent,
                                                          const std::vector<std::string>& oids,
                                                          unsigned short nrepeaters = DEFAULT_NON_REPEATERS,
                                                          unsigned short mrepetitions = DEFAULT_MAX_REPETITIONS) throw(SNMPException);

        /**
         * @brief Envia mensaje de peticion SNMP SET y recibe mensaje de respuesta.
         * @param version Version de SNMP utilizada.
         * @param community Nombre de la comunidad.
         * @param agent Dirección IP o nombre de dominio del agente SNMP.
         * @param variables Pares (OID, valor)
         * @throw SNMPException
         */
        static void snmpset(SNMPVersion version, 
                            const std::string& community,
                            const std::string& agent,
                            const std::map<std::string, SNMPDataTuple>& variables) throw(SNMPException);
    private:
        /**
         * @brief Inicializa la libreria SNMP
         */
        static void initSNMP();

        /**
         * @brief Crea, inicializa y abre una session SNMP Agente-Gestor
         * @param version Version de SNMP utilizada.
         * @param community Nombre de la comunidad.
         * @param agent Dirección IP o nombre de dominio del agente SNMP.
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
         * @param values Valores asignados a los OIDs
         * @return PDU SNMP
         */
        static SNMPPDU *createPDU(SNMPPDUType type,
                                  const std::vector<std::string>& oids,
                                  unsigned short nrepeaters = DEFAULT_NON_REPEATERS,
                                  unsigned short mrepetitions = DEFAULT_MAX_REPETITIONS,
                                  const std::vector<SNMPDataTuple>& values = std::vector<SNMPDataTuple>()) throw(SNMPException);

        /**
         * @brief Envia la PDU SNMP de peticion a traves de una sesion Gestor-Agente
         * @param session Gestion SNMP Gestor-Agente
         * @param pdu PDU SNMP de peticion
         * @return PDU de respuesta
         */
        static SNMPPDU *sendPDU(SNMPSession *session, SNMPPDU *pdu);

        /**
         * @brief Especifica si la libreria SNMP ha sido inicializada
         */
        static bool _initialized;
    };
}

#endif // SNMPMANAGER_H
