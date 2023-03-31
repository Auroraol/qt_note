/********************************************************************************
** Form generated from reading UI file 'snakegame.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SNAKEGAME_H
#define UI_SNAKEGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SnakeGame
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QLabel *label_12;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_10;
    QLabel *isRun;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_9;
    QLabel *label_score;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_7;
    QLabel *label_speed;
    QHBoxLayout *horizontalLayout;
    QLabel *label_8;
    QLabel *label_food;

    void setupUi(QWidget *SnakeGame)
    {
        if (SnakeGame->objectName().isEmpty())
            SnakeGame->setObjectName(QString::fromUtf8("SnakeGame"));
        SnakeGame->resize(1002, 585);
        gridLayout = new QGridLayout(SnakeGame);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(799, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        widget = new QWidget(SnakeGame);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(200, 0));
        widget->setMaximumSize(QSize(200, 16777215));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_12 = new QLabel(widget);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_2->addWidget(label_12, 2, 0, 1, 2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setWordWrap(false);

        verticalLayout->addWidget(label_3);


        gridLayout_2->addLayout(verticalLayout, 3, 0, 1, 2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_10 = new QLabel(widget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_4->addWidget(label_10);

        isRun = new QLabel(widget);
        isRun->setObjectName(QString::fromUtf8("isRun"));
        isRun->setStyleSheet(QString::fromUtf8("background-color: rgb(209, 209, 209);"));

        horizontalLayout_4->addWidget(isRun);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_9 = new QLabel(widget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_3->addWidget(label_9);

        label_score = new QLabel(widget);
        label_score->setObjectName(QString::fromUtf8("label_score"));
        label_score->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_score);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_7 = new QLabel(widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_2->addWidget(label_7);

        label_speed = new QLabel(widget);
        label_speed->setObjectName(QString::fromUtf8("label_speed"));

        horizontalLayout_2->addWidget(label_speed);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_8 = new QLabel(widget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout->addWidget(label_8);

        label_food = new QLabel(widget);
        label_food->setObjectName(QString::fromUtf8("label_food"));

        horizontalLayout->addWidget(label_food);


        verticalLayout_3->addLayout(horizontalLayout);


        gridLayout_2->addLayout(verticalLayout_3, 1, 0, 1, 2);


        gridLayout->addWidget(widget, 0, 1, 1, 1);


        retranslateUi(SnakeGame);

        QMetaObject::connectSlotsByName(SnakeGame);
    } // setupUi

    void retranslateUi(QWidget *SnakeGame)
    {
        SnakeGame->setWindowTitle(QCoreApplication::translate("SnakeGame", "\350\264\252\345\220\203\350\233\207", nullptr));
        label_12->setText(QString());
        label->setText(QCoreApplication::translate("SnakeGame", "Snake Game V1.0", nullptr));
        label_2->setText(QCoreApplication::translate("SnakeGame", "Create by L, 2023-01-2", nullptr));
        label_3->setText(QCoreApplication::translate("SnakeGame", "<html><head/><body><p><span style=\" font-size:7pt;\">\350\247\204\345\210\231\357\274\232</span></p><p><span style=\" font-size:7pt;\">1. \346\214\211\347\251\272\346\240\274\351\224\256\346\232\202\345\201\234</span></p><p><span style=\" font-size:7pt;\">2. \344\275\277\347\224\250\346\226\271\345\220\221\351\224\256\346\210\226wasd\347\247\273\345\212\250</span></p><p><span style=\" font-size:7pt;\">3. \351\225\277\346\214\211\346\226\271\345\220\221\351\224\256\345\217\257\345\212\240\351\200\237</span></p><p><span style=\" font-size:7pt;\">4. \347\242\260\345\210\260\350\207\252\350\272\253\346\210\226\347\242\260\345\210\260\350\276\271\347\225\214\346\270\270\346\210\217\347\273\223\346\235\237</span></p></body></html>", nullptr));
        label_10->setText(QCoreApplication::translate("SnakeGame", "\346\270\270\346\210\217\347\212\266\346\200\201:", nullptr));
        isRun->setText(QString());
        label_9->setText(QCoreApplication::translate("SnakeGame", "\346\270\270\346\210\217\345\276\227\345\210\206:", nullptr));
        label_score->setText(QCoreApplication::translate("SnakeGame", "0", nullptr));
        label_7->setText(QCoreApplication::translate("SnakeGame", "\347\247\273\345\212\250\351\200\237\345\272\246:", nullptr));
        label_speed->setText(QCoreApplication::translate("SnakeGame", "20", nullptr));
        label_8->setText(QCoreApplication::translate("SnakeGame", "\351\232\217\346\234\272\351\243\237\347\211\251:", nullptr));
        label_food->setText(QCoreApplication::translate("SnakeGame", "5", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SnakeGame: public Ui_SnakeGame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SNAKEGAME_H
