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
#ifndef SITEXCEPTION_H
#define SITEXCEPTION_H

// STD & QT Includes
#include <exception>
#include <QString>

// Custom Includes
#include "Helper/globalDefines.h"
#include "Helper/errorlogger.h"

/**
     @brief Throw exceptions and write the errors in Logfile by using ErrorLogger.

     Implemented what() it will called by the standard event handler for error stacktrace. It give the developer or internal error back.

     @author Otto Ritter me@otto-ritter.de
     @version 0.3
     @date 04.09.2011
 */
class MainException : public std::exception
{
public:
    /**
       @brief Constructor of this exception.

       Call ErrorLogger and write the error in the Logfile. Set Error for called by exception handler virtual method what().

       @param errorMsg QString sets the error message.
       @param errorLocation QString sets the location the best is use ErrorPosition::getErrorPosition(ErrorPOS).
       @param errorType int the type of the Exception is need for ErrorLogger.
       @see ErrorLogger::logError() write messages in a logfile.
       @see ErrorPosition::getErrorPosition() to get the possition of the error.
     */
    MainException(const QString errorMsg, const QString errorLocation, int errorType = 3);

    /**
        @brief Destructor.
     */
    ~MainException() throw();

    /**
        @brief This method was called from the std::exception to get message.

        @return const char *
     */
    virtual const char* what() const throw();

    /**
        @brief Returnss the message of this Exception.

        @return QString contains the error message.
      */
    QString getMessage();

protected:
    /**
        @brief contain the error message.
      */
    QString m_errorMessage;
};
#endif // SITEXCEPTION_H
