/**
 *  This file is part of QMB.
 *
 *  Copyright (c) 2013-2014 Juan Jose Salazar Garcia jjslzgc@gmail.com
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

#include "mibtreeproxymodel.h"
#include <QtNetSNMP/qmibtree.h>
#include <QtNetSNMP/qsnmpobject.h>
#include <QtNetSNMP/qsnmpoid.h>

View::MIBTreeProxyModel::MIBTreeProxyModel(QObject *parent) : QSortFilterProxyModel(parent) {}

bool View::MIBTreeProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QtNetSNMP::QMIBTree *leftNode = static_cast<QtNetSNMP::QMIBTree *>(left.internalPointer());
    QtNetSNMP::QMIBTree *rightNode = static_cast<QtNetSNMP::QMIBTree *>(right.internalPointer());

    oid leftSubId = leftNode -> object() -> objID() -> numOID() -> last();
    oid rightSubId = rightNode -> object() -> objID() -> numOID() -> last();

    return leftSubId < rightSubId;
}
