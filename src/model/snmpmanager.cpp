/**
 *  This file is part of QMB.
 *
 *  Copyright (c) 2013 2014 Juan Jose Salazar Garcia jjslzgc@gmail.com
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
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include "snmpmanager.h"
#include <algorithm>

void Model::SNMPManager::initSNMP()
{
    if(!_initialized) {
        init_snmp(APPLICATION_NAME);
        _initialized = true;
    }
}

void Model::SNMPManager::configSNMP(unsigned short remotePort, unsigned short retries, long timeout)
{
    _remotePort = remotePort;
    _retries = retries;
    _timeout = timeout;
}

void Model::SNMPManager::snmpget(SNMPVersion version,
                                 const std::string& community,
                                 const std::string& agent,
                                 std::vector<SNMPOID *> &oids) throw(SNMPException)
{
    if(!_initialized)
        return;

    snmpoperation(SNMPPDUGet, version, community, agent, oids);
}

void Model::SNMPManager::snmpgetnext(SNMPVersion version,
                                     const std::string& community,
                                     const std::string& agent,
                                     std::vector<SNMPOID *> &oids) throw(SNMPException)
{
    if(!_initialized)
        return;

    snmpoperation(SNMPPDUGetNext, version, community, agent, oids);
}

void Model::SNMPManager::snmpgetbulk(SNMPVersion version,
                                     const std::string& community,
                                     const std::string& agent,
                                     std::vector<SNMPOID *> &oids,
                                     unsigned short nrepeaters,
                                     unsigned short mrepetitions) throw(SNMPException)
{
    if(!_initialized)
        return;

    if(version == SNMPv1)
        throw SNMPException("Error en sesion SNMP. La operacion Get Bulk no esta soportada por SNMPv1");

    snmpoperation(SNMPPDUGetBulk, version, community, agent, oids, nrepeaters, mrepetitions);
}

void Model::SNMPManager::snmpset(SNMPVersion version,
                                 const std::string& community,
                                 const std::string& agent,
                                 std::vector<SNMPOID *>& oids) throw(SNMPException)
{
    if(!_initialized)
        return;

    snmpoperation(SNMPPDUSet, version, community, agent, oids);
}

Model::SNMPNode *Model::SNMPManager::getMIBTree()
{
    SNMPNode *root = 0;         // Nodo raiz del arbol de la MIB
    SNMPMIBTree *tree = 0;      // Arbol de la MIB

    snmp_set_save_descriptions(1); // Habilita el campo de descripcion del objeto
    snmp_set_mib_warnings(0);      // Inhabilita los mensajes de advertencia
    snmp_set_mib_errors(0);        // Inhabilita los mensajes de advertencia
    netsnmp_init_mib();            // Inicializa la lectura de la MIB


    // Leer el modulo SNMPv2-MIB
    if((tree = read_module("SNMPv2-MIB"))) {
    //if((tree = read_all_mibs())) {
        root = new SNMPNode; // Nodo raiz de la MIB sin OID asignado
        // Parseamos cada uno de los grupos de la MIB de mayor nivel
        // incluyendo estos como hijos en el nodo raiz
        for(SNMPMIBTree *treePtr = tree; treePtr; treePtr = treePtr -> next_peer) {
            root -> childs().push_back(new SNMPNode(0, root));
            snmpParseMIB(root -> childs().back(), treePtr);
        }
    }

    return root;
}

Model::SNMPSession *Model::SNMPManager::createSession(SNMPVersion version,
                                                      const std::string& community,
                                                      const std::string& agent) throw(SNMPException)
{
    SNMPSession session;                                // Sesion SNMP
    SNMPSession *openedSession;                         // Session SNMP abierta

    if(version != SNMPv1 && version != SNMPv2)          // Verificamos que la version esta soportada
        throw SNMPException("Error de inicializacion en sesion SNMP. Version no soportada.");

    snmp_sess_init(&session);                           // Inicializacion de sesion
    session.remote_port = _remotePort;                  // Numero de puerto del agente remoto
    session.retries = _retries;                         // Numero de reintentos
    session.timeout = _timeout;                         // Numero de uSegundos para timeout
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
        if(type == SNMPPDUSet) { // Aniadimos a la PDU el valor correspondiente al k-esimo OID
            if((*vi) -> data() -> type() == SNMPDataUnknown)
                throw SNMPOIDException((*vi) -> strOID(), "Error en la creacion de la PDU. Operacion SNMPSet sobre OID de tipo desconocido.");

            char dataType; // Tipo de dato

            switch((*vi) -> data() -> type()) {
            case SNMPDataInteger:     dataType = 'i'; break;
            case SNMPDataUnsigned:    dataType = 'u'; break;
            case SNMPDataBits:        dataType = 'b'; break;
            case SNMPDataCounter:     dataType = 'c'; break;
            case SNMPDataTimeTicks:   dataType = 't'; break;
            case SNMPDataCounter64:   dataType = 'C'; break;
            case SNMPDataBitString:   dataType = 'b'; break;
            case SNMPDataOctetString: dataType = 's'; break;
            case SNMPDataIPAddress:   dataType = 'a'; break;
            case SNMPDataObjectId:    dataType = 'o'; break;
            default:                  dataType = '=';
            }

            // Aniadimos a la PDU el (tipo, valor) correspondiente al k-esimo OID
            snmp_add_var(pdu, (*vi) -> parseOID(), (*vi) -> parseOIDLength(), dataType, (const char *) (*vi) -> data() -> value());

        } else // Aniadimos a la PDU el valor nulo correspondiente al k-esimo OID
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

void Model::SNMPManager::processResponse(SNMPPDU *pdu, std::vector<SNMPOID *>& oids, SNMPPDUType type)
{
    if(type != SNMPPDUSet) {
        // Liberamos memoria y borramos la lista de OIDs
        for(std::vector<SNMPOID *>::iterator vi = oids.begin();vi != oids.end(); ++vi)
            delete *vi;

        oids.clear();

        // Iteramos por la lista de variables de la PDU de
        // respuesta estableciendo el (tipo, valor) de cada OID
        for(SNMPVariableList *vl = pdu -> variables; vl; vl = vl -> next_variable) {
            SNMPOID *object = new SNMPOID(vl -> name, vl -> name_length);

            object -> data() -> setType((SNMPDataType) vl -> type);
            object -> data() -> setLength(vl -> val_len);
            object -> data() -> setValue((SNMPValue) vl -> val);

            oids.push_back(object);
        }
    }
}

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

void Model::SNMPManager::snmpParseMIB(SNMPNode *root, SNMPMIBTree *tree)
{
    oid *parseOID;              // OID en notacion numerica del objeto parseado
    size_t parseOIDLength = 1;  // Longitud del OID del objeto actual

    if(!tree)
        return;

    // Si el nodo actual tiene padre con OID asignado generamos el OID completo
    if(root -> parent() && root -> parent() -> object()) {
        parseOID = new oid[(parseOIDLength = root -> parent() -> object() -> parseOIDLength() + 1)];
        std::copy(root -> parent() -> object() -> parseOID(),
                  root -> parent() -> object() -> parseOID() + parseOIDLength, parseOID);
    } else // Objeto de primer nivel de la MIB
        parseOID = new oid;

    parseOID[parseOIDLength - 1] = tree -> subid; // OID numerico del objeto

    SNMPOID *object = new SNMPOID(parseOID, parseOIDLength);
    SNMPDataType type;

    // Tipos correspondientes a http://www.net-snmp.org/dev/agent/parse_8h_source.html#l00150
    switch(tree -> type) {
    case TYPE_INTEGER: case TYPE_INTEGER32: type = SNMPDataInteger; break;
    case TYPE_UINTEGER: case TYPE_UNSIGNED32: type = SNMPDataUnsigned; break;
    case TYPE_BITSTRING: type = SNMPDataBitString; break;
    case TYPE_COUNTER: type = SNMPDataCounter; break;
    case TYPE_TIMETICKS: type = SNMPDataTimeTicks; break;
    case TYPE_COUNTER64: type = SNMPDataCounter64; break;
    case TYPE_OCTETSTR: type = SNMPDataOctetString; break;
    case TYPE_IPADDR: type = SNMPDataIPAddress; break;
    case TYPE_OBJID: type = SNMPDataObjectId; break;
    case TYPE_NULL: type = SNMPDataNull; break;
    default: type = SNMPDataUnknown;
    }

    // Establecemos los atributos del OID
    object -> data() -> setType(type);
    object -> setName(tree -> label ? tree -> label : "");
    object -> setStatus((MIBStatus) tree -> status);
    object -> setAccess((MIBAccess) tree -> access);
    object -> setDescription(tree -> description ? tree -> description : "");

    // Establecemos el objeto al nodo actual
    root -> setObject(object);

    // Parseamos cada uno de los hijos del nodo actual y los incluimos como hijos del mismo
    for(SNMPMIBTree *child = tree -> child_list; child; child = child -> next_peer) {
        root -> childs().push_back(new SNMPNode(0, root));
        snmpParseMIB(root -> childs().back(), child);
    }
}

bool Model::SNMPManager::_initialized = false;

unsigned short Model::SNMPManager::_remotePort = DEFAULT_REMOTE_PORT;

unsigned short Model::SNMPManager::_retries = DEFAULT_RETRIES;

long Model::SNMPManager::_timeout = DEFAULT_TIMEOUT;
**/
