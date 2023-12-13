#ifndef CRYPTTRAFFIC_H
#define CRYPTTRAFFIC_H
#include <QString>
#include <ctime>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bn.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
class CryptSSL{
public:
    CryptSSL();
    QString gen_keys();
    QString rsa_pri_encrypt_base64(const QString &strClearData);

    QString rsa_pub_decrypt_base64(const QString &strDecryptData);
};

#endif // CRYPTTRAFFIC_H
