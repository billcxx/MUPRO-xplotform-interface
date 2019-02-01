#ifndef BATCH_H
#define BATCH_H

#include <QDialog>

namespace Ui {
class batch;
}

class batch : public QDialog
{
    Q_OBJECT

public:
    explicit batch(QWidget *parent = 0);
    QString getPath();
    QString getName();
    QString getSuffix();
    QString getLoad();
    int getLength();
    ~batch();

private slots:
    void on_loadFile_PB_released();

    void on_export_PB_released();

private:
    Ui::batch *ui;
    QString pathName,baseName,suffixName,middleName,load;
};

#endif // BATCH_H
