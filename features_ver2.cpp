#include "chatdialog.h"
#include "client.h"
#include "connection.h"
#include "peermanager.h"
#define BUF_SIZE 1024*4

#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <cstdlib>
#include <random>
#include <QClipboard>
#include <QNetworkInterface>

void ChatDialog::setNickname(){


        label_3->setVisible(true);
        lineEdit_2->setVisible(true);
        ApplyBth->setVisible(true);
        connect(ApplyBth, &QPushButton::clicked,this, &ChatDialog::saveName);
        connect(lineEdit_2, &QLineEdit::returnPressed,this, &ChatDialog::saveName);

}
void ChatDialog::saveName(){
    QFile settings("settingsName.ini");
    settings.open(QFile::WriteOnly);
    if(settings.isOpen()){
        settings.write(lineEdit_2->text().toUtf8());
        settings.close();
        QMessageBox::information(this, "Alpha security", "Name changed!Refresh program");

    }
    else{
        QMessageBox::warning(this, "Alpha security", "File not open");
    }
    label_3->setVisible(false);
    lineEdit_2->setVisible(false);
    ApplyBth->setVisible(false);

}
void ChatDialog::clearHist(){
    history = new QFile("QWidgets.hs");
    history->remove();

    textEdit->clear();
}
void ChatDialog::genTokenAction(){
    QString token;

    QString secWord;
    srand(time(NULL));
    for(int i = 0; i < 10; i++){

        secWord.append(rand() % 'a'+26);
    }

    QByteArray cryptBa = secWord.toUtf8();

    QFile *secFile = new QFile("QNetworkSecure.dll");
    secFile->open(QFile::WriteOnly);

   secFile->write(QCryptographicHash::hash(cryptBa, QCryptographicHash::Sha256).toHex());

   secFile->close();





    QNetworkInterface *inter = new QNetworkInterface();
    QList<QHostAddress> list;
    list=inter->allAddresses();
    token = list.at(1).toString();

    QClipboard* clipToken = QApplication::clipboard();
    clipToken->setText(token.toUpper().toUtf8().toBase64() + "\n" + "Sec. word: " + secWord);

    QMessageBox::information(this, ("Alpha security"), ("Private token and secure word copied in clipboard"));


}

void ChatDialog::addTokenAction(){
    widget->setVisible(true);

}
void ChatDialog::on_lineEdit_3_returnPressed()
{
    QString text = lineEdit_3->text();
    QFile *tokenFile = new QFile("names.tk");
    tokenFile->open(QFile::Append);
    if(tokenFile->isOpen()){

        QMessageBox::information(widget, "Alpha security", "Token " + text + " added");
        tokenFile->write(text.toUtf8() + "\n");
        tokenFile->close();
        widget->setVisible(false);
    }
    else{
        QMessageBox::warning(widget, "Alpha security", "Not added token");
        widget->setVisible(false);
    }
}
void ChatDialog::delTokenAction(){
    widget_2->setVisible(true);
    QFile   *tokenF = new QFile("names.tk");
    tokenF->open(QFile::ReadOnly);
    if(tokenF->isOpen()){

    QStringList tokens;
    while(!tokenF->atEnd()){

        tokens.append(tokenF->readLine());
    }

    comboBox->addItems(tokens);
    tokenF->close();

    }
    else{
        QMessageBox::warning(widget_2, "Alpha security", "Error");
        widget_2->setVisible(false);
    }
}
void ChatDialog::on_pushButton_clicked()
{
    QString str = comboBox->currentText();
    qDebug() << str;
     QFile *del = new QFile("names.tk");
     del->open(QFile::ReadOnly);
     QStringList tokens;
     while(!del->atEnd()){

         tokens.append(del->readLine());
     }
     del->close();

      writeNull();

     tokens.removeAt(tokens.indexOf(str));
     QFile *file = new QFile("names.tk");
     file->open(QFile::WriteOnly);

     QTextStream _stream(file);
     foreach(QString str, tokens){
        _stream << str;
     }
    file->close();
    QMessageBox::information(widget_2, "Alpha security", str + " deleted");
    widget_2->setVisible(false);
}

void ChatDialog::writeNull(){
    QFile *file = new QFile("names.tk");
    file->open(QFile::WriteOnly);
    file->write("");
    file->close();
}

void ChatDialog::on_pushButton_2_clicked()
{
     QFile *file = new QFile("names.tk");
     file->remove();
     QMessageBox::information(widget_2, "Alpha security", " Deleted");
     widget_2->setVisible(false);
}

void ChatDialog::genPubTokenAction(){
    QString token;
    QNetworkInterface *inter = new QNetworkInterface();
    QList<QHostAddress> list;
    list=inter->allAddresses();

    token = list.at(1).toString();
        token = token.left(25);


    QClipboard* clipToken = QApplication::clipboard();
    clipToken->setText(token.toUpper().toUtf8().toBase64());

    QMessageBox::information(this, ("Alpha security"), ("Public token copied in clipboard"));

}
void ChatDialog::connectPri(){
    widget_4->setVisible(true);

    label_7->setVisible(true);

    lineEdit_5->setVisible(true);

    if(lineEdit_5->isVisible()){
        connect(pushButton_3, &QPushButton::clicked, this, &ChatDialog::copy_connect_withSec);
    }
}
void ChatDialog::connectPub(){
    widget_4->setVisible(true);
}
void ChatDialog::on_pushButton_3_clicked()
{
    widget_3->setVisible(true);
    label_7->setVisible(false);

    widget_4->setVisible(false);

    QString addr = lineEdit_4->text();
    QByteArray decode;
    decode.append(addr);

    QString res = decode.fromBase64(decode);

    qDebug() << res;

    client.peerManager->setAddr(res);
    client.peerManager->binder();

    for(int i = 0; i < 101; i++){
        _sleep(100);
    progressBar->setValue(i);
    }

    if(progressBar->value() == 100){
        widget_3->setVisible(false);
    }// err: QAbstractSocket::waitForBytesWritten() is not allowed in UnconnectedState




}
void ChatDialog::copy_connect_withSec(){
    QString secWord = lineEdit_5->text();

    widget_3->setVisible(true);
    label_7->setVisible(false);

    widget_4->setVisible(false);

    QString addr = lineEdit_4->text();
    QByteArray decode;
    decode.append(addr);

    QString res = decode.fromBase64(decode);

    qDebug() << res;

    client.peerManager->setAddr(res);
    client.peerManager->binder();

    for(int i = 0; i < 101; i++){
        _sleep(100);
    progressBar->setValue(i);
    }

    if(progressBar->value() == 100){
        widget_3->setVisible(false);
    }// err: QAbstractSocket::waitForBytesWritten() is not allowed in UnconnectedState

}
