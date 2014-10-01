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
/**
#include "snmpnode.h"

Model::SNMPNode::SNMPNode(SNMPOID *object, SNMPNode *parent) : _object(object), _parent(parent) {}

Model::SNMPNode::~SNMPNode()
{
    delete _object;

    for(std::vector<SNMPNode *>::iterator vi = _childs.begin(); vi != _childs.end(); vi++)
        delete *vi;
}

Model::SNMPOID *Model::SNMPNode::object() const
{
    return _object;
}

void Model::SNMPNode::setObject(SNMPOID *object)
{
    _object = object;
}

Model::SNMPNode *Model::SNMPNode::parent() const
{
    return _parent;
}

void Model::SNMPNode::setParent(SNMPNode *parent)
{
    _parent = parent;
}

std::vector<Model::SNMPNode *>& Model::SNMPNode::childs()
{
    return _childs;
}

bool Model::SNMPNode::isInternalNode() const
{
    return !_childs.empty();
}
**/
