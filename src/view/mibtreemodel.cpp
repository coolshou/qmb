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
 * @file mibtreemodel.cpp
 * @brief Implementacion de metodos de la clase MIBTreeModel
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Agosto 2013
 */

#include "mibtreemodel.h"
#include "snmpnode.h"

/**
 * @brief Constructor de MIBTreeModel
 * @param parent Objeto padre
 */
View::MIBTreeModel::MIBTreeModel(QObject *parent) : QAbstractItemModel(parent)
{
    _root = 0;
}

/**
 * @brief Destructor de MIBTreeModel
 */
View::MIBTreeModel::~MIBTreeModel()
{
    if(_root)
        delete _root;
}

/**
 * @brief Establece el nodo raiz del arbol de la MIB
 * @param root nodo raiz del arbol de la MIB
 */
void View::MIBTreeModel::setRoot(Model::SNMPNode *root)
{
    if(_root)
        delete _root;

    _root = root;

    reset();
}

QModelIndex View::MIBTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    return QModelIndex();
}

QModelIndex View::MIBTreeModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

int View::MIBTreeModel::rowCount(const QModelIndex &parent) const
{
    return 0;
}

int View::MIBTreeModel::columnCount(const QModelIndex &parent) const
{
    return 0;
}

QVariant View::MIBTreeModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

QVariant View::MIBTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

Model::SNMPNode *View::MIBTreeModel::nodeFromIndex(const QModelIndex& index) const
{
    return 0;
}
