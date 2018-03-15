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

QT_BEGIN_NAMESPACE

class Ui_Configue_Parameters
{
public:

    void setupUi(QDialog *Configue_Parameters)
    {
        if (Configue_Parameters->objectName().isEmpty())
            Configue_Parameters->setObjectName(QStringLiteral("Configue_Parameters"));
        Configue_Parameters->resize(400, 300);

        retranslateUi(Configue_Parameters);

        QMetaObject::connectSlotsByName(Configue_Parameters);
    } // setupUi

    void retranslateUi(QDialog *Configue_Parameters)
    {
        Configue_Parameters->setWindowTitle(QApplication::translate("Configue_Parameters", "Configue_Parameters", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Configue_Parameters: public Ui_Configue_Parameters {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGUE_PARAMETERS_H
