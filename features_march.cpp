#include "chatdialog.h"
#include "client.h"
#include "connection.h"
#include "peermanager.h"

void ChatDialog::bindWithTokens(){
    QFile *tokensF = new QFile("names.tk");
    tokensF->open(QFile::ReadOnly);
    QStringList tokens;
    while(!tokensF->atEnd()){

        tokens.append(tokensF->readLine());
    }
    tokensF->close();

    QString currTK;

    for(int i = 0; i < tokens.size(); i++){
        currTK = tokens.at(i);
        QByteArray decode;
        decode.append(currTK);

        QString res = decode.fromBase64(decode);
        qDebug() << "huhbh " << res;

        client.peerManager->setAddr(res);
        client.peerManager->binder();
    }

}
