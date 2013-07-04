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
 * @file snmpmanager.cpp
 * @brief Implementacion de metodos de la clase SNMPManager
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Junio 2013
 */

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include "snmpmanager.h"

/**
 * @brief Envia mensaje de peticion SNMP GET y recibe mensaje de respuesta.
 * @param version Version de SNMP utilizada.
 * @param community Nombre de la comunidad.
 * @param agent Dirección IP o nombre de dominio del agente SNMP.
 * @param oids Lista de OIDs
 * @throw SNMPException
 * @return Pares (OID, valor) resultado de la consulta.
 */
std::map<std::string, void *> *Model::SNMPManager::snmpget(SNMPVersion version,
                                                           const std::string& community,
                                                           const std::string& agent,
                                                           const std::vector<std::string>& oids) throw(SNMPException)
{
    SNMPSession *session;                               // Sesion SNMP Gestor-Agente
    SNMPPDU *requestPDU;                                // PDU SNMP de peticion
    SNMPPDU *responsePDU;                               // PDU SNMP de respuesta

    initSNMP();                                         // Inicializacion libreria NET-SNMP
    session = createSession(version, community, agent); // Inicializacion de sesion
    requestPDU = createPDU(SNMPPDUGet,oids);            // Creacion de PDU de peticion
    responsePDU = sendPDU(session, requestPDU);         // Envio de PDU de peticion

    return new std::map<std::string, void *>();
}

/**
 * @brief Envia mensaje de peticion SNMP GETNEXT y recibe mensaje de respuesta.
 * @param version Version de SNMP utilizada.
 * @param community Nombre de la comunidad.
 * @param agent Dirección IP o nombre de dominio del agente SNMP.
 * @param oids Lista de OIDs
 * @throw SNMPException
 * @return Pares (OID, valor) resultado de la consulta.
 */
std::map<std::string, void *> *Model::SNMPManager::snmpgetnext(SNMPVersion version,
                                                               const std::string& community,
                                                               const std::string& agent,
                                                               const std::vector<std::string>& oids) throw(SNMPException)
{
    return new std::map<std::string, void *>();
}

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
std::map<std::string, void *> *Model::SNMPManager::snmpgetbulk(SNMPVersion version,
                                                               const std::string& community,
                                                               const std::string& agent,
                                                               const std::vector<std::string>& oids,
                                                               unsigned short nrepeaters,
                                                               unsigned short mrepetitions) throw(SNMPException)
{
    return new std::map<std::string, void *>();
}

/**
 * @brief Envia mensaje de peticion SNMP SET y recibe mensaje de respuesta.
 * @param version Version de SNMP utilizada.
 * @param community Nombre de la comunidad.
 * @param agent Dirección IP o nombre de dominio del agente SNMP.
 * @param variables Pares (OID, valor)
 * @throw SNMPException
 */
void Model::SNMPManager::snmpset(SNMPVersion version,
                                 const std::string& community,
                                 const std::string& agent,
                                 const std::map<std::string, SNMPDataTuple> &variables) throw(SNMPException)
{

}

/**
 * @brief Inicializa la libreria SNMP
 */
void Model::SNMPManager::initSNMP()
{
    if(!_initialized) {
        init_snmp(APPLICATION_NAME);
        _initialized = true;
    }
}

/**
 * @brief Crea, inicializa y abre una session SNMP Agente-Gestor
 * @param version Version de SNMP utilizada.
 * @param community Nombre de la comunidad.
 * @param agent Dirección IP o nombre de dominio del agente SNMP.
 * @return
 */
Model::SNMPSession *Model::SNMPManager::createSession(SNMPVersion version,
                                                      const std::string& community,
                                                      const std::string& agent) throw(SNMPException)
{
    SNMPSession session;                                // Sesion SNMP
    SNMPSession *openedSession;                         // Session SNMP abierta

    if(version != SNMPv1 && version != SNMPv2)          // Verificamos que la version esta soportada
        throw SNMPException("Error de inicializacion en sesion SNMP. Version no soportada.");

    snmp_sess_init(&session);                           // Inicializacion de sesion
    session.version = version;                          // Version SNMP
    session.community = (u_char *) community.c_str();   // Comunidad SNMPv1-2
    session.community_len = community.length();         // Longitud del nombre de la comunidad
    session.peername = (char *) agent.c_str();          // Direccion del agente
    SOCK_STARTUP;                                       // Inicializacion para SOs win32 (Sin efecto en SOs Unix).

    if(!(openedSession = snmp_open(&session))) {        // Apertura de sesion
        SOCK_CLEANUP;
        throw SNMPSessionException(session, "Error de apertura en sesion SNMP");
    }

    return openedSession;
}

/**
 * @brief Crea una PDU SNMP de peticion
 * @param type Tipo de PDU SNMP
 * @param oids Lista de OIDs
 * @param nrepeaters Numero de variables sobre las que no se iterara
 * @param mrepetitions Numero de iteraciones sobre cada variable
 * @param values Valores asignados a los OIDs
 * @return PDU SNMP
 */
Model::SNMPPDU *Model::SNMPManager::createPDU(SNMPPDUType type,
                                              const std::vector<std::string>& oids,
                                              unsigned short nrepeaters,
                                              unsigned short mrepetitions,
                                              const std::vector<SNMPDataTuple>& values) throw(SNMPException)
{
    SNMPPDU *pdu; // PDU SNMP de peticion

    // Verificamos el tipo de la PDU
    if(type != SNMPPDUGet && type != SNMPPDUGetNext && type != SNMPPDUGetBulk && type != SNMPPDUSet)
        throw SNMPException("Error en la creacion de la PDU. Tipo no valido");

    // Verificamos que se ha introducido al menos un OID
    if(oids.empty())
        throw SNMPException("Error en la creacion de la PDU. No especificado ningun OID.");

    // Verificamos que el numero de OIDs es igual al numero de valores (Para PDU SNMP SET)
    if(type == SNMPPDUSet && oids.size() != values.size())
        throw SNMPException("Error en la creacion de la PDU SET. Diferente numero de OIDs y valores.");

    pdu = snmp_pdu_create(type);            // Creacion de PDU SNMP

    SNMPOID *parseOIDs[oids.size()];        // Array de OIDs parseados
    size_t parseOIDLength = MAX_OID_LEN;    // Longitud de OID

    for(int k = 0; k < ((int) oids.size()); ++k) {
        parseOIDs[k] = new SNMPOID[MAX_OID_LEN]; // Reserva de memoria
        if(!snmp_parse_oid(oids.at(k).c_str(), parseOIDs[k], &parseOIDLength)) { // Parseo de OID
            for(int i = 0;i <= k; ++i) // Liberacion de memoria
                delete parseOIDs[i];
            throw SNMPOIDException(oids.at(k) ,"Error en la creacion de la PDU. OID mal formado.");
        }

        if(type == SNMPPDUSet) // Aniadimos a la PDU el valor correspondiente al k-esimo OID
            snmp_add_var(pdu, parseOIDs[k], parseOIDLength, values.at(k).type, (const char *) values.at(k).value);
        else // Aniadimos a la PDU el valor nulo correspondiente al k-esimo OID
            snmp_add_null_var(pdu, parseOIDs[k], parseOIDLength);
    }

    // Si la PDU es de tipo GET BULK los parametros nrepeaters y mrepetitions
    // se almacenan en los campos errstat y errindex respectivamente.
    if(type == SNMPPDUGetBulk) {
        pdu -> errstat = nrepeaters;
        pdu -> errindex = mrepetitions;
    }

    return pdu;
}

/**
 * @brief Envia la PDU SNMP de peticion a traves de una sesion Gestor-Agente
 * @param session Gestion SNMP Gestor-Agente
 * @param pdu PDU SNMP de peticion
 * @return PDU de respuesta
 */
Model::SNMPPDU *Model::SNMPManager::sendPDU(SNMPSession *session, SNMPPDU *pdu)
{
    SNMPPDU *response;

    return response;
}


/**
 * @brief Inicializacion de atributo estatico _initialized
 */
bool Model::SNMPManager::_initialized = false;
