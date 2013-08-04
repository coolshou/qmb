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
#include "centralwidget.h"
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
 * @brief Ranura Acerca de ..
 */
void View::MainWindow::about()
{
    QMessageBox::about(this, tr("About %1").arg(APPLICATION_NAME),
                             tr("<h2>%1 %2</h2>"
                                "<h3>Invoicing and Management for SMBs</h3>"
                                "<p>(C) %3 %4 <a href= \"mailto:%5\" >%5</a></p>"
                                "<p><a href= \"%6\" >%6</a></p>"
                                "<p>Licensed under <a href=\"http://www.gnu.org/licenses/gpl.html\" >GNU General Public License version 3</a></p>")
                             .arg(APPLICATION_NAME_LONG)
                             .arg(APPLICATION_VERSION)
                             .arg(APPLICATION_YEARS)
                             .arg(AUTHOR_NAME)
                             .arg(AUTHOR_EMAIL)
                             .arg(APPLICATION_WEB));
}

/**
 * @brief Ranura para cambio de la barra de estado
 * @param status Mensaje de estado
 */
void View::MainWindow::changeStatus(const QString& status)
{
    statusBar() -> showMessage(status, 5000);
}

/**
 * @brief Crea los widgets
 */
void View::MainWindow::createWidgets()
{
    createCentralWidget();
    createActions();
    createMenus();
    createToolBar();
    createStatusBar();
}

/**
 * @brief Crea y establece el widget central
 */
void View::MainWindow::createCentralWidget()
{
    _centralWidget = new CentralWidget;

    setCentralWidget(_centralWidget);
}

/**
 * @brief Crea las acciones del menu y barra de herramientas
 */
void View::MainWindow::createActions()
{
    _exitAction = new QAction(tr("E&xit"), this);
    _exitAction -> setStatusTip(tr("Exit the application"));

    _aboutAction = new QAction(tr("&About"), this);
    _aboutAction -> setStatusTip(tr("Show information about the Application"));

    _aboutQtAction = new QAction(tr("About &Qt"), this);
    _aboutQtAction -> setStatusTip(tr("Show information about Qt framework"));
}

/**
 * @brief Crea los menus
 */
void View::MainWindow::createMenus()
{
    _applicationMenu = menuBar() -> addMenu(tr("&Application"));
    _applicationMenu -> addAction(_exitAction);

    _helpMenu = menuBar() -> addMenu(tr("&Help"));
    _helpMenu -> addAction(_aboutAction);
    _helpMenu -> addAction(_aboutQtAction);
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
    _statusLabel = new QLabel;

    statusBar() -> addWidget(_statusLabel);
}

/**
 * @brief Establece las conexiones
 */
void View::MainWindow::createConnections()
{
    connect(_exitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(_aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    connect(_aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(_centralWidget, SIGNAL(statusChanged(QString)), this, SLOT(changeStatus(QString)));
}
