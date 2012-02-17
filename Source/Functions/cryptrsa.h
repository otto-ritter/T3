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
#ifndef CRYPTRSA_H
#define CRYPTRSA_H

// STD & QT Includes
#include <QList>
#include <QDebug>

// OpenSSL Includes
#include "openssl/bn.h"
#include "openssl/rsa.h"

// Custom Includes
#include "Helper/globalDefines.h"
#include "crypt.h"
#include <Helper/mainexception.h>

/**
    @brief Subclass from crypt for asymmetric encryption and decryption with RSA.

    This class is used differently than the others. In this case either the public or the private key may be present.
    Encryption is done with the public-key, whereas the private key is needed for decryption.
    There is a possibility to check if the private and public keys match depending on the beginning of the keys.
    Before a decryption or encryption can take place the proper key has to be set.
    This class works with the RSA struct and stores the content in a separate non-standard format.

    @author Otto Ritter me@otto-ritter.de
    @version 0.7
    @date 08.11.2011
*/
class CryptRSA : public Crypt
{
public:
    /**
        @brief Constructor create und initialize RSA struct.
      */
    CryptRSA();

    /**
        @brief Destructor destroy RSA structs.
      */
    ~CryptRSA();

    /**
        @brief Encrypt given data with RSA_public_encrypt.

         Encrypt the data in inputArray with RSA using public-key with OpenSSL. Throws MainException if a error was detected in ERR_get_error().
         If the public-key is not set it throw an exception.

         @param inputArray contains the plan data.
         @throw MainException it throw an std:exception an use ErrorLogger to write the error in the logfile.
         @return QByteArray contains the encrypted data.
     */
    QByteArray encrypt(const QByteArray & inputArray) throw (MainException);

    /**
     @brief Decrypt given data with RSA_private_decrypt.

     Decrypts the data in inputArray with RSA using private-key with OpenSSL. Throws a MainException if an error was detected in ERR_get_error().
     If the private-key is not set it throws an exception.

     @param inputArray QByteArray contains the encoded data.
     @throw MainException it throw an std:exception and use ErrorLogger to write the error in the logfile.
     @return QByteArray contains the decrypted data.
     */
    QByteArray decrypt(const QByteArray & inputArray) throw (MainException);

    /**
         @brief Set the public Key for rsa public encryption.

         This mehtod decodes the hex encoded public key and sets it in RSA struct for OpenSSL.

         @param newKey QByteArray contains the pubic key.
         @throw MainException thrown if can't set public key.
     */
    void setKey(const QByteArray &newKey) throw (MainException);

    /**
         @brief Sets the private Key for RSA private decryption with OpenSSL.

         This method decodes the hex encoded private key and sets it in RSA struct for OpenSSL.

         @param newKey QByteArray contains the key components encoded as Hex.
         @throw MainException if can't set private key.
         @return bool true if valid

         @see RSAKeyPair::generate()
     */
    void setPrivateKey(const QByteArray &newKey) throw (MainException);

    /**
        @brief Check the public key from keyfile with own private Key.
              Returns 1 if keys are valid and 0 if not.
              On error return -1.
         @param extPubKey QByteArray with the public Key from key-file
         @return int 1 if valid and 0 if not.
     */
    int checkKeys(const QByteArray &extPubKey);

 protected:
/**
    @brief contains data with the public key.

    @attention can contains binary data with \n or binary zero.
  */
    RSA *m_rsaKey;

/**
  * @brief the flag for set public key.
  *
  */
    bool m_isPublicKey;

/**
    @brief contains data with the private key.

    @attention can contains binary data with \n or binary zero.
  */
    RSA *m_rsaPrivateKey;

/**
    @brief the flag for set private key.
  */
    bool m_isPrivateKey;

/**
    @brief contains data after encryption or decryption rsaKey.

    @attention can contains binary data with \n.
  */
    QByteArray m_DataArray;
};

#endif // CRYPTRSA_H
