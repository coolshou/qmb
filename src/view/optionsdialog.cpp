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
 * @file optionsdialog.cpp
 * @brief Implementacion de metodos de la clase OptionsDialog
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Agosto 2013
 */

#include "optionsdialog.h"
#include "persistencemanager.h"
#include "global.h"
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QMessageBox>

/**
 * @brief Constructor de OptionsDialog
 * @param parent Widget padre
 */
View::OptionsDialog::OptionsDialog(QWidget *parent) : QDialog(parent)
{
    createWidgets();
    createConnections();
    setWindowTitle(tr("Options"));
    setFixedSize(sizeHint());
    loadOptions();
}

/**
 * @brief Establece el resultado de Aceptado/Rechazado del cuadro de dialogo
 * @param result Resultado del cuadro de dialogo
 */
void View::OptionsDialog::done(int result)
{
    if(result && !saveOptions()) {
            QMessageBox::critical(this, tr("Critical error"), tr("There was errors while saving changes"), QMessageBox::Ok);
            result = QDialog::Rejected;
    }

    QDialog::done(result);
}

/**
 * @brief Establece en las opciones los valores por defecto
 */
void View::OptionsDialog::setDefaultValues()
{
    _remotePortSpinBox -> setValue(DEFAULT_REMOTE_PORT);
    _timeoutSpinBox -> setValue(DEFAULT_TIMEOUT / 1000000);
    _retriesSpinBox -> setValue(DEFAULT_RETRIES);
}

/**
 * @brief Crea los widgets
 */
void View::OptionsDialog::createWidgets()
{
    _remotePortLabel = new QLabel(tr("Remote &Port:"));
    _remotePortSpinBox = new QSpinBox;
    _remotePortSpinBox -> setMinimum(0);
    _remotePortSpinBox -> setMaximum(65535);
    _remotePortLabel -> setBuddy(_remotePortSpinBox);

    _timeoutLabel = new QLabel(tr("&Timeout:"));
    _timeoutSpinBox = new QSpinBox;
    _timeoutSpinBox -> setSuffix(tr("s"));
    _timeoutSpinBox -> setMinimum(0);
    _timeoutLabel -> setBuddy(_timeoutSpinBox);

    _retriesLabel = new QLabel(tr("&Retries:"));
    _retriesSpinBox = new QSpinBox;
    _retriesSpinBox -> setMinimum(0);
    _retriesLabel -> setBuddy(_retriesSpinBox);

    _defaultPushButton = new QPushButton(tr("Default Values"));

    _okPushButton = new QPushButton(tr("Ok"));
    _okPushButton -> setDefault(true);

    _cancelPushButton = new QPushButton(tr("Cancel"));


    QGridLayout *sessionLayout = new QGridLayout;

    sessionLayout -> addWidget(_remotePortLabel, 0, 0, 1, 1);
    sessionLayout -> addWidget(_remotePortSpinBox, 0, 1, 1, 1);
    sessionLayout -> addWidget(_timeoutLabel, 1, 0, 1, 1);
    sessionLayout -> addWidget(_timeoutSpinBox, 1, 1, 1, 1);
    sessionLayout -> addWidget(_retriesLabel, 2, 0, 1, 1);
    sessionLayout -> addWidget(_retriesSpinBox, 2, 1, 1, 1);

    QGroupBox *sessionGroupBox = new QGroupBox(tr("SNMP Session"));

    sessionGroupBox -> setLayout(sessionLayout);

    QHBoxLayout *bottomLayout = new QHBoxLayout;

    bottomLayout -> addWidget(_defaultPushButton);
    bottomLayout -> addStretch();
    bottomLayout -> addWidget(_okPushButton);
    bottomLayout -> addWidget(_cancelPushButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout -> addWidget(sessionGroupBox);
    mainLayout -> addLayout(bottomLayout);

    setLayout(mainLayout);
}

/**
 * @brief Establece las conexiones
 */
void View::OptionsDialog::createConnections()
{
    connect(_defaultPushButton, SIGNAL(clicked()), this, SLOT(setDefaultValues()));
    connect(_okPushButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_cancelPushButton, SIGNAL(clicked()), this, SLOT(reject()));
}

/**
 * @brief Carga las opciones en el cuadro de dialogo
 */
void View::OptionsDialog::loadOptions()
{
    unsigned short port = Persistence::PersistenceManager::readConfig("RemotePort", "Session").toInt();
    long timeout = Persistence::PersistenceManager::readConfig("Timeout", "Session").toInt();
    unsigned short retries = Persistence::PersistenceManager::readConfig("Retries", "Session").toInt();

    _remotePortSpinBox -> setValue(port);
    _timeoutSpinBox -> setValue(timeout / 1000000);
    _retriesSpinBox -> setValue(retries);
}

/**
 * @brief Guarda las opciones
 * @return true si las opciones se guardaron correctamente y false en caso contrario
 */
bool View::OptionsDialog::saveOptions()
{
    unsigned short port = _remotePortSpinBox -> value();
    int timeout = _timeoutSpinBox -> value() * 1000000;
    unsigned short retries = _retriesSpinBox -> value();

    bool portSaved = Persistence::PersistenceManager::writeConfig(port, "RemotePort", "Session");
    bool timeoutSaved = Persistence::PersistenceManager::writeConfig(timeout, "Timeout", "Session");
    bool retriesSaved = Persistence::PersistenceManager::writeConfig(retries, "Retries", "Session");

    return portSaved && timeoutSaved && retriesSaved;
}
