#include "patternreco.h"
#include "ui_patternreco.h"
#include <QPainter>
#include <QImage>
#include <QPixmap>
#include <QFileDialog>
#include <QColorDialog>
#include "view.h"
#include <QDebug>
#include <fstream>
#include <QListView>
#include <QMessageBox>
#include <iomanip>
patternReco::patternReco(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::patternReco)
{
    ui->setupUi(this);
    originalScene=new QGraphicsScene(this);
    processedScene= new QGraphicsScene(this);
    originalView->view()->setScene(originalScene);
    processedView->view()->setScene(processedScene);
    this->ui->hwidget->layout()->addWidget(originalView);
    this->ui->hwidget->layout()->addWidget(processedView);
}

patternReco::~patternReco()
{
    delete ui;
}

void patternReco::loadImage(QString load){
    QPixmap image;
    image.load(load);
    int width,height;
    width=image.width();
    height=image.height();
    QImage *processImage=new QImage(width, height, QImage::Format_Indexed8);
    qDebug()<<"create new image";
    originalPixmap=originalView->view()->scene()->addPixmap(image);
    qDebug()<<"added original";
    processImage->setColorCount(32);
    processImage->setColor(0,qRgb(128,128,128));
    processImage->fill(0);
    processedPixmap=processedView->view()->scene()->addPixmap(QPixmap::fromImage(*processImage));
}

void patternReco::on_loadImage_clicked()
{
    QFileDialog filedialog;
    filedialog.setFileMode(QFileDialog::AnyFile);
    filedialog.setOption(QFileDialog::ReadOnly);
    QString load=filedialog.getOpenFileName();
    int x,y,z;
    qDebug()<<"Filename:"<<load;
    this->raise();
    loadImage(load);
    x=originalView->view()->scene()->width();
    y=originalView->view()->scene()->height();

    colorDistance=new double**[28];
    for(int i=0;i<28;i++){
        colorDistance[i]=new double *[x];
        for(int j=0;j<x;j++){
            colorDistance[i][j]= new double[y];
            for(int k=0;k<y;k++){
                colorDistance[i][j][k]=999;
            }
        }
    }
//    qDebug()<<"added processed"<<processImage->pixelColor(255,255).green()<<processImage->pixelColor(255,255).blue()<<processImage->pixelColor(255,255).red();
    domainRGB=new int*[28];
    for (int i=0;i<=27;++i){
        domainRGB[i] = new int[3];
    }
    domainRGB[0][0]=192;domainRGB[0][1]=192;domainRGB[0][2]=192; //sub
    domainRGB[1][0]=0;  domainRGB[1][1]=0  ;domainRGB[1][2]=255;  //R1+
    domainRGB[2][0]=117;domainRGB[2][1]=183;domainRGB[2][2]=207; //R1-
    domainRGB[3][0]=0;  domainRGB[3][1]=39; domainRGB[3][2]=0; //R2+
    domainRGB[4][0]=0;  domainRGB[4][1]=255;domainRGB[4][2]=0; //R2-
    domainRGB[5][0]=255;domainRGB[5][1]=0;  domainRGB[5][2]=0; //R3+
    domainRGB[6][0]=255;domainRGB[6][1]=145;domainRGB[6][2]=162; //R3-
    domainRGB[7][0]=255;domainRGB[7][1]=107;domainRGB[7][2]=0; //R4+
    domainRGB[8][0]=255;domainRGB[8][1]=255;domainRGB[8][2]=0; //R4-
    domainRGB[9][0]=255;domainRGB[9][1]=0;  domainRGB[9][2]=255; //O1+
    domainRGB[10][0]=165;domainRGB[10][1]=33;domainRGB[10][2]=33; //O1-
    domainRGB[11][0]=230;domainRGB[11][1]=145;domainRGB[11][2]=162; //O2+
    domainRGB[12][0]=192;domainRGB[12][1]=100;domainRGB[12][2]=192; //O2-
    domainRGB[13][0]=107;domainRGB[13][1]=7;domainRGB[13][2]=7; //O3+
    domainRGB[14][0]=173;domainRGB[14][1]=127;domainRGB[14][2]=77; //O3-
    domainRGB[15][0]=121;domainRGB[15][1]=9;domainRGB[15][2]=36; //O4+
    domainRGB[16][0]=245;domainRGB[16][1]=64;domainRGB[16][2]=51; //O4-
    domainRGB[17][0]=91;domainRGB[17][1]=247;domainRGB[17][2]=91; //O5+
    domainRGB[18][0]=10;domainRGB[18][1]=165;domainRGB[18][2]=10; //O5-
    domainRGB[19][0]=196;domainRGB[19][1]=196;domainRGB[19][2]=196; //O6+
    domainRGB[20][0]=43;domainRGB[20][1]=43;domainRGB[20][2]=43; //O6-
    domainRGB[21][0]=145;domainRGB[21][1]=145;domainRGB[21][2]=145; //a1+
    domainRGB[22][0]=100;domainRGB[22][1]=4;domainRGB[22][2]=226; //a1-
    domainRGB[23][0]=0;domainRGB[23][1]=0;domainRGB[23][2]=0; //a2+
    domainRGB[24][0]=255;domainRGB[24][1]=181;domainRGB[24][2]=0; //a2-
    domainRGB[25][0]=226;domainRGB[25][1]=207;domainRGB[25][2]=77; //c+
    domainRGB[26][0]=226;domainRGB[26][1]=111;domainRGB[26][2]=7; //c-
    domainRGB[27][0]=255;domainRGB[27][1]=255;domainRGB[27][2]=255;

    M[0][0]=0.5767309 ; M[0][1]=0.1855540;  M[0][2]=0.1881852;
    M[1][0]=0.2973769 ; M[1][1]=0.6273491 ; M[1][2]=0.0752741;
    M[2][0]=0.0270343 ; M[2][1]=0.0706872 ; M[2][2]=0.9911085;

    white[0]=95.05;white[1]=100;white[2]=108.899;

    for(int n=0;n<=27;n++){
        colorTable.push_back(qRgb(domainRGB[n][0],domainRGB[n][1],domainRGB[n][2]));
    }



}

void patternReco::on_colorPicker_PB_released()
{
    QColor color=QColorDialog::getColor(Qt::yellow,this);
    if( color.isValid() )
        {
          qDebug() << "Color Choosen : " << color.name();
          this->ui->R_LE->setText(QString::number(color.red()));
          this->ui->G_LE->setText(QString::number(color.green()));
          this->ui->B_LE->setText(QString::number(color.blue()));
        }
}

void patternReco::colorTableRow(int row){
    QString item;
    int label;
    item=this->ui->phase_table->item(row,0)->text();
    if(this->ui->scalarVectorSwitch_Combo==0){
        label=item.toInt();
    }else{
        label=this->ui->phaseLabel_Combo->findText(item);
    }
    this->ui->phase_table->item(row,0)->setBackgroundColor(QColor(domainRGB[label][0],domainRGB[label][1],domainRGB[label][2]));
    this->ui->phase_table->item(row,0)->setTextColor(QColor(255,255,255));
}

void patternReco::on_addPhase_PB_released()
{
    int row=0;
    bool add=true;
    QString  item;
    if(     (!this->ui->phaseNumber_LE->text().isEmpty() || this->ui->phaseLabel_Combo->currentIndex()!=0) && \
            !this->ui->R_LE->text().isEmpty() && \
            !this->ui->G_LE->text().isEmpty() && \
            !this->ui->B_LE->text().isEmpty() && \
            !this->ui->tolerance_LE->text().isEmpty()){

        if(this->ui->scalarVectorSwitch_Combo->currentIndex()==0){
            item=this->ui->phaseNumber_LE->text();
        }else{
            item=this->ui->phaseLabel_Combo->currentText();
        }
        QList<QTableWidgetItem*> itemList=this->ui->phase_table->findItems(item,Qt::MatchExactly);
        for(int i=0;i<itemList.count();i++){
            if(itemList[i]->column()==0){
                add=false;
                row=itemList[i]->row();
            }
        }
        if(add){
            row=this->ui->phase_table->rowCount();
            this->ui->phase_table->insertRow(row);
        }else{

        }
        this->ui->scalarVectorSwitch_Combo->setEnabled(false);


        this->ui->phase_table->setItem(row,0,new QTableWidgetItem(item));
        colorTableRow(row);

        item=this->ui->R_LE->text();
        this->ui->phase_table->setItem(row,1,new QTableWidgetItem(item));
        item=this->ui->G_LE->text();
        this->ui->phase_table->setItem(row,2,new QTableWidgetItem(item));
        item=this->ui->B_LE->text();
        this->ui->phase_table->setItem(row,3,new QTableWidgetItem(item));
        item=this->ui->tolerance_LE->text();
        this->ui->phase_table->setItem(row,4,new QTableWidgetItem(item));
    }
}

void patternReco::on_deletePhase_PB_released()
{
    this->ui->phase_table->removeRow(this->ui->phase_table->currentRow());
    if(this->ui->phase_table->rowCount()==0){
        this->ui->scalarVectorSwitch_Combo->setEnabled(true);
    }else{
        this->ui->scalarVectorSwitch_Combo->setEnabled(false);
    }
}

void patternReco::on_tolerance_slider_valueChanged(int position)
{


    this->ui->tolerance_LE->setText(QString::number(position));
    clearProcessedImage();
    int width=originalView->view()->scene()->width();
    int height=originalView->view()->scene()->height();
    if(!this->ui->showAll_CB->isChecked()){
        if(this->ui->phase_table->selectionModel()->hasSelection()){
            this->ui->phase_table->setItem(this->ui->phase_table->currentRow(),4,new QTableWidgetItem(QString::number(position)));
            colorByTable(this->ui->phase_table->currentRow(),false);
        }else{
            colorByTemp(position);
        }
    }else{
        for(int i=0;i<this->ui->phase_table->rowCount();i++){
            colorByTable(i,true);
        }
        colorByTemp(position);
    }
    if(this->ui->fillBlank_CB->isChecked()){
        updateColorByDistance();
    }
    QImage *processImage=new QImage(width, height,QImage::Format_Indexed8);
    *processImage=processedPixmap->pixmap().toImage().convertToFormat(QImage::Format_Indexed8,colorTable);
    QPalette p=this->ui->exportData_PB->palette();
    p.setColor(QPalette::ButtonText,QColor(0,0,0));
    this->ui->exportData_PB->setPalette(p);
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            if(processImage->pixelIndex(i,j)==0){
                p.setColor(QPalette::ButtonText,QColor(255,0,0));
                this->ui->exportData_PB->setPalette(p);
                goto exit;
            }
        }
    }
    exit:

    QImage outImage=*makePeriodic(processImage);
    processedPixmap->setPixmap(QPixmap::fromImage(outImage));

}


void patternReco::colorByTemp(int position){
    int r,g,b,tolerance,label;

    if(!this->ui->R_LE->text().isEmpty()&&!this->ui->B_LE->text().isEmpty()&&!this->ui->G_LE->text().isEmpty()){
        r=this->ui->R_LE->text().toInt();
        g=this->ui->G_LE->text().toInt();
        b=this->ui->B_LE->text().toInt();
        tolerance=this->ui->tolerance_LE->text().toInt();
        if(this->ui->scalarVectorSwitch_Combo->currentIndex()==0){
            if(this->ui->phaseNumber_LE->text().isEmpty()){
                label=0;
            }else{
                label=this->ui->phaseNumber_LE->text().toInt();
            }
        }else{
            label=this->ui->phaseLabel_Combo->currentIndex();
        }
        colorImage(r,g,b,tolerance,label);
    }
}

void patternReco::colorByTable(int index,bool considerTemp){
    int r,g,b,tolerance,label;
    QString name;
    if(this->ui->scalarVectorSwitch_Combo->currentIndex()==0){
        name=this->ui->phaseNumber_LE->text();
    }else{
        name=this->ui->phaseLabel_Combo->currentText();
    }
    if(considerTemp && this->ui->phase_table->item(index,0)->text()==name ){

    }else{
        r=this->ui->phase_table->item(index,1)->text().toInt();
        g=this->ui->phase_table->item(index,2)->text().toInt();
        b=this->ui->phase_table->item(index,3)->text().toInt();
        tolerance=this->ui->phase_table->item(index,4)->text().toInt();
        if(this->ui->scalarVectorSwitch_Combo->currentIndex()==0){
            label=this->ui->phase_table->item(index,0)->text().toInt();
        }else{
            label=this->ui->phaseLabel_Combo->findText(this->ui->phase_table->item(index,0)->text());
        }
        colorImage(r,g,b,tolerance,label);
    }
}

void patternReco::on_tolerance_LE_editingFinished()
{
    this->ui->tolerance_slider->setValue(this->ui->tolerance_LE->text().toInt());
}

std::array<double,3> patternReco::convertRGBToLab(int intR, int intG, int intB){
    double R,G,B,X,Y,Z,outL,outA,outB,xr,yr,zr,fx,fy,fz;
    R=intR/255.0;
    G=intG/255.0;
    B=intB/255.0;
    X=M[0][0]*R+M[0][1]*G+M[0][2]*B;
    Y=M[1][0]*R+M[1][1]*G+M[1][2]*B;
    Z=M[2][0]*R+M[2][1]*G+M[2][2]*B;
//    qDebug()<<"XYZ:"<<X<<Y<<Z;
    xr=X*100/white[0];
    yr=Y*100/white[1];
    zr=Z*100/white[2];
//    qDebug()<<"XYZR:"<<xr<<yr<<zr;

    if(xr>epsilon){
        fx=std::cbrt(xr);
    }else{
        fx=(kappa*xr+16)/116;
    }

    if(yr>epsilon){
        fy=std::cbrt(yr);
    }else{
        fy=(kappa*yr+16)/116;
    }

    if(zr>epsilon){
        fz=std::cbrt(zr);
    }else{
        fz=(kappa*zr+16)/116;
    }

    outL=116*fy-16;
    outA=500*(fx-fy);
    outB=200*(fy-fz);

    return {outL,outA,outB};
}

double patternReco::colorWithinRange(int intR,int intG, int intB, int intr, int intg, int intb, int tolerance){
    double distance;
    std::array<double,3> lab=convertRGBToLab(intr,intg,intb),LAB=convertRGBToLab(intR,intG,intB);

    distance=std::sqrt(pow((lab[0]-LAB[0]),2)+pow((lab[1]-LAB[1]),2)+pow((lab[2]-LAB[2]),2));


    if(distance < tolerance){
        return distance;
    }else{
        return 999;
    }
}

void patternReco::clearProcessedImage(){
    int width=0,height=0;
    width=originalView->view()->scene()->width();
    height=originalView->view()->scene()->height();
    for(int j=0;j<width;j++){
        for(int k=0;k<height;k++){
            for(int i=0;i<28;i++){
                colorDistance[i][j][k]=999;
            }
        }
    }
    QImage *processImage=new QImage(width, height, QImage::Format_Indexed8);
    *processImage=processedPixmap->pixmap().copy(0,0,width,height).toImage().convertToFormat(QImage::Format_Indexed8,colorTable);
    processImage->fill(0);
    processedPixmap->setPixmap(QPixmap::fromImage(*processImage));
    qDebug()<<"clear process:"<<processedPixmap->pixmap().toImage().width()<<processedPixmap->pixmap().toImage().height();
}

void patternReco::updateColorByDistance(){
    double value=999;
    int index=0;
    int width,height;
    width=originalView->view()->scene()->width();
    height=originalView->view()->scene()->height();
    QImage *processImage=new QImage(width, height, QImage::Format_Indexed8);
    *processImage=processedPixmap->pixmap().copy(0,0,width,height).toImage().convertToFormat(QImage::Format_Indexed8,colorTable);
    for (int j=0;j<width;j++){
        for (int k=0;k<height;k++){
            value=999;
            for (int i=0;i<28;i++){
                if (colorDistance[i][j][k]<value){
                    value=colorDistance[i][j][k];
                    index=i;
                }
            }
            processImage->setPixel(j,k,index);
        }
    }
    processedPixmap->setPixmap(QPixmap::fromImage(*processImage));
}

void patternReco::colorImage(int r, int g, int b, int tolerance, int label){
    if(label==0){

    }else{
        int i=0,j=0,width=0,height=0,R=0,G=0,B=0;
        QColor color,labelColor;
        double distance;
        width=originalView->view()->scene()->width();
        height=originalView->view()->scene()->height();
        QImage *processImage=new QImage(width, height, QImage::Format_Indexed8);

        *processImage=processedPixmap->pixmap().toImage().convertToFormat(QImage::Format_Indexed8,colorTable);


        for(i=0;i<width;i++){
            for(j=0;j<height;j++){
                color=originalPixmap->pixmap().toImage().pixel(i,j);
                R=color.red();
                G=color.green();
                B=color.blue();
                distance=colorWithinRange(R,G,B,r,g,b,tolerance);
                colorDistance[label][i][j]=distance;
                if(distance<500){
                    processImage->setPixel(i,j,label);
                }
            }
        }
        processedPixmap->setPixmap(QPixmap::fromImage(*processImage));
    }
}

void patternReco::on_refersh_PB_released()
{
    on_tolerance_slider_valueChanged(this->ui->tolerance_slider->value());
}

void patternReco::on_exportInfo_PB_released()
{
    QFileDialog filedialog;
    std::ofstream output;
    filedialog.setAcceptMode(QFileDialog::AcceptSave);
    filedialog.setDefaultSuffix("txt");
    QString load=filedialog.getSaveFileName(0,tr("Save file"),0,tr("Status (*.txt)"));
    if(!load.isEmpty()){
        output.open(QFileInfo(load).absoluteFilePath().toStdString().c_str(),std::fstream::out);
        output << this->ui->nx_LE->text().toInt() << " " << this->ui->ny_LE->text().toInt() << " " << this->ui->nz_LE->text().toInt() << std::endl;
        output << this->ui->ns_LE->text().toInt() << " " << this->ui->nf_LE->text().toInt() << std::endl;
        output << this->ui->scalarVectorSwitch_Combo->currentIndex() <<" " << this->ui->vectorValue_LE->text().toDouble() << std::endl;
        output << this->ui->periodic_CB->checkState() << std::endl;
        output << this->ui->batchSame_Combo->currentIndex() << std::endl;
        output << this->ui->showAll_CB->checkState() << std::endl;
        if(this->ui->scalarVectorSwitch_Combo->currentIndex()==0){
            output << this->ui->phaseNumber_LE->text().toInt() << " " <<this->ui->R_LE->text().toInt()<<" " <<this->ui->G_LE->text().toInt()<< " " << this->ui->B_LE->text().toInt()<< " " <<this->ui->tolerance_LE->text().toInt() << std::endl;
        }else{
            output << this->ui->phaseLabel_Combo->currentIndex() << " " <<this->ui->R_LE->text().toInt()<<" " <<this->ui->G_LE->text().toInt()<< " " << this->ui->B_LE->text().toInt()<< " " <<this->ui->tolerance_LE->text().toInt() << std::endl;
        }
        output << this->ui->phase_table->rowCount() << std::endl;
        for (int i=0;i<this->ui->phase_table->rowCount();i++){
            output << this->ui->phase_table->item(i,0)->text().toStdString()<<" " <<this->ui->phase_table->item(i,1)->text().toInt() << " " <<this->ui->phase_table->item(i,2)->text().toInt() << " " \
                   << this->ui->phase_table->item(i,3)->text().toInt()<<" " << this->ui->phase_table->item(i,4)->text().toInt() << std::endl ;
        }
    }
}

void patternReco::on_loadInfo_PB_released()
{
    QFileDialog filedialog;
    int checkstate,index,x,y,z,value,count;
    double doubleValue;
    std::string name;
    std::ifstream input;
    filedialog.setFileMode(QFileDialog::AnyFile);
    filedialog.setOption(QFileDialog::ReadOnly);
    QString load=filedialog.getOpenFileName();
    if(!load.isEmpty()){
        input.open(QFileInfo(load).absoluteFilePath().toStdString().c_str(),std::fstream::in);
        input >> x >> y >> z;
        this->ui->nx_LE->setText(QString::number(x));
        this->ui->ny_LE->setText(QString::number(y));
        this->ui->nz_LE->setText(QString::number(z));
        input >> x >> y;
        this->ui->ns_LE->setText(QString::number(x));
        this->ui->nf_LE->setText(QString::number(y));
        input >> index >> doubleValue;
        this->ui->scalarVectorSwitch_Combo->setCurrentIndex(index);
        this->ui->vectorValue_LE->setText(QString::number(doubleValue));
        input >> checkstate;
        this->ui->periodic_CB->setCheckState(static_cast<Qt::CheckState>(checkstate));
        input >> index;
        this->ui->batchSame_Combo->setCurrentIndex(index);
        input >> checkstate;
        this->ui->showAll_CB->setCheckState(static_cast<Qt::CheckState>(checkstate));
        input >> index >> x >> y >> z >> value;
        if(this->ui->scalarVectorSwitch_Combo->currentIndex()==0){
            this->ui->phaseNumber_LE->setText(QString::number(index));
        }else{
            this->ui->phaseLabel_Combo->setCurrentIndex(index);
        }
        this->ui->R_LE->setText(QString::number(x));
        this->ui->G_LE->setText(QString::number(y));
        this->ui->B_LE->setText(QString::number(z));
        this->ui->tolerance_LE->setText(QString::number(value));
        input >> count;
        while(this->ui->phase_table->rowCount()>0){
            this->ui->phase_table->removeRow(0);
        }
        if(count==0){
            this->ui->scalarVectorSwitch_Combo->setEnabled(true);
        }else{
            this->ui->scalarVectorSwitch_Combo->setEnabled(false);
        }
        for (int i=0;i<count;i++){
            input >> name >> x >> y >> z >> value;
            this->ui->phase_table->insertRow(i);
            this->ui->phase_table->setItem(i,0,new QTableWidgetItem(QString::fromStdString(name)));
            colorTableRow(i);
            this->ui->phase_table->setItem(i,1,new QTableWidgetItem(QString::number(x)));
            this->ui->phase_table->setItem(i,2,new QTableWidgetItem(QString::number(y)));
            this->ui->phase_table->setItem(i,3,new QTableWidgetItem(QString::number(z)));
            this->ui->phase_table->setItem(i,4,new QTableWidgetItem(QString::number(value)));;
        }
    }
}

QImage* patternReco::makePeriodic(QImage *input){
    if(!this->ui->periodic_CB->isChecked()){
        return input;
    }else{
//        QImage *image2=input,*image3=input,*image4=input;
        QPainter painter;
        int width,height;
        if(this->ui->nf_LE->text().toInt()==0){
            // This is for the bulk case
            width=input->width()*2;
            height=input->height()*2;
        }else{
            // This is for the film case
            if(this->ui->direction_Combo->currentIndex()!=2){
                width=input->width()*2;
                height=input->height();
            }else{
                width=input->width()*2;
                height=input->height()*2;
            }
        }
        QImage *result=new QImage(width,height,QImage::Format_RGB32);
//        *image2=input->mirrored(false,true);
//        *image3=input->mirrored(true,false);
//        *image4=input->mirrored(true,true);
        painter.begin(result);
        if(this->ui->nf_LE->text().toInt()==0 || this->ui->direction_Combo->currentIndex()==2){
            qDebug()<<"4 fold";
            painter.drawImage(0,0,*input);
            painter.drawImage(0,input->height(),input->mirrored(false,true));
            painter.drawImage(input->width(),0,input->mirrored(true,false));
            painter.drawImage(input->width(),input->height(),input->mirrored(true,true));
        }else{
            painter.drawImage(0,0,*input);
            painter.drawImage(input->width(),0,input->mirrored(true,false));
        }
        painter.end();
        return result;

    }

}

void patternReco::on_exportData_PB_released()
{
//    QPixmap out1Pix;

    int ***exportData;
    int x,y,z,ns,nf,label,width,height;
    QFileDialog filedialog;
    std::ofstream output;

    x=this->ui->nx_LE->text().toInt();
    y=this->ui->ny_LE->text().toInt();
    z=this->ui->nz_LE->text().toInt();
    width=originalView->view()->scene()->width();
    height=originalView->view()->scene()->height();
    qDebug()<<"width:height:"<<width<<height;
    QImage *out1Image=new QImage(width, height, QImage::Format_Indexed8);
    QImage outImage;
    QString load,imageName;

    exportData=new int**[x];
    for (int i=0;i<x;++i){
        exportData[i] = new int*[y];
        for(int j=0;j<y;j++){
            exportData[i][j]=new int[z];
            for(int k=0;k<z;k++){
                exportData[i][j][k]=0;
            }
        }
    }

    if(this->ui->scalarVectorSwitch_Combo->currentIndex()==1 && this->ui->vectorValue_LE->text().isEmpty()){
        this->ui->vectorValue_LE->setText("0.5");
    }
    if(this->ui->batchSame_Combo->currentIndex()==0){
        filedialog.setAcceptMode(QFileDialog::AcceptSave);
        filedialog.setDefaultSuffix("dat");
        load=filedialog.getSaveFileName(0,tr("Save file"),0,tr("Data (*.dat)"));
        //This is for the same across the whole thickness
        clearProcessedImage();
        for(int i=0;i<this->ui->phase_table->rowCount();i++){
            colorByTable(i,false);
        }
        qDebug()<<"In the correct path";
//        out1Pix=processedPixmap->pixmap().scaled(x,y,Qt::AspectRatioMode::KeepAspectRatioByExpanding);
        *out1Image=processedPixmap->pixmap().toImage().mirrored(false,true);
        outImage=makePeriodic(out1Image)->convertToFormat(QImage::Format_Indexed8,colorTable);
        processedPixmap->setPixmap(QPixmap::fromImage(outImage));
        processedView->view()->scene()->addPixmap(QPixmap::fromImage(outImage));
        width=outImage.width();
        height=outImage.height();
        qDebug()<<"export:"<<width<<height<<this->ui->direction_Combo->currentIndex();
        switch(this->ui->direction_Combo->currentIndex()){
        case 0:
            qDebug()<<"case0";
            for(int j=0;j<y;j++){
                for(int k=0;k<z;k++){
                    for (int i=0;i<x;++i){
                        exportData[i][j][k]=outImage.pixelIndex(int(j*double(width)/y),int(k*double(height)/z));
                    }
                }
            }
            break;
        case 1:
            qDebug()<<"case1";
            for (int i=0;i<x;++i){
                for(int k=0;k<z;k++){
                    for(int j=0;j<y;j++){
                        qDebug()<<"export for:"<<i<<j<<k<<int(i*double(width)/x)<<int(k*double(height)/z);
                        exportData[i][j][k]=outImage.pixelIndex(int(i*double(width)/x),int(k*double(height)/z));
                    }
                }
            }
            break;
        case 2:
            for (int i=0;i<x;++i){
                for(int j=0;j<y;j++){
                    for(int k=0;k<z;k++){
                        exportData[i][j][k]=outImage.pixelIndex(int(i*double(width)/x),int(j*double(height)/y));
                    }
                }
            }
//            qDebug()<<"export:"<<exportData[1][1][ns+5]<<outImage.pixelIndex(1,1);

            break;
        }


    }else{
        //This is for using a series of images
        batch *batchLayer= new batch();
        if(batchLayer->exec()){
            load=batchLayer->getLoad();
            QString pathName=batchLayer->getPath();
            QString baseName=batchLayer->getName();
            QString suffixName=batchLayer->getSuffix();
            int length=batchLayer->getLength();

            qDebug()<<"ok";
            switch(this->ui->direction_Combo->currentIndex()){
            case 0:
                for(int i=0;i<x;i++){
                    imageName=pathName+"/"+baseName+"."+QString("%1").arg(i+1,length,10,QChar('0'))+"."+suffixName;
                    loadImage(imageName);
                    clearProcessedImage();
                    for(int i=0;i<this->ui->phase_table->rowCount();i++){
                        colorByTable(i,false);
                    }
            //        out1Pix=processedPixmap->pixmap().scaled(x,y,Qt::AspectRatioMode::KeepAspectRatioByExpanding);
                    *out1Image=processedPixmap->pixmap().toImage().mirrored(false,true);
                    outImage=makePeriodic(out1Image)->convertToFormat(QImage::Format_Indexed8,colorTable);
                    processedPixmap->setPixmap(QPixmap::fromImage(outImage));
                    width=outImage.width();
                    height=outImage.height();
                    for (int j=0;j<y;++j){
                        for(int k=0;k<z;k++){
                            exportData[i][j][k]=outImage.pixelIndex(int(j*double(width)/y),int(k*double(height)/z));
                        }
                    }
                }
                break;
            case 1:
                for(int j=0;j<y;j++){
                    imageName=pathName+"/"+baseName+"."+QString("%1").arg(j+1,length,10,QChar('0'))+"."+suffixName;
                    loadImage(imageName);
                    clearProcessedImage();
                    for(int i=0;i<this->ui->phase_table->rowCount();i++){
                        colorByTable(i,false);
                    }
            //        out1Pix=processedPixmap->pixmap().scaled(x,y,Qt::AspectRatioMode::KeepAspectRatioByExpanding);
                    *out1Image=processedPixmap->pixmap().toImage().mirrored(false,true);
                    outImage=makePeriodic(out1Image)->convertToFormat(QImage::Format_Indexed8,colorTable);
                    processedPixmap->setPixmap(QPixmap::fromImage(outImage));
                    width=outImage.width();
                    height=outImage.height();
                    for (int i=0;i<x;++i){
                        for(int k=0;k<z;k++){
                            exportData[i][j][k]=outImage.pixelIndex(int(i*double(width)/x),int(k*double(height)/z));
                        }
                    }
                }
                break;
            case 2:
                for(int k=0;k<z;k++){
                    imageName=pathName+"/"+baseName+"."+QString("%1").arg(k+1,length,10,QChar('0'))+"."+suffixName;
                    loadImage(imageName);
                    clearProcessedImage();
                    for(int i=0;i<this->ui->phase_table->rowCount();i++){
                        colorByTable(i,false);
                    }
            //        out1Pix=processedPixmap->pixmap().scaled(x,y,Qt::AspectRatioMode::KeepAspectRatioByExpanding);
                    *out1Image=processedPixmap->pixmap().toImage().mirrored(false,true);
                    outImage=makePeriodic(out1Image)->convertToFormat(QImage::Format_Indexed8,colorTable);
                    processedPixmap->setPixmap(QPixmap::fromImage(outImage));
                    width=outImage.width();
                    height=outImage.height();
                    for (int i=0;i<x;++i){
                        for(int j=0;j<y;j++){
                            exportData[i][j][k]=outImage.pixelIndex(int(i*double(width)/x),int(j*double(height)/y));
                        }
                    }
                }
                break;
            }
        }else{
            qDebug()<<"cancel";
        }

    }
    ns=this->ui->ns_LE->text().toInt();
    nf=this->ui->nf_LE->text().toInt();
//        qDebug()<<"export:"<<exportData[1][1][ns+5];
    if(!nf==0){
        for (int i=0;i<x;++i){
            for(int j=0;j<y;j++){
                for(int k=0;k<ns;k++){
                    exportData[i][j][k]=0;
                }
                for(int k=nf+ns;k<z;k++){
                    exportData[i][j][k]=0;
                }
            }
        }
    }
//    qDebug()<<"export:"<<exportData[1][1][ns+5];
//    on_vectorValue_LE_textChanged(this->ui->vectorValue_LE->text());
    if(!load.isEmpty()){
        output.open(QFileInfo(load).absoluteFilePath().toStdString().c_str(),std::fstream::out);
        output << std::setw(6) << x << std::setw(6) << y << std::setw(6) << z << std::setw(80) << std::endl;
        for (int i=0;i<x;++i){
            for(int j=0;j<y;j++){
                for(int k=0;k<z;k++){
                    label=exportData[i][j][k];
//                    qDebug()<<"label:"<<label;
                    if(this->ui->scalarVectorSwitch_Combo->currentIndex()==0){
                        output << std::setw(6) << i+1 << std::setw(6) << j+1 << std::setw(6) <<k+1 << std::setw(6) << label << std::endl;
                    }else{
                        output << std::setw(6) << i+1 << std::setw(6) << j+1 << std::setw(6) <<k+1 << std::scientific << std::setw(16) <<std::setprecision(8) << outDomain[label][0] << std::setw(16) << outDomain[label][1] <<  std::setw(16) <<outDomain[label][2] << std::setw(16) <<outDomain[label][0] << std::setw(16) << outDomain[label][1] << std::setw(16) << outDomain[label][2] << std::endl;
                    }
                }
            }
        }

    }else{
        qDebug()<<"load is empty";
    }




}

void patternReco::on_scalarVectorSwitch_Combo_currentIndexChanged(int index)
{
    this->ui->scalarVector_SW->setCurrentIndex(index);

    if(index==0){
        this->ui->vectorValue_LE->setEnabled(false);
        this->ui->vectorValue_LB->setEnabled(false);
    }else{
        this->ui->vectorValue_LE->setEnabled(true);
        this->ui->vectorValue_LB->setEnabled(true);
    }
}

void patternReco::on_phaseNumber_LE_editingFinished()
{
    if(!this->ui->phaseNumber_LE->text().isEmpty()){
        int a=this->ui->phaseNumber_LE->text().toInt();
        if(a<=0 || a>27){
            QMessageBox *message=new QMessageBox(this);
            message->setText("Alert");
            message->setInformativeText("The phase label number must be integer between 1 to 27.");
            message->setStandardButtons(QMessageBox::Ok);
            message->exec();
        }
    }
}

void patternReco::on_vectorValue_LE_textChanged(const QString &arg1)
{
    double value=0.0;
    value=arg1.toDouble();
    outDomain[0][0]=0.0;outDomain[0][1]=0.0; outDomain[0][2]=0.0;
    outDomain[1][0]=value;outDomain[1][1]=value;outDomain[1][2]=value;
    outDomain[2][0]=-value;outDomain[2][1]=-value;outDomain[2][2]=-value;
    outDomain[3][0]=-value;outDomain[3][1]=value;outDomain[3][2]=value;
    outDomain[4][0]=value;outDomain[4][1]=-value;outDomain[4][2]=-value;
    outDomain[5][0]=-value;outDomain[5][1]=-value;outDomain[5][2]=value;
    outDomain[6][0]=value;outDomain[6][1]=value;outDomain[6][2]=-value;
    outDomain[7][0]=value;outDomain[7][1]=-value;outDomain[7][2]=value;
    outDomain[8][0]=-value;outDomain[8][1]=value;outDomain[8][2]=-value;
    outDomain[9][0]=value;outDomain[9][1]=value;outDomain[9][2]=0;
    outDomain[10][0]=-value;outDomain[10][1]=-value;outDomain[10][2]=0;
    outDomain[11][0]=value;outDomain[11][1]=-value;outDomain[11][2]=0;
    outDomain[12][0]=-value;outDomain[12][1]=value;outDomain[12][2]=0;
    outDomain[13][0]=value;outDomain[13][1]=0;outDomain[13][2]=value;
    outDomain[14][0]=-value;outDomain[14][1]=0;outDomain[14][2]=-value;
    outDomain[15][0]=value;outDomain[15][1]=0;outDomain[15][2]=-value;
    outDomain[16][0]=-value;outDomain[16][1]=0;outDomain[16][2]=value;
    outDomain[17][0]=0;outDomain[17][1]=value;outDomain[17][2]=value;
    outDomain[18][0]=0;outDomain[18][1]=-value;outDomain[18][2]=-value;
    outDomain[19][0]=0;outDomain[19][1]=value;outDomain[19][2]=-value;
    outDomain[20][0]=0;outDomain[20][1]=-value;outDomain[20][2]=value;
    outDomain[21][0]=value;outDomain[21][1]=0;outDomain[21][2]=0;
    outDomain[22][0]=-value;outDomain[22][1]=0;outDomain[22][2]=0;
    outDomain[23][0]=0;outDomain[23][1]=value;outDomain[23][2]=0;
    outDomain[24][0]=0;outDomain[24][1]=-value;outDomain[24][2]=0;
    outDomain[25][0]=0;outDomain[25][1]=0;outDomain[25][2]=value;
    outDomain[26][0]=0;outDomain[26][1]=0;outDomain[26][2]=-value;
    qDebug()<<"The value text changed";

}
