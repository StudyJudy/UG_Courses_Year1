/********************************************************************************
** Form generated from reading UI file 'tetrishomework.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TETRISHOMEWORK_H
#define UI_TETRISHOMEWORK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(800, 600);
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(40, 20, 111, 51));
        pushButton->setContextMenuPolicy(Qt::DefaultContextMenu);
        pushButton->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"font: 16pt \"Comic Sans MS\";"));
        pushButton_2 = new QPushButton(Widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(170, 20, 111, 51));
        pushButton_2->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"font: 16pt \"Comic Sans MS\";"));
        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(300, 20, 111, 51));
        label->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgb(241, 199, 255);\n"
"selection-background-color: rgb(230, 220, 200);\n"
"font: 16pt \"Comic Sans MS\";"));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(430, 20, 111, 51));
        label_2->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgb(172, 212, 255);\n"
"selection-background-color: rgb(230, 220, 200);\n"
"font: 16pt \"Comic Sans MS\";"));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Widget", "stop", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("Widget", "start", Q_NULLPTR));
        label->setText(QApplication::translate("Widget", "  Time", Q_NULLPTR));
        label_2->setText(QApplication::translate("Widget", " Score", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TETRISHOMEWORK_H
