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

#ifndef MIBTREEPROXYMODEL_H
#define MIBTREEPROXYMODEL_H

#include <QSortFilterProxyModel>

namespace View
{
    class MIBTreeProxyModel : public QSortFilterProxyModel
    {
        Q_OBJECT
    public:
        MIBTreeProxyModel(QObject *parent = 0);
    protected:
        bool lessThan(const QModelIndex &left, const QModelIndex &right) const;
    };
}

#endif // MIBTREEPROXYMODEL_H
