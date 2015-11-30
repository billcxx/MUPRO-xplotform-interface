#ifndef MUPROMAIN_H
#define MUPROMAIN_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QLabel>

namespace Ui {
class muproMain;
}

class muproMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit muproMain(QWidget *parent = 0);
    ~muproMain();

protected:
    void mouseMoveEvent(QMouseEvent *e);

private slots:
    void on_button_ferroelectric_clicked();

    void on_button_effect_clicked();

private:
    Ui::muproMain *ui;
    QLabel *statusLabel;
    QLabel *mousePosLabel;
};

#endif // MUPROMAIN_H
