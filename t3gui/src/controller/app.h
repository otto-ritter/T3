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

#ifndef CONTROLLSERVER_H
#define CONTROLLSERVER_H

// QT Includes
#include <QObject>
#include <QWidget>
#include <QString>
#include <QFileDialog>
#include <QList>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QFileInfo>
#include <QProgressBar>
#include <QDebug>

// Custom

#include "gui/mainwindow.h"

class App : public QApplication
{
    Q_OBJECT

public:

    /**
        @brief static method to get the instance of this object.

        @return ControllServer & reference to the instance of ControllServer.
     */
   static App& instanceOf();









   void setView(QWidget *view);

   /**
        @brief Return the View as a QWidget pointer.

        @return QWidget* the View.
     */
   QWidget* getView() { return m_View; }

   /**
        @brief Getter for selected symmetric algorithm.

        @return QString name of the selected algorithm.
     */
   QString getSymmtricAlgortihmus() { return m_cryptAlgo; }

signals:
   /**
        @brief Signal to view with title and message.
     */
  void sendWarning(QString title, QString message);

protected slots:



private:
  /**
      @brief Constructor is private to make sure only itself can create an object.
      Preselect Blowfish as symmetric algorithm.
      Create instance of FileHandler and CryptBlowfish.
   */
   App(int & argc, char *argv[]);   // not instantiable
   App(const ControllServer&) : QObject() {}  // not copied
   /**
       @brief Destructor is private and destroys the filehandler and the crypt object.
    */
   ~App();


   /**
        @brief Singleton.
     */
    static App m_instance;

    MainWindow * m_View;


};

#endif // CONTROLLSERVER_H
