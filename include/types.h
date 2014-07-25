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

#ifndef TYPES_H
#define TYPES_H

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

namespace Model
{ 
    typedef enum SNMPVersionEnum {
        SNMPv1 = SNMP_VERSION_1,
        SNMPv2 = SNMP_VERSION_2c,
        SNMPv3 = SNMP_VERSION_3
    } SNMPVersion;

    typedef enum SNMPPDUTypeEnum {
        SNMPPDUGet      = SNMP_MSG_GET,
        SNMPPDUGetNext  = SNMP_MSG_GETNEXT,
        SNMPPDUGetBulk  = SNMP_MSG_GETBULK,
        SNMPPDUSet      = SNMP_MSG_SET,
        SNMPPDUResponse = SNMP_MSG_RESPONSE
    } SNMPPDUType;

    typedef enum SNMPDataTypeEnum {
        SNMPDataUnknown     = -1,
        SNMPDataNull        = ASN_NULL,
        SNMPDataInteger     = ASN_INTEGER,
        SNMPDataUnsigned    = ASN_UNSIGNED,
        SNMPDataOctetString = ASN_OCTET_STR,
        SNMPDataBits        = ASN_BIT8,
        SNMPDataBitString   = ASN_BIT_STR,
        SNMPDataObjectId    = ASN_OBJECT_ID,
        SNMPDataIPAddress   = ASN_IPADDRESS,
        SNMPDataCounter     = ASN_COUNTER,
        SNMPDataCounter64   = ASN_COUNTER64,
        SNMPDataGauge       = ASN_GAUGE,
        SNMPDataTimeTicks   = ASN_TIMETICKS
    } SNMPDataType;

    typedef enum MIBStatusEnum {
        MIBStatusMandatory  = MIB_STATUS_MANDATORY,
        MIBStatusOptional   = MIB_STATUS_OPTIONAL,
        MIBStatusObsolete   = MIB_STATUS_OBSOLETE,
        MIBStatusDeprecated = MIB_STATUS_DEPRECATED
    } MIBStatus;

    typedef enum MIBAccessEnum {
        MIBAccessReadOnly      = MIB_ACCESS_READONLY,
        MIBAccessReadWrite     = MIB_ACCESS_READWRITE,
        MIBAccessWriteOnly     = MIB_ACCESS_WRITEONLY,
        MIBAccessNotAccessible = MIB_ACCESS_NOACCESS
    } MIBAccess;

    typedef netsnmp_vardata SNMPValue;

    typedef struct counter64 SNMPCounter64;

    typedef netsnmp_session SNMPSession;

    typedef struct snmp_pdu SNMPPDU;

    typedef netsnmp_variable_list SNMPVariableList;

    typedef struct tree SNMPMIBTree;
}

namespace Test
{
    typedef enum TestOperationEnum {
        TestGet,
        TestGetNext,
        TestGetBulk,
        TestSet
    } TestOperation;
}

#endif // TYPES_H
