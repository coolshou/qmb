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
 * @file optionsdialog.h
 * @brief Declaracion de clase OptionsDialog
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Agosto 2013
 */

#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

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
     * @brief Clase OptionsDialog que implementa un cuadro de dialogo para el establecimiento de opciones de configuracion
     */
    class OptionsDialog : public QDialog
    {
        Q_OBJECT
    public:
        /**
         * @brief Constructor de OptionsDialog
         * @param parent Widget padre
         */
        OptionsDialog(QWidget *parent = 0);

        /**
         * @brief Establece el resultado de Aceptado/Rechazado del cuadro de dialogo
         * @param result Resultado del cuadro de dialogo
         */
        void done(int result);
    private slots:

        /**
         * @brief Establece en las opciones los valores por defecto
         */
        void setDefaultValues();
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
         * @brief Carga las opciones en el cuadro de dialogo
         */
        void loadOptions();

        /**
         * @brief Guarda las opciones
         */
        void saveOptions();

        QLabel *_versionLabel;
        QComboBox *_versionComboBox;
        QLabel *_communityLabel;
        QLineEdit *_communityLineEdit;
        QLabel *_nonRepeatersLabel;
        QSpinBox *_nonRepeatersSpinBox;
        QLabel *_maxRepetitionsLabel;
        QSpinBox *_maxRepetitionsSpinBox;
        QLabel *_remotePortLabel;
        QSpinBox *_remotePortSpinBox;
        QLabel *_timeoutLabel;
        QSpinBox *_timeoutSpinBox;
        QLabel *_retriesLabel;
        QSpinBox *_retriesSpinBox;
        QPushButton *_defaultPushButton;
        QPushButton *_okPushButton;
        QPushButton *_cancelPushButton;
    };
}

#endif // OPTIONSDIALOG_H
