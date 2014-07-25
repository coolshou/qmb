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

#ifndef SNMPDATA_H
#define SNMPDATA_H

#include <string>
#include "types.h"

namespace Model
{
    class SNMPData
    {
    public:
        SNMPData(SNMPDataType type = SNMPDataUnknown, void *value = 0, size_t length = 0);
        SNMPData(const SNMPData& snmpData);
        ~SNMPData();
        SNMPData& operator=(const SNMPData& snmpData);
        void *value() const;
        void setValue(void *value);
        void setValue(const SNMPValue &value);
        size_t length() const;
        void setLength(size_t length);
        SNMPDataType type() const;
        void setType(SNMPDataType type);
        std::string toString() const;
    private:
        void initValue(void *value);
        void deleteValue();

        SNMPDataType _type;
        SNMPValue _value;
        size_t _length;
    };
}

#endif // SNMPDATA_H
