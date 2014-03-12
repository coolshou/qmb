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
 * @file main.cpp
 * @brief Implementacion de funcion principal
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Junio 2013
 */

#include <QApplication>
#include "persistencemanager.h"
#include "mainwindow.h"
#include "global.h"
#include "snmpmanager.h"

#include <iostream>

void setUpApplication(QApplication *app);
bool verifyConfig();

/**
 * @brief Implementa la funcion principal
 * @param argc Numero de argumentos
 * @param argv Argumentos de la linea de ordenes
 * @return Codigo de finalizacion de ejecucion, 0 con exito, 1 con errores.
 */
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

    return 0;
}

/**
 * @brief Establece las propiedades de la aplicacion
 * @param app Puntero a instancia de QApplication de control de flujo de ejecucion.
 */
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
