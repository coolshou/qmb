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
#ifndef TESTSNMPMANAGER_H
#define TESTSNMPMANAGER_H

#include "snmpmanager.h"
#include "types.h"
#include <string>
#include <vector>

namespace Test
{
    class TestSNMPManager
    {
    public:
        static bool testGet(Model::SNMPVersion version,
                            const std::string& community,
                            const std::string& agent,
                            std::vector<Model::SNMPOID *> oids,
                            bool verbose = false);
        static bool testGetNext(Model::SNMPVersion version,
                                const std::string& community,
                                const std::string& agent,
                                std::vector<Model::SNMPOID *> oids,
                                bool verbose = false);
        static bool testGetBulk(Model::SNMPVersion version,
                                const std::string& community,
                                const std::string& agent,
                                std::vector<Model::SNMPOID *> oids,
                                unsigned short nrepeaters = DEFAULT_NON_REPEATERS,
                                unsigned short mrepetitions = DEFAULT_MAX_REPETITIONS,
                                bool verbose = false);
        static bool testSet(Model::SNMPVersion version,
                            const std::string& community,
                            const std::string& agent,
                            std::vector<Model::SNMPOID *> oids,
                            bool verbose = false);
    private:
        static bool test(TestOperation operation,
                         Model::SNMPVersion version,
                         const std::string& community,
                         const std::string& agent,
                         std::vector<Model::SNMPOID *> oids,
                         unsigned short nrepeaters = DEFAULT_NON_REPEATERS,
                         unsigned short mrepetitions = DEFAULT_MAX_REPETITIONS,
                         bool verbose = false);
    };
}
**/
#endif // TESTSNMPMANAGER_H
