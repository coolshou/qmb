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
 * @file mibtreeproxymodel.h
 * @brief Declaracion de clase MIBTreeProxyModel
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Agosto 2013
 */

#ifndef MIBTREEPROXYMODEL_H
#define MIBTREEPROXYMODEL_H

#include <QSortFilterProxyModel>

namespace View
{
    /**
     * @brief Clase MIBTreeProxyModel que implementa un modelo proxy para la ordenacion/filtrado de un modelo origen
     */
    class MIBTreeProxyModel : public QSortFilterProxyModel
    {
        Q_OBJECT
    public:
        /**
         * @brief Constructor de MIBTreeProxyModel
         * @param parent Objeto padre
         */
        MIBTreeProxyModel(QObject *parent = 0);
    protected:
        /**
         * @brief Determina si un item referido por su indice es o no es mayor que otro item
         * @param left Indice del primer item
         * @param right Indice del segundo item
         * @return True si left < right y false en caso contrario
         */
        bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
    };
}

#endif // MIBTREEPROXYMODEL_H
