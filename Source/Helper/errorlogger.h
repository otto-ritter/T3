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
#ifndef ERRORLOGGER_H
#define ERRORLOGGER_H

#define LOG_FILENAME "errorLog.log"

// QT Includes
#include <QApplication>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QTime>
#include <QDate>
#include <QTextStream>

// Custom Includes
#include <Helper/globalDefines.h>
#include <Helper/errorposition.h>

/**
     @brief Write errors and messages to Logfile.

     This class was implemented as a Singleton. By the static method instanceOf() you get access to LogError() method and write data in the Logfile.

     @author Otto Ritter me@otto-ritter.de
     @version 0.6
     @date 06.09.2011
 */

class ErrorLogger
{
public:

    /**
        @brief Returns the instance of this singleton.

        Static method to retrieve the instance of this singleton.

        @return ErrorLogger & reference to this instance.
     */
    static ErrorLogger& instanceOf();

    /**
        @brief Sets the message, location, type and write in Logfile.

        @param ErrorMsg QString the message.
        @param ErrorLocation QString the location that send the Error
        @param type int 1 = Information / 2 = Warning / 3 = Error
     */
    void logError(QString ErrorMsg, QString ErrorLocation, int type = 2);

    /**
        @brief Sets the application directory.

        @param path QString contains the application directory.
     */
    void setAppPath(QString);

private:

    /**
      @brief empty private Constructor.
     */
    ErrorLogger() {}  // not instantiable
    ErrorLogger(const ErrorLogger&) {}  // not copied

    /**
        @brief empty Destructor.
     */
    ~ErrorLogger() {}

/**
    @brief contains the path to the Application.
  */
    QString m_appPath;
/**
    @brief contains the instance of this Object.
  */
     static ErrorLogger m_instance;
};

#endif // ERRORLOGGER_H
