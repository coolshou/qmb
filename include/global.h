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
 * @file global.h
 * @brief Constantes globales
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Junio 2013
 */

#ifndef GLOBAL_H
#define GLOBAL_H

#include "types.h"

#define ORGANIZATION_NAME     "j2sg_software"                           /**< Nombre de la organizacion */
#define ORGANIZATION_DOMAIN   "http://j2sg.wordpress.com"               /**< Web de la organizacion */
#define AUTHOR_NAME           "Juan Jose Salazar Garcia"                /**< Autor */
#define AUTHOR_EMAIL          "jjslzgc@gmail.com"                       /**< Email del autor */
#define APPLICATION_NAME      "QMB"                                     /**< Nombre de la aplicacion */
#define APPLICATION_NAME_LONG "QMB MIB Browser"                         /**< Nombre extendido de la aplicacion */
#define APPLICATION_VERSION   "0.1.0"                                   /**< Version */
#define APPLICATION_YEARS     "2013"                                    /**< Anios de desarrollo */
#define APPLICATION_WEB       "http://j2sg.wordpress.com/proyectos/qmb" /**< Web de la aplicacion */

#define DEFAULT_VERSION Model::SNMPv1                                   /**< Version SNMP */
#define DEFAULT_COMMUNITY_NAME "public"                                 /**< Nombre de comunidad SNMP version 1/2c */
#define DEFAULT_NON_REPEATERS 0                                         /**< Numero de variables por defecto sobre las que no se iterara en una operacion GET BULK */
#define DEFAULT_MAX_REPETITIONS 10                                      /**< Numero de iteraciones por defecto sobre cada variable en una operacion GET BULK */
#define DEFAULT_REMOTE_PORT 161                                         /**< Numero de puerto del agente SNMP remoto */
#define DEFAULT_RETRIES 2                                               /**< Numero de reintentos */
#define DEFAULT_TIMEOUT 2000000                                         /**< Numero de uSegundos para producirse un timeout */

#endif // GLOBAL_H
