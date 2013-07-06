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
 * @file mainwindow.cpp
 * @brief Implementacion de metodos de la clase MainWindow
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Julio 2013
 */

#include <QtGui>
#include "mainwindow.h"
#include "global.h"

/**
 * @brief Constructor de MainWindow
 */
View::MainWindow::MainWindow()
{
    createWidgets();
    createConnections();

    setWindowTitle(APPLICATION_NAME_LONG);
}

/**
 * @brief Destructor de MainWindow
 */
View::MainWindow::~MainWindow()
{

}

/**
 * @brief Manejador de eventos de cierre de la ventana principal
 * @param event Evento de cierre
 */
void View::MainWindow::closeEvent(QCloseEvent *event)
{
    event -> accept();
}

/**
 * @brief Crea los widgets
 */
void View::MainWindow::createWidgets()
{
    createCentralWidget();
    createActions();
    createMenu();
    createToolBar();
    createStatusBar();
}

/**
 * @brief Crea y establece el widget central
 */
void View::MainWindow::createCentralWidget()
{

}

/**
 * @brief Crea las acciones del menu y barra de herramientas
 */
void View::MainWindow::createActions()
{

}

/**
 * @brief Crea los menus
 */
void View::MainWindow::createMenu()
{

}

/**
 * @brief Crea las barras de herramientas
 */
void View::MainWindow::createToolBar()
{

}

/**
 * @brief Crea la barra de estado
 */
void View::MainWindow::createStatusBar()
{

}

/**
 * @brief Establece las conexiones
 */
void View::MainWindow::createConnections()
{

}
