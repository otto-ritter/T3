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
#ifndef CRYPTBLOWFISH_H
#define CRYPTBLOWFISH_H

// STD & QT Includes
#include <QDebug>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

// Custom Includes
#include "Helper/globalDefines.h"
#include "crypt.h"
#include "Helper/errorposition.h"
#include "sha_api.h"

/**
    @brief Subclass from crypt for symmetric encryption and decryption with Blowfish.

    It reimplements the crypt und decrypt method from Crypt. With this Class it is easy to encrypt and decrypt data.
    You must only set the key or call Crypt::genRandPassword() to generate a random key. After that you can use the encrypt and decrypt methods.

    Blowfish has a variable key length of up to 448 bits.

    @author Otto Ritter me@otto-ritter.de
    @version 0.8
    @date 06.01.2012
 */
class CryptBlowfish : public Crypt
{
public:

    /**
        @brief Sets the Cipher for encryption and decryption to use in OpenSSL.

        If define DEBUG_BF it set the cipher to null so this plan data through and if all ok you become the same plan data back.
    */
    CryptBlowfish();

    /**
        @brief The standard destrictor.
    */
     ~CryptBlowfish();

    /**
         @brief Encrypt given data with the Blowfish (ede) in CBC-Mode.

         Encryt the data in inputArray with Blowfish using OpenSSL. If an error was detected in ERR_get_error() it throws a MainException.

         @param inputArray contains the plan data.
         @throw MainException it throw an std:exception an use ErrorLogger to write the error in the logfile.
         @return QByteArray contains the encrypted data.
     */
    QByteArray encrypt(const QByteArray & inputArray) throw (MainException);

    /**
         @brief Decrypt given data with Blowfish in CBC-Mode.

         Decrypt data in inputArray with Blowfish using OpenSSL. If an error was detected in ERR_get_error() it throw a MainException.
         If the padding is not correct it means the key or data is not correct.

         @param inputArray QByteArray contains the encrypted data.
         @throw MainException it throw an std:exception and use ErrorLogger to write the error in the logfile.
         @return QByteArray contains the decrypted (plan) data.
     */
    QByteArray decrypt(const QByteArray & inputArray) throw (MainException);
};

#endif // CRYPTBLOWFISH_H
