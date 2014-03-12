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
 * @file propertiesdialog.h
 * @brief Declaracion de clase PropertiesDialog
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Agosto 2013
 */

#ifndef PROPERTIESDIALOG_H
#define PROPERTIESDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QComboBox;
class QLineEdit;
class QSpinBox;
class QPushButton;
QT_END_NAMESPACE

namespace View
{
    /**
     * @brief Clase PropertiesDialog que implementa un cuadro de dialogo para introducir las propiedades de la sesion SNMP
     */
    class PropertiesDialog : public QDialog
    {
        Q_OBJECT
    public:
        /**
         * @brief Constructor de PropertiesDialog
         * @param community Nombre de comunidad SNMP version 1/2c
         * @param nonRepeaters Numero de Non Repeaters
         * @param maxRepetitions Numero de Max Repetitions
         * @param parent Widget padre
         */
        PropertiesDialog(const QString& community, unsigned short nonRepeaters, unsigned short maxRepetitions, QWidget *parent = 0);

        /**
         * @brief Establece el resultado de Aceptado/Rechazado del cuadro de dialogo
         * @param result Resultado del cuadro de dialogo
         */
        void done(int result);

        /**
         * @brief Obtiene el nombre de la comunidad SNMPv1/v2c
         * @return Nombre de la comunidad SNMPv1/v2c
         */
        const QString& community() const;

        /**
         * @brief Obtiene el numero de NON REPEATERS para operaciones SNMP GET BULK
         * @return  Numero de NON REPEATERS para operaciones SNMP GET BULK
         */
        unsigned short nonRepeaters() const;

        /**
         * @brief Obtiene el numero de MAX REPETITIONS para operaciones SNMP GET BULK
         * @return  Numero de MAX REPETITIONS para operaciones SNMP GET BULK
         */
        unsigned short maxRepetitions() const;
    private:
        /**
         * @brief Crea los widgets
         */
        void createWidgets();

        /**
         * @brief Establece las conexiones
         */
        void createConnections();

        /**
         * @brief Carga las propiedades de la sesion SNMP
         */
        void loadProperties();

        /**
         * @brief Guarda las propiedades de la sesion SNMP
         */
        void saveProperties();

        QLabel *_versionLabel;
        QComboBox *_versionComboBox;
        QLabel*_communityLabel;
        QLineEdit *_communityLineEdit;
        QLabel*_nonRepeatersLabel;
        QSpinBox *_nonRepeatersSpinBox;
        QLabel*_maxRepetitionsLabel;
        QSpinBox *_maxRepetitionsSpinBox;
        QPushButton *_okPushButton;
        QPushButton *_cancelPushButton;

        QString _community;
        unsigned short _nonRepeaters;
        unsigned short _maxRepetitions;
    };
}

#endif // PROPERTIESDIALOG_H
