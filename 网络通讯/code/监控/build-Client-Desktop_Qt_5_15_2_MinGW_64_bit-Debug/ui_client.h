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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEdit_ip;
    QPushButton *pushButton_connect;
    QListWidget *listWidget;
    QLineEdit *lineEdit_file;
    QPushButton *pushButton_getpic;
    QPushButton *pushButton_playback;
    QPushButton *pushButton_record;
    QPushButton *pushButton_unlock;
    QPushButton *pushButton_lock;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *label_show;

    void setupUi(QWidget *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QString::fromUtf8("Client"));
        Client->resize(658, 453);
        gridLayout_3 = new QGridLayout(Client);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox = new QGroupBox(Client);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMaximumSize(QSize(250, 16777215));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        lineEdit_ip = new QLineEdit(groupBox);
        lineEdit_ip->setObjectName(QString::fromUtf8("lineEdit_ip"));

        gridLayout_2->addWidget(lineEdit_ip, 6, 0, 1, 1);

        pushButton_connect = new QPushButton(groupBox);
        pushButton_connect->setObjectName(QString::fromUtf8("pushButton_connect"));

        gridLayout_2->addWidget(pushButton_connect, 6, 1, 1, 1);

        listWidget = new QListWidget(groupBox);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        gridLayout_2->addWidget(listWidget, 0, 0, 1, 2);

        lineEdit_file = new QLineEdit(groupBox);
        lineEdit_file->setObjectName(QString::fromUtf8("lineEdit_file"));

        gridLayout_2->addWidget(lineEdit_file, 3, 1, 1, 1);

        pushButton_getpic = new QPushButton(groupBox);
        pushButton_getpic->setObjectName(QString::fromUtf8("pushButton_getpic"));

        gridLayout_2->addWidget(pushButton_getpic, 1, 0, 1, 1);

        pushButton_playback = new QPushButton(groupBox);
        pushButton_playback->setObjectName(QString::fromUtf8("pushButton_playback"));

        gridLayout_2->addWidget(pushButton_playback, 3, 0, 1, 1);

        pushButton_record = new QPushButton(groupBox);
        pushButton_record->setObjectName(QString::fromUtf8("pushButton_record"));

        gridLayout_2->addWidget(pushButton_record, 1, 1, 1, 1);

        pushButton_unlock = new QPushButton(groupBox);
        pushButton_unlock->setObjectName(QString::fromUtf8("pushButton_unlock"));

        gridLayout_2->addWidget(pushButton_unlock, 5, 1, 1, 1);

        pushButton_lock = new QPushButton(groupBox);
        pushButton_lock->setObjectName(QString::fromUtf8("pushButton_lock"));

        gridLayout_2->addWidget(pushButton_lock, 5, 0, 1, 1);


        horizontalLayout->addWidget(groupBox);


        horizontalLayout_2->addLayout(horizontalLayout);

        scrollArea = new QScrollArea(Client);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1102, 406));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_show = new QLabel(scrollAreaWidgetContents);
        label_show->setObjectName(QString::fromUtf8("label_show"));
        label_show->setMinimumSize(QSize(1080, 0));

        gridLayout->addWidget(label_show, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_2->addWidget(scrollArea);


        gridLayout_3->addLayout(horizontalLayout_2, 0, 0, 1, 1);


        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QWidget *Client)
    {
        Client->setWindowTitle(QCoreApplication::translate("Client", "Client", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Client", "\347\233\221\346\216\247\345\210\227\350\241\250", nullptr));
        pushButton_connect->setText(QCoreApplication::translate("Client", "\350\277\236\346\216\245\346\234\215\345\212\241\345\231\250", nullptr));
        pushButton_getpic->setText(QCoreApplication::translate("Client", "\346\210\252\345\233\276", nullptr));
        pushButton_playback->setText(QCoreApplication::translate("Client", "\345\233\236\346\224\276", nullptr));
        pushButton_record->setText(QCoreApplication::translate("Client", "\345\275\225\345\203\217", nullptr));
        pushButton_unlock->setText(QCoreApplication::translate("Client", "\350\247\243\351\224\201\351\274\240\346\240\207", nullptr));
        pushButton_lock->setText(QCoreApplication::translate("Client", "\351\224\201\345\256\232\351\274\240\346\240\207", nullptr));
        label_show->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
