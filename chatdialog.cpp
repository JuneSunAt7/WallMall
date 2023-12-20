/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWebEngineWidgets/QWebEnginePage>
#include "chatdialog.h"
#include <QDate>
// TODO review code
ChatDialog::ChatDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    lineEdit->setFocusPolicy(Qt::StrongFocus);
    textEdit->setFocusPolicy(Qt::NoFocus);
    textEdit->setReadOnly(true);
    listWidget->setFocusPolicy(Qt::NoFocus);
    widget_3->setVisible(false);

    connect(lineEdit, &QLineEdit::returnPressed,
            this, &ChatDialog::on_lineEdit_returnPressed);
    connect(&client, &Client::newMessage,
            this, &ChatDialog::appendMessage);
    connect(&client, &Client::newParticipant,
            this, &ChatDialog::newParticipant);
    connect(&client, &Client::participantLeft,
            this, &ChatDialog::participantLeft);

    myNickName = client.nickName();
    newParticipant(myNickName);
    tableFormat.setBorder(0);

    QMenuBar *menu = new QMenuBar(this);
    menu->setStyleSheet("background-color: rgb(31, 31, 31);;font: 24pt 'Segoe UI Historic';color: rgb(35, 35, 71);min-width:50; min-height:50;");


    QMenu *settingsMenu = new QMenu(tr("Settings"), this);
    settingsMenu->setIcon(QIcon("icons/iconsettings.png"));
    settingsMenu->setStyleSheet("background-color: rgb(61, 61, 61);;font:16pt'Sergoe UI Historic';color: rgb(255,255,255)");


    QMenu *tokenMenu = new QMenu(tr("Token"), this);
    tokenMenu->setIcon(QIcon("icons/tokenIcon.png"));
    tokenMenu->setStyleSheet("background-color: rgb(61, 61, 61);font:16pt'Sergoe UI Historic';color: rgb(255,255,255)");


    QMenu *connectionMenu = new QMenu(tr("Connection"), this);
    connectionMenu->setIcon(QIcon("icons/connectIcon.png"));
    connectionMenu->setStyleSheet("background-color: rgb(61, 61, 61);font:16pt'Sergoe UI Historic';color: rgb(255,255,255)");


    QAction *generateToken = tokenMenu->addAction(tr("Generate private token"));
    generateToken->setIcon(QIcon("icons/privateTokenIcon.png"));
    connect(generateToken, &QAction::triggered, this, &ChatDialog::genTokenAction);

    QAction *genPublicToken = tokenMenu->addAction(tr("Generate public token"));
    genPublicToken->setIcon(QIcon("icons/publicTokenIcon.png"));
    connect(genPublicToken, &QAction::triggered, this, &ChatDialog::genPubTokenAction);

    QAction *addToken = tokenMenu->addAction(tr("Add token"));
    addToken->setIcon(QIcon("icons/addToken.png"));
    connect(addToken, &QAction::triggered, this, &ChatDialog::addTokenAction);

    QAction *deleteToken = tokenMenu->addAction(tr("Delete token"));
    deleteToken->setIcon(QIcon("icons/delToken.png"));
    connect(deleteToken, &QAction::triggered, this, &ChatDialog::delTokenAction);


    QAction *chNickAction = settingsMenu->addAction(tr("Nickname"));
    connect(chNickAction, &QAction::triggered, this, &ChatDialog::setNickname);
    chNickAction->setIcon(QIcon("icons/nickIcon.png"));

    QAction *browser = settingsMenu->addAction(tr("Search"));
    connect(browser, &QAction::triggered, this, &ChatDialog::on_pushButton_4_clicked);
    browser->setIcon(QIcon("icons/iconsearch.png"));

    QAction *connectPriUser = connectionMenu->addAction(tr("Connect with private token"));
    connectPriUser->setIcon(QIcon("icons/priConnect.png"));
    connect(connectPriUser, &QAction::triggered, this, &ChatDialog::connectPri);

    QAction *connectPubUser = connectionMenu->addAction(tr("Connect with public token"));
    connectPubUser->setIcon(QIcon("icons/pubConnect.png"));
    connect(connectPubUser, &QAction::triggered, this, &ChatDialog::connectPub);

    menu->addMenu(settingsMenu);
    menu->addMenu(tokenMenu);
    menu->addMenu(connectionMenu);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menu);
    setLayout(mainLayout);

    QColor color = textEdit->textColor();
    textEdit->setTextColor(Qt::white);
    textEdit->setTextColor(color);

    bindWithTokens();
    QTextCursor cursor( textEdit->textCursor() );

    QTextCharFormat format;
    format.setFontWeight( QFont::Bold );
    format.setForeground( QBrush( QColor( "white" ) ) );
    cursor.setCharFormat( format );


    appendMessage(" ", "                                                                                           Today");

ready();
lineEdit->setPlaceholderText("   Message...");

}
void ChatDialog::ready(){

    QFile   *tokenF = new QFile("names.tk");
    tokenF->open(QFile::ReadOnly);
    if(tokenF->isOpen()){

    QStringList tokens;
    while(!tokenF->atEnd()){
        newParticipant(tokenF->readLine());
    }
    tokenF->close();

    }
    else{
        return;
   }
}
void ChatDialog::appendMessage(const QString &from, const QString &message)
{


    widget_3->setVisible(false);


    history = new QFile("QWidgets.hs");
    history->open(QFile::Append);

    QString currTime = QTime::currentTime().toString("hh:mm");

    if (from.isEmpty() || message.isEmpty())
        return;
    if (from == myNickName){

        QColor myMess(106, 33, 131);


        QTextCharFormat nickFormat;
        nickFormat.setForeground(Qt::white);
        nickFormat.setFontWeight(QFont::Bold);

        QTextCursor cursor(textEdit->textCursor());
        cursor.movePosition(QTextCursor::Right);

        QTextTableFormat tableFormat;


        tableFormat.setBackground(QBrush(myMess));


        tableFormat.setMargin(15);
        tableFormat.setWidth(700);
        tableFormat.setBorder(0);

        tableFormat.setAlignment(Qt::AlignRight);
        tableFormat.setCellPadding(10);

        QTextTable *table = cursor.insertTable(1, 1, tableFormat);

        QTextTableCell fromCell = table->cellAt(0, 0);

        fromCell.setFormat(nickFormat);
        fromCell.firstCursorPosition().insertText(from + " : " +currTime + "\n" + message);


        QScrollBar *bar = textEdit->verticalScrollBar();
        bar->setValue(bar->maximum());
    }else if(message == "                                                                                           Today"){
        QTextCharFormat nickFormat;
          nickFormat.setForeground(Qt::white);
          nickFormat.setFontWeight(QFont::Light);

          // Print who & when
          QTextCursor cursor(textEdit->textCursor());
          cursor.movePosition(QTextCursor::End);
          QTextTableFormat tableFormat;
          tableFormat.setBorder(0);
          QTextTable *table = cursor.insertTable(1, 1, tableFormat);


          QTextTableCell fromCell = table->cellAt(0, 0);
          fromCell.setFormat(nickFormat);
          fromCell.firstCursorPosition().insertText(from);

          // Print what
          QTextCursor nextCursor(textEdit->textCursor());
          nextCursor.movePosition(QTextCursor::End);
          table = nextCursor.insertTable(1, 1, tableFormat);
          table->cellAt(0, 0).firstCursorPosition().insertText(message);


          QScrollBar *bar = textEdit->verticalScrollBar();
          bar->setValue(bar->maximum());
}else{
        QColor ourMess(53,51,184);

        QTextCharFormat nickFormat;
        nickFormat.setForeground(Qt::white);
        nickFormat.setFontWeight(QFont::Bold);


        QTextCursor cursor(textEdit->textCursor());
        cursor.movePosition(QTextCursor::Right);

        QTextTableFormat tableFormat;
        tableFormat.setBackground(QBrush(ourMess));

        tableFormat.setMargin(10);
        tableFormat.setBorder(0);
        tableFormat.setWidth(700);
        tableFormat.setAlignment(Qt::AlignLeft);


        QTextTable *table = cursor.insertTable(1, 1, tableFormat);


        QTextTableCell fromCell = table->cellAt(0, 0);

        fromCell.setFormat(nickFormat);
        fromCell.firstCursorPosition().insertText(from + " : " +currTime + "\n" + message);


        QScrollBar *bar = textEdit->verticalScrollBar();
        bar->setValue(bar->maximum());
    }


    history->write(( from+": "+currTime+ "       " + message + "\n").toUtf8());
    history->close();


}


void ChatDialog::newParticipant(const QString &nick)
{

    widget_3->setVisible(false);

    if (nick.isEmpty())
        return;

    if(nick == myNickName)
        return;
    QList<QListWidgetItem*> itemsToRemove;

    for (int i = 0; i < listWidget->count(); ++i) {
        QListWidgetItem* currentItem = listWidget->item(i);
        if (currentItem->text() == nick) {
            return;
        }
    }



    listWidget->addItem(nick);
    listWidget->setStyleSheet("font: 14pt 'Segoe UI Historic';color: #4dff00;background-color: rgb(31, 31, 31);border-radius:15px;");
}

void ChatDialog::participantLeft(const QString &nick)
{

    widget_3->setVisible(false);


    if (nick.isEmpty())
        return;

    QList<QListWidgetItem *> items = listWidget->findItems(nick,
                                                           Qt::MatchExactly);
    if (items.isEmpty())
        return;

    delete items.at(0);
    QColor color = textEdit->textColor();
    textEdit->setTextColor(Qt::red);
    textEdit->append(tr("                                                                                %1 has left").arg(nick));
    textEdit->setTextColor(color);
}


void ChatDialog::on_pushButton_4_clicked()
{

    view = new QWebEngineView;
    view->load(QUrl("https://duckduckgo.com/"));
    view->showNormal();
}


void ChatDialog::on_lineEdit_returnPressed()
{

    widget_3->setVisible(false);


    QString text = lineEdit->text();
    if (text.isEmpty())
        return;

    if (text.startsWith(QChar('/'))) {
        QColor color = textEdit->textColor();
        textEdit->setTextColor(Qt::red);
        textEdit->append(tr("! Unknown command: %1")
                         .arg(text.left(text.indexOf(' '))));
        textEdit->setTextColor(color);
    } else {
        client.sendMessage(text);
        appendMessage(myNickName, text);
    }

    lineEdit->clear();
}


void ChatDialog::on_sendMess_clicked()
{
    QString text = lineEdit->text();
    if (text.isEmpty())
        return;

    if (text.startsWith(QChar('/'))) {
        QColor color = textEdit->textColor();
        textEdit->setTextColor(Qt::red);
        textEdit->append(tr("! Unknown command: %1")
                         .arg(text.left(text.indexOf(' '))));
        textEdit->setTextColor(color);
    } else {
        client.sendMessage(text);
        appendMessage(myNickName, text);
    }

    lineEdit->clear();
}

