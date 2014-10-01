/**
 *  This file is part of QMB.
 *
 *  Copyright (c) 2013 2014 Juan Jose Salazar Garcia jjslzgc@gmail.com
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

#ifndef MIBTREEMODEL_H
#define MIBTREEMODEL_H

#include <QAbstractItemModel>

/**namespace Model
{
    class SNMPNode;
}*/

#include <QtNetSNMP/qmibtree.h>

namespace View
{
    class MIBTreeModel : public QAbstractItemModel
    {
    public:
        MIBTreeModel(QObject *parent = 0);
        ~MIBTreeModel();
        void setRoot(QtNetSNMP::QMIBTree *root);
        QModelIndex index(int row, int column, const QModelIndex &parent) const;
        QModelIndex parent(const QModelIndex &child) const;
        int rowCount(const QModelIndex &parent) const;
        int columnCount(const QModelIndex &parent) const;
        QVariant data(const QModelIndex &index, int role) const;
        QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    private:
        QtNetSNMP::QMIBTree *nodeFromIndex(const QModelIndex& index) const;

        //Model::SNMPNode *_root;
        QtNetSNMP::QMIBTree *_root;
    };
}

#endif // MIBTREEMODEL_H
