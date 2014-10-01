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

#ifndef SNMPNODE_H
#define SNMPNODE_H
/**
#include "snmpoid.h"
#include <vector>

namespace Model
{
    class SNMPNode
    {
    public:
        SNMPNode(SNMPOID *object = 0, SNMPNode *parent = 0);
        ~SNMPNode();
        SNMPOID *object() const;
        void setObject(SNMPOID *object);
        SNMPNode *parent() const;
        void setParent(SNMPNode *parent);
        std::vector<SNMPNode *>& childs();
        bool isInternalNode() const;
    private:
        SNMPOID *_object;
        SNMPNode *_parent;
        std::vector<SNMPNode *> _childs;
    };
}
**/
#endif // SNMPNODE_H
