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

#include "propertiesdialog.h"
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>

View::PropertiesDialog::PropertiesDialog(const QString &community, unsigned short nonRepeaters, unsigned short maxRepetitions, QWidget *parent)
    : QDialog(parent), _community(community), _nonRepeaters(nonRepeaters), _maxRepetitions(maxRepetitions)
{
    createWidgets();
    createConnections();
    setWindowTitle(tr("SNMP Session Properties"));
    setFixedSize(sizeHint());
    loadProperties();
}

void View::PropertiesDialog::done(int result)
{
    if(result)
        saveProperties();

    QDialog::done(result);
}

const QString& View::PropertiesDialog::community() const
{
    return _community;
}

unsigned short View::PropertiesDialog::nonRepeaters() const
{
    return _nonRepeaters;
}

unsigned short View::PropertiesDialog::maxRepetitions() const
{
    return _maxRepetitions;
}

void View::PropertiesDialog::createWidgets()
{
    _versionLabel = new QLabel(tr("&Version:"));
    _versionComboBox = new QComboBox;
    _versionLabel -> setBuddy(_versionComboBox);
    _versionComboBox -> addItem(tr("v1/v2C"));

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

    _okPushButton = new QPushButton(tr("Ok"));
    _okPushButton -> setDefault(true);

    _cancelPushButton = new QPushButton(tr("Cancel"));

    QGridLayout *accessLayout = new QGridLayout;

    accessLayout -> addWidget(_versionLabel, 0, 0, 1, 1);
    accessLayout -> addWidget(_versionComboBox, 0, 1, 1, 1);
    accessLayout -> addWidget(_communityLabel, 1, 0, 1, 1);
    accessLayout -> addWidget(_communityLineEdit, 1, 1, 1, 2);

    QGroupBox *accessGroupBox = new QGroupBox(tr("&Access"));

    accessGroupBox -> setLayout(accessLayout);

    QGridLayout *getBulkLayout = new QGridLayout;

    getBulkLayout -> addWidget(_nonRepeatersLabel, 0, 0, 1, 1);
    getBulkLayout -> addWidget(_nonRepeatersSpinBox, 0, 1, 1, 1);
    getBulkLayout -> addWidget(_maxRepetitionsLabel, 1, 0, 1, 1);
    getBulkLayout -> addWidget(_maxRepetitionsSpinBox, 1, 1, 1, 1);

    QGroupBox *getBulkGroupBox = new QGroupBox(tr("&Get Bulk Parameters"));

    getBulkGroupBox -> setLayout(getBulkLayout);

    QHBoxLayout *bottomLayout = new QHBoxLayout;

    bottomLayout -> addStretch();
    bottomLayout -> addWidget(_okPushButton);
    bottomLayout -> addWidget(_cancelPushButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout -> addWidget(accessGroupBox);
    mainLayout -> addWidget(getBulkGroupBox);
    mainLayout -> addLayout(bottomLayout);

    setLayout(mainLayout);
}

void View::PropertiesDialog::createConnections()
{
    connect(_okPushButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_cancelPushButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void View::PropertiesDialog::loadProperties()
{
    _communityLineEdit -> setText(_community);
    _nonRepeatersSpinBox -> setValue(_nonRepeaters);
    _maxRepetitionsSpinBox -> setValue(_maxRepetitions);
}

void View::PropertiesDialog::saveProperties()
{
    _community = _communityLineEdit -> text();
    _nonRepeaters = (unsigned short) _nonRepeatersSpinBox -> value();
    _maxRepetitions = (unsigned short) _maxRepetitionsSpinBox -> value();
}
