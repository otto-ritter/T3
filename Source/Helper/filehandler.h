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
#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QFile>
#include <QByteArray>
#include <QString>
//#include <QINT64>
#include <QDebug>
#include <QFileInfo>
#include <Helper/errorposition.h>
#include <Helper/mainexception.h>
#include <Helper/userexception.h>


/**
     @class FileHandler

     @brief Handle source and destination file to read an write to filesystem.

     After set the input or output filepath so it check is this file exist and readable if so open the filehandle.
     Parse the input file path to genarate path to key file to read.
     After write data so it parse the output filepath to ganarate path for keyfile to write.

     @author Otto Ritter me@otto-ritter.de
     @version 0.3
     @date 09.01.2012
 */

class FileHandler
{   
public:
    /**
        @brief Constructor intialize the Object.
     */
    FileHandler();

    /**
         @brief Setter for the input file. After setting the path, creates a file handler and checks the file.

         @param filePath QString path to the file that will be read.
         @throws MainException if the file can't be read.
     */
    void setInputPath(QString filePath) throw (MainException);

    /**
         @brief Setter to the output file. After setting the path, creates a file handler and checks the file.

         @param filePath QString path to the file that will be create in the filesystem and write.
         @throws MainException if the file can't be write.
     */
    void setOutputPath(QString filePath) throw (MainException);

    /**
         @brief Get the path to the file that will be read.
         @return QString path to the file in the filesystem.
     */
    QString getInputPath() { return m_infoForInputFile->canonicalFilePath(); }

    /**
        @brief Get the path to the file that will be write.
        @return QString path to the file in the filesystem.
     */
    QString getOutputPath() { return m_infoForOutputFile->canonicalFilePath(); }

    /**
        @brief Get the path to the keyfile.

        Befor call write the path is to keyfile for reading.
        After write return path to keyfile for write.

      */
    QString getKeyPath() { return m_keyPath; }

    /**
        @brief Get the size of the file that will be read.
     */
    int sizeInput() { return m_inputFileHandler->size(); }

    /**
         @brief Return the QFileInfo object for input file that will be read.

         @see FileHandler::setInputFilePath();
      */
    QFileInfo * getInputInfo() { return m_infoForInputFile; }

    /**
        @brief Return the QFileInfo object for output file that was be written.

        @see FileHandler::setOutputFilePath();
      */
    QFileInfo * getOutputInfo() { return m_infoForOutputFile; }

    /**
        @brief Reads the data from filesystem to QByteArray and returns it.

        @return QByteArray data from file.
     */
    QByteArray readAll();

    /**
        @brief Reads from inputfile only the given numbers of bytes.

        @param numberOfBytes int number of bytes that will be read.
     */
    QByteArray read(int numberOfBytes) throw (MainException);

    /**
        @brief Writes the given QByteArray in the file that is defined by setOutputFilePath.

        @param writeData QByteArray& the will be write on the filesystem
        @return boolean true if write correct else false.
     */
    bool write(const QByteArray & writeData);

    /**
         @brief Writes the Data to file that defined in setOutputFilePath.

         @param writeData QByteArray& referenz to the QByteArray with data to write.
         @param length int number of byte to write in the file.
         @return boolean if write fine then return true else false.
     */
    bool write(const QByteArray & writeData, int length);

    /**
          @brief Writes the file with the key information for the encrypted file.

          @param keyContent QString the content that will be written to the file.
          @return true if write is sucsessful.
      */
    void writeKey(const QString) throw (MainException);

    /**
        @brief Checks if the filehandler is not at the end of the file.

        @return boolean true if filehandler is not at the and.
     */
    bool hasNext();

    /**
        @brief Reinitializes this Object. All attributes will be reset to default.
     */
    void clear();

signals:

public slots:

private:

    /**
        @brief The internal method to reset or initialize the Object.
     */
    void init();

    /**
      @brief Parse given path to genarate path for the keyfile.
      */
    void parseKeyPath(QFileInfo *fromPath);

    /**
        @brief Path to the keyfile.

        Befor write is called the input path of the file is used to generate the key file path.
        After write the path is changed to path to outputfile but with the .key surfix.
      */
    QString m_keyPath;

    /**
        @brief Filehandler to write the keyfile.
      */
    QFile * m_keyFileHandler;

    /**
        @brief Filehandler to read the file.
      */
    QFile * m_inputFileHandler;
    /**
        @brief Filehandler to write the file.
      */
    QFile * m_outputFileHandler;

    /**
        @brief Contain the information of the input file.
      */
    QFileInfo * m_infoForInputFile;
    /**
        @brief Contain the information of the output file.
      */
    QFileInfo * m_infoForOutputFile;

};

#endif // FILEHANDLER_H
