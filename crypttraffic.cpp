#include "crypttraffic.h"

CryptSSL::CryptSSL(){

}

QString CryptSSL::rsa_pri_encrypt_base64(const QString& strClearData)
{
         // Длина закрытого ключа 512 (используйте открытый ключ, сгенерированный вами)
    char private_key[] = "-----BEGIN PRIVATE KEY-----\n"\
            "MIIBVgIBADANBgkqhkiG9w0BAQEFAASCAUAwggE8AgEAAkEAzpXEGSjFGDRdr4Gp\n"\
            "k/impFrqxw0JUs7oUwTheJgqNIfCJfw00PHOKmIDI9UoS+E3Ozs1reMP1r0IuUys\n"\
            "zX5LGwIDAQABAkEAhUCjcdsTbu5wM8H+QT0VOFSQtf5ZsjlWMB6o1SHJr4Fs8UEE\n"\
            "7JHUTGrlUopMrhQDfYxGqDUAXykca99xu8e1QQIhAPPdcze2DeV5X9a8bcd3VEzK\n"\
            "Luy6SMOtomEMUKPlYEa7AiEA2N1puJwKEulYWaHywLwhA8tM08YFsFqh18JsUbP5\n"\
            "NyECIQCtuykXGnLB9XsqfyjyPnfnEO7nJTsrdGrHGr/kU0gIewIgVWqYGntzSFGa\n"\
            "V+t+psUyp8DqaLslQHniJw5QBbpCXaECIQDgDWRfFb7h68XMi2fpkd727YDpl64p\n"\
            "fb2H/qFyq3xBDw==\n"\
            "-----END PRIVATE KEY-----";

         // Загружаем строковый ключ в био объект
    BIO* pKeyBio = BIO_new_mem_buf(private_key, strlen(private_key));
    if (pKeyBio == NULL){
        return "";
    }
    RSA* pRsa = RSA_new();
    pRsa = PEM_read_bio_RSAPrivateKey(pKeyBio, &pRsa, NULL, NULL);
    if ( pRsa == NULL ){
         BIO_free_all(pKeyBio);
         return "";
    }
    int nLen = RSA_size(pRsa);
    char* pEncryptBuf = new char[nLen];
    memset(pEncryptBuf, 0, nLen);
    QByteArray clearDataArry = strClearData.toUtf8();
    int nClearDataLen = clearDataArry.length();
    uchar* pClearData = (uchar*)clearDataArry.data();
    int nSize = RSA_private_encrypt(nClearDataLen,
                                    pClearData,
                                    (uchar*)pEncryptBuf,
                                    pRsa,
                                    RSA_PKCS1_PADDING);

    QString strEncryptData = "";
    if ( nSize >= 0 ){
         QByteArray arry(pEncryptBuf, nSize);
         strEncryptData = arry.toBase64();
    }
         // освобождаем память
    delete pEncryptBuf;
    BIO_free_all(pKeyBio);
    RSA_free(pRsa);
    return strEncryptData;
}

QString CryptSSL::rsa_pub_decrypt_base64(const QString &strDecryptData){
    // Расшифровка открытого ключа
char public_key[] = "-----BEGIN PUBLIC KEY-----\n"\
       "MFwwDQYJKoZIhvcNAQEBBQADSwAwSAJBAM6VxBkoxRg0Xa+BqZP4pqRa6scNCVLO\n"\
       "6FME4XiYKjSHwiX8NNDxzipiAyPVKEvhNzs7Na3jD9a9CLlMrM1+SxsCAwEAAQ==\n"\
       "-----END PUBLIC KEY-----";

    // Загружаем строковый ключ в био объект
BIO* pKeyBio = BIO_new_mem_buf(public_key, strlen(public_key));
if (pKeyBio == NULL){
   return "";
}

RSA* pRsa = RSA_new();

pRsa = PEM_read_bio_RSA_PUBKEY(pKeyBio, &pRsa, NULL, NULL);


if ( pRsa == NULL ){
   BIO_free_all(pKeyBio);
   return "";
}
int nLen = RSA_size(pRsa);
char* pClearBuf = new char[nLen];
memset(pClearBuf, 0, nLen);
    // Расшифровать
QByteArray decryptDataArry = strDecryptData.toUtf8();
decryptDataArry = QByteArray::fromBase64(decryptDataArry);
int nDecryptDataLen = decryptDataArry.length();
uchar* pDecryptData = (uchar*)decryptDataArry.data();
int nSize = RSA_public_decrypt(nDecryptDataLen,
                              pDecryptData,
                              (uchar*)pClearBuf,
                              pRsa,
                              RSA_PKCS1_PADDING);
QString strClearData = "";
if ( nSize >= 0 ){
   strClearData = QByteArray(pClearBuf, nSize);
}

    // освобождаем память
delete pClearBuf;
BIO_free_all(pKeyBio);
RSA_free(pRsa);
return strClearData;
}

QString CryptSSL::gen_keys(){
QString key = "";

return key;
}
