#include "app.h"

App::App() : QObject()
{
    m_fileHandler = new FileHandler();
    m_cryptAlgo = "BlowFish";
    m_cryptionObject = new CryptBlowfish();
}

App::~ControllServer()
{
    delete m_fileHandler;
    delete m_cryptionObject;
}

App& App::instanceOf()
{
    static ControllServer m_instance;
    return m_instance;
}

QStringList ControllServer::getFiendList()
{
    return QStringList(m_Personen.getNameList());
}

void ControllServer::addFriend(QString name, QByteArray key)
{
    m_Personen.addPerson(name, key);
}

void ControllServer::editFriend(QString name, QByteArray key)
{
    m_Personen.setRSAKey(name, key);
}

void ControllServer::deleteFriend(QString name)
{
    m_Personen.deletePerson(name);
}

QString ControllServer::getPublicKey()
{
    return QString(m_KeyPair.getPublicKey());
}

QByteArray ControllServer::getPublicKeyByName(QString name){
   return m_Personen.getRSAKey(name);
}

void ControllServer::setFilePathToProcess(QString pathToFile)
{
    try{
        m_fileHandler->setInputPath(pathToFile);
    }
    catch (MainException e)
    {
        m_fileHandler->clear();
        emit sendWarning("Warning", e.getMessage());
    }
}

bool App::doEnCrypt(QListWidgetItem* selectedFriend)
{
    QString friendName;
    if(selectedFriend) {
        friendName = selectedFriend->text();
    }
    if(friendName.isEmpty() || m_fileHandler->getInputPath().isEmpty())  {
        emit sendWarning("Can't encrypt...", "Check:\n - select Friend\n - select File");
        return false;
    }
    try {
        selectSymmetricAlgorithmus(); // Create new Crypt-Object dependent on selected algorithmus.
        m_fileHandler->setOutputPath(m_fileHandler->getInputInfo()->canonicalPath()+"/"+friendName+"_"+m_fileHandler->getInputInfo()->completeBaseName()+".enc");
        m_fileHandler->write( m_cryptionObject->encrypt( m_fileHandler->readAll() ) );
        writeKeyFile(friendName);
        delete m_cryptionObject;
    } catch (MainException e) {
        emit sendWarning("Warning", e.getMessage());
        return false;
    }

#ifdef DEBUG_MSG
  //  ErrorLogger::instanceOf().logError(QString::number(QByteArray::fromHex(*m_CryptedAndDecryptedData).size(),10) +" Er = Ob " + QString::number(m_cryptionObject->getLastLength()), ErrorPosition::getErrorPosition(ErrorPOS),1);
#endif

return true;
}

bool ControllServer::doDeCrypt()
{
    try  {
        selectSymmetricAlgorithmus(); // Create new Crypt-Object dependent on selected algorithmus.
        readKeyFile(); // read the key-file. If can't load throw Exeptions.
        m_fileHandler->write( m_cryptionObject->decrypt( m_fileHandler->readAll() ) );
        delete m_cryptionObject;
    } catch( MainException e ) {
        emit sendWarning("Warning", e.getMessage());
        return false;
    }
    #ifdef DEBUG_MSG
     //   ErrorLogger::instanceOf().logError(QString::number(QByteArray::fromHex(*m_CryptedAndDecryptedData).size(),10) +" Er = Ob " + QString::number(m_cryptionObject->getLastLength()), ErrorPosition::getErrorPosition(ErrorPOS),1);
    #endif
    return true;
}

void ControllServer::readKeyFile() throw (MainException, UserException)
{
    QDomDocument doc("KeyFile");

    QFile file(m_fileHandler->getKeyPath());
    if (!file.open(QIODevice::ReadOnly)) {
        file.close();
        throw MainException("Can't open "+ m_fileHandler->getKeyPath() +" to read. " + file.errorString() ,ErrorPosition::getErrorPosition(ErrorPOS));
    }
    if (!doc.setContent(&file))
    {
        file.close();
        throw UserException("The selected keyfile: "+ m_fileHandler->getKeyPath() +" is damaged. Please tell your friend to send it again ", "Can't parse " + m_fileHandler->getKeyPath(), ErrorPosition::getErrorPosition(ErrorPOS));
    }

    CryptRSA * RSACryptObj = new CryptRSA();
    RSACryptObj->setPrivateKey(m_KeyPair.getPrivateKey());

    QDomElement docElement = doc.documentElement();
    QDomNode node = docElement.firstChild();
    while(!node.isNull()) {
        QDomElement element = node.toElement(); // try to convert the node to an element.
        if(!element.isNull()) {
            if(element.tagName() == "pubkey") {
                if( element.attribute("hash") != QString(QCryptographicHash::hash(element.attribute("value").toUtf8(), QCryptographicHash::Md5).toHex())) {
                    #ifdef DEBUG_MSG
                        ErrorLogger::instanceOf().logError("Public-RSA: " + element.attribute("hash") + " == " + QString(QCryptographicHash::hash(QByteArray::fromHex(element.attribute("value").toUtf8()), QCryptographicHash::Md5).toHex()), ErrorPosition::getErrorPosition(ErrorPOS),1);
                    #endif
                    throw UserException("Cancel decryption because the public-key was manipulated", "Different hashes -> corrupt public-key.", ErrorPosition::getErrorPosition(ErrorPOS));
                }
                if(RSACryptObj->checkKeys(element.attribute("value").toUtf8()) != 1) {
                    throw UserException("This file is not for you or your friend still has your old key. Please give him your new key.", "Public and private keys are not suitable.", ErrorPosition::getErrorPosition(ErrorPOS));
                }
            } else if(element.tagName() == "key") {
                if( element.attribute("hash") != QString(QCryptographicHash::hash(QByteArray::fromHex(element.attribute("value").toUtf8()), QCryptographicHash::Md5).toHex())) {
                    #ifdef DEBUG_MSG
                        ErrorLogger::instanceOf().logError("Symmetric-Key: " + element.attribute("hash") + " == " + QString(QCryptographicHash::hash(QByteArray::fromHex(element.attribute("value").toUtf8()), QCryptographicHash::Md5).toHex()), ErrorPosition::getErrorPosition(ErrorPOS),1);
                    #endif
                    throw UserException("Cancel decryption because the key was manipulated", "Different hashes -> corrupt symmetric key.", ErrorPosition::getErrorPosition(ErrorPOS));
                }

                #ifdef DEBUG_MSG
                    ErrorLogger::instanceOf().logError("Befor RSA decryption: " + QString(QByteArray::fromHex(element.attribute("value").toUtf8())), ErrorPosition::getErrorPosition(ErrorPOS),1);
                #endif

                // Read and decrypt Key with own RSA Private Key.
                QByteArray tmpData;
                tmpData = RSACryptObj->decrypt( QByteArray::fromHex(element.attribute("value").toUtf8()) );
                m_cryptionObject->setKey( QByteArray::fromHex(tmpData.data()) );

                #ifdef DEBUG_MSG
                    ErrorLogger::instanceOf().logError("After RSA decryption: " + QString(QByteArray::fromHex(tmpData.data())), ErrorPosition::getErrorPosition(ErrorPOS),1);
                #endif

            } else if(element.tagName() == "algorithmus" ) {
              selectSymmetricAlgorithmus(element.attribute("value"));
            } else if(element.tagName() == "file" ) {
                if( element.attribute("hashfile") != QString(QCryptographicHash::hash(QByteArray::fromHex(element.attribute("value").toUtf8()), QCryptographicHash::Md5).toHex())) {
                    #ifdef DEBUG_MSG
                        ErrorLogger::instanceOf().logError("Encrypted-File: " + element.attribute("hashfile") + " == " + QString(QCryptographicHash::hash(QByteArray::fromHex(element.attribute("value").toUtf8()), QCryptographicHash::Md5).toHex()), ErrorPosition::getErrorPosition(ErrorPOS),1);
                    #endif
                    throw UserException("Cancel decryption because the encrypted file was manipulated", "Different hashes -> corrupt encrypted file..", ErrorPosition::getErrorPosition(ErrorPOS));
                }
                m_fileHandler->setOutputPath(QString(QByteArray::fromHex(element.attribute("value").toUtf8())));
            }
        }
        node = node.nextSibling();
    }
}

void ControllServer::writeKeyFile(QString selectedFriend) throw (UserException)
{

    #ifdef DEBUG_MSG
        ErrorLogger::instanceOf().logError("Befor RSA encryption: " + QString(m_cryptionObject->getKey()), ErrorPosition::getErrorPosition(ErrorPOS),1);
    #endif
    // Encrypt symetric key with the public rsa key from friend.
    CryptRSA * RSACryptObj = new CryptRSA();
    QByteArray symKey;
    try {
        RSACryptObj->setKey( m_Personen.getRSAKey(selectedFriend) );
        symKey = RSACryptObj->encrypt(m_cryptionObject->getKey() );
    } catch(MainException e) {
        throw UserException("Internal Error: Can't create key-file. You have not select a friend or his key is not suitable", QString(e.what()), ErrorPosition::getErrorPosition(ErrorPOS));
    }
    #ifdef DEBUG_MSG
        ErrorLogger::instanceOf().logError("After RSA encryption: " + QString(QByteArray::fromHex(symKey)), ErrorPosition::getErrorPosition(ErrorPOS),1);
    #endif

    QDomDocument doc;
    QDate currentDate = QDate::currentDate();
    QTime currentTime = QTime::currentTime();

    QDomElement root = doc.createElement("KeyFile");

    QDomElement algo = doc.createElement("algorithmus");
    algo.setAttribute("value", m_cryptAlgo);

    QDomElement pubkey = doc.createElement("pubkey");
    pubkey.setAttribute("value", QString(m_Personen.getRSAKey(selectedFriend)));
    pubkey.setAttribute("hash", QString(QCryptographicHash::hash(m_Personen.getRSAKey(selectedFriend), QCryptographicHash::Md5).toHex()));

    QDomElement key = doc.createElement("key");
    key.setAttribute("value", QString(symKey));
    key.setAttribute("hash", QString(QCryptographicHash::hash(QByteArray::fromHex(symKey), QCryptographicHash::Md5).toHex()));

    QDomElement filename = doc.createElement("file");
    filename.setAttribute("value", QString(m_fileHandler->getInputInfo()->fileName().toUtf8().toHex()));
    filename.setAttribute("hashfile", QString(QCryptographicHash::hash(m_fileHandler->getInputInfo()->fileName().toUtf8(), QCryptographicHash::Md5).toHex()));

    QDomElement datetime = doc.createElement("create");
    datetime.setAttribute("date", currentDate.toString("dd.MM.yyyy"));
    datetime.setAttribute("time", currentTime.toString("hh:mm:ss"));

    root.appendChild(algo);
    root.appendChild(pubkey);
    root.appendChild(key);
    root.appendChild(filename);
    root.appendChild(datetime);
    doc.appendChild(root);

    m_fileHandler->writeKey(doc.toString());
}

bool ControllServer::checkKeySyntax(QByteArray key, int keyType)
{
    return m_KeyPair.checkKeySyntax(key, keyType);
}

void ControllServer::setAppPath(QString path)
{
    #ifdef DEBUG_MSG
        ErrorLogger::instanceOf().logError("GCS The App-Path: " + path, ErrorPosition::getErrorPosition(ErrorPOS),1);
    #endif
    m_appPath = path;
    ErrorLogger::instanceOf().setAppPath(path);
    m_KeyPair.setAppPath(path);
    m_Personen.setAppPath(path);
}

QString ControllServer::getAppPath() {
    return m_appPath;
}

void ControllServer::exportPublicKey()
{
    m_KeyPair.exportPublicKey();
}

void ControllServer::setView(QWidget *view) {
    m_View = view;
    connect(this, SIGNAL(sendWarning(QString,QString)), m_View, SLOT(showWarnings(QString,QString)));
    connect(m_cryptionObject, SIGNAL(changeProgress(int)), m_View, SLOT(updateProcessBar(int)));
}

void ControllServer::selectSymmetricAlgorithmus(QString changedCryptAlgorithmus){
    if(!changedCryptAlgorithmus.isEmpty() || m_cryptAlgo != changedCryptAlgorithmus ){
        m_cryptAlgo = changedCryptAlgorithmus;
    }

    if(m_cryptAlgo == "AES") {
        m_cryptionObject = new CryptAES();
    } else if(m_cryptAlgo == "3DES") {
        m_cryptionObject = new Crypt3DES();
    } else {
        m_cryptionObject = new CryptBlowfish();
    }
    connect(m_cryptionObject, SIGNAL(changeProgress(int)), m_View, SLOT(updateProcessBar(int)));
}
