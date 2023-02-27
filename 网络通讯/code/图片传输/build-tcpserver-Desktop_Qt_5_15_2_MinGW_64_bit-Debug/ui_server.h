/********************************************************************************
** Form generated from reading UI file 'server.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVER_H
#define UI_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Server
{
public:
    QLabel *serverStatusLabel;
    QPushButton *startButton;
    QLabel *imageLabel;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *portLineEdit;
    QLabel *label_2;

    void setupUi(QDialog *Server)
    {
        if (Server->objectName().isEmpty())
            Server->setObjectName(QString::fromUtf8("Server"));
        Server->resize(671, 439);
        serverStatusLabel = new QLabel(Server);
        serverStatusLabel->setObjectName(QString::fromUtf8("serverStatusLabel"));
        serverStatusLabel->setGeometry(QRect(20, 400, 301, 16));
        startButton = new QPushButton(Server);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setGeometry(QRect(570, 400, 75, 23));
        imageLabel = new QLabel(Server);
        imageLabel->setObjectName(QString::fromUtf8("imageLabel"));
        imageLabel->setGeometry(QRect(10, 50, 641, 331));
        layoutWidget = new QWidget(Server);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(360, 400, 185, 26));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        portLineEdit = new QLineEdit(layoutWidget);
        portLineEdit->setObjectName(QString::fromUtf8("portLineEdit"));

        horizontalLayout->addWidget(portLineEdit);

        label_2 = new QLabel(Server);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(265, 10, 181, 31));

        retranslateUi(Server);

        QMetaObject::connectSlotsByName(Server);
    } // setupUi

    void retranslateUi(QDialog *Server)
    {
        Server->setWindowTitle(QCoreApplication::translate("Server", "Server", nullptr));
        serverStatusLabel->setText(QCoreApplication::translate("Server", "\346\234\215\345\212\241\345\231\250\347\212\266\346\200\201\346\230\276\347\244\272", nullptr));
        startButton->setText(QCoreApplication::translate("Server", "\347\233\221\345\220\254", nullptr));
        imageLabel->setText(QCoreApplication::translate("Server", "\345\233\276\347\211\207\346\230\276\347\244\272\344\275\215\347\275\256", nullptr));
        label->setText(QCoreApplication::translate("Server", "\347\233\221\345\220\254\347\253\257\345\217\243", nullptr));
        label_2->setText(QCoreApplication::translate("Server", "\346\234\215\345\212\241\345\231\250\347\253\257(\350\264\237\350\264\243\346\230\276\347\244\272\345\233\276\347\211\207)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Server: public Ui_Server {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_H
