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
 * @file types.h
 * @brief Declaracion de tipos
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Junio 2013
 */

#ifndef TYPES_H
#define TYPES_H

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

namespace Model
{ 
    /**
     * @brief Version SNMP utilizada
     */
    typedef enum SNMPVersionEnum {
        SNMPv1 = SNMP_VERSION_1,  /**< SNMP VERSION 1 */
        SNMPv2 = SNMP_VERSION_2c, /**< SNMP VERSION 2 */
        SNMPv3 = SNMP_VERSION_3   /**< SNMP VERSION 3 */
    } SNMPVersion;

    /**
     * @brief Tipo de PDU SNMP
     */
    typedef enum SNMPPDUTypeEnum {
        SNMPPDUGet      = SNMP_MSG_GET,         /**< PDU de peticion GET */
        SNMPPDUGetNext  = SNMP_MSG_GETNEXT,     /**< PDU de peticion GETNEXT */
        SNMPPDUGetBulk  = SNMP_MSG_GETBULK,     /**< PDU de peticion GETBULK */
        SNMPPDUSet      = SNMP_MSG_SET,         /**< PDU de peticion SET */
        SNMPPDUResponse = SNMP_MSG_RESPONSE     /**< PDU de respuesta */
    } SNMPPDUType;

    /**
     * @brief Tipo de dato SNMP
     */
    typedef enum SNMPDataTypeEnum {
        SNMPDataNull        = ASN_NULL,         /**< Tipo Null */
        SNMPDataInteger     = ASN_INTEGER,      /**< Tipo Integer */
        SNMPDataUnsigned    = ASN_UNSIGNED,     /**< Tipo Unsigned */
        SNMPDataOctetString = ASN_OCTET_STR,    /**< Tipo String */
        SNMPDataBits        = ASN_BIT8,         /**< Tipo Bits */
        SNMPDataBitString   = ASN_BIT_STR,      /**< Tipo Bit String */
        SNMPDataObjectId    = ASN_OBJECT_ID,    /**< Tipo OID */
        SNMPDataIPAddress   = ASN_IPADDRESS,    /**< Tipo IP Address */
        SNMPDataCounter     = ASN_COUNTER,      /**< Tipo Counter */
        SNMPDataCounter64   = ASN_COUNTER64,    /**< Tipo Counter64 */
        SNMPDataGauge       = ASN_GAUGE,        /**< Tipo Gauge */
        SNMPDataTimeTicks   = ASN_TIMETICKS     /**< Tipo Time Ticks */
    } SNMPDataType;


    /**
     * @brief Estado del objeto de la MIB
     */
    typedef enum MIBStatusEnum {
        MIBStatusMandatory  = MIB_STATUS_MANDATORY,   /**< Estado Mandatory */
        MIBStatusOptional   = MIB_STATUS_OPTIONAL,    /**< Estado Optional */
        MIBStatusObsolete   = MIB_STATUS_OBSOLETE,    /**< Estado Obsolete */
        MIBStatusDeprecated = MIB_STATUS_DEPRECATED   /**< Estado Deprecated */
    } MIBStatus;

    /**
     * @brief Model de acceso del objeto de la MIB
     */
    typedef enum MIBAccessEnum {
        MIBAccessReadOnly      = MIB_ACCESS_READONLY,  /**< Acceso Read-Only */
        MIBAccessReadWrite     = MIB_ACCESS_READWRITE, /**< Acceso Read-Write */
        MIBAccessWriteOnly     = MIB_ACCESS_WRITEONLY, /**< Acceso Write-Only */
        MIBAccessNotAccessible = MIB_ACCESS_NOACCESS   /**< Acceso Not-Accessible */
    } MIBAccess;

    /**
     * @brief Valor tomado por un dato en SNMP
     */
    typedef netsnmp_vardata SNMPValue;

    /**
     * @brief Contador de 64 bits
     */
    typedef struct counter64 SNMPCounter64;

    /**
     * @brief Sesion SNMP Gestor-Agente
     */
    typedef netsnmp_session SNMPSession;

    /**
     * @brief PDU SNMP Peticion/Respuesta
     */
    typedef struct snmp_pdu SNMPPDU;

    /**
     * @brief Lista de variables de PDU SNMP
     */
    typedef netsnmp_variable_list SNMPVariableList;
}

#endif // TYPES_H
