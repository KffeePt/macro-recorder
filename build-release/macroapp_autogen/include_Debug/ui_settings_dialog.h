/********************************************************************************
** Form generated from reading UI file 'settings_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_DIALOG_H
#define UI_SETTINGS_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *appearanceGroup;
    QHBoxLayout *horizontalLayout;
    QLabel *themeLabel;
    QComboBox *themeComboBox;
    QGroupBox *behaviorGroup;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *startupCheckBox;
    QCheckBox *trayCheckBox;
    QCheckBox *disableMouseMovementCheckBox;
    QCheckBox *disableMouseClicksCheckBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName("SettingsDialog");
        SettingsDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(SettingsDialog);
        verticalLayout->setObjectName("verticalLayout");
        appearanceGroup = new QGroupBox(SettingsDialog);
        appearanceGroup->setObjectName("appearanceGroup");
        horizontalLayout = new QHBoxLayout(appearanceGroup);
        horizontalLayout->setObjectName("horizontalLayout");
        themeLabel = new QLabel(appearanceGroup);
        themeLabel->setObjectName("themeLabel");

        horizontalLayout->addWidget(themeLabel);

        themeComboBox = new QComboBox(appearanceGroup);
        themeComboBox->addItem(QString());
        themeComboBox->addItem(QString());
        themeComboBox->addItem(QString());
        themeComboBox->setObjectName("themeComboBox");

        horizontalLayout->addWidget(themeComboBox);


        verticalLayout->addWidget(appearanceGroup);

        behaviorGroup = new QGroupBox(SettingsDialog);
        behaviorGroup->setObjectName("behaviorGroup");
        verticalLayout_2 = new QVBoxLayout(behaviorGroup);
        verticalLayout_2->setObjectName("verticalLayout_2");
        startupCheckBox = new QCheckBox(behaviorGroup);
        startupCheckBox->setObjectName("startupCheckBox");

        verticalLayout_2->addWidget(startupCheckBox);

        trayCheckBox = new QCheckBox(behaviorGroup);
        trayCheckBox->setObjectName("trayCheckBox");

        verticalLayout_2->addWidget(trayCheckBox);

        disableMouseMovementCheckBox = new QCheckBox(behaviorGroup);
        disableMouseMovementCheckBox->setObjectName("disableMouseMovementCheckBox");

        verticalLayout_2->addWidget(disableMouseMovementCheckBox);

        disableMouseClicksCheckBox = new QCheckBox(behaviorGroup);
        disableMouseClicksCheckBox->setObjectName("disableMouseClicksCheckBox");

        verticalLayout_2->addWidget(disableMouseClicksCheckBox);


        verticalLayout->addWidget(behaviorGroup);

        buttonBox = new QDialogButtonBox(SettingsDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SettingsDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, SettingsDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, SettingsDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QCoreApplication::translate("SettingsDialog", "Settings", nullptr));
        appearanceGroup->setTitle(QCoreApplication::translate("SettingsDialog", "Appearance", nullptr));
        themeLabel->setText(QCoreApplication::translate("SettingsDialog", "Theme:", nullptr));
        themeComboBox->setItemText(0, QCoreApplication::translate("SettingsDialog", "Light", nullptr));
        themeComboBox->setItemText(1, QCoreApplication::translate("SettingsDialog", "Dark", nullptr));
        themeComboBox->setItemText(2, QCoreApplication::translate("SettingsDialog", "System", nullptr));

        behaviorGroup->setTitle(QCoreApplication::translate("SettingsDialog", "Behavior", nullptr));
        startupCheckBox->setText(QCoreApplication::translate("SettingsDialog", "Launch on system startup", nullptr));
        trayCheckBox->setText(QCoreApplication::translate("SettingsDialog", "Start minimized to system tray", nullptr));
        disableMouseMovementCheckBox->setText(QCoreApplication::translate("SettingsDialog", "Disable Mouse Movement Recording", nullptr));
        disableMouseClicksCheckBox->setText(QCoreApplication::translate("SettingsDialog", "Disable Mouse Click Recording", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_DIALOG_H
