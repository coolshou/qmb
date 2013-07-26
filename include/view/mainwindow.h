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
 * @file mainwindow.h
 * @brief Declaracion de clase MainWindow
 * @author Juan Jose Salazar Garcia, jjslzgc@gmail.com
 * @version 0.1.0
 * @date Julio 2013
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

namespace View
{
    class CentralWidget;

    /**
     * @brief Clase MainWindow
     */
    class MainWindow : public QMainWindow
    {
        Q_OBJECT
    public:
        /**
         * @brief Constructor de MainWindow
         */
        MainWindow();

        /**
         * @brief Destructor de MainWindow
         */
        ~MainWindow();

    protected:
        /**
         * @brief Manejador de eventos de cierre de la ventana principal
         * @param event Evento de cierre
         */
        void closeEvent(QCloseEvent *event);

    private slots:
        /**
         * @brief Ranura Acerca de ..
         */
        void about();

    private:
        /**
         * @brief Crea los widgets
         */
        void createWidgets();

        /**
         * @brief Crea y establece el widget central
         */
        void createCentralWidget();

        /**
         * @brief Crea las acciones del menu y barra de herramientas
         */
        void createActions();

        /**
         * @brief Crea los menus
         */
        void createMenus();

        /**
         * @brief Crea las barras de herramientas
         */
        void createToolBar();

        /**
         * @brief Crea la barra de estado
         */
        void createStatusBar();

        /**
         * @brief Establece las conexiones
         */
        void createConnections();

        QAction *_exitAction;          /**< Accion Salir */
        QAction *_aboutAction;         /**< Accion Acerca de */
        QAction *_aboutQtAction;       /**< Accion Acerca de Qt */
        QMenu *_applicationMenu;       /**< Menu Aplication */
        QMenu *_helpMenu;              /**< Menu Ayuda */
        CentralWidget *_centralWidget;
    };
}

#endif // MAINWINDOW_H
