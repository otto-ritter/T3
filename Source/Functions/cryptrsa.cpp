#include "cryptrsa.h"

CryptRSA::CryptRSA()
{
    m_isPrivateKey = false;    
    m_isPublicKey = false;
    m_rsaKey = RSA_new();
    m_rsaPrivateKey = RSA_new();
}

CryptRSA::~CryptRSA()
{
    RSA_free(m_rsaKey);
    RSA_free(m_rsaPrivateKey);
}

QByteArray CryptRSA::encrypt(const QByteArray & inputArray) throw (MainException)
{
    emit changeProgress(0);
    // if no public key is set throw exception.
    if(!m_isPublicKey)
    {
        throw MainException(QString("Set public-key befor start encryption.") ,ErrorPosition::getErrorPosition(ErrorPOS));
    }

    /**
     * initialize variable and decryption.
     */

    m_DataArray.clear(); // clear data from previous operations
    unsigned char *crypted;

#ifdef DEBUG_RSA_MSG
    ErrorLogger::instanceOf().logError("Size: " + QString::number(inputArray.size(), 10) + " InputArray: " + QString(inputArray.data()), ErrorPosition::getErrorPosition(ErrorPOS),1);
#endif

    crypted = (unsigned char*)malloc(RSA_size(m_rsaKey));

    /**
    *   start encryption.
    */

    m_EnDeCryptedSize = RSA_public_encrypt(inputArray.size(), (unsigned char*)inputArray.data(), crypted, m_rsaKey, RSA_PKCS1_OAEP_PADDING);
    checkErrorQueue(ErrorPosition::getErrorPosition(ErrorPOS));  // check for errors ERR_get_error();

    /**
      *   end encryption and write data back.
      */

    m_DataArray.append((char*)crypted,m_EnDeCryptedSize);
    m_DataArray = m_DataArray.toHex();

#ifdef DEBUG_RSA_MSG
    ErrorLogger::instanceOf().logError("Size: " + QString::number(m_DataArray.size(), 10) + " OutputArray: " + QString(m_DataArray.data()), ErrorPosition::getErrorPosition(ErrorPOS),1);
#endif
    emit changeProgress(100);
    return m_DataArray;
}

QByteArray CryptRSA::decrypt(const QByteArray & inputArray) throw (MainException)
{
    emit changeProgress(0);
    // if no private key is set throw exception.
    if(!m_isPrivateKey) {
        throw MainException(QString("Set private-key befor start decryption.") ,ErrorPosition::getErrorPosition(ErrorPOS));
    }

    /**
     * initialize variable and decryption.
     */

    m_DataArray.clear(); // clear data from previous operations
    QByteArray tmp_Data;
    tmp_Data = QByteArray::fromHex(inputArray); // Decode from given hex data

#ifdef DEBUG_RSA_MSG
    ErrorLogger::instanceOf().logError("Size: " + QString::number(inputArray.size(),10) + " InputArray: " + QString(inputArray.data()), ErrorPosition::getErrorPosition(ErrorPOS),1);
#endif

    unsigned char *decrypted;
    decrypted = (unsigned char*)malloc(RSA_size(m_rsaPrivateKey));

    /**
    *   start decryption.
    */

    m_EnDeCryptedSize = RSA_private_decrypt(inputArray.size(), (unsigned char*)inputArray.data(), decrypted, m_rsaPrivateKey, RSA_PKCS1_OAEP_PADDING);
    checkErrorQueue(ErrorPosition::getErrorPosition(ErrorPOS)); // check for errors ERR_get_error();

    /**
      *   end decryption and write data back.
      */

    m_DataArray.append((char*)decrypted,m_EnDeCryptedSize);    
    m_DataArray = m_DataArray.toHex();
#ifdef DEBUG_RSA_MSG
    ErrorLogger::instanceOf().logError("Size: " + QString::number(m_DataArray.size(),10) + " OutputArray: " + QString(m_DataArray.data()), ErrorPosition::getErrorPosition(ErrorPOS),1);
#endif
    emit changeProgress(100);
    return m_DataArray;
}

void CryptRSA::setPrivateKey(const QByteArray &newKey) throw (MainException)
{
    QList<QByteArray> tmpKey;
    tmpKey = newKey.fromBase64(newKey).split('-');
    if(tmpKey.size() != 8) {
        throw MainException(QString("Private-key set failure.") ,ErrorPosition::getErrorPosition(ErrorPOS));
    }
    m_rsaPrivateKey->n = BN_new();
    m_rsaPrivateKey->e = BN_new();
    m_rsaPrivateKey->d = BN_new();
    m_rsaPrivateKey->p = BN_new();
    m_rsaPrivateKey->q = BN_new();
    m_rsaPrivateKey->dmp1 = BN_new();
    m_rsaPrivateKey->dmq1 = BN_new();
    m_rsaPrivateKey->iqmp = BN_new();
    BN_hex2bn(&m_rsaPrivateKey->n, tmpKey.at(0).data());
    BN_hex2bn(&m_rsaPrivateKey->e, tmpKey.at(1).data());
    BN_hex2bn(&m_rsaPrivateKey->d, tmpKey.at(2).data());
    BN_hex2bn(&m_rsaPrivateKey->p, tmpKey.at(3).data());
    BN_hex2bn(&m_rsaPrivateKey->q, tmpKey.at(4).data());
    BN_hex2bn(&m_rsaPrivateKey->dmp1, tmpKey.at(5).data());
    BN_hex2bn(&m_rsaPrivateKey->dmq1, tmpKey.at(6).data());
    BN_hex2bn(&m_rsaPrivateKey->iqmp, tmpKey.at(7).data());

    if(RSA_check_key(m_rsaPrivateKey) == 1) {
        m_isPrivateKey = true;
    } else {
        checkErrorQueue(ErrorPosition::getErrorPosition(ErrorPOS));
    }
}

void CryptRSA::setKey(const QByteArray &newKey) throw (MainException)
{
    QList<QByteArray> tmpKey;
    tmpKey = newKey.fromBase64(newKey).split('-');
    if(tmpKey.size() != 2) {
        throw MainException(QString("Public-key set failure.") ,ErrorPosition::getErrorPosition(ErrorPOS));
    }
    // Preparing RSA Strukt.
    m_rsaKey->n = BN_new();
    m_rsaKey->e = BN_new();
    m_rsaKey->d=NULL;
    m_rsaKey->p=NULL;
    m_rsaKey->q=NULL;
    m_rsaKey->dmp1=NULL;
    m_rsaKey->dmq1=NULL;
    m_rsaKey->iqmp=NULL;

    BN_hex2bn(&m_rsaKey->n, tmpKey.at(0).data());
    BN_hex2bn(&m_rsaKey->e, tmpKey.at(1).data());
    m_isPublicKey = true;
}

int CryptRSA::checkKeys(const QByteArray &extPubKey)
{
    // if no private Key is set return error.
    if(!m_isPrivateKey) {
        return -1;
    }
    // Check for both Keys are equal.
    QByteArray tmpExtKey, tmpKey;
    tmpExtKey = QByteArray::fromBase64(extPubKey); // Base64 decode

    // create hex encoded public key from own private key and compare both.
    tmpKey.append(BN_bn2hex(m_rsaPrivateKey->n)); // public modulus (n)
    tmpKey.append('-');
    tmpKey.append(BN_bn2hex(m_rsaPrivateKey->e)); // public exponent (e)

    return (tmpKey == tmpExtKey) ?  1 : 0;
}
