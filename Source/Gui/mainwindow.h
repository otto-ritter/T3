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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// STD & QT Includes
#include <QMainWindow>
#include <QClipboard>
#include <QDebug>
#include <QMap>
#include <QList>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopServices>

// Custom Includes
#include "Helper/globalDefines.h"
#include "Controller/controllserver.h"
#include "Gui/managingfrienddialog.h"
#include "Gui/settings.h"

namespace Ui {
    class MainWindow;
}

/**
     @brief This Class represents the view for T3.

     MainWindow inherits from QMainWindow and is the main view containing the friends list.
     Methods that were named on_xxxxxxxx_pressed or on_xxxxxxxx_triggered are autoconnected slots.

     @see ControllServer::instanceOf();

     @author Otto Ritter me@otto-ritter.de
     @version 0.6
     @date 14.01.2012
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /**
         @brief Constructor for the Gui.

         Sets the window's title and loads existing friends from model.
         Connects buttons and menu actions to slots.

         @param parent QWidget with the gui.
     */
    explicit MainWindow(QWidget *parent = 0);    

    /**
        @brief Destructor destroy the Gui.
     */
    ~MainWindow();

public slots:

    /**
         @brief Loads and reloads the friends list from the model.

         The ControllServer contains the model with the friends.
         It fetches the friends list and sets it in the QListWidget.

         @param preSelectedRow int the row that was selected befor reload list.
         @see ControllServer::getFriendList()
     */
    void reloadFriendList(int preSelectedRow = 0);

signals:

protected slots:

    /**
         @brief Called when the user selects a file for encryption or decryption.

         Shows a QFileDialog to the user to retrieve the file to process.
         After the file was selected check if the file suffix is ended by .enc or .key then activate decryprion button else the encryption button.

         The selected filepath will be transmitted to the ControllServer directly.
     */
    void on_toolButtonSelectFile_pressed();

    /**
         @brief When the addfriend button is being pressed, open the ManagingFriendDialog to add a new friend.
         If the entered information is correct, call the ControllServer to update the Model.

         @see ManagingFriendDialog::ManagingFriendDialog()
         @see ControllServer::addFriend()
     */
    void on_toolButtonAddFriend_pressed();

    /**
         @brief Open the ManagingFriendDialog to edit the selected friend in the friendlist.

         @see ManagingFriendDialog::ManagingFriendDialog()
         @see ManagingFriendDialog::editData()
         @see ControllServer::editFriend()
     */
    void on_toolButtonEditFriend_pressed();

    /**
         @brief Ask whether the user is sure that he would like to delete this friend.
         If the user confirms the deletion, delete the friend from the model.

         @see ControllServer::deleteFriend()
     */
    void on_toolButtonDeleteFriend_pressed();

    /**
         @brief Starts the decryption by calling doDeCrypt from ControllServer

         Use updateProcessBar to make the ProgressBar invisible and set the value to 0.

         @see MainWindow::updateProcessBar()
         @see ControllServer::doDeCrypt()
     */
    void on_toolButton_deCrypt_pressed();

    /**
         @brief Starts the encryption by calling doEnCrypt from ControllServer

         Use updateProcessBar to make the ProgressBar invisible and set the value to 0.

         @see ControllServer::doEnCrypt()
     */
    void on_toolButton_enCrypt_pressed();

    /**
        @brief Copy the public key to the clipboard to make it easy to share it with friends.
        Generate as public key file myPublic.key that can be sent to a friend.
     */
    void on_toolButtonCopyToClipbord_pressed();

    /**
        @brief File->Close was selected in the menu. Closes the application.
     */
    void on_action_Close_triggered();

    /**
        @brief Open the settings dialog if that action is triggered in the menu.
      */
    void on_actionOpenSettings_triggered();

    /**
         @brief Key-Help button was pressed.

         Shows a messagebox containg a help text to the user.
     */
    void on_action_About_triggered();

    /**
        @brief Open default browser and show the T3 webpage.

      */
    void on_actionHelp_Webpage_triggered();
    /**
         @brief Slot to change Progressbar

         If the value of progress is zero, hides the progressbar.

         @param newValue int range 0 to 100 if larger than 100 then set it to 100.
     */
    void updateProcessBar(int);

    /**
         @brief Slot to show Warnings to User

         Shows a messagebox containing the warning to the user.
     */
    void showWarnings(QString titel, QString message);

private:
/**
    @brief Contains the widgets from the ui-file.
  */
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
