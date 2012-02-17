#include "cryptaes.h"

CryptAES::CryptAES()
{
#ifdef DEBUG_AES
    cipher = EVP_enc_null(); // plan encryption
#else
    cipher = EVP_aes_256_cbc(); // set AES as Algorihmus
#endif
    EVP_add_cipher(cipher);    
}

CryptAES::~CryptAES()
{
}

QByteArray CryptAES::encrypt(const QByteArray & inputArray) throw (MainException)
{
    readyEnDeCrypted.clear();
    emit changeProgress(0);
    /**
     * initialize variable and encryption.
     */
    this->setKey(genRandPassword(32));
    this->genRandIv(8); // read and set random IV.

#ifdef DEBUG_AES_MSG
    ErrorLogger::instanceOf().logError("(AES) Encryption", ErrorPosition::getErrorPosition(ErrorPOS),1);
    ErrorLogger::instanceOf().logError("(AES) Key length: " + QString::number(this->key.length(),10), ErrorPosition::getErrorPosition(ErrorPOS),1);
    ErrorLogger::instanceOf().logError("(AES) IV = " + QString(iv.data()) + "Size: "+QString::number(iv.size()), ErrorPosition::getErrorPosition(ErrorPOS),1);
    ErrorLogger::instanceOf().logError("(AES) Size: " + QString::number(inputArray.size(), 10) + " InputArray: " + QString(inputArray.toHex().data()), ErrorPosition::getErrorPosition(ErrorPOS),1);
#endif

#ifdef DEBUG_AES
    EVP_EncryptInit(ctx,cipher,(unsigned char*)key.data(),(unsigned char*)iv.data());
#else
    EVP_EncryptInit(ctx,cipher,NULL,(unsigned char*)iv.data());
    EVP_CIPHER_CTX_set_key_length(ctx, key.size());
    EVP_EncryptInit(ctx,NULL,(unsigned char*)key.data(), (unsigned char*)iv.data());
#endif
    checkErrorQueue(ErrorPosition::getErrorPosition(ErrorPOS)); // check for errors ERR_get_error();

    unsigned char *crypted;
    crypted = (unsigned char*)malloc(inputArray.size() + EVP_CIPHER_CTX_block_size(ctx)+1);
    int count = 0, len=0;

    /**
    *   start encryption.
    */

    // Now encrypt full blocks.
    EVP_EncryptUpdate(ctx, crypted, &count, (unsigned char*)inputArray.data(), inputArray.size());
    checkErrorQueue(ErrorPosition::getErrorPosition(ErrorPOS)); // check for errors ERR_get_error();
    len +=count;

    // add padding
    EVP_EncryptFinal(ctx, &crypted[len], &count);
    len +=count;    
    checkErrorQueue(ErrorPosition::getErrorPosition(ErrorPOS)); // check for errors ERR_get_error();

    /**
      *   end encryption and write data back.
      */

    readyEnDeCrypted.append(iv); // write iv.
    readyEnDeCrypted.append((char*)crypted,len); // write encrypted data.
    m_EnDeCryptedSize = readyEnDeCrypted.size();
#ifdef DEBUG_AES_MSG
    ErrorLogger::instanceOf().logError("(AES) Size: " + QString::number(readyEnDeCrypted.size(), 10) + " OutputArray: " + QString(readyEnDeCrypted.data()), ErrorPosition::getErrorPosition(ErrorPOS),1);
#endif
    emit changeProgress(100);
    free(crypted);
    return readyEnDeCrypted;
}

QByteArray CryptAES::decrypt(const QByteArray & inputArray) throw (MainException)
{
    readyEnDeCrypted.clear();
    emit changeProgress(0);
    /**
     * cut and set IV from input data.
     */

    QByteArray clearInputArray;
    clearInputArray = QByteArray(inputArray);
    setIv(clearInputArray.mid(0,8).toHex());
    clearInputArray.remove(0,8);

#ifdef DEBUG_AES_MSG
    ErrorLogger::instanceOf().logError("(AES) Decryption", ErrorPosition::getErrorPosition(ErrorPOS),1);
    ErrorLogger::instanceOf().logError("(AES) Key length: " + QString::number(this->key.length(),10), ErrorPosition::getErrorPosition(ErrorPOS),1);
    ErrorLogger::instanceOf().logError("(AES) IV = " + QString(iv.data()) + "Size: "+QString::number(iv.size()), ErrorPosition::getErrorPosition(ErrorPOS),1);
    ErrorLogger::instanceOf().logError("(AES) Size: " + QString::number(clearInputArray.size(), 10) + " InputArray: " + QString(clearInputArray.toHex().data()), ErrorPosition::getErrorPosition(ErrorPOS),1);
#endif

    /**
     * initialize variable and encryption.
     */

    EVP_DecryptInit(ctx,cipher,(const unsigned char*)this->key.data(),(const unsigned char*)this->iv.data());
    checkErrorQueue(ErrorPosition::getErrorPosition(ErrorPOS)); // check for errors ERR_get_error();
    unsigned char *decrypted;
    decrypted = (unsigned char*)malloc(inputArray.size() + EVP_CIPHER_CTX_block_size(ctx)+1);
    int count=0, len=0;

    /**
      *   start decryption.
      */

    // decrypt data
    EVP_DecryptUpdate(ctx, decrypted, &count, (unsigned char*)clearInputArray.data(), clearInputArray.size());
    checkErrorQueue(ErrorPosition::getErrorPosition(ErrorPOS)); // check for errors ERR_get_error();
    len += count;

    // check padding. if not ok throw exceoption.
    if(EVP_DecryptFinal(ctx, (unsigned char*)&decrypted[count], &count)==0)
    {
        checkErrorQueue(ErrorPosition::getErrorPosition(ErrorPOS)); // check for errors ERR_get_error();
    }
    len += count;
    checkErrorQueue(ErrorPosition::getErrorPosition(ErrorPOS)); // check for errors ERR_get_error();

    /**
      *   end decryption and write data back.
      */

    readyEnDeCrypted.append((char*)decrypted,len); // write decrypted date.
    m_EnDeCryptedSize = readyEnDeCrypted.size();
#ifdef DEBUG_AES_MSG
    ErrorLogger::instanceOf().logError("(AES) Size: " + QString::number(readyEnDeCrypted.size(), 10) + " OutputArray: " + QString(readyEnDeCrypted.data()), ErrorPosition::getErrorPosition(ErrorPOS),1);
#endif
    emit changeProgress(100);
    free(decrypted);
    return readyEnDeCrypted;
}
