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
 * @file oideditordialog.h
 * @brief Declaracion de clase OIDEditorDialog
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Agosto 2013
 */

#ifndef OIDEDITORDIALOG_H
#define OIDEDITORDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

namespace Model
{
    class SNMPOID;
}

namespace View
{
    /**
     * @brief Clase OIDEditorDialog que implementa un cuadro de dialogo para introducir el valor del OID
     */
    class OIDEditorDialog : public QDialog
    {
        Q_OBJECT
    public:
        /**
         * @brief Constructor de OIDEditorDialog
         * @param object OID al que asignar el valor
         * @param parent Widget padre
         */
        OIDEditorDialog(Model::SNMPOID *object, QWidget *parent = 0);

        /**
         * @brief Establece el resultado de Aceptado/Rechazado del cuadro de dialogo
         * @param result Resultado del cuadro de dialogo
         */
        void done(int result);

    private slots:
        /**
         * @brief Ranura en habilita/inhabilita el boton ok
         * @param text Texto en QLineEdit
         */
        void textChangedOnValueLineEdit(QString text);

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
         * @brief Carga el OID en el cuadro de dialogo
         */
        void loadObject();

        /**
         * @brief Guarda el valor introducido en el OID
         */
        void saveObject();

        QLabel *_nameLabel;
        QLabel*_nameValue;
        QLabel*_oidLabel;
        QLabel*_oidValue;
        QLabel *_typeLabel;
        QLabel *_typeValue;
        QLabel *_valueLabel;
        QLineEdit *_valueLineEdit;
        QPushButton *_okPushButton;
        QPushButton *_cancelPushButton;

        Model::SNMPOID *_object;
    };
}

#endif // OIDEDITORDIALOG_H
