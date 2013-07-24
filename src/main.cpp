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
#include <vector>
#include <iostream>

// Declaracion de funciones

void setUpApplication(QApplication *app);

int testSNMPAPI(const char *agent);

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

   window.show();

   return app.exec();
   //return testSNMPAPI("192.168.1.30");

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

/**
 * @brief Realiza conjunto de pruebas de la API SNMP sobre un agente SNNP
 * @param agent IP o dominio del agente SNMP
 */
int testSNMPAPI(const char *agent)
{
    std::vector<Model::SNMPOID *> oids;

    Model::SNMPManager::initSNMP();

    try {
        oids.push_back(new Model::SNMPOID("1.3.6.1.2.1"));
        Model::SNMPManager::snmpgetbulk(Model::SNMPv2, "public", agent, oids, 0, 5);
        for(std::vector<Model::SNMPOID *>::iterator vi=oids.begin();vi!=oids.end();++vi)
            std::cout << (*vi) -> strOID() << " := "
                      <<  (*vi) -> data() -> toString() << std::endl;
    } catch (Model::SNMPSessionException& exception) {
        std::cout << exception.message() << std::endl;
        std::cout << "Agent : " << exception.session().peername << ":"
                  << exception.session().remote_port << " Community: "
                  << exception.session().community << std::endl;
        return -1;
    } catch (Model::SNMPOIDException& exception) {
        std::cout << exception.message() << std::endl;
        std::cout << "OID : " << exception.badOID() << std::endl;
        return -1;
    } catch (Model::SNMPPacketException& exception) {
        std::cout << exception.message() << std::endl;
        std::cout << "Packet Error : " << exception.error() << std::endl;
        return -1;
    } catch (Model::SNMPException& exception) {
        std::cout << exception.message() << std::endl;
        return -1;
    }

    return 0;
}
