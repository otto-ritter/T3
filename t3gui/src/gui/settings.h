/*
    Application to encrypt and decrypt files to share with friends.
    Copyright (C) 2012 Otto Ritter

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <Controller/controllserver.h>

namespace Ui {
    class Settings;
}
/**
   @brief This is the settings dialog to change algorithm and see own public key.

   Show the public key in a readonly PlanTaxtArea. In the Settings dialog it's possible to change the symmetric algorithmus with a Combobox.
   The combobox send a signal to ControllServer to change the algorihmus.

   @author Otto Ritter me@otto-ritter.de
   @version 0.4
   @date 06.09.2011
 */
class Settings : public QDialog
{
    Q_OBJECT

public:
    /**
        @brief Constructor for the Settings dialog.

        Get the public key and the selected symmetric algorithm from ControllServer and show it.
        Connect the combobox to change the symmetric algorithm with the ControllServer.
      */
    explicit Settings(QWidget *parent = 0);

    /**
        @brief Destructor to destroy the ui object.
      */
    ~Settings();
protected slots:

    /**
        @brief Closes the windows and sends the accept signal.
      */
    void on_closeButton_clicked();

private:
    /**
        Pointer to the UI::Settings from settings.ui
     */
    Ui::Settings *ui;
};

#endif // SETTINGS_H
