#include "insert_event_dialog.h"
#include "ui_insert_event_dialog.h"
#include <QKeySequence>

InsertEventDialog::InsertEventDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertEventDialog)
{
    ui->setupUi(this);
}

InsertEventDialog::~InsertEventDialog()
{
    delete ui;
}

MacroEvent InsertEventDialog::getEventData()
{
    MacroEvent event;
    event.type = (ui->eventTypeComboBox->currentText() == "Key Press") ? KEY_PRESS : KEY_RELEASE;
    event.key_code = QKeySequence(ui->keyEdit->text())[0];
    event.delay_ms = ui->delaySpinBox->value();
    return event;
}