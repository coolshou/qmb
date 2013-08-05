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
#include "mainwindow.h"
#include "global.h"
#include "snmpmanager.h"
#include "testsnmpmanager.h"
#include <iostream>

// Declaracion de funciones

void setUpApplication(QApplication *app);
void testSNMP(std::string agent, std::string community);

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

    if(argc == 3) {
        testSNMP(std::string(argv[1]), std::string(argv[2]));
        return 0;
    }

    setUpApplication(&app);

    window.show();

    return app.exec();
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

void testSNMP(std::string agent, std::string community)
{
    Model::SNMPManager::initSNMP();
    std::vector<Model::SNMPOID *> oids;
    oids.push_back(new Model::SNMPOID("1.3.6.1.2.1.1.0"));
    std::cout << "SNMP Get Bulk test " << (Test::TestSNMPManager::testGetBulk(Model::SNMPv2, community, agent, oids, 0, 10., true) ? "completed successfully" : "has errors") << std::endl;
}
