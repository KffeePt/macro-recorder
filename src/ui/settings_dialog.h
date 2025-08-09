#ifndef SETTINGS_DIALOG_H
#define SETTINGS_DIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

protected:
    void accept() override;

private:
    void loadSettings();
    void saveSettings();
    Ui::SettingsDialog *ui;
};

#endif // SETTINGS_DIALOG_H