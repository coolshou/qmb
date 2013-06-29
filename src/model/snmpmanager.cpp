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

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include "snmpmanager.h"

bool Model::SNMPManager::snmpget(SNMPVersion version, const std::string& community, const std::string& address, const std::string& strOID) throw(SNMPException)
{
    struct snmp_session session, *ss;                   // Datos de sesión gestor<->agente
    struct snmp_pdu *pdu;                               // PDU SNMP de peticion
    struct snmp_pdu *response;                          // PDU SNMP de respuesta

    oid myOID[MAX_OID_LEN];                             // OID del objeto objetivo
    size_t myOIDLen = MAX_OID_LEN;                      // Longitud de la cadena que representa el OID.

    struct variable_list *vars;                         // Lista de variables de la PDU de respuesta

    int status;                                         // Estado de la sesion

    init_snmp("snmptest");                              // Inicializacion de libreria net-snmp

    snmp_sess_init(&session);                           // Inicializacion de sesion
    session.peername = (char *) address;                // Direccion del agente SNMP
    session.version = version;                          // Version SNMP
    session.community = (u_char *) community;           // Comunidad SNMPv1-2
    session.community_len = strlen(community);          // Longitud del nombre de la comunidad

    ss = snmp_open(&session);                           // Apertura de sesion

    if(!ss)
        return false;

    pdu = snmp_pdu_create(SNMP_MSG_GET);                // Creacion de PDU SNMP GET de peticion

    if(!snmp_parse_oid(strOID, myOID, &myOIDLen))
        cout << "Error en myOID" << endl;
    //read_objid(strOID, myOID, &myOIDLen);               // Inicialización de myOID
    snmp_add_null_var(pdu, myOID, myOIDLen);            // Inclusion de la tupla (myOID, valor nulo)

    status = snmp_synch_response(ss, pdu, &response);   // Envio de peticion

    if(status == STAT_SUCCESS && response -> errstat == SNMP_ERR_NOERROR) {
        //for(vars=response->variables; vars; vars = vars->next_variable)
        //    print_variable(vars->name, vars->name_length, vars);

        for(vars=response->variables; vars; vars = vars->next_variable) {
            if (vars->type == ASN_OCTET_STR) {
                     char *sp = (char *) malloc(1 + vars->val_len);
                     memcpy(sp, vars->val.string, vars->val_len);
                     sp[vars->val_len] = '\0';
                     printf("value is a string: %s\n", sp);
                     free(sp);
                     cout << "OID: ";
                     for(int i=0;i<vars->name_length;i++) {
                         cout << (vars->name)[i];
                         if(i != vars->name_length-1)
                             cout << ".";
                     }
                     cout << endl;
                   }
                   else
                     printf("value is NOT a string! Ack!\n");
        }
    } else {
        if(status == STAT_SUCCESS)
            cout << "Error in packet: " << snmp_errstring(response->errstat) << endl;
        else
            cout << "Unknown error" << endl;
    }
    if(response)
        snmp_free_pdu(response);
    snmp_close(ss);

    return true;
}

bool Model::SNMPManager::snmpgetnext(SNMPVersion version, const std::string& community, const std::string& address, const std::string& strOID) throw(SNMPException)
{

}

bool Model::SNMPManager::snmpget(SNMPVersion version, const std::string& community, const std::string& address, const std::string& strOID) throw(SNMPException)
{

}

bool Model::SNMPManager::snmpgetbulk(SNMPVersion version, const std::string& community, const std::string& address, const std::string& strOID) throw(SNMPException)
{

}
