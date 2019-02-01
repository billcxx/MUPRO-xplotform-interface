#ifndef GENERATEBATCH_H
#define GENERATEBATCH_H

#include <QDialog>

namespace Ui {
class generateBatch;
}

class generateBatch : public QDialog
{
    Q_OBJECT

public:
    explicit generateBatch(QWidget *parent = 0,QVector<QString> integerList=QVector<QString>()<<"integer",QVector<QString> doubleList=QVector<QString>()<<"double",QVector<QString> booleanList=QVector<QString>()<<"boolean");
    ~generateBatch();
    QVector<QString> batchList;

private slots:
    void on_add_PB_released();

    void on_parameter_Combo_currentIndexChanged(const QString &arg1);

    void on_delete_PB_released();

    void on_pushButton_released();

private:
    Ui::generateBatch *ui;
    int booleanParameters=0,numericParameters=0;
    QVector<QString> integerList,doubleList,booleanList;
};

#endif // GENERATEBATCH_H
