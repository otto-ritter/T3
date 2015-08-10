#include "crypt.h"

Crypt::Crypt() : QObject()
{
    cipher = EVP_enc_null();
    ERR_load_crypto_strings();
    ctx = (EVP_CIPHER_CTX*)malloc(sizeof(EVP_CIPHER_CTX));
    EVP_CIPHER_CTX_init(ctx);
}

Crypt::~Crypt()
{
    EVP_CIPHER_CTX_cleanup(ctx);
    free(ctx);
}

void Crypt::checkErrorQueue(QString location) throw (MainException)
{
    unsigned long errCode;
    char errMsg[256];
    while(ERR_peek_error() != 0)
    {
        errCode = ERR_get_error();
        ERR_error_string_n(errCode,errMsg,254);        
        throw new MainException(QString(errMsg) ,location);
    }
}

QByteArray Crypt::genRandString(int len)
{
    QByteArray newRandString;
    // Read from dev/urandom factor 8 more data as need to become more entropie
    #ifdef Q_OS_LINUX
        FILE* file = fopen("/dev/urandom", "r");
        for(int i = 0; i < len*8; i++){
            newRandString.append(QString::number(fgetc(file),10));
        }
        fclose (file);
    #elif Q_OS_WIN32 // If compiled on Windows.
        newRandString.append(QTime::currentTime().toString()); // get Systemtime toString for hashing.
    #endif
    // Hash the readed entropie and cut the needed len from the Hash
    return hashKey(newRandString, len);
}

void Crypt::genRandIv(int len)
{
    setIv(genRandString(len));
}

QByteArray Crypt::genRandPassword(int len)
{
    setKey(genRandString(len));
    return key.toHex();
}

QByteArray Crypt::getKey()
{
    return key.toHex();
}

QByteArray Crypt::hashKey(const QByteArray & newKey, int len)
{
    ShaApi* mysha = new ShaApi();
    mysha->sha512(newKey);
    return mysha->getBinHash().mid(0,len).toHex();
}
