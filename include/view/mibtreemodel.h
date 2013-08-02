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
 * @file mibtreemodel.h
 * @brief Declaracion de clase MIBTreeModel
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Agosto 2013
 */

#ifndef MIBTREEMODEL_H
#define MIBTREEMODEL_H

#include <QAbstractItemModel>

namespace Model
{
    class SNMPNode;
}

namespace View
{
    /**
     * @brief Clase MIBTreeModel que implementa el modelo jerarquico usado por QTreeView y que representa el arbol de la MIB
     */
    class MIBTreeModel : public QAbstractItemModel
    {
    public:
        /**
         * @brief Constructor de MIBTreeModel
         * @param parent Objeto padre
         */
        MIBTreeModel(QObject *parent = 0);

        /**
         * @brief Destructor de MIBTreeModel
         */
        ~MIBTreeModel();

        /**
         * @brief Establece el nodo raiz del arbol de la MIB
         * @param root nodo raiz del arbol de la MIB
         */
        void setRoot(Model::SNMPNode *root);

        QModelIndex index(int row, int column, const QModelIndex &parent) const;
        QModelIndex parent(const QModelIndex &child) const;
        int rowCount(const QModelIndex &parent) const;
        int columnCount(const QModelIndex &parent) const;
        QVariant data(const QModelIndex &index, int role) const;
        QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    private:
        Model::SNMPNode *nodeFromIndex(const QModelIndex& index) const;

        Model::SNMPNode *_root;
    };
}

#endif // MIBTREEMODEL_H
