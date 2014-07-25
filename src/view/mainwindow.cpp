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

#include <QtGui>
#include "mainwindow.h"
#include "centralwidget.h"
#include "optionsdialog.h"
#include "snmpmanager.h"
#include "persistencemanager.h"
#include "global.h"

View::MainWindow::MainWindow()
{
    createWidgets();
    createConnections();

    setWindowTitle(APPLICATION_NAME_LONG);
    setWindowIcon(QIcon(":/images/qmb.svg"));
}

View::MainWindow::~MainWindow()
{
}

void View::MainWindow::closeEvent(QCloseEvent *event)
{
    event -> accept();
}

void View::MainWindow::options()
{
    OptionsDialog dialog(this);

    if(dialog.exec() == QDialog::Accepted) {
        changeStatus(tr("Options changes has been saved"));

        unsigned short port = Persistence::PersistenceManager::readConfig("RemotePort", "Session").toInt();
        unsigned short retries = Persistence::PersistenceManager::readConfig("Retries", "Session").toInt();
        long timeout = Persistence::PersistenceManager::readConfig("Timeout", "Session").toInt();

        Model::SNMPManager::configSNMP(port, retries, timeout);
        _centralWidget -> loadMIBTree();

        changeStatus(tr("Changes applied"));
    }
}

void View::MainWindow::about()
{
    QMessageBox::about(this, tr("About %1").arg(APPLICATION_NAME),
                             tr("<h2>%1 %2</h2>"
                                "<h3>MIB Browser to SNMP Agents</h3>"
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

void View::MainWindow::changeStatus(const QString& status)
{
    statusBar() -> showMessage(status, 5000);
}

void View::MainWindow::createWidgets()
{
    createCentralWidget();
    createActions();
    createMenus();
    createToolBar();
    createStatusBar();
}

void View::MainWindow::createCentralWidget()
{
    _centralWidget = new CentralWidget;

    setCentralWidget(_centralWidget);
}

void View::MainWindow::createActions()
{
    _optionsAction = new QAction(tr("&Options"), this);
    _optionsAction -> setStatusTip(tr("Application options"));

    _exitAction = new QAction(tr("E&xit"), this);
    _exitAction -> setStatusTip(tr("Exit the application"));

    _aboutAction = new QAction(tr("&About"), this);
    _aboutAction -> setStatusTip(tr("Show information about the Application"));

    _aboutQtAction = new QAction(tr("About &Qt"), this);
    _aboutQtAction -> setStatusTip(tr("Show information about Qt framework"));
}

void View::MainWindow::createMenus()
{
    _applicationMenu = menuBar() -> addMenu(tr("&Application"));
    _applicationMenu -> addAction(_optionsAction);
    _applicationMenu -> addAction(_exitAction);

    _helpMenu = menuBar() -> addMenu(tr("&Help"));
    _helpMenu -> addAction(_aboutAction);
    _helpMenu -> addAction(_aboutQtAction);
}

void View::MainWindow::createToolBar()
{

}

void View::MainWindow::createStatusBar()
{
    _statusLabel = new QLabel;

    statusBar() -> addWidget(_statusLabel);
}

void View::MainWindow::createConnections()
{
    connect(_optionsAction, SIGNAL(triggered()), this, SLOT(options()));
    connect(_exitAction, SIGNAL(triggered()), this, SLOT(close()));
    connect(_aboutAction, SIGNAL(triggered()), this, SLOT(about()));
    connect(_aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(_centralWidget, SIGNAL(statusChanged(QString)), this, SLOT(changeStatus(QString)));
}
