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

#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QSpinBox;
class QPushButton;
QT_END_NAMESPACE

namespace View
{
    class OptionsDialog : public QDialog
    {
        Q_OBJECT
    public:
        OptionsDialog(QWidget *parent = 0);
        void done(int result);
    private slots:
        void setDefaultValues();
    private:
        void createWidgets();
        void createConnections();
        void loadOptions();
        bool saveOptions();

        QLabel *_remotePortLabel;
        QSpinBox *_remotePortSpinBox;
        QLabel *_timeoutLabel;
        QSpinBox *_timeoutSpinBox;
        QLabel *_retriesLabel;
        QSpinBox *_retriesSpinBox;
        QPushButton *_defaultPushButton;
        QPushButton *_okPushButton;
        QPushButton *_cancelPushButton;
    };
}

#endif // OPTIONSDIALOG_H
