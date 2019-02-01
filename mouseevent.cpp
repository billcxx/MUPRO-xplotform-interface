#include "mouseevent.h"
#include <QDebug>


mouseevent::mouseevent(QWidget *parent) :
    QMainWindow(parent)
{
    ui->setupUi(this);

    this->setMouseTracking(true);
    qDebug()<<"reached here the mouse event"<<this->size();
    resize(400,200);
    qDebug()<<"reached here the mouse event"<<this->size();
}

mouseevent::~mouseevent(){}

