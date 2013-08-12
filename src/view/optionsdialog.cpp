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

}

/**
 * @brief Crea los widgets
 */
void View::OptionsDialog::createWidgets()
{

}

/**
 * @brief Establece las conexiones
 */
void View::OptionsDialog::createConnections()
{

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
