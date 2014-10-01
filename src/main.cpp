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

#include <QApplication>
#include "persistencemanager.h"
#include "mainwindow.h"
#include "global.h"
#include <iostream>

void setUpApplication(QApplication *app);
bool verifyConfig();

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    View::MainWindow window;

    setUpApplication(&app);

    std::cout << QString("%1 %2").arg(app.applicationName()).arg(app.applicationVersion()).toStdString() << std::endl;
    std::cout << QObject::tr("Starting ...").toStdString() << std::endl << std::endl;

    if(!verifyConfig()) {
        std::cout << QObject::tr("Config : Error : Application will be closed").toStdString() << std::endl;
        return 1;
    } else
        std::cout << QObject::tr("Config : OK").toStdString() << std::endl;

    window.show();

    return app.exec();
}

void setUpApplication(QApplication *app)
{
    if(!app)
        return;

    app -> setOrganizationName(ORGANIZATION_NAME);
    app -> setOrganizationDomain(ORGANIZATION_DOMAIN);
    app -> setApplicationName(APPLICATION_NAME);
    app -> setApplicationVersion(APPLICATION_VERSION);
}

bool verifyConfig()
{
    if(!Persistence::PersistenceManager::existsConfig() && !Persistence::PersistenceManager::createConfig())
        return false;

    return true;
}
