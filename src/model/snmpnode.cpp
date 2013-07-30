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
 * @file snmpnode.cpp
 * @brief Implementacion de metodos de la clase SNMPNode
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Julio 2013
 */

#include "snmpnode.h"

/**
 * @brief Constructor de SNMPNode
 * @param object OID asociado al nodo del arbol
 */
Model::SNMPNode::SNMPNode(SNMPOID *object) : _object(object)
{
    _parent = 0;
}

/**
 * @brief Destructor de SNMPNode
 */
Model::SNMPNode::~SNMPNode()
{
    delete _object;

    for(std::vector<SNMPNode *>::iterator vi = _childs.begin(); vi != _childs.end(); vi++)
        delete *vi;
}

/**
 * @brief Obtiene el OID asociado al nodo del arbol
 * @return OID asociado al nodo del arbol
 */
Model::SNMPOID *Model::SNMPNode::object() const
{
    return _object;
}

/**
 * @brief Obtiene el nodo padre
 * @return Nodo padre
 */
Model::SNMPNode *Model::SNMPNode::parent() const
{
    return _parent;
}

/**
 * @brief Establece el nodo padre
 * @param Nodo padre
 */
void Model::SNMPNode::setParent(SNMPNode *parent)
{
    _parent = parent;
}

/**
 * @brief Obtiene la lista de nodos hijo
 * @return Lista de nodos hijo
 */
std::vector<Model::SNMPNode *>& Model::SNMPNode::childs()
{
    return _childs;
}
