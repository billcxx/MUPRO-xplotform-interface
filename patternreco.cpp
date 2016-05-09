#include "patternreco.h"
#include "ui_patternreco.h"
#include <QFileDialog>

#include <QDebug>

patternReco::patternReco(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::patternReco)
{
    ui->setupUi(this);
    scene=new QGraphicsScene(this);
    ui->originImage->setScene(scene);
}

patternReco::~patternReco()
{
    delete ui;
}

void patternReco::on_loadImage_clicked()
{
    QFileDialog filedialog;
    filedialog.setFileMode(QFileDialog::AnyFile);
    filedialog.setOption(QFileDialog::ReadOnly);
    QString load=filedialog.getOpenFileName();
    qDebug()<<"Filename:"<<load;
    this->raise();
    QPixmap image;
    image.load(load);
    QPixmap newimage=image.scaledToWidth(300);
    int imageHeight=newimage.height();
    ui->originImage->resize(320,imageHeight+10);
    ui->processedImage->resize(320,imageHeight+10);
    ui->originImage->scene()->addPixmap(newimage);
    ui->hwidget->resize(680,imageHeight+10);
    ui->vwidget->resize(680,imageHeight+100);
    this->adjustSize();

    qDebug()<<ui->originImage->isVisible()<<imageHeight;



}
