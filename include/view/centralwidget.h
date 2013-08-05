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
 * @file centralwidget.h
 * @brief Declaracion de clase CentralWidget
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Julio 2013
 */

#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QSpinBox;
class QComboBox;
class QPushButton;
class QTreeView;
class QTextEdit;
QT_END_NAMESPACE

namespace View
{
    class MIBTreeModel;
    class MIBTreeProxyModel;

    /**
     * @brief Clase CentralWidget que implementa el widget central de la ventana principal
     */
    class CentralWidget : public QWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief Constructor de CentralWidget
         * @param parent Widget padre
         */
        CentralWidget(QWidget *parent = 0);

        /**
         * @brief Destructor de CentralWidget
         */
        ~CentralWidget();

    signals:
        /**
         * @brief Señal de notificacion de un cambio de estado
         * @param status Mensaje de estado
         */
        void statusChanged(const QString& status);

    private slots:
        /**
         * @brief Invoca operacion SNMP GET
         */
        void invokeGet();

        /**
         * @brief Invoca operacion SNMP GET NEXT
         */
        void invokeGetNext();

        /**
         * @brief Invoca operacion SNMP GET BULK
         */
        void invokeGetBulk();

        /**
         * @brief Invoca operacion SNMP SET
         */
        void invokeSet();

        /**
         * @brief Activa/Desactiva botones de operacion ante cambios en los otros widgets
         */
        void readyToInvoke();
    private:
        /**
         * @brief Crea los widgets
         */
        void createWidgets();

        /**
         * @brief Establece las conexiones
         */
        void createConnections();

        /**
         * @brief Carga el arbol MIB en el modelo MIBTreeModel
         */
        void loadMIBTree();

        QLabel *_agentLabel;
        QLineEdit *_agentLineEdit;
        QLabel *_portLabel;
        QSpinBox *_portSpinBox;
        QLabel *_versionLabel;
        QComboBox *_versionComboBox;
        QPushButton *_propertiesButton;
        QTreeView *_mibTreeView;
        MIBTreeModel *_mibTreeModel;
        MIBTreeProxyModel *_mibTreeProxyModel;
        QPushButton *_getPushButton;
        QPushButton *_getNextPushButton;
        QPushButton *_getBulkPushButton;
        QPushButton *_setPushButton;
        QTextEdit *_resultTextEdit;
    };
}

#endif // CENTRALWIDGET_H
