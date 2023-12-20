#include "chatdialog.h"
#include "client.h"
#include "connection.h"
#include "peermanager.h"
#include "showLabels.h"
#define BUF_SIZE 1024*4

#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <cstdlib>
#include <random>
#include <QClipboard>
#include <QNetworkInterface>
#include <QPushButton>
#include <QComboBox>
#include <QStyleFactory>

void ChatDialog::setNickname(){
newNick = new QLabel();
     newNick->resize(621,221);
     newNick->setMaximumSize(621,221);
    newNick->setWindowTitle("Change nickname");
     newNick->setTextInteractionFlags(Qt::TextSelectableByMouse);
    newNick->setStyleSheet("background-color: rgb(31, 31, 31); border-radius: 15px;");

    QLabel *text = new QLabel(newNick);
    text->setGeometry(10,30,261,50);
    text->setText("Your new nickname:");
    text->setStyleSheet("font: 700 14pt 'Arial';background-color: rgba(255, 255, 255, 0);color: rgb(255, 255, 255)");

    newNameLine = new QLineEdit(newNick);
    newNameLine->setGeometry(280,30,241,50);
    newNameLine->setStyleSheet("font: 700 12pt 'Arial';background-color: rgb(42, 42, 42);color: rgb(255, 255, 255);border-radius: 15px;");

    QPushButton *applybth = new QPushButton(newNick);
    applybth->setText("Apply");
    applybth->setGeometry(220, 110, 151,50);
    applybth->setStyleSheet("border-radius: 25px;color: rgb(255, 255, 255);background-color: rgb(106, 33, 131);font: 700 14pt 'Arial';");
    connect(applybth, &QPushButton::clicked,this, &ChatDialog::saveName);
    connect(newNameLine, &QLineEdit::returnPressed,this, &ChatDialog::saveName);

    newNick->show();


}
void ChatDialog::saveName(){
    newNick->hide();
    QFile settings("settingsName.ini");
    settings.open(QFile::WriteOnly);
    if(settings.isOpen()){
        settings.write(newNameLine->text().toUtf8());
        settings.close();
        QMessageBox::information(this, "Wall Mall", "Name changed!Refresh program");

    }
    else{
        QMessageBox::warning(this, "Alpha security", "File not open");
    }


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
    newNick = new QLabel();
         newNick->resize(621,221);
         newNick->setMaximumSize(621,221);
        newNick->setWindowTitle("Wall Mall");
         newNick->setTextInteractionFlags(Qt::TextSelectableByMouse);
        newNick->setStyleSheet("background-color: rgb(31, 31, 31); border-radius: 15px;");

        QLabel *text = new QLabel(newNick);
        text->setGeometry(10,30,241,50);
        text->setText("Add token:");
        text->setStyleSheet("font: 700 14pt 'Arial';background-color: rgba(255, 255, 255, 0);color: rgb(255, 255, 255)");

        newNameLine = new QLineEdit(newNick);
        newNameLine->setGeometry(260,30,241,50);
        newNameLine->setStyleSheet("font: 700 12pt 'Arial';background-color: rgb(42, 42, 42);color: rgb(255, 255, 255);border-radius: 15px;");

        QPushButton *applybth = new QPushButton(newNick);
        applybth->setText("Add");
        applybth->setGeometry(220, 110, 151,50);
        applybth->setStyleSheet("border-radius: 25px;color: rgb(255, 255, 255);background-color: rgb(106, 33, 131);font: 700 14pt 'Arial';");
        connect(applybth, &QPushButton::clicked,this, &ChatDialog::on_lineEdit_3_returnPressed);
        connect(newNameLine, &QLineEdit::returnPressed,this, &ChatDialog::on_lineEdit_3_returnPressed);
    newNick->show();

}
void ChatDialog::on_lineEdit_3_returnPressed()
{
    newNick->hide();
    QString text = newNameLine->text();
    QFile *tokenFile = new QFile("names.tk");
    tokenFile->open(QFile::Append);
    if(tokenFile->isOpen()){

        QMessageBox::information(this, "Alpha security", "Token " + text + " added");
        tokenFile->write(text.toUtf8() + "\n");
        tokenFile->close();

    }
    else{
        QMessageBox::warning(this, "Alpha security", "Not added token");

    }
}
void ChatDialog::delTokenAction(){

        newNick = new QLabel();
         newNick->resize(700,321);
         newNick->setMaximumSize(700,321);
        newNick->setWindowTitle("Delete friend");
         newNick->setTextInteractionFlags(Qt::TextSelectableByMouse);
        newNick->setStyleSheet("background-color: rgb(31, 31, 31); border-radius: 15px;");

        QLabel *text = new QLabel(newNick);
        text->setGeometry(10,30,241,50);
        text->setText("All tokens:");
        text->setStyleSheet("font: 700 14pt 'Arial';background-color: rgba(255, 255, 255, 0);color: rgb(255, 255, 255)");

        tokenBox = new QComboBox(newNick);
        tokenBox->setGeometry(260,30,351,50);
        tokenBox->setStyleSheet("font: 700 12pt 'Arial';background-color: rgb(42, 42, 42);color: rgb(255, 255, 255);border-radius: 15px;");

        QPushButton *delOne = new QPushButton(newNick);
        delOne->setText("Delete");
        delOne->setGeometry(40, 200, 241,70);
        delOne->setStyleSheet("border-radius: 25px;color: rgb(255, 255, 255);background-color: rgb(106, 33, 131);font: 700 14pt 'Arial';");
        connect(delOne, &QPushButton::clicked,this, &ChatDialog::on_pushButton_clicked);

        QPushButton *delAll = new QPushButton(newNick);
        delAll->setText("Delete all");
        delAll->setGeometry(300, 200, 241,70);
        delAll->setStyleSheet("border-radius: 25px;color: rgb(255, 255, 255);background-color: rgb(106, 33, 131);font: 700 14pt 'Arial';");
        connect(delAll, &QPushButton::clicked,this, &ChatDialog::on_pushButton_2_clicked);

        newNick->show();


    QFile   *tokenF = new QFile("names.tk");
    tokenF->open(QFile::ReadOnly);
    if(tokenF->isOpen()){

    QStringList tokens;
    while(!tokenF->atEnd()){

        tokens.append(tokenF->readLine());
    }

    tokenBox->addItems(tokens);
    tokenF->close();

    }
    else{
        QMessageBox::warning(newNick, "Wall Mall", "Error");
    }
}
void ChatDialog::on_pushButton_clicked()
{
    newNick->hide();
    QString str = tokenBox->currentText();
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
     newNick->hide();
    QMessageBox::information(this, "Wall Mall", str + " deleted");
}

void ChatDialog::writeNull(){
    QFile *file = new QFile("names.tk");
    file->open(QFile::WriteOnly);
    file->write("");
    file->close();
}

void ChatDialog::on_pushButton_2_clicked()
{
    newNick->hide();
     QFile *file = new QFile("names.tk");
     file->remove();
      newNick->hide();
     QMessageBox::information(this, "Alpha security", " Deleted");
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

    QMessageBox::information(this, ("Wall Mall"), ("Public token copied in clipboard"));

}
void ChatDialog::connectPri(){
    newNick = new QLabel();
         newNick->resize(621,421);
         newNick->setMaximumSize(621,421);
        newNick->setWindowTitle("Private connect");
         newNick->setTextInteractionFlags(Qt::TextSelectableByMouse);
        newNick->setStyleSheet("background-color: rgb(31, 31, 31); border-radius: 15px;");

        QLabel *text = new QLabel(newNick);
        text->setGeometry(10,30,241,50);
        text->setText("Enter token:");
        text->setStyleSheet("font: 700 14pt 'Arial';background-color: rgba(255, 255, 255, 0);color: rgb(255, 255, 255)");

        newNameLine = new QLineEdit(newNick);
        newNameLine->setGeometry(260,30,241,50);
        newNameLine->setStyleSheet("font: 700 12pt 'Arial';background-color: rgb(42, 42, 42);color: rgb(255, 255, 255);border-radius: 15px;");

        QLabel *secword = new QLabel(newNick);
        secword->setGeometry(10,100,241,50);
        secword->setText("Enter secure word:");
        secword->setStyleSheet("font: 700 14pt 'Arial';background-color: rgba(255, 255, 255, 0);color: rgb(255, 255, 255)");

        newWordLine = new QLineEdit(newNick);
        newWordLine->setGeometry(260,110,241,50);
        newWordLine->setStyleSheet("font: 700 12pt 'Arial';background-color: rgb(42, 42, 42);color: rgb(255, 255, 255);border-radius: 15px;");

        QPushButton *applybth = new QPushButton(newNick);
        applybth->setText("Connect!");
        applybth->setGeometry(220, 210, 151,50);
        applybth->setStyleSheet("border-radius: 25px;color: rgb(255, 255, 255);background-color: rgb(106, 33, 131);font: 700 14pt 'Arial';");
        connect(applybth, &QPushButton::clicked,this, &ChatDialog::copy_connect_withSec);
        connect(newNameLine, &QLineEdit::returnPressed,this, &ChatDialog::copy_connect_withSec);

        newNick->show();

        connect(applybth, &QPushButton::clicked, this, &ChatDialog::copy_connect_withSec);

}
void ChatDialog::connectPub(){
        newNick = new QLabel();
         newNick->resize(621,221);
         newNick->setMaximumSize(621,221);
        newNick->setWindowTitle("Public connect");
         newNick->setTextInteractionFlags(Qt::TextSelectableByMouse);
        newNick->setStyleSheet("background-color: rgb(31, 31, 31); border-radius: 15px;");

        QLabel *text = new QLabel(newNick);
        text->setGeometry(10,30,241,50);
        text->setText("Enter token:");
        text->setStyleSheet("font: 700 14pt 'Arial';background-color: rgba(255, 255, 255, 0);color: rgb(255, 255, 255)");

        newNameLine = new QLineEdit(newNick);
        newNameLine->setGeometry(260,30,241,50);
        newNameLine->setStyleSheet("font: 700 12pt 'Arial';background-color: rgb(42, 42, 42);color: rgb(255, 255, 255);border-radius: 15px;");

        QPushButton *applybth = new QPushButton(newNick);
        applybth->setText("Connect!");
        applybth->setGeometry(220, 110, 151,50);
        applybth->setStyleSheet("border-radius: 25px;color: rgb(255, 255, 255);background-color: rgb(106, 33, 131);font: 700 14pt 'Arial';");
        connect(applybth, &QPushButton::clicked,this, &ChatDialog::on_pushButton_3_clicked);
        connect(newNameLine, &QLineEdit::returnPressed,this, &ChatDialog::on_pushButton_3_clicked);
        newNick->show();


}
void ChatDialog::on_pushButton_3_clicked()
{
    QString addr = newNameLine->text();
    newNick->hide();
    widget_3->setVisible(true);


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

    QString secWord = newWordLine->text();
    QString addr = newNameLine->text();
    newNick->hide();
    widget_3->setVisible(true);



    QByteArray decode;
    decode.append(addr);

    QString res = decode.fromBase64(decode);
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
