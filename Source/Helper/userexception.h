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
#ifndef SITUSEREXCEPTION_H
#define SITUSEREXCEPTION_H

// STD & QT Includes
#include <exception>
#include <QString>

// Custom Includes
#include "Helper/globalDefines.h"
#include "Helper/errorlogger.h"
#include <Helper/mainexception.h>

/**
     @brief Is a Exception class was inherits from MainException and is use to show User errors.

     This Class has a technical and a user friendly error message to tell him the warnings.
     Implemented what() it will called by the standard event handler for error stacktrace. It give the user friendly errors back.
     If you want become the user friendly error then use the method getMessage() else getDebugMessages().

     @author Otto Ritter me@otto-ritter.de
     @version 0.2
     @date 04.09.2011
 */
class UserException : public MainException
{
public:
    /**
       @brief Constructor of this exception.

       This Exception is used to tell the user that he made an mistake.
       Call the MainException constructor to write to a logfile.

       @param errorMsgForUser QString error message that can be show to the user.
       @param errorMsg QString error message that will write to Logfile by MainException.
       @param errorLocation QString the location to store the error. Usually this is ErrorPosition::getErrorPosition(ErrorPOS).
       @see ErrorPosition::getErrorPosition()
     */
    UserException(const QString, const QString, const QString);

    /**
        @brief Destructor.
     */
    ~UserException() throw();

    /**
        @brief Call this to get a message without the location.

        @return QString error message that can be used to show it to the user.
     */
   QString getMessage() throw();

   /**
       @brief Message that is given to write in logfile for developers.
       Show only in debug mode.

       @return QString contains the message for debugging purposes.
     */
   QString getDebugMessage() throw();

private:
    /**
        @brief contains the user friendly message.
      */
    QString m_userErrorMessage;
};

#endif // SITUSEREXCEPTION_H
