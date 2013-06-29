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

#ifndef SNMPEXCEPTION_H
#define SNMPEXCEPTION_H

namespace Model
{
    class SNMPException
    {
    public:
        SNMPException(const char *message = "SNMP Exception") : _message(message) {}
        const char *message() const
        {
            return _message;
        }
    protected:
        const char *_message;
    };
}

#endif // SNMPEXCEPTION_H
