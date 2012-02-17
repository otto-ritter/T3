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
*/#ifndef PERSONENLIST_H
#define PERSONENLIST_H

#define FRIENDLIST_FILENAME "friendList.list"

#include <QApplication>
#include <QMap>
#include <QString>
#include <QByteArray>
#include <QList>
#include <QFile>
#include <QtXml>
#include <QCryptographicHash>
#include <QTextStream>
#include <QDir>

// Custom Includes
#include <Helper/globalDefines.h>
#include <Helper/errorlogger.h>

/**
     @brief Model for the friendlist.

     It store data with friends names und her public keys.
     If the list was changed then it will be only saved on application close without errors.
     If find an existing list so import the this on application start.

     @author Otto Ritter me@otto-ritter.de
     @version 0.6
     @date 06.09.2011
 */
class PersonenList
{
 public:
    /**
        @brief Constructor.
     */
    PersonenList();

    /**
        @brief Decstructor.

        If the friends list was changed it will save the friends list befor closing.
     */
    ~PersonenList();

    /**
         @brief Adds a person to the friends list.

         Adds a new person to the list and sets the change flag.

         @param name QString name of the person.
         @param rsaKey QByteArray contains the public key of this person.
     */
    void addPerson(QString name, QByteArray rsaKey);

    /**
         @brief Returns the public key from the person with a given name.

         @param name QString friend name.
         @return QByteArray public key.
     */
    QByteArray getRSAKey(QString name);

    /**
         @brief Sets the public key of the person with the given name.

         @param name QString person name.
         @param rsaKey QByteArray public-key.
     */
    void setRSAKey(QString name, QByteArray rsaKey);

    /**
         @brief Returns a list of all friends in the list.

         @return QList<QString> contains friend names.
     */
    QList<QString> getNameList() const;

    /**
         @brief Delete person from list.

         @param name QString person name.
         @return int 0 if no person was removed.
     */
    int deletePerson(QString);

    /**
         @brief Sets the application directory.

         After setting the path this methods tries to load an existing friends list.

         @param path QString contain the application dir.
     */
    void setAppPath(QString);

private:
    /**
         @brief Loads the friends list.

         Loads the existing friends list. It is used by the ErrorLogger to log errors.

         @return bool true if the list was loaded successfully.
     */
    bool importList();

    /**
         @brief Saves the friends list.

         Saves the list if the list was changed.
     */
    void exportList();


/**
    @brief Contain application path.
  */
    QString m_appPath;

/**
    @brief contains the names and keys in this QMap.
  */
    QMap<QString, QByteArray> m_PersonList;

/**
    @brief flag if the list was changed.
  */
    bool m_isChanged;

/**
    @brief is true if the list is loaded.
  */
    bool m_isLoaded;
};

#endif // PERSONENLIST_H
