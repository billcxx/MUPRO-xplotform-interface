#include "readimage.h"
#include "ui_readimage.h"

readImage::readImage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::readImage)
{
    ui->setupUi(this);
}

readImage::~readImage()
{
    delete ui;
}
