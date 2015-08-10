#include "crypt3des.h"


Crypt3DES::Crypt3DES()
{
#ifdef DEBUG_3DES
    cipher = EVP_enc_null(); // plan encryption
#else
    cipher = EVP_des_ede3_cbc(); // set 3DS as Algo
#endif
    EVP_add_cipher(cipher);
}

Crypt3DES::~Crypt3DES()
{
}

QByteArray Crypt3DES::encrypt(const QByteArray & inputArray) throw (MainException)
{
    readyEnDeCrypted.clear();
    emit changeProgress(0);
    /**
     * initialize variable and encryption.
     */
    this->setKey(genRandPassword(21));
    this->genRandIv(8); // read and set random IV.

#ifdef DEBUG_3DES_MSG
    ErrorLogger::instanceOf().logError("(3DES) Encryption", ErrorPosition::getErrorPosition(ErrorPOS),1);
    ErrorLogger::instanceOf().logError("(3DES) Key length: " + QString::number(this->key.length(),10), ErrorPosition::getErrorPosition(ErrorPOS),1);
    ErrorLogger::instanceOf().logError("(3DES) IV = " + QString(iv.data()) + "Size: "+QString::number(iv.size()), ErrorPosition::getErrorPosition(ErrorPOS),1);
    ErrorLogger::instanceOf().logError("(3DES) Size: " + QString::number(inputArray.size(), 10) + " InputArray: " + QString(inputArray.toHex().data()), ErrorPosition::getErrorPosition(ErrorPOS),1);
#endif

    EVP_EncryptInit(ctx,cipher,(unsigned char*)this->key.data(),(unsigned char*)this->iv.data());

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

    // now add padding
    EVP_EncryptFinal(ctx, &crypted[len], &count);
    len +=count;
    checkErrorQueue(ErrorPosition::getErrorPosition(ErrorPOS)); // check for errors ERR_get_error();

    /**
      *   end encryption and write data back.
      */

    readyEnDeCrypted.append(iv); // write IV
    readyEnDeCrypted.append((char*)crypted,len); // write encrypted data.
    m_EnDeCryptedSize = readyEnDeCrypted.size();    
#ifdef DEBUG_3DES_MSG
    ErrorLogger::instanceOf().logError("Size: " + QString::number(readyEnDeCrypted.size(), 10) + " OutputArray: " + QString(readyEnDeCrypted.data()), ErrorPosition::getErrorPosition(ErrorPOS),1);
#endif
    free(crypted);
    emit changeProgress(100);
    return readyEnDeCrypted;
}

QByteArray Crypt3DES::decrypt(const QByteArray & inputArray) throw (MainException)
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

#ifdef DEBUG_3DES_MSG
    ErrorLogger::instanceOf().logError("(3DES) Decryption", ErrorPosition::getErrorPosition(ErrorPOS),1);
    ErrorLogger::instanceOf().logError("(3DES) Key length: " + QString::number(this->key.length(),10), ErrorPosition::getErrorPosition(ErrorPOS),1);
    ErrorLogger::instanceOf().logError("(3DES) IV = " + QString(iv.data()) + "Size: "+QString::number(iv.size()), ErrorPosition::getErrorPosition(ErrorPOS),1);
    ErrorLogger::instanceOf().logError("(3DES) Size: " + QString::number(clearInputArray.size(), 10) + " InputArray: " + QString(clearInputArray.toHex().data()), ErrorPosition::getErrorPosition(ErrorPOS),1);
#endif

    /**
     * initialize variable and encryption.
     */

    EVP_DecryptInit(ctx,cipher,(const unsigned char*)this->key.data(),(const unsigned char*)iv.data());

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
    if(EVP_DecryptFinal(ctx, (unsigned char*)&decrypted[count], &count) == 0)
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
#ifdef DEBUG_3DES_MSG
    ErrorLogger::instanceOf().logError("(3DES) Size: " + QString::number(readyEnDeCrypted.size(), 10) + " OutputArray: " + QString(readyEnDeCrypted.data()), ErrorPosition::getErrorPosition(ErrorPOS),1);
#endif
    free(decrypted);
    emit changeProgress(100);
    return readyEnDeCrypted;
}
