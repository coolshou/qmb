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
 * @file snmpnode.h
 * @brief Declaracion de clase SNMPNode
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Julio 2013
 */

#ifndef SNMPNODE_H
#define SNMPNODE_H

#include "snmpoid.h"
#include <vector>

namespace Model
{
    /**
     * @brief Clase SNMPNode que implementa un nodo del arbol de la MIB
     */
    class SNMPNode
    {
    public:
        /**
         * @brief Constructor de SNMPNode
         * @param object OID asociado al nodo del arbol
         * @param parent Nodo padre
         */
        SNMPNode(SNMPOID *object = 0, SNMPNode *parent = 0);

        /**
         * @brief Destructor de SNMPNode
         */
        ~SNMPNode();

        /**
         * @brief Obtiene el OID asociado al nodo del arbol
         * @return OID asociado al nodo del arbol
         */
        SNMPOID *object() const;

        /**
         * @brief Establece el OID asociado al nodo del arbol
         * @param object OID asociado al nodo del arbol
         */
        void setObject(SNMPOID *object);

        /**
         * @brief Obtiene el nodo padre
         * @return Nodo padre
         */
        SNMPNode *parent() const;

        /**
         * @brief Establece el nodo padre
         * @param Nodo padre
         */
        void setParent(SNMPNode *parent);

        /**
         * @brief Obtiene la lista de nodos hijo
         * @return Lista de nodos hijo
         */
        std::vector<SNMPNode *>& childs();

        /**
         * @brief Determina si el nodo actual es un nodo interno del arbol
         * @return true si es un nodo interno false en caso contrario
         */
        bool isInternalNode() const;
    private:
        /**
         * @brief OID asociado al nodo del arbol
         */
        SNMPOID *_object;

        /**
         * @brief Nodo padre
         */
        SNMPNode *_parent;

        /**
         * @brief Lista de nodos hijo
         */
        std::vector<SNMPNode *> _childs;
    };
}

#endif // SNMPNODE_H
