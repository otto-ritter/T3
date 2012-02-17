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
#ifndef MANAGINGFRIENDDIALOG_H
#define MANAGINGFRIENDDIALOG_H

// STD & QT Includes
#include <QDialog>
#include <QString>
#include <QByteArray>
#include <QMessageBox>

// Custom Includes
#include <Controller/controllserver.h>
#include "Helper/globalDefines.h"

namespace Ui {
    class ManagingFriendDialog;
}

/**
     @brief This dialog is being used to manage friends.

     Show this dialog for add or edit of a person in the friends list.

     @author Otto Ritter me@otto-ritter.de
     @version 0.5
     @date 06.11.2011
 */
class ManagingFriendDialog : public QDialog
{
    Q_OBJECT

public:

    /**
        @brief Constructor.

        @param parent QWidget the called QWidget.
     */
    explicit ManagingFriendDialog(QWidget *parent = 0);

    /**
        @brief Destructor.
     */
    ~ManagingFriendDialog();

    /**
         @brief Processed when the user edits a person.

         This method will be called when the user changes a person from the friends list.
         It reads data from the list model and sets it to this dialog.

         @param name QString name from person.
         @param rsaKey QByteArray the public key.
     */
    void editData(QString, QByteArray);

    /**
         @brief Returns the name of the person stored in this dialog.

         @return QString
     */
    QString getName();

    /**
         @brief Returns the key that is stored in this dialog.

         @return QByteArray public key.
     */
    QByteArray getKey();

    /**
         @brief Returns true if data was edited.

         @return bool true if changes were made, otherwise false.
     */
    bool isEdited();

protected slots:

    /**
         @brief This method will be called if the user clicks the save button.

         If not both fieds are filled it open QMessageBox.
         If both fields are filled than save the data in the internal variables.

         The entered RSAKey will be checked before saving.
     */
    void on_saveButton_clicked();

    /**
        @brief Open a file and read the key in the file if the syntax are correct put the key in the Textarea.

    */
    void on_readKeyButton_clicked();

private:
    /**
        @brief Contain the Objects from the ui-File.
      */
    Ui::ManagingFriendDialog *ui;

    /**
        @brief Flag if the data was changed.
      */
    bool isEdit;

    /**
        @brief Contains the name of the person.
      */
    QString m_Name;

    /**
        @brief Contains the public-key from person.
      */
    QByteArray m_Key;
};

#endif // MANAGINGFRIENDDIALOG_H
