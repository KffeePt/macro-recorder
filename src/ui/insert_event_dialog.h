#ifndef INSERT_EVENT_DIALOG_H
#define INSERT_EVENT_DIALOG_H

#include <QDialog>
#include "macro_engine.h"

namespace Ui {
class InsertEventDialog;
}

class InsertEventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InsertEventDialog(QWidget *parent = nullptr);
    ~InsertEventDialog();

    MacroEvent getEventData();

private:
    Ui::InsertEventDialog *ui;
};

#endif // INSERT_EVENT_DIALOG_H