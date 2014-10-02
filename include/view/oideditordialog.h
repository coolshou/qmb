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

#ifndef OIDEDITORDIALOG_H
#define OIDEDITORDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

/**namespace Model
{
    class SNMPOID;
}**/

#include <QtNetSNMP/qsnmpobject.h>

namespace View
{
    class OIDEditorDialog : public QDialog
    {
        Q_OBJECT
    public:
        OIDEditorDialog(QtNetSNMP::QSNMPObject *object, QWidget *parent = 0);
        void done(int result);
    private slots:
        void textChangedOnValueLineEdit(QString text);
    private:
        void createWidgets();
        void createConnections();
        void loadObject();
        void saveObject();

        QLabel *_nameLabel;
        QLabel*_nameValue;
        QLabel*_oidLabel;
        QLabel*_oidValue;
        QLabel *_typeLabel;
        QLabel *_typeValue;
        QLabel *_valueLabel;
        QLineEdit *_valueLineEdit;
        QPushButton *_okPushButton;
        QPushButton *_cancelPushButton;

        QtNetSNMP::QSNMPObject *_object;
    };
}

#endif // OIDEDITORDIALOG_H
