/********************************************************************************
** Form generated from reading UI file 'insert_event_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSERT_EVENT_DIALOG_H
#define UI_INSERT_EVENT_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_InsertEventDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *eventGroup;
    QFormLayout *formLayout;
    QLabel *eventTypeLabel;
    QComboBox *eventTypeComboBox;
    QLabel *keyLabel;
    QLineEdit *keyEdit;
    QLabel *delayLabel;
    QSpinBox *delaySpinBox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *InsertEventDialog)
    {
        if (InsertEventDialog->objectName().isEmpty())
            InsertEventDialog->setObjectName("InsertEventDialog");
        InsertEventDialog->resize(400, 300);
        verticalLayout = new QVBoxLayout(InsertEventDialog);
        verticalLayout->setObjectName("verticalLayout");
        eventGroup = new QGroupBox(InsertEventDialog);
        eventGroup->setObjectName("eventGroup");
        formLayout = new QFormLayout(eventGroup);
        formLayout->setObjectName("formLayout");
        eventTypeLabel = new QLabel(eventGroup);
        eventTypeLabel->setObjectName("eventTypeLabel");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, eventTypeLabel);

        eventTypeComboBox = new QComboBox(eventGroup);
        eventTypeComboBox->addItem(QString());
        eventTypeComboBox->addItem(QString());
        eventTypeComboBox->setObjectName("eventTypeComboBox");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, eventTypeComboBox);

        keyLabel = new QLabel(eventGroup);
        keyLabel->setObjectName("keyLabel");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, keyLabel);

        keyEdit = new QLineEdit(eventGroup);
        keyEdit->setObjectName("keyEdit");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, keyEdit);

        delayLabel = new QLabel(eventGroup);
        delayLabel->setObjectName("delayLabel");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, delayLabel);

        delaySpinBox = new QSpinBox(eventGroup);
        delaySpinBox->setObjectName("delaySpinBox");
        delaySpinBox->setMaximum(999999);

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, delaySpinBox);


        verticalLayout->addWidget(eventGroup);

        buttonBox = new QDialogButtonBox(InsertEventDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(InsertEventDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, InsertEventDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, InsertEventDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(InsertEventDialog);
    } // setupUi

    void retranslateUi(QDialog *InsertEventDialog)
    {
        InsertEventDialog->setWindowTitle(QCoreApplication::translate("InsertEventDialog", "Insert Event", nullptr));
        eventGroup->setTitle(QCoreApplication::translate("InsertEventDialog", "Event Details", nullptr));
        eventTypeLabel->setText(QCoreApplication::translate("InsertEventDialog", "Event Type:", nullptr));
        eventTypeComboBox->setItemText(0, QCoreApplication::translate("InsertEventDialog", "Key Press", nullptr));
        eventTypeComboBox->setItemText(1, QCoreApplication::translate("InsertEventDialog", "Key Release", nullptr));

        keyLabel->setText(QCoreApplication::translate("InsertEventDialog", "Key:", nullptr));
        delayLabel->setText(QCoreApplication::translate("InsertEventDialog", "Delay (ms):", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InsertEventDialog: public Ui_InsertEventDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSERT_EVENT_DIALOG_H
