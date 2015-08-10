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

#ifndef CONTROLLSERVER_H
#define CONTROLLSERVER_H

// QT Includes
#include <QObject>
#include <QWidget>
#include <QString>
#include <QFileDialog>
#include <QList>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QFileInfo>
#include <QProgressBar>
#include <QDebug>

// Custom Includes
#include <Helper/globalDefines.h>
#include <Model/personenlist.h>
#include <Model/rsakeypair.h>
#include <Functions/crypt.h>
#include <Functions/cryptblowfish.h>
#include <Functions/cryptaes.h>
#include <Functions/crypt3des.h>
#include <Functions/cryptrsa.h>
#include <Helper/mainexception.h>
#include <Helper/userexception.h>
#include <Helper/errorposition.h>
#include <Gui/mainwindow.h>
#include <Helper/filehandler.h>

/**
    @class ControllServer

    @brief Controller that connects model and gui.

    Designed as a singleton to make sure that only one controller is available.
    ControllServer catches MainExceptions and UserExceptions and sends signals to the view.

    @author Otto Ritter me@otto-ritter.de
    @version 0.8
    @date 07.09.2011
 */
class ControllServer : public QObject
{
Q_OBJECT

public:

    /**
        @brief static method to get the instance of this object.

        @return ControllServer & reference to the instance of ControllServer.
     */
   static ControllServer& instanceOf();

   /**
       @brief With this method it is possible to add a friend to the model.

       @param name QString name of the friend.
       @param key QByteArray contains the public key.
    */
   void addFriend(QString, QByteArray);

   /**
        @brief Change a public key from an existing friend.

        @param name QString name of the friend.
        @param key QByteArray contains the public key.
    */
   void editFriend(QString, QByteArray);

   /**
        @brief Delete a friend from model detected by name.

        @param name QString contain the name of the friend that will delete.
    */
   void deleteFriend(QString);

   /**
      @brief Encrypt the given file with selected encryption algorithm and the public key from friend.

      After all tests done then encrypt symmetrically the chosen file and then creates a key file.
      The symmetric key is RSA encrypted the public key from theselected friend and written in the key file.
      It will catch the MainException and the UserException exception and send it over Signal and Slot to the View.

      @param selectedFriend QListWidgetItem* contains the selecte friend to get her public key.

      @return boolean true if successful else false.
      @see Crypt::encrypt() call to encrypt the QByteArray.
      @see FileHandler::readAll() read the source file.
      @see FileHandler::write() write the encrypted file.

    */
   bool doEnCrypt(QListWidgetItem* selectedFriend);

   /**
      @brief Decrypt the file that was selected by the user.

      First, the key file is being and parsed to get some information about the encrypted file. Therefore, the method uses readKeyFile.
      If the file has been read successfully, the algorithm is chosen to decrypt and open the encrypted file.
      The content is passed to the method of the respective encryption class.
      If everything was successful, the decrypted file is stored at the same location where the file was encrypted.
      This method catches MainExceptions and transmits warnings over signals to view.

      @return boolen true if successful else false.
      @see Crypt::decrypt() is call to decrypt the file.
      @see FileHandler::readAll() read the given file.
      @see FileHandler::write() write the encrypted file.
    */
   bool doDeCrypt();

   /**
       @brief Export own public key to a key file.

       @see RSAKeyPair::exportPublicKey()
    */
   void exportPublicKey();

   /**
         @brief Delegates the syntax check to the keypair Object.

         @param key QByteArray the key that want to check.
         @param keyType int the type of the key 0 is public and 1 is private.

         @return boolean if the syntax is correct.
         @see KeyPair::checkKeySyntax() check the given key.
    */
   bool checkKeySyntax(QByteArray key, int keyType = 0);


   /**
         @brief Give the public key from selected friend as QByteArray back.

         @param name QString the name of the friend the public key was need.

         @return QByteArray contain the encoded public key.
    */
   QByteArray getPublicKeyByName(QString);

   /**
       @brief Return a list with names from friends that was saved in the model.

       @return QStringList list with the name of friends from model.
    */
   QStringList getFiendList();

   /**
        @brief Give own public key back.

        Read the the own public key from keypair model.

        @return QString contains own public.
    */
   QString getPublicKey();

   /**
       @brief set the application directory.

       @param path QString contain the application directory.
    */
   void setAppPath(QString);

   /**
       @brief get the application directory.

       @return QString application path.
    */
   QString getAppPath();

   /**
         @brief Setter for filepath.

         Set it direct in the FileHandler it is possible that the FileHandler can throw a MainException if the file is not exist or is not able to read.

         @param pathToFile QString contain the path to the file to process.
         @see FileHandler::setInputPath();
     */
   void setFilePathToProcess(QString pathToFile);

   /**
        @brief Get the path to the selected file.

        @return QString path to file.
     */
   QString getFilePathToProcess() { return m_fileHandler->getInputPath(); }

   /**
       @brief Setter for view to make it possible to connect ControllServer and crypt object with the view.

       @param view QWidget* the pointer to the view.

    */
   void setView(QWidget *view);

   /**
        @brief Return the View as a QWidget pointer.

        @return QWidget* the View.
     */
   QWidget* getView() { return m_View; }

   /**
        @brief Getter for selected symmetric algorithm.

        @return QString name of the selected algorithm.
     */
   QString getSymmtricAlgortihmus() { return m_cryptAlgo; }

signals:
   /**
        @brief Signal to view with title and message.
     */
  void sendWarning(QString title, QString message);

protected slots:
  /**
      @brief changes the symmetric algorithm, creates a new object and connects it with the progressbar in the view.
   */
  void selectSymmetricAlgorithmus(QString changedCryptAlgorithmus = "BlowFish");


private:
  /**
      @brief Constructor is private to make sure only itself can create an object.

      Preselect Blowfish as symmetric algorithm.
      Create instance of FileHandler and CryptBlowfish.
   */
   ControllServer();   // not instantiable
   ControllServer(const ControllServer&) : QObject() {}  // not copied
   /**
       @brief Destructor is private and destroys the filehandler and the crypt object.
    */
   ~ControllServer();

   /**
      @brief Create the keyfile for the encrypted file.

      This private method will be called from doEnCrypt after the encryption was successful.
      It creates MD5 hashes from the values and write it to the key file for a valid check.

      On errors it throws a UserException that must be catched.

      @param selectedFriend QString name of the selected friend to choose her public key.
      @throw UserException
    */
   void writeKeyFile(QString) throw (UserException);

   /**
      @brief Read the keyfile for dectyption.

      This private method was called from doDeCrypt before the dectyption starts.
      Checks whether the public-key encryption fits with its own private key, otherwise an exception will be thrown.
      When read, the hash values ​​compare whether they are still correct. If the values are invalid an exception will be thrown.

      @throws MainException, UserException.
    */
   void readKeyFile() throw (MainException, UserException);


   /**
        @brief Singleton.
     */
    static ControllServer m_instance;

    QWidget * m_View;
    /**
        @brief Model for friendlist.
        @see PersonenList
      */
    PersonenList m_Personen;

    /**
        @brief Model for keypair.
        @see RSAKeyPair
      */
    RSAKeyPair m_KeyPair;

    /**
        @brief The chosen algorithm.
      */
    QString m_cryptAlgo;

    /**
        @brief The application path.
      */
    QString m_appPath;

    /**
        @brief Object that is being used for encryption and decryption.
     */
    Crypt * m_cryptionObject;

    /**
        @brief Object that is being used to handle the files in the filesystem.
      */
    FileHandler * m_fileHandler;

};

#endif // CONTROLLSERVER_H
