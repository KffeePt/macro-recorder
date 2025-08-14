#include "settings_dialog.h"
#include "ui_settings_dialog.h"
#include <QSettings>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    loadSettings();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::accept()
{
    saveSettings();
    QDialog::accept();
}

void SettingsDialog::loadSettings()
{
    QSettings settings("MySoft", "MacroApp");
    ui->themeComboBox->setCurrentText(settings.value("appearance/theme", "System").toString());
    ui->startupCheckBox->setChecked(settings.value("behavior/startup", false).toBool());
    ui->trayCheckBox->setChecked(settings.value("behavior/tray", false).toBool());
    ui->disableMouseMovementCheckBox->setChecked(settings.value("behavior/disableMouseMovement", false).toBool());
    ui->disableMouseClicksCheckBox->setChecked(settings.value("behavior/disableMouseClicks", false).toBool());
    ui->ignoreHotkeysCheckBox->setChecked(settings.value("behavior/ignoreHotkeys", true).toBool());
}

void SettingsDialog::saveSettings()
{
    QSettings settings("MySoft", "MacroApp");
    settings.setValue("appearance/theme", ui->themeComboBox->currentText());
    settings.setValue("behavior/startup", ui->startupCheckBox->isChecked());
    settings.setValue("behavior/tray", ui->trayCheckBox->isChecked());
    settings.setValue("behavior/disableMouseMovement", ui->disableMouseMovementCheckBox->isChecked());
    settings.setValue("behavior/disableMouseClicks", ui->disableMouseClicksCheckBox->isChecked());
    settings.setValue("behavior/ignoreHotkeys", ui->ignoreHotkeysCheckBox->isChecked());
}