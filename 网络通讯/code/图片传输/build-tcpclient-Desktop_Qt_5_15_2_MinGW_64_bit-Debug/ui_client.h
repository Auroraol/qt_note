/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QLabel *clientStatusLabel;
    QPushButton *openButton;
    QPushButton *sendButton;
    QPushButton *connectButton;
    QLabel *label_3;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *portLineEdit;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *hostLineEdit;

    void setupUi(QDialog *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QString::fromUtf8("Client"));
        Client->resize(400, 188);
        clientStatusLabel = new QLabel(Client);
        clientStatusLabel->setObjectName(QString::fromUtf8("clientStatusLabel"));
        clientStatusLabel->setGeometry(QRect(30, 130, 331, 41));
        openButton = new QPushButton(Client);
        openButton->setObjectName(QString::fromUtf8("openButton"));
        openButton->setGeometry(QRect(290, 60, 75, 23));
        sendButton = new QPushButton(Client);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setGeometry(QRect(290, 100, 75, 23));
        connectButton = new QPushButton(Client);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));
        connectButton->setGeometry(QRect(290, 23, 80, 23));
        label_3 = new QLabel(Client);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(120, 0, 161, 31));
        widget = new QWidget(Client);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(30, 100, 172, 26));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        portLineEdit = new QLineEdit(widget);
        portLineEdit->setObjectName(QString::fromUtf8("portLineEdit"));

        horizontalLayout->addWidget(portLineEdit);

        widget1 = new QWidget(Client);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(30, 40, 172, 26));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget1);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        hostLineEdit = new QLineEdit(widget1);
        hostLineEdit->setObjectName(QString::fromUtf8("hostLineEdit"));

        horizontalLayout_2->addWidget(hostLineEdit);


        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QDialog *Client)
    {
        Client->setWindowTitle(QCoreApplication::translate("Client", "Client", nullptr));
        clientStatusLabel->setText(QCoreApplication::translate("Client", "\347\212\266\346\200\201\357\274\232\347\255\211\345\276\205\346\211\223\345\274\200\346\226\207\344\273\266\357\274\201", nullptr));
        openButton->setText(QCoreApplication::translate("Client", "\346\211\223  \345\274\200", nullptr));
        sendButton->setText(QCoreApplication::translate("Client", "\345\217\221  \351\200\201", nullptr));
        connectButton->setText(QCoreApplication::translate("Client", "\350\277\236\346\216\245", nullptr));
        label_3->setText(QCoreApplication::translate("Client", "\345\256\242\346\210\267\347\253\257(\350\264\237\350\264\243\345\217\221\345\233\276\347\211\207)", nullptr));
        label_2->setText(QCoreApplication::translate("Client", "\347\253\257\345\217\243\357\274\232", nullptr));
        portLineEdit->setPlaceholderText(QCoreApplication::translate("Client", "6666", nullptr));
        label->setText(QCoreApplication::translate("Client", "\344\270\273\346\234\272\357\274\232", nullptr));
        hostLineEdit->setPlaceholderText(QCoreApplication::translate("Client", "127.0.0.1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
