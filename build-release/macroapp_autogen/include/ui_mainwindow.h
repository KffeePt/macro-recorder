/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *recordButton;
    QPushButton *playbackButton;
    QLabel *labelLoopCount;
    QSpinBox *loopCountSpinBox;
    QLabel *labelLoopInterval;
    QSpinBox *loopIntervalSpinBox;
    QComboBox *intervalUnitComboBox;
    QSpacerItem *horizontalSpacer;
    QPushButton *settingsButton;
    QPushButton *saveButton;
    QPushButton *loadButton;
    QPushButton *insertEventButton;
    QTabWidget *tabWidget;
    QWidget *keyboardTab;
    QVBoxLayout *verticalLayout_2;
    QTreeView *keyboardEventsView;
    QWidget *mouseTab;
    QVBoxLayout *verticalLayout_3;
    QTreeView *mouseEventsView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(500, 400);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        recordButton = new QPushButton(centralwidget);
        recordButton->setObjectName("recordButton");
        recordButton->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(recordButton);

        playbackButton = new QPushButton(centralwidget);
        playbackButton->setObjectName("playbackButton");
        playbackButton->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(playbackButton);

        labelLoopCount = new QLabel(centralwidget);
        labelLoopCount->setObjectName("labelLoopCount");

        horizontalLayout->addWidget(labelLoopCount);

        loopCountSpinBox = new QSpinBox(centralwidget);
        loopCountSpinBox->setObjectName("loopCountSpinBox");

        horizontalLayout->addWidget(loopCountSpinBox);

        labelLoopInterval = new QLabel(centralwidget);
        labelLoopInterval->setObjectName("labelLoopInterval");

        horizontalLayout->addWidget(labelLoopInterval);

        loopIntervalSpinBox = new QSpinBox(centralwidget);
        loopIntervalSpinBox->setObjectName("loopIntervalSpinBox");
        loopIntervalSpinBox->setMaximum(999999);

        horizontalLayout->addWidget(loopIntervalSpinBox);

        intervalUnitComboBox = new QComboBox(centralwidget);
        intervalUnitComboBox->addItem(QString());
        intervalUnitComboBox->addItem(QString());
        intervalUnitComboBox->addItem(QString());
        intervalUnitComboBox->addItem(QString());
        intervalUnitComboBox->setObjectName("intervalUnitComboBox");

        horizontalLayout->addWidget(intervalUnitComboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        settingsButton = new QPushButton(centralwidget);
        settingsButton->setObjectName("settingsButton");

        horizontalLayout->addWidget(settingsButton);

        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName("saveButton");

        horizontalLayout->addWidget(saveButton);

        loadButton = new QPushButton(centralwidget);
        loadButton->setObjectName("loadButton");

        horizontalLayout->addWidget(loadButton);


        verticalLayout->addLayout(horizontalLayout);

        insertEventButton = new QPushButton(centralwidget);
        insertEventButton->setObjectName("insertEventButton");

        verticalLayout->addWidget(insertEventButton);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        keyboardTab = new QWidget();
        keyboardTab->setObjectName("keyboardTab");
        verticalLayout_2 = new QVBoxLayout(keyboardTab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        keyboardEventsView = new QTreeView(keyboardTab);
        keyboardEventsView->setObjectName("keyboardEventsView");

        verticalLayout_2->addWidget(keyboardEventsView);

        tabWidget->addTab(keyboardTab, QString());
        mouseTab = new QWidget();
        mouseTab->setObjectName("mouseTab");
        verticalLayout_3 = new QVBoxLayout(mouseTab);
        verticalLayout_3->setObjectName("verticalLayout_3");
        mouseEventsView = new QTreeView(mouseTab);
        mouseEventsView->setObjectName("mouseEventsView");

        verticalLayout_3->addWidget(mouseEventsView);

        tabWidget->addTab(mouseTab, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 500, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Macro Recorder", nullptr));
        recordButton->setText(QCoreApplication::translate("MainWindow", "Record", nullptr));
        playbackButton->setText(QCoreApplication::translate("MainWindow", "Playback", nullptr));
        labelLoopCount->setText(QCoreApplication::translate("MainWindow", "Loop Count (0=inf):", nullptr));
        labelLoopInterval->setText(QCoreApplication::translate("MainWindow", "Loop Interval (ms):", nullptr));
        intervalUnitComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "ms", nullptr));
        intervalUnitComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "s", nullptr));
        intervalUnitComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "min", nullptr));
        intervalUnitComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "hr", nullptr));

        settingsButton->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        loadButton->setText(QCoreApplication::translate("MainWindow", "Load", nullptr));
        insertEventButton->setText(QCoreApplication::translate("MainWindow", "Insert Event", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(keyboardTab), QCoreApplication::translate("MainWindow", "Keyboard Events", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(mouseTab), QCoreApplication::translate("MainWindow", "Mouse Events", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
