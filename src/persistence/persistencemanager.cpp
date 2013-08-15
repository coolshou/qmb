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
 * @file persistencemanager.cpp
 * @brief Implementacion de metodos de la clase PersistenceManager
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Agosto 2013
 */

#include "persistencemanager.h"
#include "global.h"
#include <QSettings>

/**
 * @brief Determina si existe o no la configuracion
 * @return true si existe la configuracion y false en caso contrario
 */
bool Persistence::PersistenceManager::existsConfig()
{
    QSettings setting(ORGANIZATION_NAME, APPLICATION_NAME);

    return setting.value("Executed", false).toBool();
}

/**
 * @brief Crea la configuracion por defecto
 * @param overwrite Si existe la configuracion esta sera sobreescrita
 * @return true si se ha creado correctamente y false en caso contrario
 */
bool Persistence::PersistenceManager::createConfig(bool overwrite)
{
    if(existsConfig() && !overwrite)
        return false;

    QSettings setting(ORGANIZATION_NAME, APPLICATION_NAME);

    setting.setValue("Executed",       true);
    setting.beginGroup("Session");
    setting.setValue("RemotePort",     DEFAULT_REMOTE_PORT);
    setting.setValue("Timeout",        DEFAULT_TIMEOUT);
    setting.setValue("Retries",        DEFAULT_RETRIES);
    setting.endGroup();

    return true;
}

/**
 * @brief Borra la configuracion
 * @return true si se ha borrado correctamente o false en caso contrario
 */
bool Persistence::PersistenceManager::deleteConfig()
{
    QSettings setting(ORGANIZATION_NAME, APPLICATION_NAME);

    if(!existsConfig())
        return false;

    setting.clear();

    return true;
}

/**
 * @brief Lee el valor correspondiente a la clave perteneciente a un grupo de la configuracion
 * @param key Clave
 * @param group Grupo al que pertenece la clave
 * @return Valor correspondiente al grupo y clave
 */
QVariant Persistence::PersistenceManager::readConfig(const QString &key, const QString &group)
{
    QSettings setting(ORGANIZATION_NAME, APPLICATION_NAME);

    if(existsConfig()) {
        setting.beginGroup(group);
        return setting.value(key);
    }

    return QVariant();
}

/**
 * @brief Escribe el valor correspondiente a la clave perteneciente a un grupo de la configuracion
 * @param value Valor
 * @param key Clave
 * @param group Grupo al que pertenece la clave
 * @return true si el valor se escribio correscamente y false en caso contrario
 */
bool Persistence::PersistenceManager::writeConfig(const QVariant &value, const QString &key, const QString &group)
{
    QSettings setting(ORGANIZATION_NAME, APPLICATION_NAME);

    if(!existsConfig())
        return false;

    setting.beginGroup(group);
    if(!setting.contains(key))
        return false;
    setting.setValue(key, value);
    setting.endGroup();

    return true;
}

