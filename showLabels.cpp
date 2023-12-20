#include "showLabels.h"
#include "chatdialog.h"
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

void Labels::showChangeNick(){
    QLabel *nickLbl = new QLabel;
     nickLbl->resize(700, 470);
     nickLbl->setWindowTitle("Change nickname");
     nickLbl->setTextInteractionFlags(Qt::TextSelectableByMouse);
    nickLbl->setStyleSheet("background-color: rgb(31, 31, 31); border-radius: 15px;");

    QLabel *text = new QLabel(nickLbl);
    text->setGeometry(10,30,241,50);
    text->setText("Your new nickname:");
    text->setStyleSheet("font: 700 14pt 'Arial';background-color: rgba(255, 255, 255, 0);color: rgb(255, 255, 255)");

    QLineEdit *newNameLine = new QLineEdit(nickLbl);
    newNameLine->setGeometry(260,30,241,50);
    newNameLine->setStyleSheet("font: 700 12pt 'Arial';background-color: rgb(42, 42, 42);color: rgb(255, 255, 255);border-radius: 15px;");

    QPushButton *applybth = new QPushButton(nickLbl);
    applybth->setText("Apply");
    applybth->setGeometry(220, 110, 151,50);
    applybth->setStyleSheet("border-radius: 25px;color: rgb(255, 255, 255);background-color: rgb(106, 33, 131);font: 700 14pt 'Arial';");
    connect(ApplyBth, &QPushButton::clicked,this, &ChatDialog::saveName);
    connect(lineEdit_2, &QLineEdit::returnPressed,this, &ChatDialog::saveName);

    nickLbl->show();

}
