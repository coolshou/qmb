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
 * @brief Envia mensaje de peticion SNMP GET y recibe mensaje de respuesta.
 * @param version Version de SNMP utilizada.
 * @param community Nombre de la comunidad.
 * @param agent Dirección IP o nombre de dominio del agente SNMP.
 * @param oids Lista de OIDs
 * @throw SNMPException
 */
void Model::SNMPManager::snmpget(SNMPVersion version,
                                 const std::string& community,
                                 const std::string& agent,
                                 std::vector<SNMPOID *> &oids) throw(SNMPException)
{
    snmpoperation(SNMPPDUGet, version, community, agent, oids);
}

/**
 * @brief Envia mensaje de peticion SNMP GETNEXT y recibe mensaje de respuesta.
 * @param version Version de SNMP utilizada.
 * @param community Nombre de la comunidad.
 * @param agent Dirección IP o nombre de dominio del agente SNMP.
 * @param oids Lista de OIDs
 * @throw SNMPException
 */
void Model::SNMPManager::snmpgetnext(SNMPVersion version,
                                     const std::string& community,
                                     const std::string& agent,
                                     std::vector<SNMPOID *> &oids) throw(SNMPException)
{
    snmpoperation(SNMPPDUGetNext, version, community, agent, oids);
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
 */
void Model::SNMPManager::snmpgetbulk(SNMPVersion version,
                                     const std::string& community,
                                     const std::string& agent,
                                     std::vector<SNMPOID *> &oids,
                                     unsigned short nrepeaters,
                                     unsigned short mrepetitions) throw(SNMPException)
{
    snmpoperation(SNMPPDUGetBulk, version, community, agent, oids, nrepeaters, mrepetitions);
}

/**
 * @brief Envia mensaje de peticion SNMP SET y recibe mensaje de respuesta.
 * @param version Version de SNMP utilizada.
 * @param community Nombre de la comunidad.
 * @param agent Dirección IP o nombre de dominio del agente SNMP.
 * @param oids Lista de OIDs con su tipo y valor
 * @throw SNMPException
 */
void Model::SNMPManager::snmpset(SNMPVersion version,
                                 const std::string& community,
                                 const std::string& agent,
                                 std::vector<SNMPOID *>& oids) throw(SNMPException)
{
    snmpoperation(SNMPPDUSet, version, community, agent, oids);
}

/**
 * @brief Crea, inicializa y abre una session SNMP Agente-Gestor
 * @param version Version de SNMP utilizada.
 * @param community Nombre de la comunidad.
 * @param agent Dirección IP o nombre de dominio del agente SNMP.
 * @throw SNMPException
 * @return Sesion SNMP Agente-Gestor inicializada y abierta.
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
        SOCK_CLEANUP;                                   // Liberacion de recursos para SOs win32 (Sin efecto en SOs Unix).
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
 * @throw SNMPException
 * @return PDU SNMP
 */
Model::SNMPPDU *Model::SNMPManager::createPDU(SNMPPDUType type,
                                              const std::vector<SNMPOID *>& oids,
                                              unsigned short nrepeaters,
                                              unsigned short mrepetitions) throw(SNMPException)
{
    SNMPPDU *pdu; // PDU SNMP de peticion

    // Verificamos el tipo de la PDU
    if(type != SNMPPDUGet && type != SNMPPDUGetNext && type != SNMPPDUGetBulk && type != SNMPPDUSet)
        throw SNMPException("Error en la creacion de la PDU. Tipo no valido");

    // Verificamos que se ha introducido al menos un OID
    if(oids.empty())
        throw SNMPException("Error en la creacion de la PDU. No especificado ningun OID.");

    pdu = snmp_pdu_create(type);            // Creacion de PDU SNMP

    // Iteramos a traves de los OIDs
    for(std::vector<SNMPOID *>::const_iterator vi = oids.begin(); vi != oids.end(); vi++) {
        if(type == SNMPPDUSet) // Aniadimos a la PDU el valor correspondiente al k-esimo OID
            snmp_add_var(pdu, (*vi) -> parseOID(), (*vi) -> parseOIDLength(),
                         (*vi) -> data() -> type(),
                         (const char *) (*vi) -> data() -> value());
        else // Aniadimos a la PDU el valor nulo correspondiente al k-esimo OID
            snmp_add_null_var(pdu, (*vi) -> parseOID(), (*vi) -> parseOIDLength());
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
 * @throw SNMPException
 * @return PDU de respuesta
 */
Model::SNMPPDU *Model::SNMPManager::sendPDU(SNMPSession *session, SNMPPDU *pdu) throw(SNMPException)
{
    SNMPPDU *response;  // PDU SNMP de respuesta
    int status;         // Estado de la recepcion del mensaje
    
    // Enviamos la PDU SNMP de peticion
    status = snmp_synch_response(session, pdu, &response);
    
    // Evaluamos la recepcion del mensaje de respuesta
    if(status == STAT_SUCCESS) // Recibido con exito
        if(response -> errstat == SNMP_ERR_NOERROR) // Mensaje de respuesta sin errores
            return response;
        else // Mensaje de respuesta con errores
            throw SNMPPacketException(snmp_errstring(response -> errstat), "Error en la PDU de respuesta");
    else if(status == STAT_TIMEOUT) // No hay respuesta del agente
        throw SNMPException("Timeout, no hay respuesta del agente");
    else // Error de sesion (comunidad no valida, acceso no permitido, etc)
        throw SNMPSessionException(*session, "Error en sesion SNMP");
}

/**
 * @brief Procesa la PDU SNMP de respuesta del agente
 * @param pdu PDU SNMP de respuesta
 * @param oids Lista de OIDs
 */
void Model::SNMPManager::processResponse(SNMPPDU *pdu, std::vector<SNMPOID *>& oids, SNMPPDUType type)
{
    if(type == SNMPPDUGet || type == SNMPPDUGetNext) {
        int k = 0;

        // Iteramos por la lista de variables de la PDU de
        // respuesta estableciendo el (tipo, valor) de cada OID
        for(SNMPVariableList *vl = pdu -> variables; vl; vl = vl -> next_variable, k++) {
            oids.at(k) -> data() -> setType((SNMPDataType) vl -> type);
            oids.at(k) -> data() -> setValue((SNMPValue) vl -> val);
        }
    } else if(type == SNMPPDUGetBulk) {
        // TO DO
    }
}

/**
 * @brief Busca el OID correspondiente a una variable de una PDU SNMP de respuesta
 * @param oids Lista de OIDs
 * @param var Variable de la lista de variables de una PDU SNMP de respuesta
 * @return OID correspondiente a la variable si se encuentra en el vector o 0 en caso contrario
 */
Model::SNMPOID *Model::SNMPManager::findOID(const std::vector<SNMPOID *>& oids, SNMPVariableList *var)
{
    if(oids.empty()) // Lista de OIDs vacia
        return 0;    // OID no encontrado

    // Iteramos por la lista de OIDs en busca del OID asociado a la variable de la PDU
    for(std::vector<SNMPOID *>::const_iterator vi = oids.begin(); vi != oids.end(); vi++) {
        SNMPOID *currOID = *vi; // OID actual
        // Comprobamos si las longitudes coinciden
        if(currOID -> parseOIDLength() == var -> name_length) {
            oid *currParseOID = currOID -> parseOID(); // Obtenemos puntero al OID en notacion numerica
            bool equal = true;
            // Comprobamos la igualdad de los numeros que componen el OID
            for(int k = 0; k < (int) currOID -> parseOIDLength() && equal; k++)
                equal = currParseOID[k] == (var -> name)[k];
            if(equal) // OID encontrado
                return currOID;
        }
    }

    return 0; // OID no encontrado
}

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
void Model::SNMPManager::snmpoperation(SNMPPDUType type,
                                       SNMPVersion version,
                                       const std::string& community,
                                       const std::string& agent,
                                       std::vector<SNMPOID *> &oids,
                                       unsigned short nrepeaters,
                                       unsigned short mrepetitions)
{
    SNMPSession *session; // Sesion SNMP Gestor-Agente
    SNMPPDU *requestPDU;  // PDU SNMP de peticion
    SNMPPDU *responsePDU; // PDU SNMP de respuesta

    initSNMP();                                                   // Inicializacion libreria NET-SNMP
    session = createSession(version, community, agent);           // Inicializacion de sesion
    requestPDU = createPDU(type, oids, nrepeaters, mrepetitions); // Creacion de PDU de peticion
    responsePDU = sendPDU(session, requestPDU);                   // Envio de PDU de peticion
    if(type != SNMPPDUSet)                                        // Procesamos la respuesta a una consulta
        processResponse(responsePDU, oids, type);                 // Procesamiento de PDU de respuesta

    snmp_free_pdu(responsePDU);                                   // Liberacion de recursos en PDU de respuesta
    snmp_close(session);                                          // Cerramos la sesion
    SOCK_CLEANUP;                                                 // Liberacion de recursos para SOs win32 (Sin efecto en SOs Unix).
}

/**
 * @brief Inicializacion de atributo estatico _initialized
 */
bool Model::SNMPManager::_initialized = false;
