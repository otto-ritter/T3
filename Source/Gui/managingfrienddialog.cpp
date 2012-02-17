#include "managingfrienddialog.h"
#include "ui_managingfrienddialog.h"

ManagingFriendDialog::ManagingFriendDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManagingFriendDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("T3 - Add friend");
    isEdit = false;
}

ManagingFriendDialog::~ManagingFriendDialog()
{
    delete ui;
}

void ManagingFriendDialog::editData(QString name, QByteArray rsaKey)
{
    this->setWindowTitle("T3 - Edit friend");
    isEdit = true;
    m_Name = name;
    m_Key = rsaKey;
    ui->lineEditName->setText(name);
    ui->lineEditName->setEnabled(false);
    ui->plaintexteditRSAKey->setPlainText(QString(rsaKey));
}

void ManagingFriendDialog::on_saveButton_clicked()
{

    if(ui->lineEditName->text().isEmpty() || ui->plaintexteditRSAKey->toPlainText().isEmpty()) {
        QMessageBox::warning(this, tr("Not everything filled"),tr("You must enter Friend Name und his RSA-Key."));
    }
    if(!ControllServer::instanceOf().checkKeySyntax(ui->plaintexteditRSAKey->toPlainText().toUtf8(),0)) {
        QMessageBox::warning(this, "Invalid Key", "The entered public key for this friend is not correct.");
        #ifdef DEBUG_MSG
            ErrorLogger::instanceOf().logError("The entered public key for this friend is not correct.", ErrorPosition::getErrorPosition(ErrorPOS));
        #endif
        return;
    } else {
        m_Name = ui->lineEditName->text();
        m_Key = ui->plaintexteditRSAKey->toPlainText().toUtf8();
        this->accept();
    }
}

void ManagingFriendDialog::on_readKeyButton_clicked(){
    QFileDialog* filedlg = new QFileDialog(this,"Please select keyfile");
    filedlg->setFileMode (QFileDialog::ExistingFile);
    filedlg->setViewMode (QFileDialog::Detail);
    filedlg->setFilter("KEY (*.key);; All files (*.*)");
    filedlg->setDirectory (ControllServer::instanceOf().getAppPath());
    // Wenn neue Datei ausgesucht wurde dann einlesen.
    if(filedlg->exec()){
        QString tempPublicKey;
        qDebug() << filedlg->selectedFiles().at(0);
        QFile file(filedlg->selectedFiles().at(0));
        file.open(QIODevice::ReadOnly);
        tempPublicKey = file.readAll();
        file.close();
        if(!ControllServer::instanceOf().checkKeySyntax(tempPublicKey.toUtf8(), 0)){
            QMessageBox::warning(this, "Invalid Key", "The opened public key for this friend is not correct.\n Please try a other file.");
            return;
        }
        ui->plaintexteditRSAKey->setPlainText(tempPublicKey);
    }
}

QString ManagingFriendDialog::getName()
{
    return m_Name;
}

QByteArray ManagingFriendDialog::getKey()
{
    return m_Key;
}

bool ManagingFriendDialog::isEdited()
{
    return isEdit;
}
