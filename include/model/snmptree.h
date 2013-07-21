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
 * @file snmptree.h
 * @brief Declaracion de clase SNMPTree
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Julio 2013
 */

#ifndef SNMPTREE_H
#define SNMPTREE_H

#include "snmpoid.h"
#include <vector>

namespace Model
{
    /**
     * @brief Clase SNMPTree que implementa el arbol de OIDs
     */
    class SNMPTree
    {
    public:
        /**
         * @brief Constructor de SNMPTree
         * @param object OID asociado al nodo del arbol
         */
        SNMPTree(SNMPOID *object);

        /**
         * @brief Obtiene el OID asociado al nodo del arbol
         * @return OID asociado al nodo del arbol
         */
        SNMPOID *object() const;

        /**
         * @brief Obtiene el nodo padre
         * @return Nodo padre
         */
        SNMPTree *parent() const;

        /**
         * @brief Establece el nodo padre
         * @param Nodo padre
         */
        void setParent(SNMPTree *parent);

        /**
         * @brief Obtiene la lista de nodos hijo
         * @return Lista de nodos hijo
         */
        std::vector<SNMPTree *>& childs();
    private:
        /**
         * @brief OID asociado al nodo del arbol
         */
        SNMPOID *_object;

        /**
         * @brief Nodo padre
         */
        SNMPTree *_parent;

        /**
         * @brief Lista de nodos hijo
         */
        std::vector<SNMPTree *> _childs;
    };
}

#endif // SNMPTREE_H
