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
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef RSAKEYPAIR_H
#define RSAKEYPAIR_H

#define KEYPAIR_FILENAME "rsaKeyPair.key"
#define PUBKEY_FILENAME "myPublic.key"

#include <QApplication>
#include <QDebug>
#include <QByteArray>
#include <QString>
#include <QFile>
#include <QtXml>
#include <QCryptographicHash>
#include <QTextStream>
#include <QDir>

// Custom Includes
#include "Helper/globalDefines.h"
#include <Helper/errorlogger.h>
#include "Helper/errorposition.h"
#include "Helper/mainexception.h"
#include <Functions/cryptrsa.h>
#include <openssl/bn.h>
#include <openssl/rsa.h>

/**
    @brief Model for the RSA-Keypair.

    It store data with Keypair in a XML-Formated file. If the keypair was generated then it will be saved on application close.
    If an existing keypair was found so import the kaypair on application start.

    @author Otto Ritter me@otto-ritter.de
    @version 0.4
    @date 06.09.2011
 */
class RSAKeyPair
{
public:
    /**
        @brief Constructor.
     */
    RSAKeyPair();

    /**
        @brief Destructor.

        If the keypair was generated successfully it will save the keys before closing.
     */
    ~RSAKeyPair();

    /**
        @brief Returns the public key.

        @return QByteArray key in internal key format.
     */
    QByteArray getPublicKey();

    /**
        @brief Return the private key.

        @return QByteArray key in internal key format.
     */
    QByteArray getPrivateKey();

    /**
        @brief This will reset the existing keypair.

        @throw MainException thrown if can't generate a new key.
     */
    void reset() throw (MainException);

    /**
        @brief Set sthe application directory.

        After the application path is set, this will call the load method to load an existing keypair.

        @param path QString contains the application dir.
     */
    void setAppPath(QString);

    /**
         @brief Exports the stored public key as a key file to make it easier to share it.

         The public key file is being placed where the application is started.
     */
    void exportPublicKey();

    /**
         @brief Checks the given key if the intern store syntax is correct.
                  Decodes the key and check the syntax.
         @param key QByteArray with the base64 encoded key.
         @param keyType int 0 = public, 1 = private
         @return bool true if syntax is correct, otherwise false.
     */
    bool checkKeySyntax(QByteArray key, int keyType);

private:

    /**
        @brief This method will load the existing keys.

        @return bool true if is possible to load the keys, otherwise returns false.
     */
    bool load();

    /**
        @brief Saves the keys in XML-Format.

        It uses ErrorLogger to write errors to the logfile.
     */
    void save();

    /**
        @brief Generates a keypair und saves it to file.

        This private method generates the keys with OpenSSL in an RSA struct and converts it to an internal storage format.

        @throw MainException is unable to genarate keypair.
     */
    void generate() throw (MainException);

/**
    @brief Contain application path.
 */
    QString m_appPath;

/**
    @brief flag if new keypair was generated.
  */
    bool m_isNewKeyPair;

/**
    @brief contains the public part from RSA-Key.
  */
    QByteArray m_PublicKey;

/**
    @brief contains the private part from RSA-Key.
  */
    QByteArray m_PrivateKey;

/**
    @brief is true if the list is loaded.
  */
    bool m_isLoaded;
};

#endif // RSAKEYPAIR_H
