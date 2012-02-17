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
#ifndef ERRORPOSITION_H
#define ERRORPOSITION_H

// QT Includes
#include <QString>

// Custom Includes
#include "Helper/globalDefines.h"

/**
    @brief Make possible to become the location where an error was called.

    Has only the static method getErrorPosition() use it to become the position.

    @author Otto Ritter me@otto-ritter.de
    @version 0.6
    @date 06.09.2011
 */
class ErrorPosition
{
    // This PreProcessor derictives is using to get FilePath and Line that the Message are called.
    #define STRINGIFY(x) #x
    #define TOSTRING(x) STRINGIFY(x)
    #define ErrorPOS " in "__FILE__" at "TOSTRING(__LINE__)
public:

    /**
       @brief This static method makes the given position printable.

       The given position in most cases ErrorPos from define ErrorPos will make printable by this method.

       @param pos QString contains the position in the file.
       @return QString contains the printable String of the position.
     */
    static QString getErrorPosition(const QString pos);
};

#endif // ERRORPOSITION_H
