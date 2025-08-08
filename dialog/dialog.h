#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

    void Dialog_create();
    void Message_dialog();
    void File_dialog();
};
#endif // DIALOG_H
