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
 * @file persistencemanager.h
 * @brief Declaracion de clase PersistenceManager
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Agosto 2013
 */

#ifndef PERSISTENCEMANAGER_H
#define PERSISTENCEMANAGER_H

#include <QVariant>
#include <QString>

namespace Persistence
{
    /**
     * @brief Clase PersistenceManager que implementa la persistencia de la configuracion de la aplicacion
     */
    class PersistenceManager
    {
    public:
        /**
         * @brief Determina si existe o no la configuracion
         * @return true si existe la configuracion y false en caso contrario
         */
        static bool existsConfig();

        /**
         * @brief Crea la configuracion por defecto
         * @param overwrite Si existe la configuracion esta sera sobreescrita
         * @return true si se ha creado correctamente y false en caso contrario
         */
        static bool createConfig(bool overwrite = false);

        /**
         * @brief Borra la configuracion
         * @return true si se ha borrado correctamente o false en caso contrario
         */
        static bool deleteConfig();

        /**
         * @brief Lee el valor correspondiente a la clave perteneciente a un grupo de la configuracion
         * @param key Clave
         * @param group Grupo al que pertenece la clave
         * @return Valor correspondiente al grupo y clave
         */
        static QVariant readConfig(const QString &key, const QString &group = QString());

        /**
         * @brief Escribe el valor correspondiente a la clave perteneciente a un grupo de la configuracion
         * @param value Valor
         * @param key Clave
         * @param group Grupo al que pertenece la clave
         * @return true si el valor se escribio correscamente y false en caso contrario
         */
        static bool writeConfig(const QVariant &value, const QString &key, const QString &group = QString());
    };
}

#endif // PERSISTENCEMANAGER_H
