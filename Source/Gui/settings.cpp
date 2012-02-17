#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    this->setWindowTitle("T3 - Settings");
    ui->lineEditPublicKey->setPlainText(ControllServer::instanceOf().getPublicKey());
    ui->comboBoxSelectAlgo->setCurrentIndex(ui->comboBoxSelectAlgo->findText(ControllServer::instanceOf().getSymmtricAlgortihmus()));
    connect(ui->comboBoxSelectAlgo, SIGNAL(currentIndexChanged(QString)), &ControllServer::instanceOf(), SLOT(selectSymmetricAlgorithmus(QString)));
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_closeButton_clicked(){
    this->accept();
}
