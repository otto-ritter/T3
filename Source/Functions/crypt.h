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
#ifndef CRYPT_H
#define CRYPT_H

//#define DEBUG_CRYPTO

// STD & QT  Includes
#include <QByteArray>
#include <QDebug>
#include <QTime>
#include <exception>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

// OpenSSL Includes
#include <openssl/evp.h>
#include <openssl/err.h>

// Custom Includes
#include <Helper/globalDefines.h>
#include "Functions/sha_api.h"
#include "Helper/errorlogger.h"
#include "Helper/errorposition.h"
#include "Helper/mainexception.h"
#include "Helper/filehandler.h"

/**
    @brief The base class for all used encryption and decryption classes.

    This BaseClass for all other classes that use OpenSSL for encryption and decryption.
    It allocates memory and initializes the context that is used in subclasses. Contains methods to generate random strings to set as key or IV.

    @author Otto Ritter me@otto-ritter.de
    @version 0.6
    @date 06.09.2011
  */
class Crypt : public QObject {
    Q_OBJECT

public:
    /**
        @brief Standard constructor.

        Load error string from OpenSSL and allocate memory for ctx (context) after the initialization of ctx.
    */
    Crypt();

    /**
        @brief Standard destructor.

        Destroy ctx and free memory.
    */
    virtual ~Crypt();

    /**
        @brief Sets the key for encryption and decryption.

        @param newKey contains the new key.
     */
    virtual void setKey(const QByteArray & newKey)  { this->key = QByteArray::fromHex(newKey); }

    /**
        @brief Sets the IV.

        This was used to initialize the encryption and decryption.
        It is reommended that it is not empty or null.

        @param newIv contains the new IV.
     */
    virtual void setIv(const QByteArray & newIv){this->iv = QByteArray::fromHex(newIv);}

    /**
        @brief This virtual method for encryption must be implemented in the subclass.

        @param inputArray QByteArray with data to encryption
        @return QByteArray* the pointer to the encrypted data.
     */
    virtual QByteArray encrypt(const QByteArray & inputArray) throw (MainException) = 0;

    /**
        @brief This virtual method for decryption must be implemented in the subclass.

        @param inputArray QByteArray with data to decryption.
        @return QByteArray* the pointer to the decrypted data.
     */
    virtual QByteArray decrypt(const QByteArray & inputArray) throw (MainException) = 0;

    /**
        @brief Check the OpenSSL Error Queue and throw an exception with a message in which
            line the error was found.

        @param location where the method was called.
    */
    virtual void checkErrorQueue(QString location) throw (MainException);

    /**
        @brief Return the length of encrypted or decrypted data in bytes.

        @return int size of the last encrypted or decrypted data.
     */
    int getLastLength() { return m_EnDeCryptedSize; }

    /**
        @brief Returns the key.

        @return QByteArray contains the hex encoded key.
     */
    QByteArray getKey();

signals:

    /**
        @brief Signal to change the progressbar in the view.

        @param progress int percent of progress range 0 to 100.
      */
    void changeProgress(int progress);

protected:

    /**
         @brief Generates and sets a random initial vector.

         @param len int needed length.
         @see Crypt::genRandString()
    */
    void genRandIv(int len);

    /**
         @brief Generate random string to use as random password or initial vector.

         Genarate random data by using /dev/urandom on Linux and Systemtime on Windows after that hash the strings with sha512 and return the len of the hashed string.

         @param len int the needed length of the random data dafault is 8.
         @return QByteArray contains the random string with the length len.
     */
    QByteArray genRandString(int len = 8);

    /**
         @brief Generates and sets a random key.

         @param len int needed length.
         @return QByteArray contain generated password is hex encoded.
         @see Crypt::genRandString()
    */
    QByteArray genRandPassword(int len);

    /**
         @brief If the entered key is too short this method can enlarge it.

         @param newKey QByteArray with the Key.
         @param len int the len you need.
         @return QByteArray contains the hex encoded key.
    */
    QByteArray hashKey(const QByteArray & newKey,int len);

    /**
        @brief contains data after encryption and decryption.

        @attention can contains binary data with \n.
      */
    QByteArray readyEnDeCrypted;   

    /**
        @brief contains the key.

        @attention can contains binary data with binary zero.
      */
    QByteArray key;

    /**
        @brief contains the IV.

        @attention can contains binary data with binary zero.
      */
    QByteArray iv;

    /**
        @brief contains the length of the QByteArray readyEnDeCrypted after encryption or decryption.
      */
    int m_EnDeCryptedSize;

    /**
        @brief The cipher for OpenSSL.

        This is set and initialized in the SubClasses.

        @attention This is necessary for OpenSSL EVP-API.
      */
    const EVP_CIPHER * cipher;

    /**
        @brief The context for OpenSSL.

        This is set and initialize in the constructor.

        @attention This is necesseary for OpenSSL EVP-API.
      */
    EVP_CIPHER_CTX * ctx;
};

#endif  // CRYPT_H
