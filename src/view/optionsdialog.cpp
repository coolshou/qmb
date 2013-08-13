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
#include "global.h"
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>

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
    if(result)
        saveOptions();

    QDialog::done(result);
}

/**
 * @brief Establece en las opciones los valores por defecto
 */
void View::OptionsDialog::setDefaultValues()
{
    _versionComboBox -> setCurrentIndex(0);
    _communityLineEdit -> setText(DEFAULT_COMMUNITY_NAME);
    _nonRepeatersSpinBox -> setValue(DEFAULT_NON_REPEATERS);
    _maxRepetitionsSpinBox -> setValue(DEFAULT_MAX_REPETITIONS);
    _remotePortSpinBox -> setValue(DEFAULT_REMOTE_PORT);
    _timeoutSpinBox -> setValue(DEFAULT_TIMEOUT);
    _retriesSpinBox -> setValue(DEFAULT_RETRIES);
}

/**
 * @brief Crea los widgets
 */
void View::OptionsDialog::createWidgets()
{
    _versionLabel = new QLabel(tr("&Version:"));
    _versionComboBox = new QComboBox;
    _versionComboBox -> addItem(tr("v1"));
    _versionComboBox -> addItem(tr("v2C"));
    //_versionComboBox -> addItem(tr("v3"));
    _versionLabel -> setBuddy(_versionComboBox);

    _communityLabel = new QLabel(tr("&Community:"));
    _communityLineEdit = new QLineEdit;
    _communityLabel -> setBuddy(_communityLineEdit);

    _nonRepeatersLabel = new QLabel(tr("&Non Repeaters:"));
    _nonRepeatersSpinBox = new QSpinBox;
    _nonRepeatersSpinBox -> setMinimum(0);
    _nonRepeatersLabel -> setBuddy(_nonRepeatersSpinBox);

    _maxRepetitionsLabel = new QLabel(tr("&Max Repetitions:"));
    _maxRepetitionsSpinBox = new QSpinBox;
    _maxRepetitionsSpinBox -> setMinimum(0);
    _maxRepetitionsLabel -> setBuddy(_maxRepetitionsSpinBox);

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

    QGridLayout *valuesByDefaultLayout = new QGridLayout;

    valuesByDefaultLayout -> addWidget(_versionLabel, 0, 0, 1, 1);
    valuesByDefaultLayout -> addWidget(_versionComboBox, 0, 1, 1, 1);
    valuesByDefaultLayout -> addWidget(_communityLabel, 1, 0, 1, 1);
    valuesByDefaultLayout -> addWidget(_communityLineEdit, 1, 1, 1, 3);
    valuesByDefaultLayout -> addWidget(_nonRepeatersLabel, 2, 0, 1, 1);
    valuesByDefaultLayout -> addWidget(_nonRepeatersSpinBox, 2, 1, 1, 1);
    valuesByDefaultLayout -> addWidget(_maxRepetitionsLabel, 2, 2, 1, 1);
    valuesByDefaultLayout -> addWidget(_maxRepetitionsSpinBox, 2, 3, 1, 1);

    QGroupBox *valuesByDefaultGroupBox = new QGroupBox(tr("Values by default"));

    valuesByDefaultGroupBox -> setLayout(valuesByDefaultLayout);

    QGridLayout *sessionLayout = new QGridLayout;

    sessionLayout -> addWidget(_remotePortLabel, 0, 0, 1, 1);
    sessionLayout -> addWidget(_remotePortSpinBox, 0, 1, 1, 1);
    sessionLayout -> addWidget(_timeoutLabel, 1, 0, 1, 1);
    sessionLayout -> addWidget(_timeoutSpinBox, 1, 1, 1, 1);
    sessionLayout -> addWidget(_retriesLabel, 2, 0, 1, 1);
    sessionLayout -> addWidget(_retriesSpinBox, 2, 1, 1, 1);

    QGroupBox *sessionGroupBox = new QGroupBox(tr("Session parameters"));

    sessionGroupBox -> setLayout(sessionLayout);

    QHBoxLayout *bottomLayout = new QHBoxLayout;

    bottomLayout -> addWidget(_defaultPushButton);
    bottomLayout -> addStretch();
    bottomLayout -> addWidget(_okPushButton);
    bottomLayout -> addWidget(_cancelPushButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout -> addWidget(valuesByDefaultGroupBox);
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

}

/**
 * @brief Guarda las opciones
 */
void View::OptionsDialog::saveOptions()
{

}
