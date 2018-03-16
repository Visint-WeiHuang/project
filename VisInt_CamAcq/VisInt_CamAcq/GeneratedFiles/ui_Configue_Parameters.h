/********************************************************************************
** Form generated from reading UI file 'Configue_Parameters.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGUE_PARAMETERS_H
#define UI_CONFIGUE_PARAMETERS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Configue_Parameters
{
public:
    QPushButton *BnLoadConfigureFile;
    QPushButton *BnPicSavePath;

    void setupUi(QDialog *Configue_Parameters)
    {
        if (Configue_Parameters->objectName().isEmpty())
            Configue_Parameters->setObjectName(QStringLiteral("Configue_Parameters"));
        Configue_Parameters->resize(544, 432);
        BnLoadConfigureFile = new QPushButton(Configue_Parameters);
        BnLoadConfigureFile->setObjectName(QStringLiteral("BnLoadConfigureFile"));
        BnLoadConfigureFile->setGeometry(QRect(40, 30, 141, 23));
        BnPicSavePath = new QPushButton(Configue_Parameters);
        BnPicSavePath->setObjectName(QStringLiteral("BnPicSavePath"));
        BnPicSavePath->setGeometry(QRect(40, 70, 141, 23));

        retranslateUi(Configue_Parameters);

        QMetaObject::connectSlotsByName(Configue_Parameters);
    } // setupUi

    void retranslateUi(QDialog *Configue_Parameters)
    {
        Configue_Parameters->setWindowTitle(QApplication::translate("Configue_Parameters", "Configue_Parameters", Q_NULLPTR));
        BnLoadConfigureFile->setText(QApplication::translate("Configue_Parameters", "\345\212\240\350\275\275\351\205\215\347\275\256\346\226\207\344\273\266", Q_NULLPTR));
        BnPicSavePath->setText(QApplication::translate("Configue_Parameters", "\351\200\211\346\213\251\345\233\276\347\211\207\344\277\235\345\255\230\350\267\257\345\276\204", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Configue_Parameters: public Ui_Configue_Parameters {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGUE_PARAMETERS_H
