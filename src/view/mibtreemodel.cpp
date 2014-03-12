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

/**
 * @brief Redefinicion de metodo QAbstractItemModel::index(..) usado por la vista y el modelo para crear nuevos indices
 * @param row Fila
 * @param column Columna
 * @param parent Indice padre
 * @return Nuevo indice
 */
QModelIndex View::MIBTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!_root) // Nodo raiz no establecido
        return QModelIndex(); // Devuelve indice invalido

    Model::SNMPNode *parentNode = nodeFromIndex(parent);

    // Creacion de indice
    return createIndex(row, column, parentNode -> childs().at(row));
}

/**
 * @brief Redefinicion de metodo QAbstractItemModel::parent(..) usado por la vista y el modelo para la obtencion del indice padre a partir de un hijo
 * @param child Indice hijo
 * @return Indice padre
 */
QModelIndex View::MIBTreeModel::parent(const QModelIndex &child) const
{
    Model::SNMPNode *node = nodeFromIndex(child);

    if(!node)
        return QModelIndex();

    Model::SNMPNode *parentNode = node -> parent();

    if(!parentNode)
        return QModelIndex();

    Model::SNMPNode *grandParentNode = parentNode -> parent();

    if(!grandParentNode)
        return QModelIndex();

    int row = std::find(grandParentNode -> childs().begin(), grandParentNode -> childs().end(), parentNode) - grandParentNode -> childs().begin();

    return createIndex(row, child.column(), parentNode);

}

/**
 * @brief Obtiene el numero de filas de un item (numero de hijos)
 * @param parent Indice padre
 * @return Numero de filas
 */
int View::MIBTreeModel::rowCount(const QModelIndex &parent) const
{
    Model::SNMPNode *parentNode = nodeFromIndex(parent);

    if(!parentNode)
        return 0;

    return (int) parentNode -> childs().size();

}

/**
 * @brief Obtiene el numero de columnas de un item
 * @param parent Indice padre
 * @return Numero de columnas
 */
int View::MIBTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 1;
}

/**
 * @brief Obtiene el dato del item para la vista
 * @param index Indice
 * @param role Rol
 * @return Dato del item
 */
QVariant View::MIBTreeModel::data(const QModelIndex &index, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    Model::SNMPNode *node = nodeFromIndex(index);

    if(!node)
        return QVariant();

    if(index.column() == 0)
        return node -> object() ? node -> object() -> name().c_str() : "";

    return QVariant();
}

/**
 * @brief Obtiene la etiquetas de las cabeceras vertical y horizontal para la vista
 * @param section Fila/Columna (segun orientacion)
 * @param orientation Orientacion
 * @param role Rol
 * @return Etiqueta de la cabecera
 */
QVariant View::MIBTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole && section == 0)
        return tr("Object");

    return QVariant();
}

/**
 * @brief Obtiene el nodo del arbol asociado a un item (indice)
 * @param index Indice del item
 * @return  nodo del arbol asociado
 */
Model::SNMPNode *View::MIBTreeModel::nodeFromIndex(const QModelIndex& index) const
{
    // El nodo raiz del arbol usa un indice invalido
    return index.isValid() ? static_cast<Model::SNMPNode *> (index.internalPointer()) : _root;
}
