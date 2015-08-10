#include "rsakeypair.h"

RSAKeyPair::RSAKeyPair()
{    
    m_isNewKeyPair = false;
    m_isLoaded = false;
}

RSAKeyPair::~RSAKeyPair()
{
    if(m_isNewKeyPair) {
        save();
    }
}

void RSAKeyPair::reset() throw (MainException)
{
    try  {
        generate();
    } catch(MainException e) {
        throw MainException(e.getMessage() ,ErrorPosition::getErrorPosition(ErrorPOS));
    }
}

bool RSAKeyPair::load()
{
    QDomDocument doc("RSAKeys");
    QDir dataDir(m_appPath+"/Data");

    if(!dataDir.exists()) {
        #ifdef DEBUG_MSG
            ErrorLogger::instanceOf().logError("Create dir in :"+ dataDir.path(), ErrorPosition::getErrorPosition(ErrorPOS),1);
        #endif
        dataDir.mkdir(dataDir.path());
    }
    QFile file(dataDir.path()+"/"+KEYPAIR_FILENAME);

    if(!file.exists()) {
        #ifdef DEBUG_MSG
            ErrorLogger::instanceOf().logError("No keypair exist. :", ErrorPosition::getErrorPosition(ErrorPOS),1);
        #endif
        return false;
    }
    if (!file.open(QIODevice::ReadOnly)) {
        ErrorLogger::instanceOf().logError("Can't load RSA-Keypair -> "+file.errorString(), ErrorPosition::getErrorPosition(ErrorPOS));
        return false;
    }
    if (!doc.setContent(&file)) {
        file.close();
        ErrorLogger::instanceOf().logError("Can't Parse the XML-File.", ErrorPosition::getErrorPosition(ErrorPOS));
        return false;
    }
   QDomElement docElement = doc.documentElement();

   QDomNode node = docElement.firstChild();
    while(!node.isNull()) {
        QDomElement element = node.toElement(); // try to convert the node to an element.
        if(!element.isNull()) {
            if(element.attribute("Hash") == QString(QCryptographicHash::hash(element.attribute("Key").toUtf8(), QCryptographicHash::Md5).toHex())) {
                if(element.tagName() == "PrivateKey") {
                    m_PrivateKey = element.attribute("Key").toUtf8();
                }
                if(element.tagName() == "PublicKey" ) {
                   m_PublicKey = element.attribute("Key").toUtf8();
                }
            }
        }
        node = node.nextSibling();
    }
    #ifdef DEBUG_MSG
        ErrorLogger::instanceOf().logError("Load keypair successful.", ErrorPosition::getErrorPosition(ErrorPOS),1);
    #endif
    return true;
}

void RSAKeyPair::save()
{
    QDir dataDir(m_appPath+"/Data");

    if(!dataDir.exists()) {
        #ifdef DEBUG_MSG
            ErrorLogger::instanceOf().logError("Create dir in :"+ dataDir.path(), ErrorPosition::getErrorPosition(ErrorPOS),1);
        #endif
        dataDir.mkdir(dataDir.path());
    }

    QFile file(dataDir.path()+"/"+KEYPAIR_FILENAME);
    if (!file.open(QIODevice::WriteOnly)) {
        ErrorLogger::instanceOf().logError("Can't save keypair " +file.errorString(), ErrorPosition::getErrorPosition(ErrorPOS));
        return;
    }
    QDomDocument doc;
    QDomElement root = doc.createElement("root");
    QDomElement PrivKey = doc.createElement("PrivateKey");

    PrivKey.setAttribute("Key", QString(m_PrivateKey));
    PrivKey.setAttribute("Hash", QString(QCryptographicHash::hash(m_PrivateKey, QCryptographicHash::Md5).toHex()) );

    QDomElement PublKey = doc.createElement("PublicKey");
    PublKey.setAttribute("Key", QString(m_PublicKey));
    PublKey.setAttribute("Hash", QString(QCryptographicHash::hash(m_PublicKey, QCryptographicHash::Md5).toHex()) );

    root.appendChild(PrivKey);
    root.appendChild(PublKey);
    doc.appendChild(root);

    QTextStream out(&file);
    out << doc.toString();
    file.close();
    #ifdef DEBUG_MSG
        ErrorLogger::instanceOf().logError("Save keypair successful.", ErrorPosition::getErrorPosition(ErrorPOS),1);
    #endif

}

void RSAKeyPair::generate() throw (MainException)
{
    m_isNewKeyPair = true;
    RSA *rsaKeyPair;

    rsaKeyPair = RSA_generate_key(2048,656537,NULL,NULL);
    if( rsaKeyPair  == NULL ) {         
        throw MainException("Can't generate RSA KeyPair." ,ErrorPosition::getErrorPosition(ErrorPOS));
    }
    // Encode RSA struct to internal data storage format for private and public key.
    QByteArray tmpKey;
    tmpKey.append(BN_bn2hex(rsaKeyPair->n)); // public modulus (n)
    tmpKey.append('-');
    tmpKey.append(BN_bn2hex(rsaKeyPair->e)); // public exponent (e)
    m_PublicKey = tmpKey.toBase64();

    tmpKey.clear();
    tmpKey.append(BN_bn2hex(rsaKeyPair->n)); // public modulus (n)
    tmpKey.append('-');
    tmpKey.append(BN_bn2hex(rsaKeyPair->e)); // public exponent (e)
    tmpKey.append('-');
    tmpKey.append(BN_bn2hex(rsaKeyPair->d)); // private exponent (d)
    tmpKey.append('-');
    tmpKey.append(BN_bn2hex(rsaKeyPair->p)); // secret prime factor (p)
    tmpKey.append('-');
    tmpKey.append(BN_bn2hex(rsaKeyPair->q)); // secret prime factor (q)
    tmpKey.append('-');
    tmpKey.append(BN_bn2hex(rsaKeyPair->dmp1)); // dmp1 [ d mod (p-1) ]
    tmpKey.append('-');
    tmpKey.append(BN_bn2hex(rsaKeyPair->dmq1)); // dmq1 [ d mod (q-1) ]
    tmpKey.append('-');
    tmpKey.append(BN_bn2hex(rsaKeyPair->iqmp)); // iqmp [ q^-1 mod p ]
    m_PrivateKey = tmpKey.toBase64();

    tmpKey.clear();
    #ifdef DEBUG_MSG
        ErrorLogger::instanceOf().logError("RSA-Size: "+ QString::number(RSA_size(rsaKeyPair),10), ErrorPosition::getErrorPosition(ErrorPOS),1);
        ErrorLogger::instanceOf().logError("Public Key: "+ QString(m_PublicKey), ErrorPosition::getErrorPosition(ErrorPOS),1);
        ErrorLogger::instanceOf().logError("Private Key: "+ QString(m_PrivateKey), ErrorPosition::getErrorPosition(ErrorPOS),1);
    #endif
    save();
}

QByteArray RSAKeyPair::getPublicKey()
{
    return m_PublicKey;
}

QByteArray RSAKeyPair::getPrivateKey()
{
    return m_PrivateKey;
}

void RSAKeyPair::setAppPath(QString path)
{
    m_appPath = path;
    if(!load()) {
        m_isLoaded = true;
        generate();
    }
}

void RSAKeyPair::exportPublicKey()
{
    QFile file(m_appPath+"/"+PUBKEY_FILENAME);
    if (!file.open(QIODevice::WriteOnly)) {
        ErrorLogger::instanceOf().logError("Can't export public key " +file.errorString(), ErrorPosition::getErrorPosition(ErrorPOS));
        return;
    }
    QTextStream out(&file);
    out << m_PublicKey;
    file.close();
}

bool RSAKeyPair::checkKeySyntax(QByteArray key, int keyType){
    QList<QByteArray> tmpKey;
    tmpKey = QByteArray::fromBase64(key).split('-');
    return ( (tmpKey.size() == 2 && keyType == 0) || (tmpKey.size() == 8 && keyType == 1) ) ? true : false;
}
