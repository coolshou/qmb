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

#ifndef GLOBAL_H
#define GLOBAL_H

#include <QtNetSNMP/qsnmptypes.h>

#define ORGANIZATION_NAME     "j2sg_software"
#define ORGANIZATION_DOMAIN   "http://j2sg.wordpress.com"
#define AUTHOR_NAME           "Juan Jose Salazar Garcia"
#define AUTHOR_EMAIL          "jjslzgc@gmail.com"
#define APPLICATION_NAME      "QMB"
#define APPLICATION_NAME_LONG "QMB MIB Browser"
#define APPLICATION_VERSION   "0.1.1"
#define APPLICATION_YEARS     "2013-2014"
#define APPLICATION_WEB       "http://j2sg.wordpress.com/proyectos/qmb"

#define DEFAULT_VERSION QtNetSNMP::SNMPv1
#define DEFAULT_COMMUNITY_NAME "public"
#define DEFAULT_NON_REPEATERS 0
#define DEFAULT_MAX_REPETITIONS 10
#define DEFAULT_REMOTE_PORT 161
#define DEFAULT_RETRIES 2
#define DEFAULT_TIMEOUT 1000000

#endif // GLOBAL_H
