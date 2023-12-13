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


    label_3->setVisible(false);
    lineEdit_2->setVisible(false);
    ApplyBth->setVisible(false);
    widget->setVisible(false);
    widget_2->setVisible(false);
    widget_3->setVisible(false);
    widget_4->setVisible(false);

    label_7->setVisible(false);

    lineEdit_5->setVisible(false);



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
    menu->setStyleSheet("background-color: rgb(210, 224, 251);font: 24pt 'Segoe UI Historic';color: rgb(35, 35, 71);min-width:50; min-height:50;");

    //menu->minimumSize();


    QMenu *settingsMenu = new QMenu(tr("Settings"), this);
    settingsMenu->setIcon(QIcon("icons/iconsettings.png"));
    settingsMenu->setStyleSheet("background-color: rgb(210, 224, 251);font:16pt'Sergoe UI Historic';color rgb(20,20,20)");


    QMenu *tokenMenu = new QMenu(tr("Token"), this);
    tokenMenu->setIcon(QIcon("icons/tokenIcon.png"));
    tokenMenu->setStyleSheet("background-color: rgb(210, 224, 251);font:16pt'Sergoe UI Historic';color rgb(20,20,20)");


    QMenu *connectionMenu = new QMenu(tr("Connection"), this);
    connectionMenu->setIcon(QIcon("icons/connectIcon.png"));
    connectionMenu->setStyleSheet("background-color: rgb(210, 224, 251);font:16pt'Sergoe UI Historic';color rgb(20,20,20)");


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

    QAction *clearHist = settingsMenu->addAction(tr("Clear history"));
    connect(clearHist, &QAction::triggered, this, &ChatDialog::clearHist);
    clearHist->setIcon(QIcon("icons/clearHist.png"));

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

    history = new QFile("QWidgets.hs");

    history->open(QFile::ReadOnly);

    QTextCursor cursor( textEdit->textCursor() );

    QTextCharFormat format;
    format.setFontWeight( QFont::Serif );
    format.setForeground( QBrush( QColor( "teal" ) ) );
    cursor.setCharFormat( format );

    cursor.insertText( " "+ history->readAll() );


    history->close();


    appendMessage("Today  date ", QDate::currentDate().toString());


}

void ChatDialog::appendMessage(const QString &from, const QString &message)
{
    label_3->setVisible(false);
    lineEdit_2->setVisible(false);
    ApplyBth->setVisible(false);
    widget->setVisible(false);
    widget_2->setVisible(false);
    widget_3->setVisible(false);
    widget_4->setVisible(false);

    label_7->setVisible(false);

    lineEdit_5->setVisible(false);

    history = new QFile("QWidgets.hs");
    history->open(QFile::Append);

    QString currTime = QTime::currentTime().toString("hh:mm");

    if (from.isEmpty() || message.isEmpty())
        return;
    if (from == myNickName){
        QColor color = textEdit->textColor();
        textEdit->setTextColor(Qt::cyan);
        textEdit->setTextColor(color);
    }

    QTextCursor cursor(textEdit->textCursor());
    cursor.movePosition(QTextCursor::End);
    QTextTable *table = cursor.insertTable(2, 2, tableFormat);
    table->cellAt(0, 0).firstCursorPosition().insertText(from+ ": "+ currTime + "       " );
    table->cellAt(0, 1).firstCursorPosition().insertText(message);
    QScrollBar *bar = textEdit->verticalScrollBar();
    bar->setValue(bar->maximum());

    history->write(( from+": "+currTime+ "       " + message + "\n").toUtf8());
    history->close();



}


void ChatDialog::newParticipant(const QString &nick)
{
    label_3->setVisible(false);
    lineEdit_2->setVisible(false);
    ApplyBth->setVisible(false);
    widget->setVisible(false);
    widget_2->setVisible(false);
    widget_3->setVisible(false);
    widget_4->setVisible(false);

    label_7->setVisible(false);

    lineEdit_5->setVisible(false);
    if (nick.isEmpty())
        return;

    if(nick == myNickName)
        return;


    QColor color = textEdit->textColor();
    textEdit->setTextColor(Qt::green);
    textEdit->append(tr("                                      %1 has joined").arg(nick));
    textEdit->setTextColor(color);
    listWidget->addItem(nick);
}

void ChatDialog::participantLeft(const QString &nick)
{
    label_3->setVisible(false);
    lineEdit_2->setVisible(false);
    ApplyBth->setVisible(false);
    widget->setVisible(false);
    widget_2->setVisible(false);
    widget_3->setVisible(false);
    widget_4->setVisible(false);

    label_7->setVisible(false);

    lineEdit_5->setVisible(false);

    if (nick.isEmpty())
        return;

    QList<QListWidgetItem *> items = listWidget->findItems(nick,
                                                           Qt::MatchExactly);
    if (items.isEmpty())
        return;

    delete items.at(0);
    QColor color = textEdit->textColor();
    textEdit->setTextColor(Qt::red);
    textEdit->append(tr("                                        %1 has left").arg(nick));
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
    label_3->setVisible(false);
    lineEdit_2->setVisible(false);
    ApplyBth->setVisible(false);
    widget->setVisible(false);
    widget_2->setVisible(false);
    widget_3->setVisible(false);
    widget_4->setVisible(false);

    label_7->setVisible(false);

    lineEdit_5->setVisible(false);

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





