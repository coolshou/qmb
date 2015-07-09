/**
 *  This file is part of QMB.
 *
 *  Copyright (c) 2013-2015 Juan Jose Salazar Garcia jjslzgc@gmail.com
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

#include "mibtreemodel.h"
#include <QtNetSNMP/qsnmpobject.h>

View::MIBTreeModel::MIBTreeModel(QObject *parent) : QAbstractItemModel(parent)
{
    _root = 0;
}

View::MIBTreeModel::~MIBTreeModel()
{
    if(_root)
        delete _root;
}

void View::MIBTreeModel::setRoot(QtNetSNMP::QMIBTree *root)
{
    beginResetModel();

    if(_root)
        delete _root;

    _root = root;

    endResetModel();
}

QModelIndex View::MIBTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!_root)
        return QModelIndex();

    QtNetSNMP::QMIBTree *parentNode = nodeFromIndex(parent);

    return createIndex(row, column, parentNode -> childs().at(row));
}

QModelIndex View::MIBTreeModel::parent(const QModelIndex &child) const
{
    QtNetSNMP::QMIBTree *node = nodeFromIndex(child);

    if(!node)
        return QModelIndex();

    QtNetSNMP::QMIBTree *parentNode = node -> parent();

    if(!parentNode)
        return QModelIndex();

    QtNetSNMP::QMIBTree *grandParentNode = parentNode -> parent();

    if(!grandParentNode)
        return QModelIndex();

    int row = grandParentNode -> childs().indexOf(parentNode);

    return createIndex(row, child.column(), parentNode);

}

int View::MIBTreeModel::rowCount(const QModelIndex &parent) const
{
    QtNetSNMP::QMIBTree *parentNode = nodeFromIndex(parent);

    if(!parentNode)
        return 0;

    return (int) parentNode -> childs().size();

}

int View::MIBTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 1;
}

QVariant View::MIBTreeModel::data(const QModelIndex &index, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    QtNetSNMP::QMIBTree *node = nodeFromIndex(index);

    if(!node)
        return QVariant();

    if(index.column() == 0)
        return node -> object() ? node -> object() -> name() : "";

    return QVariant();
}

QVariant View::MIBTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole && section == 0)
        return tr("Object");

    return QVariant();
}

QtNetSNMP::QMIBTree *View::MIBTreeModel::nodeFromIndex(const QModelIndex& index) const
{
    return index.isValid() ? static_cast<QtNetSNMP::QMIBTree *> (index.internalPointer()) : _root;
}
