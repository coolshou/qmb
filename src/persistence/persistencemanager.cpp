/**
 *  This file is part of QMB.
 *
 *  Copyright (c) 2013-2015 Juan Jose Salazar Garcia jjslzgc@gmail.com
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

#include "persistencemanager.h"
#include "global.h"
#include <QSettings>

bool Persistence::PersistenceManager::existsConfig()
{
    QSettings setting(ORGANIZATION_NAME, APPLICATION_NAME);

    return setting.value("Executed", false).toBool();
}

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

bool Persistence::PersistenceManager::deleteConfig()
{
    QSettings setting(ORGANIZATION_NAME, APPLICATION_NAME);

    if(!existsConfig())
        return false;

    setting.clear();

    return true;
}

QVariant Persistence::PersistenceManager::readConfig(const QString &key, const QString &group)
{
    QSettings setting(ORGANIZATION_NAME, APPLICATION_NAME);

    if(existsConfig()) {
        setting.beginGroup(group);
        return setting.value(key);
    }

    return QVariant();
}

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
