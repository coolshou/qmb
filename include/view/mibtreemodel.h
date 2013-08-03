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

        /**
         * @brief Redefinicion de metodo QAbstractItemModel::index(..) usado por la vista y el modelo para crear nuevos indices
         * @param row Fila
         * @param column Columna
         * @param parent Indice padre
         * @return Nuevo indice
         */
        QModelIndex index(int row, int column, const QModelIndex &parent) const;

        /**
         * @brief Redefinicion de metodo QAbstractItemModel::parent(..) usado por la vista y el modelo para la obtencion del indice padre a partir de un hijo
         * @param child Indice hijo
         * @return Indice padre
         */
        QModelIndex parent(const QModelIndex &child) const;

        /**
         * @brief Obtiene el numero de filas de un item (numero de hijos)
         * @param parent Indice padre
         * @return Numero de filas
         */
        int rowCount(const QModelIndex &parent) const;

        /**
         * @brief Obtiene el numero de columnas de un item
         * @param parent Indice padre
         * @return Numero de columnas
         */
        int columnCount(const QModelIndex &parent) const;

        /**
         * @brief Obtiene el dato del item para la vista
         * @param index Indice
         * @param role Rol
         * @return Dato del item
         */
        QVariant data(const QModelIndex &index, int role) const;

        /**
         * @brief Obtiene la etiquetas de las cabeceras vertical y horizontal para la vista
         * @param section Fila/Columna (segun orientacion)
         * @param orientation Orientacion
         * @param role Rol
         * @return Etiqueta de la cabecera
         */
        QVariant headerData(int section, Qt::Orientation orientation, int role) const;     
    private:
        /**
         * @brief Obtiene el nodo del arbol asociado a un indice
         * @param index Indice
         * @return  nodo del arbol asociado
         */
        Model::SNMPNode *nodeFromIndex(const QModelIndex& index) const;

        Model::SNMPNode *_root;
    };
}

#endif // MIBTREEMODEL_H
