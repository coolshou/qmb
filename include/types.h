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

#ifndef TYPES_H
#define TYPES_H

#include <net-snmp/net-snmp-includes.h>

namespace Model
{
    typedef enum {
        SNMPv1 = SNMP_VERSION_1,
        SNMPv2 = SNMP_VERSION_2c,
        SNMPv3 = SNMP_VERSION_3
    } SNMPVersion;
}

#endif // TYPES_H
