#include "sha_api.h"

ShaApi::ShaApi()
{
}

void ShaApi::sha1( const QByteArray & stringarray)
{
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA_CTX sha1;
    SHA1_Init(&sha1);
    SHA1_Update(&sha1, (unsigned char*)stringarray.data(), stringarray.size());
    SHA1_Final(hash, &sha1);
    for(int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        m_output.append(hash[i]);
    }    
}

void ShaApi::sha256( const QByteArray & stringarray)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, (unsigned char*)stringarray.data(), stringarray.size());
    SHA256_Final(hash, &ctx);
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        m_output.append(hash[i]);
    }
}

void ShaApi::sha512( const QByteArray & stringarray)
{
    unsigned char hash[SHA512_DIGEST_LENGTH];
    SHA512_CTX ctx;
    SHA512_Init(&ctx);
    SHA512_Update(&ctx, (unsigned char*)stringarray.data(), stringarray.size());
    SHA512_Final(hash, &ctx);
    for(int i = 0; i < SHA512_DIGEST_LENGTH; i++) {
        m_output.append(hash[i]);
    }
}

QByteArray ShaApi::getHash()
{
    return m_output.toHex();
}

QByteArray ShaApi::getBinHash()
{
    return m_output;
}
