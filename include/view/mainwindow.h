/**
 *  This file is part of QMB.
 *
 *  Copyright (c) 2013-2015 Juan Jose Salazar Garcia jjslzgc@gmail.com
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QLabel;
QT_END_NAMESPACE

namespace View
{
    class CentralWidget;

    class MainWindow : public QMainWindow
    {
        Q_OBJECT
    public:
        MainWindow();
        ~MainWindow();
    protected:
        void closeEvent(QCloseEvent *event);
    private slots:
        void options();
        void about();
        void changeStatus(const QString& status);
    private:
        void createWidgets();
        void createCentralWidget();
        void createActions();
        void createMenus();
        void createToolBar();
        void createStatusBar();
        void createConnections();

        QAction *_optionsAction;
        QAction *_exitAction;
        QAction *_aboutAction;
        QAction *_aboutQtAction;
        QMenu *_applicationMenu;
        QMenu *_helpMenu;
        CentralWidget *_centralWidget;
        QLabel *_statusLabel;
    };
}

#endif // MAINWINDOW_H
