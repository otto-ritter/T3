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
#ifndef SHAAPI_H
#define SHAAPI_H

// STD & QT Includes
#include <QByteArray>
#include <stdio.h>
#include <stdlib.h>
#include <QDebug>

// OpenSSL Includes
#include "openssl/sha.h"

// Custom Includes
#include "Helper/globalDefines.h"

/**
     @brief Hash data with sha1, sha256, sha512 algorithm.

     It is possible that the hash value is encoded as binary or hex.
     The hash is generated with the SHA1, SHA256 or SHA512 algorithm.

     @author Otto Ritter me@otto-ritter.de
     @version 0.3
     @date 06.09.2011
 */
class ShaApi
{
public:
    /**
        @brief Standard constructor.
     */
    ShaApi();    

    /**
        @brief Using SHA1 algorithm to hash.

        @param stringarray QByteArray contains the data to hash.
     */
    void sha1( const QByteArray & stringarray);

    /**
        @brief Using SHA256 algorithm to hash.

        @param stringarray QByteArray contains the data to hash.
     */
    void sha256( const QByteArray & stringarray);

    /**
        @brief Using SHA512 algorithm to hash.

        @param stringarray QByteArray contains the data to hash.
     */
    void sha512( const QByteArray & stringarray);

    /**
        @brief Returns the hex encoded hashed data.

        @return QByteArray contains the hex encoded hashed string.
     */
    QByteArray getHash();

    /**
        @brief Returns the binary hashed data.

        @return QByteArray contains the binary hashed string.
     */
    QByteArray getBinHash();

private:
/**
    @brief contains the hashed string.
 */
    QByteArray m_output;
};

#endif // SHAAPI_H
