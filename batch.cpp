#include "batch.h"
#include <QFileInfo>
#include <QFileDialog>
#include <fstream>
#include <QDebug>
#include "ui_batch.h"

batch::batch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::batch)
{
    ui->setupUi(this);
}

batch::~batch()
{
    delete ui;
}

void batch::on_loadFile_PB_released()
{
    QFileDialog filedialog;
    std::ifstream input;
    filedialog.setFileMode(QFileDialog::AnyFile);
    filedialog.setOption(QFileDialog::ReadOnly);
    QString load=filedialog.getOpenFileName();
    QString fullName,fileName;
    if(!load.isEmpty()){
        fullName=QFileInfo(load).absoluteFilePath();
        suffixName=QFileInfo(load).suffix();
        pathName=QFileInfo(load).absolutePath();
        baseName=QFileInfo(load).baseName();
        fileName=QFileInfo(load).completeBaseName();
        middleName=fileName.split(".",QString::SkipEmptyParts).at(1);
        qDebug()<<"batch name:"<<fullName;
        qDebug()<<"suffix"<<suffixName;
        qDebug()<<"pathName"<<pathName;
        qDebug()<<"baseName"<<baseName;
        qDebug()<<"middleName:" << middleName;
    }
}

QString batch::getPath(){
    return pathName;
}

QString batch::getName(){
    return baseName;
}

QString batch::getSuffix(){
    return suffixName;
}

int batch::getLength(){
    return middleName.length();
}

void batch::on_export_PB_released()
{
    QFileDialog filedialog;
    filedialog.setAcceptMode(QFileDialog::AcceptSave);
    filedialog.setDefaultSuffix("dat");
    load=filedialog.getSaveFileName(0,tr("Save file"),0,tr("Data (*.dat)"));
}

QString batch::getLoad(){
    return load;
}
