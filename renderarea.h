#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>

namespace Ui {
class renderArea;
}

class renderArea : public QWidget
{
    Q_OBJECT

public:
    explicit renderArea(QWidget *parent = 0);
    ~renderArea();

private:
    Ui::renderArea *ui;
};

#endif // RENDERAREA_H
