#include <QApplication>
#include <QSplashScreen>
#include "gui/mainwindow.h"
#include <QPixmap>

/*!
  @mainpage T3 - Trusted Transmission Tool

   @section desc Description

   This Application can be used to share files with friends so that only you and your friends can open it.
   The usage is very simple: Select the file that you want to share and to whom you want to send it.
   Optionally, you can choose between three symmetric encryption algorithms.

   @section friendlist Friendlist

   With this list it is easy to manage your friends that you want to share files with.

   @subsection fl_addfriend Add friend

   If you start T3 for the first time your friends list will be empty.
   Now you can add a new friend by using the addfriend-Button.
   A dialog will open in which you can enter the name of your friend and the public key that you have received from your friend.

   Attention: An already existing name-entry will overwrite the old friend.

   @subsection fl_editfriend Edit friend

   Choose the friend that you want to edit and push the edit button.
   A dialog opens up in which you can change the key of this friend.

   @subsection fl_deletefriend Delete friend

   Choose the friend that you want to delete and push the delete button.
   After you confirmed this action your friend will be deleted.

   @section encrypt Encryption

   In order to send one of your friends a secret file.

   -# Select the file that you want to encrypt.
   -# Select the friend that you want to send this file.
   -# Click to encryption button (red lock)

   If all wents well you get two new files with the suffix .enc and .key at the same location that your selected file are.
   Now you can send both files to your friend that you selected in your friends list.

   Attention: Only with both files it is possible to decrypt. The files must have the same names.

   @section decrypt Decryption

   You receive two files from your friend and you want to decrypt them.

   -# Select the file with suffix .key or .enc
   -# Click the decryption button (green lock)

   If all wents well you get the decrypted file that your friend encrypted at the same location where the encrypted filse are.

  */

/**
 * @brief Entry point to the application.
 *
 * @param argc
 * @param argv[]
 * @return int
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QPixmap pixmap(":/splash.png");
    //QSplashScreen splash(pixmap);

    //splash.show();
    a.processEvents();

    // Set the application path to controller.
    ControllServer::instanceOf().setAppPath(a.applicationDirPath());
    MainWindow w;
    ControllServer::instanceOf().setView(&w);
    w.show();
    //splash.finish(&w);
    return a.exec();
}
