#ifndef PATTERNRECO_H
#define PATTERNRECO_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsView>

namespace Ui {
class patternReco;
}

class patternReco : public QDialog
{
    Q_OBJECT

public:
    explicit patternReco(QWidget *parent = 0);
    ~patternReco();

private slots:
    void on_loadImage_clicked();

private:
    Ui::patternReco *ui;
    QGraphicsScene *scene;
};

#endif // PATTERNRECO_H
