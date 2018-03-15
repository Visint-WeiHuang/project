/********************************************************************************
** Form generated from reading UI file 'visint_camacq.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VISINT_CAMACQ_H
#define UI_VISINT_CAMACQ_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VisInt_CamAcqClass
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QPushButton *BtInit;
    QPushButton *BtConfig;
    QPushButton *BtFreez;
    QPushButton *BtStartGrap;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *VisInt_CamAcqClass)
    {
        if (VisInt_CamAcqClass->objectName().isEmpty())
            VisInt_CamAcqClass->setObjectName(QStringLiteral("VisInt_CamAcqClass"));
        VisInt_CamAcqClass->resize(600, 400);
        centralWidget = new QWidget(VisInt_CamAcqClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 251, 301));
        BtInit = new QPushButton(groupBox);
        BtInit->setObjectName(QStringLiteral("BtInit"));
        BtInit->setGeometry(QRect(10, 30, 91, 51));
        BtConfig = new QPushButton(groupBox);
        BtConfig->setObjectName(QStringLiteral("BtConfig"));
        BtConfig->setGeometry(QRect(10, 100, 91, 51));
        BtFreez = new QPushButton(groupBox);
        BtFreez->setObjectName(QStringLiteral("BtFreez"));
        BtFreez->setGeometry(QRect(10, 240, 91, 51));
        BtStartGrap = new QPushButton(groupBox);
        BtStartGrap->setObjectName(QStringLiteral("BtStartGrap"));
        BtStartGrap->setGeometry(QRect(10, 170, 91, 51));
        VisInt_CamAcqClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(VisInt_CamAcqClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        VisInt_CamAcqClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(VisInt_CamAcqClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        VisInt_CamAcqClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(VisInt_CamAcqClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        VisInt_CamAcqClass->setStatusBar(statusBar);

        retranslateUi(VisInt_CamAcqClass);

        QMetaObject::connectSlotsByName(VisInt_CamAcqClass);
    } // setupUi

    void retranslateUi(QMainWindow *VisInt_CamAcqClass)
    {
        VisInt_CamAcqClass->setWindowTitle(QApplication::translate("VisInt_CamAcqClass", "VisInt_CamAcq", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("VisInt_CamAcqClass", "GroupBox", Q_NULLPTR));
        BtInit->setText(QApplication::translate("VisInt_CamAcqClass", "\345\210\235\345\247\213\345\214\226", Q_NULLPTR));
        BtConfig->setText(QApplication::translate("VisInt_CamAcqClass", "\350\256\276\347\275\256\345\217\202\346\225\260", Q_NULLPTR));
        BtFreez->setText(QApplication::translate("VisInt_CamAcqClass", "\345\201\234\346\255\242\351\207\207\351\233\206", Q_NULLPTR));
        BtStartGrap->setText(QApplication::translate("VisInt_CamAcqClass", "\345\274\200\345\247\213\351\207\207\351\233\206", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class VisInt_CamAcqClass: public Ui_VisInt_CamAcqClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VISINT_CAMACQ_H
