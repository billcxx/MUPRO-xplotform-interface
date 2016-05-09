#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include <QWidget>

#include "mupromain.h"
#include "ui_mupromain.h"

class mouseevent : public QMainWindow
{
    Q_OBJECT
public:
    explicit mouseevent(QWidget *parent = 0);
    ~mouseevent();
protected:
    void mouseMoveEvent(QMouseEvent *e);
private:
    Ui::muproMain *ui;


signals:

public slots:
};

#endif // MOUSEEVENT_H
