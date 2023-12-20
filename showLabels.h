#ifndef SHOWLABELS_H
#define SHOWLABELS_H
#include "ui_chatdialog.h"
#include "client.h"
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWebEngineWidgets/QWebEnginePage>

class Labels:public QLabel, private Ui::ChatDialog
{
   Q_OBJECT

public:
   Labels(QWidget *parent = nullptr);


public slots:
    void showChangeNick();
    void showPubToken();
    void showPriToken();
    void showMessageFromMe();
    void showMessageFromUser();
    void showAddFriend();
    void showDeleteFriend();

};

#endif
