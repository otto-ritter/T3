#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setVisible(false);
    reloadFriendList(0);
    this->setWindowTitle("Trusted Transmission Tool");

    // Connect the Friendmenü
    connect(ui->action_Add, SIGNAL(triggered()), this, SLOT(on_toolButtonAddFriend_pressed()));
    connect(ui->action_Edit, SIGNAL(triggered()), this, SLOT(on_toolButtonEditFriend_pressed()));
    connect(ui->action_Delete, SIGNAL(triggered()), this, SLOT(on_toolButtonDeleteFriend_pressed()));

    // Connect the Filemenü
    connect(ui->actionSelect_File, SIGNAL(triggered()), this, SLOT(on_toolButtonSelectFile_pressed()));
    connect(ui->actionEncrypt, SIGNAL(triggered()), this, SLOT(on_toolButton_deCrypt_pressed()));
    connect(ui->actionDecrypt, SIGNAL(triggered()), this, SLOT(on_toolButton_deCrypt_pressed()));
    connect(ui->actionExport_Public_Key, SIGNAL(triggered()), this, SLOT(on_toolButtonCopyToClipbord_pressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reloadFriendList(int preSelectedRow)
{
    ui->listFriendsWidget->clear();
    ui->listFriendsWidget->addItems(ControllServer::instanceOf().getFiendList());
    if( ui->listFriendsWidget->count()>0)
        ui->listFriendsWidget->setCurrentRow(preSelectedRow);
}

void MainWindow::on_action_Close_triggered()
{
    this->close();
}

void MainWindow::on_action_About_triggered()
{
    QMessageBox::information(this,tr("About T3"),tr("Trusted Transmission Tool was written by Otto Ritter for a development in IT Security at the University of Applied Sciences South Westphalia in Iserlohn.\n\nIt was used the OpenSSL with Qt framework , and should, be used to share files between friends to transmit encrypted.\nThe use is free but without any warranty."));
}

void MainWindow::on_actionHelp_Webpage_triggered(){
    QDesktopServices::openUrl(QUrl("http://t3.otto-ritter.de?page=help", QUrl::TolerantMode));
}

void MainWindow::showWarnings(QString titel, QString message){
    QMessageBox::warning(this, titel, message ,QMessageBox::Ok);
}

void MainWindow::updateProcessBar(int newValue){
    if( newValue > 100 ){
        newValue = 100;
    }

    if(newValue < 1){
        ui->progressBar->setVisible(false);
        ui->progressBar->setTextVisible(false);
    } else {
        ui->progressBar->setVisible(true);
        ui->progressBar->setTextVisible(true);
    }
    ui->progressBar->setValue(newValue);
}

void MainWindow::on_toolButtonSelectFile_pressed()
{
    updateProcessBar(0);

    QFileDialog* filedlg = new QFileDialog(this,"Please select File");
    filedlg->setFileMode (QFileDialog::ExistingFile);
    filedlg->setViewMode (QFileDialog::Detail);
    filedlg->setDirectory (ControllServer::instanceOf().getAppPath());
    (filedlg->exec()) ? ControllServer::instanceOf().setFilePathToProcess(filedlg->selectedFiles().at(0)) : ControllServer::instanceOf().setFilePathToProcess("");

    ui->lineEdit_selectedFile->setText ( ControllServer::instanceOf().getFilePathToProcess() );
    (ControllServer::instanceOf().getFilePathToProcess().isEmpty()) ?  ui->lineEdit_selectedFile->setToolTip("Please first select a file..."): ui->lineEdit_selectedFile->setToolTip( ControllServer::instanceOf().getFilePathToProcess() );
    if(!ui->lineEdit_selectedFile->text().isEmpty()) {
        QFileInfo FileInfo(ui->lineEdit_selectedFile->text());

        if(FileInfo.suffix() == "enc" || FileInfo.suffix() == "key") {
            ui->actionEncrypt->setEnabled(false);
            ui->actionDecrypt->setEnabled(true);
            ui->toolButton_enCrypt->setEnabled(false);
            ui->toolButton_deCrypt->setEnabled(true);
        } else {
            ui->actionEncrypt->setEnabled(true);
            ui->actionDecrypt->setEnabled(false);
            ui->toolButton_enCrypt->setEnabled(true);
            ui->toolButton_deCrypt->setEnabled(false);
        }
    } else {
        ui->actionEncrypt->setEnabled(false);
        ui->actionDecrypt->setEnabled(false);
        ui->toolButton_deCrypt->setEnabled(false);
        ui->toolButton_enCrypt->setEnabled(false);
    }
}

void MainWindow::on_actionOpenSettings_triggered()
{
    Settings *settingsDialog = new Settings(this);
    settingsDialog->exec();
}

void MainWindow::on_toolButtonAddFriend_pressed()
{
    int row = (ui->listFriendsWidget->currentRow() < 0) ?  0 : ui->listFriendsWidget->currentRow();

    ManagingFriendDialog *friendDialog = new ManagingFriendDialog(this);
    if(friendDialog->exec()) {
        ControllServer::instanceOf().addFriend(friendDialog->getName(), friendDialog->getKey());
    }
    reloadFriendList(row);
}

void MainWindow::on_toolButtonEditFriend_pressed()
{
    QListWidgetItem *friends = ui->listFriendsWidget->currentItem();
    if(friends) {
        int row = ui->listFriendsWidget->currentRow();

        ManagingFriendDialog *friendDialog = new ManagingFriendDialog(this);
        QString friendName;
        friendName = friends->text();
        friendDialog->editData(friendName, ControllServer::instanceOf().getPublicKeyByName(friendName));
        if(friendDialog->exec()) {
            ControllServer::instanceOf().editFriend(friendName, friendDialog->getKey());
        }
        reloadFriendList(row);
    }
}

void MainWindow::on_toolButtonDeleteFriend_pressed()
{
    QListWidgetItem *friends = ui->listFriendsWidget->currentItem();

   if(friends) {
        QString friendNames;
        friendNames.append("Are you sure to delete ?\n");
        friendNames.append(friends->text());

        int ret = QMessageBox::warning(this, tr("Delete Friends"),friendNames,QMessageBox::Ok, QMessageBox::Cancel);
        if(ret == QMessageBox::Ok) {
           ControllServer::instanceOf().deleteFriend(friends->text());
        }
    }
    reloadFriendList(0);
}

void MainWindow::on_toolButtonCopyToClipbord_pressed()
{
     QClipboard *clipboard = QApplication::clipboard();
     clipboard->setText(ControllServer::instanceOf().getPublicKey());
     ControllServer::instanceOf().exportPublicKey();
}

void MainWindow::on_toolButton_deCrypt_pressed()
{
    updateProcessBar(0);
    ControllServer::instanceOf().setFilePathToProcess(ui->lineEdit_selectedFile->text());
    ControllServer::instanceOf().doDeCrypt();
}

void MainWindow::on_toolButton_enCrypt_pressed()
{
    updateProcessBar(0);
    ControllServer::instanceOf().setFilePathToProcess(ui->lineEdit_selectedFile->text());
    ControllServer::instanceOf().doEnCrypt(ui->listFriendsWidget->currentItem());
}
