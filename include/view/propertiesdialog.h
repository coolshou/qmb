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

#ifndef PROPERTIESDIALOG_H
#define PROPERTIESDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QComboBox;
class QLineEdit;
class QSpinBox;
class QPushButton;
QT_END_NAMESPACE

namespace View
{
    class PropertiesDialog : public QDialog
    {
        Q_OBJECT
    public:
        PropertiesDialog(const QString& community, unsigned short nonRepeaters, unsigned short maxRepetitions, QWidget *parent = 0);
        void done(int result);
        const QString& community() const;
        unsigned short nonRepeaters() const;
        unsigned short maxRepetitions() const;
    private:
        void createWidgets();
        void createConnections();
        void loadProperties();
        void saveProperties();

        QLabel *_versionLabel;
        QComboBox *_versionComboBox;
        QLabel*_communityLabel;
        QLineEdit *_communityLineEdit;
        QLabel*_nonRepeatersLabel;
        QSpinBox *_nonRepeatersSpinBox;
        QLabel*_maxRepetitionsLabel;
        QSpinBox *_maxRepetitionsSpinBox;
        QPushButton *_okPushButton;
        QPushButton *_cancelPushButton;

        QString _community;
        unsigned short _nonRepeaters;
        unsigned short _maxRepetitions;
    };
}

#endif // PROPERTIESDIALOG_H
