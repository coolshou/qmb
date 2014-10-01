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

#ifndef SNMPMANAGER_H
#define SNMPMANAGER_H
/**
#include <string>
#include <vector>
#include "types.h"
#include "global.h"
#include "snmpoid.h"
#include "snmpnode.h"
#include "snmpexception.h"

namespace Model
{
    class SNMPManager
    {
    public:
        static void initSNMP();
        static void configSNMP(unsigned short remotePort = DEFAULT_REMOTE_PORT,
                               unsigned short retries = DEFAULT_RETRIES,
                               long timeout = DEFAULT_TIMEOUT);
        static void snmpget(SNMPVersion version,
                            const std::string& community,
                            const std::string& agent,
                            std::vector<SNMPOID *>& oids) throw(SNMPException);
        static void snmpgetnext(SNMPVersion version,
                                const std::string& community,
                                const std::string& agent,
                                std::vector<SNMPOID *> &oids) throw(SNMPException);
        static void snmpgetbulk(SNMPVersion version,
                                const std::string& community,
                                const std::string& agent,
                                std::vector<SNMPOID *>& oids,
                                unsigned short nrepeaters = DEFAULT_NON_REPEATERS,
                                unsigned short mrepetitions = DEFAULT_MAX_REPETITIONS) throw(SNMPException);
        static void snmpset(SNMPVersion version,
                            const std::string& community,
                            const std::string& agent,
                            std::vector<SNMPOID *> &oids) throw(SNMPException);
        static SNMPNode *getMIBTree();
    private:
        static SNMPSession *createSession(SNMPVersion version,
                                          const std::string& community,
                                          const std::string& agent) throw(SNMPException);
        static SNMPPDU *createPDU(SNMPPDUType type,
                                  const std::vector<SNMPOID *> &oids,
                                  unsigned short nrepeaters = DEFAULT_NON_REPEATERS,
                                  unsigned short mrepetitions = DEFAULT_MAX_REPETITIONS) throw(SNMPException);
        static SNMPPDU *sendPDU(SNMPSession *session, SNMPPDU *pdu) throw(SNMPException);
        static void processResponse(SNMPPDU *pdu, std::vector<SNMPOID *>& oids, SNMPPDUType type);
        static void snmpoperation(SNMPPDUType type,
                                  SNMPVersion version,
                                  const std::string& community,
                                  const std::string& agent,
                                  std::vector<SNMPOID *> &oids,
                                  unsigned short nrepeaters = DEFAULT_NON_REPEATERS,
                                  unsigned short mrepetitions = DEFAULT_MAX_REPETITIONS);
        static void snmpParseMIB(SNMPNode *root, SNMPMIBTree *tree);

        static bool _initialized;
        static unsigned short _remotePort;
        static unsigned short _retries;
        static long _timeout;
    };
}
**/
#endif // SNMPMANAGER_H
