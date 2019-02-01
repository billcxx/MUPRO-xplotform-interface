#include "magnetic.h"
#include "ui_magnetic.h"
#include "generatebatch.h"
#include <QDebug>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <QDialog>
#include <QFileDialog>
#include <QFile>
#include <QListView>

magnetic::magnetic(QWidget *parent) :
    QDialog(parent),
//    QMainWindow(parent),
    ui(new Ui::magnetic)
{
    ui->setupUi(this);
    ui->choiceAnis_Combo->setView(new QListView());
    ui->choiceGrainStruct_Combo->setView(new QListView());
    ui->choiceHext_Combo->setView(new QListView());
    ui->choiceIslandShape_Combo->setView(new QListView());
    ui->choiceST_Combo->setView(new QListView());
    ui->choiceInitial_Combo->setView(new QListView());
    ui->flagElasConstrain_Combo->setView(new QListView());
    ui->choiceLLGSolver_Combo->setView(new QListView());
    ui->ezz_LB->setEnabled(false);
    ui->ezz_LE->setEnabled(false);
    ui->exz_LB->setEnabled(false);
    ui->exz_LE->setEnabled(false);
    ui->eyz_LB->setEnabled(false);
    ui->eyz_LE->setEnabled(false);
    lx=125;
    ly=125;
    lz=10;
    nx=50;
    ny=50;
    nz=2;
    ns=0;
    nf=0;
    choiceIslandShape=1;
    ni1=40;
    ni2=40;
    ni3=2;
    choiceGrainStruct=1;
    phiC=0;
    thetaC=0;
    psiC=0;
    M0=800e3;
    gamma=2.211e5;
    alphaM=0.1;
    flagAnisotropy=false;
    choiceAnisotropy=1;
    kc1=0;
    kc2=0;
    kc3=0;
    flagStrayField=true;
    flagPeriodic=false;
    nd11=0.0;
    nd22=0.0;
    nd33=0.0;
    nd12=0.0;
    nd13=0.0;
    nd23=0.0;
    choiceHext=1;
    hdc1=0.0;
    hdc2=0.0;
    hdc3=0.0;
    hac1=0.0;
    hac2=0.0;
    hac3=0.0;
    frequence=0;
    Aexch=1.3e-11;
    flagElastic=false;
    lam100=0;
    lam111=0;
    c11=0;
    c12=0;
    c44=0;
    cs11=0;
    cs12=0;
    cs44=0;
    flagConstrained=true;
    exx=0.00;
    eyy=0;
    exy=0;
    ezz=0.00;
    exz=0;
    eyz=0;
    recursionLimit=0;
    errorTolerance=0;
    flagST=true;
    choiceST=3;
    angleSH=0;
    etaSP=0;
    jElect1=1.0e12;
    jElect2=0;
    jElect3=0;
    sigmaFixed1=0;
    sigmaFixed2=0;
    sigmaFixed3=0;
    flagDMI=false;
    dDMI=0.0e-3;
    flagThermalFluc=false;
    temperature=0;
    choiceLLGSolver=1;
    dt=1.0e-13;
    kt0=0;
    ktmax=50000;
    ktOutTable=100;
    ktOutDist=10000;
    choiceInitialMag=0;
    axisInitialM1=0;
    axisInitialM2=0;
    axisInitialM3=0;
    flagOutH=false;
    flagOutE=false;
    flagOutS=false;



    updateCheckBox();
}
magnetic::~magnetic()
{
    delete ui;
}

void magnetic::keyPressEvent(QKeyEvent* ke){
    if(ke->key() == Qt::Key_Escape){

    }else{
         QDialog::keyPressEvent(ke);
    }
}

void magnetic::loadData(QString filedir){
    std::ifstream in;
    QByteArray dir1=filedir.toLatin1();
    const char *dir=dir1.data();
    qDebug()<<dir;
    in.open(dir);
    qDebug()<<in.is_open();
    in >> lx >>ly>>lz;
    in.ignore(1000000,'\n');
    in >> nx>>ny>>nz;
    in.ignore(1000000,'\n');
    in >> ns>>nf;
    in.ignore(1000000,'\n');
    in >> choiceIslandShape;
    in.ignore(1000000,'\n');
    in >> ni1 >> ni2 >> ni3;
    in.ignore(1000000,'\n');
    in >> choiceGrainStruct;
    in.ignore(1000000,'\n');
    in >> phiC >> thetaC >> psiC;
    in.ignore(1000000,'\n');
    in >> M0 >> gamma >> alphaM;
    in.ignore(1000000,'\n');
    in >> std::boolalpha >> flagAnisotropy;
    in.ignore(1000000,'\n');
    in >> choiceAnisotropy ;
    in.ignore(1000000,'\n');
    in >> kc1 >> kc2 >> kc3;
    in.ignore(1000000,'\n');

    in >> std::boolalpha >> flagStrayField;
    in.ignore(1000000,'\n');
    in >> std::boolalpha >> flagPeriodic;
    in.ignore(1000000,'\n');
    //in >> fhd1 >> fhd2 >> fhd3;
    in >> nd11 >> nd22 >> nd33;
    in.ignore(1000000,'\n');
    in >>nd23 >> nd13 >> nd12;
    in.ignore(1000000,'\n');
    in >> choiceHext ;
    in.ignore(1000000,'\n');
    in >> hdc1 >> hdc2 >> hdc3;
    in.ignore(1000000,'\n');
    in >> hac1 >> hac2 >> hac3;
    in.ignore(1000000,'\n');
    in >> frequence;
    in.ignore(1000000,'\n');
    in >> Aexch;
    in.ignore(1000000,'\n');
    in >> std::boolalpha >> flagElastic;
    in.ignore(1000000,'\n');
    in >> lam100 >> lam111 ;
    in.ignore(1000000,'\n');
    in >> c11 >> c12 >> c44;
    in.ignore(1000000,'\n');
    in >> cs11 >> cs12 >> cs44;
    in.ignore(1000000,'\n');
    in >> std::boolalpha >> flagConstrained;
    in.ignore(1000000,'\n');
    in >> exx >> eyy >> exy;
    in.ignore(1000000,'\n');
    in >> ezz >> exz >> eyz;
    in.ignore(1000000,'\n');
    in >> recursionLimit >> errorTolerance;
    in.ignore(1000000,'\n');

    in >> std::boolalpha >> flagST ;
    in.ignore(1000000,'\n');
    in >> choiceST;
    in.ignore(1000000,'\n');
    in >> angleSH;
    in.ignore(1000000,'\n');
    in >> etaSP;
    in.ignore(1000000,'\n');
    in >> KsiSTT ;
    in.ignore(1000000,'\n');
    in >>jElect1 >> jElect2 >> jElect3;
    in.ignore(1000000,'\n');
    in >> sigmaFixed1 >> sigmaFixed2 >> sigmaFixed3;
    in.ignore(1000000,'\n');
    in >> std:: boolalpha >> flagDMI;
    in.ignore(1000000,'\n');
    in >> dDMI;
    in.ignore(1000000,'\n');
    in >> std::boolalpha >> flagThermalFluc;
    in.ignore(1000000,'\n');
    in >> temperature;
    in.ignore(1000000,'\n');
    in >> choiceLLGSolver;
    in.ignore(1000000,'\n');

    in >> dt;
    in.ignore(1000000,'\n');
    in >> kt0 >> ktmax ;
    in.ignore(1000000,'\n');
    in >> ktOutTable >> ktOutDist;
    in.ignore(1000000,'\n');
    in >> choiceInitialMag;
    in.ignore(1000000,'\n');
    in >> axisInitialM1 >> axisInitialM2 >> axisInitialM3;
    in.ignore(1000000,'\n');

    in >> std::boolalpha >> flagOutH >> std::boolalpha >> flagOutE;
    in.ignore(1000000,'\n');
    in >> std::boolalpha >> flagOutS;
    in.ignore(1000000,'\n');
    in.close();




    qDebug()<<"in lx,ly,lz:"<<lx<<ly<<lz;
    qDebug()<<"in nx,ny,nz:"<<nx<<ny<<nz;
    qDebug()<<"in ns,nf:"<<ns<<nf;
    qDebug()<<"in M0,gamma,alphaM:"<<M0<<gamma<<alphaM;
    qDebug()<<"in choiceAnisotropy:"<<choiceAnisotropy;
    qDebug()<<"in kc1,kc2,kc3:" << kc1<<kc2<<kc3;
    qDebug()<<"in nd11,nd22,nd33:"<<nd11<<nd22<<nd33;
    qDebug()<<"in nd23,nd13,nd12:"<<nd23<<nd13<<nd12;
    qDebug()<<"in lam100,lam111:"<<lam100<<lam111;
    qDebug()<<"in c11,c12,c44:"<<c11<<c12<<c44;
    qDebug()<<"in Aexch:"<<Aexch;
    qDebug()<<"in choiceHext:"<<choiceHext;
    qDebug()<<"in hdc1,hdc2,hdc3:"<<hdc1<<hdc2<<hdc3;
    qDebug()<<"in hac1,hac2,hac3:"<<hac1<<hac2<<hac3;
    qDebug()<<"in frequency:"<<frequence;
    qDebug()<<"in flagAnisotropy:"<<flagAnisotropy;
    qDebug()<<"in flagPerioic:"<<flagPeriodic;
    qDebug()<<"in flagElastic:"<<flagElastic;
    qDebug()<<"in flagConstrained:"<<flagConstrained;
    qDebug()<<"in exx,eyy,exy:"<<exx<<eyy<<exy;
    qDebug()<<"in ezz,exz,eyz:"<<ezz<<exz<<eyz;
    qDebug()<<"in dt:"<<dt;
    qDebug()<<"in kt0,ktmax,ktprint:"<<kt0<<ktmax<<ktOutTable<<ktOutDist;
    qDebug()<<"in choiceInitialMag:"<<choiceInitialMag;
    qDebug()<<"in flagOutH:"<<flagOutH;
    qDebug()<<"in flagOutS:"<<flagOutS;
}

void magnetic::updateCheckBox(){
    if (ui->nf_LE->text().toInt()==0){
        ui->ni3_LB->setEnabled(true);
        ui->ni3_LE->setEnabled(true);
    }
    else{
        ui->ni3_LB->setEnabled(false);
        ui->ni3_LE->setEnabled(false);
    }

    if(ui->choiceIslandShape_Combo->currentIndex()!=0 && ui->nf_LE->text().toInt()==0){
        ui->ni1_LE->setEnabled(true);
        ui->ni2_LE->setEnabled(true);
        ui->ni1_LB->setEnabled(true);
        ui->ni2_LB->setEnabled(true);
    }else{
        ui->ni1_LB->setEnabled(false);
        ui->ni2_LB->setEnabled(false);
        ui->ni1_LE->setEnabled(true);
        ui->ni2_LE->setEnabled(true);
    }


    if(ui->choiceGrainStruct_Combo->currentIndex()==1){
        ui->phi_LE->setEnabled(true);
        ui->theta_LE->setEnabled(true);
        ui->psi_LE->setEnabled(true);
    }else{
        ui->phi_LE->setEnabled(false);
        ui->theta_LE->setEnabled(false);
        ui->psi_LE->setEnabled(false);
    }

    if(ui->flagAnisotropy_CB->isChecked()){
        ui->choiceAnis_Combo->setEnabled(true);
    }

    if(ui->flagAnisotropy_CB->isChecked()==true && ui->choiceAnis_Combo->currentIndex()==0){
        ui->k1_LE->setEnabled(true);
        ui->k2_LE->setEnabled(true);
        ui->k3_LE->setEnabled(true);
    }else if (ui->flagAnisotropy_CB->isChecked()==true && ui->choiceAnis_Combo->currentIndex()==1){
        ui->k1_LE->setEnabled(true);
        ui->k2_LE->setEnabled(false);
        ui->k3_LE->setEnabled(false);
    }else{
        ui->k1_LE->setEnabled(false);
        ui->k2_LE->setEnabled(false);
        ui->k3_LE->setEnabled(false);
    }

    if(ui->flagStrayField_CB->isChecked()){
        ui->flagPeriodic_CB->setEnabled(true);
    }else{
        ui->flagPeriodic_CB->setEnabled(false);
    }

    if (ui->flagStrayField_CB->isChecked() && ui->flagPeriodic_CB->isChecked()){
        ui->nd11_LE->setEnabled(true);
        ui->nd22_LE->setEnabled(true);
        ui->nd33_LE->setEnabled(true);
        ui->nd11_LB->setEnabled(true);
        ui->nd22_LB->setEnabled(true);
        ui->nd33_LB->setEnabled(true);
        ui->nd23_LE->setEnabled(true);
        ui->nd13_LE->setEnabled(true);
        ui->nd12_LE->setEnabled(true);
        ui->nd23_LB->setEnabled(true);
        ui->nd13_LB->setEnabled(true);
        ui->nd12_LB->setEnabled(true);
        ui->demag_LB->setEnabled(true);
    }
    else{
        ui->nd11_LE->setEnabled(false);
        ui->nd22_LE->setEnabled(false);
        ui->nd33_LE->setEnabled(false);
        ui->nd11_LB->setEnabled(false);
        ui->nd22_LB->setEnabled(false);
        ui->nd33_LB->setEnabled(false);
        ui->nd23_LE->setEnabled(false);
        ui->nd13_LE->setEnabled(false);
        ui->nd12_LE->setEnabled(false);
        ui->nd23_LB->setEnabled(false);
        ui->nd13_LB->setEnabled(false);
        ui->nd12_LB->setEnabled(false);
        ui->demag_LB->setEnabled(false);
    }

    if(ui->flagST_CB->isChecked()){
        ui->angleSH_LE->setEnabled(false);
        ui->etaSP_LE->setEnabled(false);
        ui->KsiSTT_LE->setEnabled(false);
        ui->angleSH_LB->setEnabled(false);
        ui->etaSP_LB->setEnabled(false);
        ui->KsiSTT_LB->setEnabled(false);
        ui->jElect1_LB->setEnabled(true);
        ui->jElect1_LE->setEnabled(true);
        ui->jElect2_LB->setEnabled(false);
        ui->jElect2_LE->setEnabled(false);
        ui->jElect3_LB->setEnabled(false);
        ui->jElect3_LE->setEnabled(false);
        if(ui->choiceST_Combo->currentIndex()==2){
            ui->KsiSTT_LE->setEnabled(true);
            ui->KsiSTT_LB->setEnabled(true);
            ui->jElect1_LB->setEnabled(true);
            ui->jElect1_LE->setEnabled(true);
            ui->jElect2_LB->setEnabled(true);
            ui->jElect2_LE->setEnabled(true);
            ui->jElect3_LB->setEnabled(true);
            ui->jElect3_LE->setEnabled(true);
            ui->sigmaFixed_LB->setEnabled(false);
            ui->sigmaFixed1_LE->setEnabled(false);
            ui->sigmaFixed2_LE->setEnabled(false);
            ui->sigmaFixed3_LE->setEnabled(false);
            ui->sigmaFixed1_LB->setEnabled(false);
            ui->sigmaFixed2_LB->setEnabled(false);
            ui->sigmaFixed3_LB->setEnabled(false);
        }else{
            ui->sigmaFixed_LB->setEnabled(true);
            ui->sigmaFixed1_LE->setEnabled(true);
            ui->sigmaFixed2_LE->setEnabled(true);
            ui->sigmaFixed3_LE->setEnabled(true);
            ui->sigmaFixed1_LB->setEnabled(true);
            ui->sigmaFixed2_LB->setEnabled(true);
            ui->sigmaFixed3_LB->setEnabled(true);
            if(ui->choiceST_Combo->currentIndex()==1){
                ui->etaSP_LE->setEnabled(true);
                ui->etaSP_LB->setEnabled(true);
            }else if(ui->choiceST_Combo->currentIndex()==0){
                ui->angleSH_LE->setEnabled(true);
                ui->angleSH_LB->setEnabled(true);
            }
        }
    }else{
        ui->angleSH_LE->setEnabled(false);
        ui->etaSP_LE->setEnabled(false);
        ui->KsiSTT_LE->setEnabled(false);
        ui->angleSH_LB->setEnabled(false);
        ui->etaSP_LB->setEnabled(false);
        ui->KsiSTT_LB->setEnabled(false);
        ui->jElect1_LB->setEnabled(false);
        ui->jElect1_LE->setEnabled(false);
        ui->jElect2_LB->setEnabled(false);
        ui->jElect2_LE->setEnabled(false);
        ui->jElect3_LB->setEnabled(false);
        ui->jElect3_LE->setEnabled(false);
    }


    if (ui->choiceHext_Combo->currentIndex()==1){
        ui->hdc1_LE->setEnabled(true);
        ui->hdc2_LE->setEnabled(true);
        ui->hdc3_LE->setEnabled(true);
        ui->hac1_LE->setEnabled(true);
        ui->hac2_LE->setEnabled(true);
        ui->hac3_LB->setEnabled(true);
        ui->hdc1_LB->setEnabled(true);
        ui->hdc2_LB->setEnabled(true);
        ui->hdc3_LB->setEnabled(true);
        ui->hac1_LB->setEnabled(true);
        ui->hac2_LB->setEnabled(true);
        ui->hac3_LB->setEnabled(true);
        ui->frequence_LB->setEnabled(true);
        ui->frequence_LE->setEnabled(true);
    }
    else{
        ui->hdc1_LE->setEnabled(false);
        ui->hdc2_LE->setEnabled(false);
        ui->hdc3_LE->setEnabled(false);
        ui->hac1_LE->setEnabled(false);
        ui->hac2_LE->setEnabled(false);
        ui->hac3_LE->setEnabled(false);
        ui->hdc1_LB->setEnabled(false);
        ui->hdc2_LB->setEnabled(false);
        ui->hdc3_LB->setEnabled(false);
        ui->hac1_LB->setEnabled(false);
        ui->hac2_LB->setEnabled(false);
        ui->hac3_LB->setEnabled(false);
        ui->frequence_LB->setEnabled(false);
        ui->frequence_LE->setEnabled(false);
    }

    if(ui->flagElastic_CB->isChecked()){
        ui->exx_LB->setEnabled(true);
        ui->exx_LE->setEnabled(true);
        ui->eyy_LB->setEnabled(true);
        ui->eyy_LE->setEnabled(true);
        ui->exy_LB->setEnabled(true);
        ui->exy_LE->setEnabled(true);
    }else{
        ui->exx_LB->setEnabled(false);
        ui->exx_LE->setEnabled(false);
        ui->eyy_LB->setEnabled(false);
        ui->eyy_LE->setEnabled(false);
        ui->exy_LB->setEnabled(false);
        ui->exy_LE->setEnabled(false);
    }

    if(ui->nf_LE->text().toInt()==0 && ui->ni3_LE->text().toInt()==0 && ui->flagElastic_CB->isChecked()){
        ui->flagElasConstrain_Combo->setEnabled(true);
        ui->flagElasConstrain_LB->setEnabled(true);
        ui->ezz_LB->setEnabled(true);
        ui->ezz_LE->setEnabled(true);
        ui->exz_LB->setEnabled(true);
        ui->exz_LE->setEnabled(true);
        ui->eyz_LB->setEnabled(true);
        ui->eyz_LE->setEnabled(true);
    }else{
        ui->flagElasConstrain_Combo->setEnabled(false);
        ui->flagElasConstrain_LB->setEnabled(false);
        ui->ezz_LB->setEnabled(false);
        ui->ezz_LE->setEnabled(false);
        ui->exz_LB->setEnabled(false);
        ui->exz_LE->setEnabled(false);
        ui->eyz_LB->setEnabled(false);
        ui->eyz_LE->setEnabled(false);
    }

    if(ui->choiceInitial_Combo->currentIndex()==2 || ui->choiceInitial_Combo->currentIndex()==3){
        ui->axisInitialM1_LE->setEnabled(true);
        ui->axisInitialM2_LE->setEnabled(true);
        ui->axisInitialM3_LE->setEnabled(true);
        ui->axisInitialM1_LB->setEnabled(true);
        ui->axisInitialM2_LB->setEnabled(true);
        ui->axisInitialM3_LB->setEnabled(true);
    }
    else{
        ui->axisInitialM1_LE->setEnabled(false);
        ui->axisInitialM2_LE->setEnabled(false);
        ui->axisInitialM3_LE->setEnabled(false);
        ui->axisInitialM1_LB->setEnabled(false);
        ui->axisInitialM2_LB->setEnabled(false);
        ui->axisInitialM3_LB->setEnabled(false);
    }





    if(ui->flagDMI_CB->isChecked()){
        ui->dDMI_LB->setEnabled(true);
        ui->dDMI_LE->setEnabled(true);
    }else{
        ui->dDMI_LB->setEnabled(false);
        ui->dDMI_LE->setEnabled(false);
    }


    if(ui->flagThermalFluc_CB->isChecked()==true){
        ui->temperature_LE->setEnabled(true);
        ui->temperature_LB->setEnabled(true);
    }else{
        ui->temperature_LE->setEnabled(false);
        ui->temperature_LB->setEnabled(false);
    }

}

void magnetic::setData(){
    ui->lx_LE->setText(QString::number(lx));
    ui->ly_LE->setText(QString::number(ly));
    ui->lz_LE->setText(QString::number(lz));
    ui->nx_LE->setText(QString::number(nx));
    ui->ny_LE->setText(QString::number(ny));
    ui->nz_LE->setText(QString::number(nz));
    ui->ns_LE->setText(QString::number(ns));
    ui->nf_LE->setText(QString::number(nf));
    ui->choiceIslandShape_Combo->setCurrentIndex(choiceIslandShape);
    ui->ni1_LE->setText(QString::number(ni1));
    ui->ni2_LE->setText(QString::number(ni2));
    ui->ni3_LE->setText(QString::number(ni3));
    ui->choiceGrainStruct_Combo->setCurrentIndex(choiceGrainStruct);
    ui->phi_LE->setText(QString::number(phiC));
    ui->psi_LE->setText(QString::number(psiC));
    ui->theta_LE->setText(QString::number(thetaC));

    ui->mag_sat_LE->setText(QString::number(M0));
    ui->gyro_ratio_LE->setText(QString::number(gamma));
    ui->damp_const_LE->setText(QString::number(alphaM));
    ui->flagAnisotropy_CB->setChecked(flagAnisotropy);
    ui->choiceAnis_Combo->setCurrentIndex(choiceAnisotropy-1);
    ui->k1_LE->setText(QString::number(kc1));
    ui->k2_LE->setText(QString::number(kc2));
    ui->k3_LE->setText(QString::number(kc3));
    ui->flagStrayField_CB->setChecked(flagStrayField);
    ui->flagPeriodic_CB->setChecked(flagPeriodic);
    ui->nd11_LE->setText(QString::number(nd11));
    ui->nd22_LE->setText(QString::number(nd22));
    ui->nd33_LE->setText(QString::number(nd33));
    ui->nd23_LE->setText(QString::number(nd23));
    ui->nd13_LE->setText(QString::number(nd13));
    ui->nd12_LE->setText(QString::number(nd12));
    ui->choiceHext_Combo->setCurrentIndex(choiceHext);
    ui->hdc1_LE->setText(QString::number(hdc1));
    ui->hdc2_LE->setText(QString::number(hdc2));
    ui->hdc3_LE->setText(QString::number(hdc3));
    ui->hac1_LE->setText(QString::number(hac1));
    ui->hac2_LE->setText(QString::number(hac2));
    ui->hac3_LE->setText(QString::number(hac3));
    ui->frequence_LE->setText(QString::number(frequence));
    ui->aexch_LE->setText(QString::number(Aexch));
    ui->flagElastic_CB->setChecked(flagElastic);
    ui->lam100_LE->setText(QString::number(lam100));
    ui->lam111_LE->setText(QString::number(lam111));
    ui->c11_LE->setText(QString::number(c11));
    ui->c12_LE->setText(QString::number(c12));
    ui->c44_LE->setText(QString::number(c44));
    ui->cs11_LE->setText(QString::number(cs11));
    ui->cs12_LE->setText(QString::number(cs12));
    ui->cs44_LE->setText(QString::number(cs44));

    ui->flagElasConstrain_Combo->setCurrentIndex(flagConstrained);
    ui->exx_LE->setText(QString::number(exx));
    ui->eyy_LE->setText(QString::number(eyy));
    ui->exy_LE->setText(QString::number(exy));
    ui->ezz_LE->setText(QString::number(ezz));
    ui->exz_LE->setText(QString::number(exz));
    ui->eyz_LE->setText(QString::number(eyz));
    ui->recursionLimit_LE->setText(QString::number(recursionLimit));
    ui->errorTotal_LE->setText(QString::number(errorTolerance));
    ui->flagST_CB->setChecked(flagST);
    ui->choiceST_Combo->setCurrentIndex(choiceST-1);
    ui->angleSH_LE->setText(QString::number(angleSH));
    ui->etaSP_LE->setText(QString::number(etaSP));
    ui->jElect1_LE->setText(QString::number(jElect1));
    ui->jElect2_LE->setText(QString::number(jElect2));
    ui->jElect3_LE->setText(QString::number(jElect3));
    ui->sigmaFixed1_LE->setText(QString::number(sigmaFixed1));
    ui->sigmaFixed2_LE->setText(QString::number(sigmaFixed2));
    ui->sigmaFixed3_LE->setText(QString::number(sigmaFixed3));
    ui->flagDMI_CB->setChecked(flagDMI);
    ui->dDMI_LE->setText(QString::number(dDMI));
    ui->flagThermalFluc_CB->setChecked(flagThermalFluc);
    ui->temperature_LE->setText(QString::number(temperature));
    ui->dt_LE->setText(QString::number(dt));
    ui->kt0_LE->setText(QString::number(kt0));
    ui->ktmax_LE->setText(QString::number(ktmax));
    ui->ktOutTable_LE->setText(QString::number(ktOutTable));
    ui->ktOutDist_LE->setText(QString::number(ktOutDist));
    ui->choiceInitial_Combo->setCurrentIndex(choiceInitialMag);
    ui->axisInitialM1_LE->setText(QString::number(axisInitialM1));
    ui->axisInitialM2_LE->setText(QString::number(axisInitialM2));
    ui->axisInitialM3_LE->setText(QString::number(axisInitialM3));
    ui->outputH_CB->setChecked(flagOutH);
    ui->outputE_CB->setChecked(flagOutE);
    ui->outputS_CB->setChecked(flagOutS);
    ui->KsiSTT_LE->setText(QString::number(KsiSTT));

    updateCheckBox();
}


void magnetic::getData(){
    lx=ui->lx_LE->text().toDouble();
    ly=ui->ly_LE->text().toDouble();
    lz=ui->lz_LE->text().toDouble();
    nz=ui->nx_LE->text().toInt();
    ny=ui->ny_LE->text().toInt();
    nz=ui->nz_LE->text().toInt();
    ns=ui->ns_LE->text().toInt();
    nf=ui->nf_LE->text().toInt();
    choiceIslandShape=ui->choiceIslandShape_Combo->currentIndex();
    ni1=ui->ni1_LE->text().toInt();
    ni2=ui->ni2_LE->text().toInt();
    ni3=ui->ni3_LE->text().toInt();
    choiceGrainStruct=ui->choiceGrainStruct_Combo->currentIndex();
    phiC=ui->phi_LE->text().toDouble();
    psiC=ui->psi_LE->text().toDouble();
    thetaC=ui->theta_LE->text().toDouble();

    M0=ui->mag_sat_LE->text().toDouble();
    gamma=ui->gyro_ratio_LE->text().toDouble();
    alphaM=ui->damp_const_LE->text().toDouble();
    flagAnisotropy=ui->flagAnisotropy_CB->isChecked();
    choiceAnisotropy=ui->choiceAnis_Combo->currentIndex()+1;
    kc1=ui->k1_LE->text().toDouble();
    kc2=ui->k2_LE->text().toDouble();
    kc3=ui->k3_LE->text().toDouble();
    flagStrayField=ui->flagStrayField_CB->isChecked();
    flagPeriodic=ui->flagPeriodic_CB->isChecked();
    nd11=ui->nd11_LE->text().toDouble();
    nd22=ui->nd22_LE->text().toDouble();
    nd33=ui->nd33_LE->text().toDouble();
    nd23=ui->nd23_LE->text().toDouble();
    nd13=ui->nd13_LE->text().toDouble();
    nd12=ui->nd12_LE->text().toDouble();
    choiceHext=ui->choiceHext_Combo->currentIndex();
    hdc1=ui->hdc1_LE->text().toDouble();
    hdc2=ui->hdc2_LE->text().toDouble();
    hdc3=ui->hdc3_LE->text().toDouble();
    hac1=ui->hac1_LE->text().toDouble();
    hac2=ui->hac2_LE->text().toDouble();
    hac3=ui->hac3_LE->text().toDouble();
    frequence=ui->frequence_LE->text().toDouble();
    Aexch=ui->aexch_LE->text().toDouble();
    flagElastic=ui->flagElastic_CB->isChecked();
    lam100=ui->lam100_LE->text().toDouble();
    lam111=ui->lam111_LE->text().toDouble();
    c11=ui->c11_LE->text().toDouble();
    c12=ui->c12_LE->text().toDouble();
    c44=ui->c44_LE->text().toDouble();
    cs11=ui->cs11_LE->text().toDouble();
    cs12=ui->cs12_LE->text().toDouble();
    cs44=ui->cs44_LE->text().toDouble();

    flagElastic=ui->flagElasConstrain_Combo->currentIndex();
    exx=ui->exx_LE->text().toDouble();
    eyy=ui->eyy_LE->text().toDouble();
    exy=ui->exy_LE->text().toDouble();
    ezz=ui->ezz_LE->text().toDouble();
    exz=ui->exz_LE->text().toDouble();
    eyz=ui->eyz_LE->text().toDouble();
    recursionLimit=ui->recursionLimit_LE->text().toInt();
    errorTolerance=ui->errorTotal_LE->text().toDouble();
    flagST=ui->flagST_CB->isChecked();
    choiceST=ui->choiceST_Combo->currentIndex()+1;
    angleSH=ui->angleSH_LE->text().toDouble();
    etaSP=ui->etaSP_LE->text().toDouble();
    jElect1=ui->jElect1_LE->text().toDouble();
    jElect2=ui->jElect2_LE->text().toDouble();
    jElect3=ui->jElect3_LE->text().toDouble();
    sigmaFixed1=ui->sigmaFixed1_LE->text().toDouble();
    sigmaFixed2=ui->sigmaFixed2_LE->text().toDouble();
    sigmaFixed3=ui->sigmaFixed3_LE->text().toDouble();
    flagDMI=ui->flagDMI_CB->isChecked();
    dDMI=ui->dDMI_LE->text().toDouble();
    flagThermalFluc=ui->flagThermalFluc_CB->isChecked();
    temperature=ui->temperature_LE->text().toDouble();
    dt=ui->dt_LE->text().toDouble();
    kt0=ui->kt0_LE->text().toInt();
    ktmax=ui->ktmax_LE->text().toInt();
    ktOutTable=ui->ktOutTable_LE->text().toInt();
    ktOutDist=ui->ktOutDist_LE->text().toInt();
    choiceInitialMag=ui->choiceInitial_Combo->currentIndex();
    axisInitialM1=ui->axisInitialM1_LE->text().toDouble();
    axisInitialM2=ui->axisInitialM2_LE->text().toDouble();
    axisInitialM3=ui->axisInitialM3_LE->text().toDouble();
    flagOutH=ui->outputH_CB->isChecked();
    flagOutE=ui->outputE_CB->isChecked();
    flagOutS=ui->outputS_CB->isChecked();
    KsiSTT=ui->KsiSTT_LE->text().toDouble();

    updateCheckBox();
}

void magnetic::on_loadFile_pressed()
{
    QFileDialog filedialog;
    filedialog.setFileMode(QFileDialog::AnyFile);
    filedialog.setNameFilter(tr("Input (*.in)"));
    filedialog.setOption(QFileDialog::ReadOnly);
    QString load=filedialog.getOpenFileName();
    qDebug()<<"Filename:"<<load;
    if(load!=""){
        loadData(load);
        this->raise();
        setData();
    }else{
        qDebug()<<"nothing to load";
    }
}

template <typename T> void magnetic::outFixed(QString filedir,std::string parameterName,T parameter){
    std::ofstream out;
    out.open(filedir.toStdString().c_str(),std::fstream::in | std::fstream::out | std::fstream::app);
    if(batchList.indexOf(QString::fromStdString(parameterName))!=-1){
        out << parameterName << " ";
    }else{
        out << std::fixed;
        out << parameter << " ";
    }
    out.close();
}

void magnetic::outScientific(QString filedir,std::string parameterName,double parameter){
    std::ofstream out;
    out.open(filedir.toStdString().c_str(),std::fstream::in | std::fstream::out | std::fstream::app);
    if(batchList.indexOf(QString::fromStdString(parameterName))!=-1){
        out << parameterName << " ";
    }else{
        out << std::scientific;
        out << parameter << " ";
    }
    out.close();
}

void magnetic::outBoolean(QString filedir,std::string parameterName,bool parameter){
    std::ofstream out;
    out.open(filedir.toStdString().c_str(),std::fstream::in | std::fstream::out | std::fstream::app);
    if(batchList.indexOf(QString::fromStdString(parameterName))!=-1){
        out << parameterName << " ";
    }else{
        out << std::boolalpha;
        out << parameter << " ";
    }
    out.close();
}

void magnetic::outEndl(QString filedir){
    std::ofstream out;
    out.open(filedir.toStdString().c_str(),std::fstream::in | std::fstream::out | std::fstream::app);
    out << "\n";
    out.close();
}
void magnetic::outputPbs(QString filedir){
    std::ofstream out;
    out.open(filedir.toStdString().c_str(),std::ios_base::binary);
    out << "#PBS -l nodes=1:ppn=1" << "\n";
    out << "#PBS -l walltime=24:00:00" << "\n";
    out << "#PBS -l pmem=2gb" << "\n";
    out << "#PBS -j oe" << "\n";
    out << "#PBS -N jobName" << "\n";
    out << "cd $PBS_O_WORKDIR" << "\n";
    out << "echo \"Job started on `hostname` at `date`\"" << "\n";
    out << "mpirun magnetic.exe" << "\n";
    out << "echo \"Job started on `hostname` at `date`\"" << "\n";
    out.close();
}

void magnetic::outputData(QString filedir){
    std::ofstream out;
    qDebug()<<filedir;
    qDebug()<<lx;
    getData();
    out.open(filedir.toStdString().c_str(),std::ios_base::binary);
    out.close();
    outFixed(filedir,"lx",lx);
    outFixed(filedir,"ly",ly);
    outFixed(filedir,"lz",lz);
    outEndl(filedir);
    outFixed(filedir,"nx",nx);
    outFixed(filedir,"ny",ny);
    outFixed(filedir,"nz",nz);
    outEndl(filedir);
    outFixed(filedir,"ns",ns);
    outFixed(filedir,"nf",nf);
    outEndl(filedir);
    outFixed(filedir,"choiceIsland",choiceIslandShape);
    outEndl(filedir);
    outFixed(filedir,"ni1",ni1);
    outFixed(filedir,"ni2",ni2);
    outFixed(filedir,"ni3",ni3);
    outEndl(filedir);
    outFixed(filedir,"choiceGrain",choiceGrainStruct);
    outEndl(filedir);
    outFixed(filedir,"phi",phiC);
    outFixed(filedir,"theta",thetaC);
    outFixed(filedir,"psi",psiC);
    outEndl(filedir);
    outScientific(filedir,"saturateMagn",M0);
    outScientific(filedir,"gyromagneticRatio",gamma);
    outScientific(filedir,"dampingConst",alphaM);
    outEndl(filedir);
    outBoolean(filedir,"flagAnisotropy",flagAnisotropy);
    outEndl(filedir);
    outFixed(filedir,"choiceAnisotropy",choiceAnisotropy);
    outEndl(filedir);
    outScientific(filedir,"anisotropy1",kc1);
    outScientific(filedir,"anisotropy2",kc2);
    outScientific(filedir,"anisotropy3",kc3);
    outEndl(filedir);
    outBoolean(filedir,"flagStray",flagStrayField);
    outEndl(filedir);
    outBoolean(filedir,"flagPeriodic",flagPeriodic);
    outEndl(filedir);
    outFixed(filedir,"demagn11",nd11);
    outFixed(filedir,"demagn22",nd22);
    outFixed(filedir,"demagn33",nd33);
    outEndl(filedir);
    outFixed(filedir,"demagn23",nd23);
    outFixed(filedir,"demagn13",nd13);
    outFixed(filedir,"demagn12",nd12);
    outEndl(filedir);
    outFixed(filedir,"choiceExternalH",choiceHext);
    outEndl(filedir);
    outFixed(filedir,"externalHDC1",hdc1);
    outFixed(filedir,"externalHDC2",hdc2);
    outFixed(filedir,"externalHDC3",hdc3);
    outEndl(filedir);
    outFixed(filedir,"externalHAC1",hac1);
    outFixed(filedir,"externalHAC2",hac2);
    outFixed(filedir,"externalHAC3",hac3);
    outEndl(filedir);
    outScientific(filedir,"frequency",frequence);
    outEndl(filedir);
    outScientific(filedir,"exchangeEnergyCoeff",Aexch);
    outEndl(filedir);
    outBoolean(filedir,"flagMagnetoElastic",flagElastic);
    outEndl(filedir);
    outScientific(filedir,"magnetoStriction100",lam100);
    outScientific(filedir,"magnetoStriction111",lam111);
    outEndl(filedir);
    outScientific(filedir,"CFilm11",c11);
    outScientific(filedir,"CFilm12",c12);
    outScientific(filedir,"CFilm44",c44);
    outEndl(filedir);
    outScientific(filedir,"CSub11",cs11);
    outScientific(filedir,"CSub12",cs12);
    outScientific(filedir,"CSub44",cs44);
    outEndl(filedir);
    outBoolean(filedir,"flagStrainBC",flagConstrained);
    outEndl(filedir);
    outFixed(filedir,"epsilon11",exx);
    outFixed(filedir,"epsilon22",eyy);
    outFixed(filedir,"epsilon12",exy);
    outEndl(filedir);
    outFixed(filedir,"epsilon33",exx);
    outFixed(filedir,"epsilon13",eyy);
    outFixed(filedir,"epsilon23",exy);
    outEndl(filedir);
    outFixed(filedir,"elasRecursionMax",recursionLimit);
    outFixed(filedir,"elasTolerance",errorTolerance);
    outEndl(filedir);
    outBoolean(filedir,"flagSpinTorque",flagST);
    outEndl(filedir);
    outFixed(filedir,"choiceSpinTorque",choiceST);
    outEndl(filedir);
    outFixed(filedir,"spinHallAngle",angleSH);
    outEndl(filedir);
    outFixed(filedir,"spinPolarConst",etaSP);
    outEndl(filedir);
    outFixed(filedir,"nonAdiabaticity",KsiSTT);
    outEndl(filedir);
    outScientific(filedir,"spinPolarCurrentDensity1",jElect1);
    outScientific(filedir,"spinPolarCurrentDensity2",jElect2);
    outScientific(filedir,"spinPolarCurrentDensity3",jElect3);
    outEndl(filedir);
    outFixed(filedir,"fixedLayerNormalizedMagn1",sigmaFixed1);
    outFixed(filedir,"fixedLayerNormalizedMagn2",sigmaFixed2);
    outFixed(filedir,"fixedLayerNormalizedMagn3",sigmaFixed3);
    outEndl(filedir);
    outBoolean(filedir,"flagDMI",flagDMI);
    outEndl(filedir);
    outScientific(filedir,"effectiveDMConst",dDMI);
    outEndl(filedir);
    outBoolean(filedir,"flagThermo",flagThermalFluc);
    outEndl(filedir);
    outFixed(filedir,"temperature",temperature);
    outEndl(filedir);
    outFixed(filedir,"choiceLLG",choiceLLGSolver);
    outEndl(filedir);
    outScientific(filedir,"deltaT",dt);
    outEndl(filedir);
    outFixed(filedir,"stepStart",kt0);
    outFixed(filedir,"stepFinish",ktmax);
    outEndl(filedir);
    outFixed(filedir,"intervalTableOut",ktOutTable);
    outFixed(filedir,"intervalDistOut",ktOutDist);
    outEndl(filedir);
    outFixed(filedir,"choiceInitialMagnDist",choiceInitialMag);
    outEndl(filedir);
    outFixed(filedir,"axis1",axisInitialM1);
    outFixed(filedir,"axis2",axisInitialM2);
    outFixed(filedir,"axis3",axisInitialM3);
    outEndl(filedir);
    outBoolean(filedir,"flagOutH",flagOutH);
    outBoolean(filedir,"flagOutE",flagOutE);
    outEndl(filedir);
    outBoolean(filedir,"flagOutS",flagOutS);


//    out.open("C:/Users/cxx/Desktop/input/compare.in");
//    out << std::fixed;
//    out << lx << " "<< ly << " "<<lz <<"\n";
//    out << nx << " " <<ny << " "<<nz <<"\n";
//    out << ns <<" "<<nf<<"\n";
//    out << choiceIslandShape <<"\n";
//    out << ni1 << " " << ni2 << " " << ni3<<"\n";
//    out << choiceGrainStruct << "\n";
//    out << phiC << " " << thetaC << " " << psiC <<"\n";
//    out << std::scientific << M0 << " "<<gamma<<" "<<alphaM<<"\n";
//    out << std::boolalpha<<flagAnisotropy <<"\n";
//    out << choiceAnisotropy <<"\n";
//    out << std::scientific << kc1 <<" "<<kc2<<" "<<kc3<<"\n";
//    out << std::boolalpha << flagStrayField <<"\n";
//    out << std::boolalpha << flagPeriodic <<"\n";
//    out << std::fixed<<nd11<<" "<<nd22<<" "<<nd33<<"\n";
//    out << std::fixed<<nd23<<" "<<nd13<<" "<<nd12<<"\n";
//    out <<choiceHext<<"\n";
//    out <<hdc1<<" "<<hdc2<<" "<<hdc3<<"\n";
//    out <<hac1<<" "<<hac2<<" "<<hac3<<"\n";
//    out << std::scientific<<frequence<<"\n";
//    out <<Aexch<<"\n";
//    out << std::boolalpha << flagElastic <<"\n";
//    out << std::scientific<<lam100<<" "<<lam111<<"\n";
//    out << std::scientific<<c11<<" "<<c12<<" "<<c44<<"\n";
//    out << std::scientific<<cs11<<" "<<cs12<<" "<<cs44<<"\n";
//    out << std::boolalpha<<flagConstrained<<"\n";
//    out << exx<<" "<<eyy<<" "<<exy<<"\n";
//    out << ezz<<" "<<exz<<" "<<eyz<<"\n";
//    out << recursionLimit << " " << errorTolerance<<"\n";
//    out << std::boolalpha << flagST<<"\n";
//    out << choiceST << "\n";
//    out << angleSH << "\n";
//    out << etaSP << "\n";
//    out << KsiSTT << "\n";
//    out << std::scientific << jElect1<< " "<< jElect2<< " "<< jElect3<<"\n";
//    out << std::fixed << sigmaFixed1 << " " << sigmaFixed2 << " " << sigmaFixed3<<"\n";
//    out << std::boolalpha << flagDMI << "\n";
//    out << std::scientific << dDMI << "\n";
//    out << std::boolalpha << flagThermalFluc << "\n";
//    out << std::fixed << temperature << "\n";
//    out << choiceLLGSolver << "\n";
//    out << std::scientific << dt<<"\n";
//    out << kt0<<" "<<ktmax<<"\n";
//    out <<ktOutTable<< " " << ktOutDist << "\n";
//    out << choiceInitialMag <<"\n";
//    out << std::fixed << axisInitialM1<<" "<<axisInitialM2<< " " << axisInitialM3 <<"\n";
//    out << std::boolalpha << flagOutH<< " " << flagOutE << "\n";
//    out << std::boolalpha << flagOutS<<"\n";
//    out.close();
//    qDebug()<<"closed";
}

void magnetic::on_Generate_pressed()
{
    QFileDialog filedialog;
    filedialog.setFileMode(QFileDialog::Directory);
    filedialog.setOption(QFileDialog::ShowDirsOnly);
    QString generateDir=filedialog.getExistingDirectory();
    qDebug()<<"Filename:"<<generateDir;
    QString filedir=generateDir+"/parameter.in";
    QString pbsdir=generateDir+"/run.pbs";

    qDebug()<<"Filedir:"<<filedir;
    lx=ui->lx_LE->text().toDouble();
    ly=ui->ly_LE->text().toDouble();
    lz=ui->lz_LE->text().toDouble();
    nx=ui->nx_LE->text().toInt();
    ny=ui->ny_LE->text().toInt();
    nz=ui->nz_LE->text().toInt();
    ns=ui->ns_LE->text().toInt();
    choiceIslandShape=ui->choiceIslandShape_Combo->currentIndex();
    ni1=ui->ni1_LE->text().toInt();
    ni2=ui->ni2_LE->text().toInt();
    ni3=ui->ni3_LE->text().toInt();
    choiceGrainStruct=ui->choiceGrainStruct_Combo->currentIndex();
    phiC=ui->phi_LE->text().toDouble();
    psiC=ui->psi_LE->text().toDouble();
    thetaC=ui->theta_LE->text().toDouble();

    M0=ui->mag_sat_LE->text().toDouble();
    gamma=ui->gyro_ratio_LE->text().toDouble();
    alphaM=ui->damp_const_LE->text().toDouble();
    choiceAnisotropy=ui->choiceAnis_Combo->currentIndex()+1;
    kc1=ui->k1_LE->text().toDouble();
    kc2=ui->k2_LE->text().toDouble();
    kc3=ui->k3_LE->text().toDouble();
    flagStrayField=ui->flagStrayField_CB->isChecked();
    flagPeriodic=ui->flagPeriodic_CB->isChecked();
    nd11=ui->nd11_LE->text().toDouble();
    nd22=ui->nd22_LE->text().toDouble();
    nd33=ui->nd33_LE->text().toDouble();
    nd12=ui->nd12_LE->text().toDouble();
    nd13=ui->nd13_LE->text().toDouble();
    nd23=ui->nd23_LE->text().toDouble();
    choiceHext=ui->choiceHext_Combo->currentIndex();
    hdc1=ui->hdc1_LE->text().toDouble();
    hdc2=ui->hdc2_LE->text().toDouble();
    hdc3=ui->hdc3_LE->text().toDouble();
    hac1=ui->hac1_LE->text().toDouble();
    hac2=ui->hac2_LE->text().toDouble();
    hac3=ui->hac3_LE->text().toDouble();
    frequence=ui->frequence_LE->text().toDouble();
    Aexch=ui->aexch_LE->text().toDouble();
    flagElastic=ui->flagElastic_CB->isChecked();
    lam100=ui->lam100_LE->text().toDouble();
    lam111=ui->lam111_LE->text().toDouble();
    c11=ui->c11_LE->text().toDouble();
    c12=ui->c12_LE->text().toDouble();
    c44=ui->c44_LE->text().toDouble();
    cs11=ui->cs11_LE->text().toDouble();
    cs12=ui->cs12_LE->text().toDouble();
    cs44=ui->cs44_LE->text().toDouble();
    flagConstrained=ui->flagElasConstrain_Combo->currentIndex();
    exx=ui->exx_LE->text().toDouble();
    eyy=ui->eyy_LE->text().toDouble();
    exy=ui->exy_LE->text().toDouble();
    ezz=ui->ezz_LE->text().toDouble();
    exz=ui->exz_LE->text().toDouble();
    eyz=ui->eyz_LE->text().toDouble();
    recursionLimit=ui->recursionLimit_LE->text().toInt();
    errorTolerance=ui->errorTotal_LE->text().toDouble();

    flagST=ui->flagST_CB->isChecked();
    choiceST=ui->choiceST_Combo->currentIndex()+1;
    angleSH=ui->angleSH_LE->text().toDouble();
    etaSP=ui->etaSP_LE->text().toDouble();
    jElect1=ui->jElect1_LE->text().toDouble();
    jElect2=ui->jElect2_LE->text().toDouble();
    jElect3=ui->jElect3_LE->text().toDouble();
    sigmaFixed1=ui->sigmaFixed1_LE->text().toDouble();
    sigmaFixed2=ui->sigmaFixed2_LE->text().toDouble();
    sigmaFixed3=ui->sigmaFixed3_LE->text().toDouble();
    flagDMI=ui->flagDMI_CB->isChecked();
    dDMI=ui->dDMI_LE->text().toDouble();
    flagThermalFluc=ui->flagThermalFluc_CB->isChecked();
    KsiSTT=ui->KsiSTT_LE->text().toDouble();

    dt=ui->dt_LE->text().toDouble();
    kt0=ui->kt0_LE->text().toInt();
    ktmax=ui->ktmax_LE->text().toInt();
    ktOutTable=ui->ktOutTable_LE->text().toInt();
    ktOutDist=ui->ktOutDist_LE->text().toInt();
    choiceLLGSolver=ui->choiceLLGSolver_Combo->currentIndex()+1;


    if (!generateDir.isNull()){
        outputData(filedir);
        outputPbs(pbsdir);
        this->accept();
    }else{
        qDebug()<<"Do nothing";
    }
}


void magnetic::on_nf_LE_editingFinished()
{
    nf=ui->nf_LE->text().toInt();
    if (nf==0 && ui->flagElastic_CB->isChecked()){
        ui->flagElasConstrain_Combo->setEnabled(true);
        ui->flagElasConstrain_LB->setEnabled(true);
        ui->ezz_LB->setEnabled(true);
        ui->ezz_LE->setEnabled(true);
        ui->exz_LB->setEnabled(true);
        ui->exz_LE->setEnabled(true);
        ui->eyz_LB->setEnabled(true);
        ui->eyz_LE->setEnabled(true);
    }
    else{
        ui->flagElasConstrain_Combo->setEnabled(false);
        ui->flagElasConstrain_LB->setEnabled(false);
        ui->ezz_LB->setEnabled(false);
        ui->ezz_LE->setEnabled(false);
        ui->exz_LB->setEnabled(false);
        ui->exz_LE->setEnabled(false);
        ui->eyz_LB->setEnabled(false);
        ui->eyz_LE->setEnabled(false);
    }
    if(nf==0){
        ui->ni3_LB->setEnabled(true);
        ui->ni3_LE->setEnabled(true);
    }else{
        ui->ni3_LB->setEnabled(false);
        ui->ni3_LE->setEnabled(false);
    }
    qDebug()<<"nf:"<<nf;
}

void magnetic::on_choiceAnis_Combo_activated(int index)
{
    choiceAnisotropy=ui->choiceAnis_Combo->currentIndex()+1;
    qDebug()<<"choiceAnisotropy:"<<choiceAnisotropy;
    if(choiceAnisotropy==1){
        ui->k2_LB->setEnabled(true);
        ui->k2_LE->setEnabled(true);
        ui->k3_LB->setEnabled(true);
        ui->k3_LE->setEnabled(true);
    }
    else{
        ui->k2_LB->setEnabled(false);
        ui->k2_LE->setEnabled(false);
        ui->k3_LB->setEnabled(false);
        ui->k3_LE->setEnabled(false);
    }
}

void magnetic::on_choiceHext_Combo_activated(int index)
{
    bool choice;
    choiceHext=ui->choiceHext_Combo->currentIndex();
    qDebug()<<"choiceHext:"<<choiceHext;
    if (choiceHext==1){
        choice=true;
        ui->hdc1_LE->setEnabled(true);
        ui->hdc2_LE->setEnabled(true);
        ui->hdc3_LE->setEnabled(true);
        ui->hac1_LE->setEnabled(true);
        ui->hac2_LE->setEnabled(true);
        ui->hac3_LB->setEnabled(true);
        ui->hdc1_LB->setEnabled(true);
        ui->hdc2_LB->setEnabled(true);
        ui->hdc3_LB->setEnabled(true);
        ui->hac1_LB->setEnabled(true);
        ui->hac2_LB->setEnabled(true);
        ui->hac3_LB->setEnabled(true);
        ui->frequence_LB->setEnabled(true);
        ui->frequence_LE->setEnabled(true);
    }
    else{
        choice=false;
        ui->hdc1_LE->setEnabled(false);
        ui->hdc2_LE->setEnabled(false);
        ui->hdc3_LE->setEnabled(false);
        ui->hac1_LE->setEnabled(false);
        ui->hac2_LE->setEnabled(false);
        ui->hac3_LE->setEnabled(false);
        ui->hdc1_LB->setEnabled(false);
        ui->hdc2_LB->setEnabled(false);
        ui->hdc3_LB->setEnabled(false);
        ui->hac1_LB->setEnabled(false);
        ui->hac2_LB->setEnabled(false);
        ui->hac3_LB->setEnabled(false);
        ui->frequence_LB->setEnabled(false);
        ui->frequence_LE->setEnabled(false);
    }
}

void magnetic::on_tabWidget_currentChanged(int index)
{
    
    this->adjustSize();
}

void magnetic::on_flagAnisotropy_CB_stateChanged(int arg1)
{
    flagAnisotropy=arg1;
    if(flagAnisotropy){
        ui->choiceAnis_Combo->setEnabled(true);
        ui->k1_LB->setEnabled(true);
        ui->k1_LE->setEnabled(true);
        if(choiceAnisotropy==1){
            ui->k2_LE->setEnabled(true);
            ui->k3_LE->setEnabled(true);
            ui->k2_LB->setEnabled(true);
            ui->k3_LB->setEnabled(true);
        }else{
            ui->k2_LE->setEnabled(false);
            ui->k3_LE->setEnabled(false);
            ui->k2_LB->setEnabled(false);
            ui->k3_LB->setEnabled(false);
        }
    }else{
        ui->choiceAnis_Combo->setEnabled(false);
        ui->k1_LE->setEnabled(false);
        ui->k1_LB->setEnabled(false);
        ui->k2_LE->setEnabled(false);
        ui->k3_LE->setEnabled(false);
        ui->k2_LB->setEnabled(false);
        ui->k3_LB->setEnabled(false);
    }

    qDebug()<<"flagAnisotropy:"<<flagAnisotropy;
}

void magnetic::on_flagPeriodic_CB_stateChanged(int arg1)
{
    flagPeriodic=arg1;
    if (flagPeriodic){
        ui->nd11_LE->setEnabled(true);
        ui->nd22_LE->setEnabled(true);
        ui->nd33_LE->setEnabled(true);
        ui->nd11_LB->setEnabled(true);
        ui->nd22_LB->setEnabled(true);
        ui->nd33_LB->setEnabled(true);
        ui->nd13_LE->setEnabled(true);
        ui->nd23_LE->setEnabled(true);
        ui->nd12_LE->setEnabled(true);
        ui->nd13_LB->setEnabled(true);
        ui->nd23_LB->setEnabled(true);
        ui->nd12_LB->setEnabled(true);
        ui->demag_LB->setEnabled(true);
    }
    else{
        ui->nd11_LE->setEnabled(false);
        ui->nd22_LE->setEnabled(false);
        ui->nd33_LE->setEnabled(false);
        ui->nd11_LB->setEnabled(false);
        ui->nd22_LB->setEnabled(false);
        ui->nd33_LB->setEnabled(false);
        ui->nd13_LE->setEnabled(false);
        ui->nd12_LE->setEnabled(false);
        ui->nd23_LE->setEnabled(false);
        ui->nd13_LB->setEnabled(false);
        ui->nd12_LB->setEnabled(false);
        ui->nd23_LB->setEnabled(false);
        ui->demag_LB->setEnabled(false);
    }
    qDebug()<<"flagPeriodic:"<<flagPeriodic;
}

void magnetic::on_flagElastic_CB_stateChanged(int arg1)
{
    flagElastic=arg1;
    if(flagElastic){
        ui->lam100_LE->setEnabled(true);
        ui->lam111_LE->setEnabled(true);
        ui->lam100_LB->setEnabled(true);
        ui->lam111_LB->setEnabled(true);
        ui->c11_LE->setEnabled(true);
        ui->c12_LE->setEnabled(true);
        ui->c44_LE->setEnabled(true);
        ui->cs11_LE->setEnabled(true);
        ui->cs12_LE->setEnabled(true);
        ui->cs44_LE->setEnabled(true);
        ui->c11_LB->setEnabled(true);
        ui->c12_LB->setEnabled(true);
        ui->c44_LB->setEnabled(true);
        ui->cs11_LB->setEnabled(true);
        ui->cs12_LB->setEnabled(true);
        ui->cs44_LB->setEnabled(true);
        ui->exx_LE->setEnabled(true);
        ui->eyy_LE->setEnabled(true);
        ui->exy_LE->setEnabled(true);
        ui->exx_LB->setEnabled(true);
        ui->eyy_LB->setEnabled(true);
        ui->exy_LB->setEnabled(true);
        ui->outputS_CB->setEnabled(true);
        ui->recursionLimit_LE->setEnabled(true);
        ui->errorTotal_LE->setEnabled(true);
    }else{
        ui->lam100_LB->setEnabled(false);
        ui->lam111_LB->setEnabled(false);
        ui->lam100_LE->setEnabled(false);
        ui->lam111_LE->setEnabled(false);
        ui->c11_LE->setEnabled(false);
        ui->c12_LE->setEnabled(false);
        ui->c44_LE->setEnabled(false);
        ui->cs11_LE->setEnabled(false);
        ui->cs12_LE->setEnabled(false);
        ui->cs44_LE->setEnabled(false);
        ui->c11_LB->setEnabled(false);
        ui->c12_LB->setEnabled(false);
        ui->c44_LB->setEnabled(false);
        ui->cs11_LB->setEnabled(false);
        ui->cs12_LB->setEnabled(false);
        ui->cs44_LB->setEnabled(false);
        ui->exx_LE->setEnabled(false);
        ui->eyy_LE->setEnabled(false);
        ui->exy_LE->setEnabled(false);
        ui->exx_LB->setEnabled(false);
        ui->eyy_LB->setEnabled(false);
        ui->exy_LB->setEnabled(false);
        ui->outputS_CB->setEnabled(false);
        ui->recursionLimit_LE->setEnabled(false);
        ui->errorTotal_LE->setEnabled(false);
    }

    if(flagElastic && ui->nf_LE->text().toInt()==0 && ui->ni3_LE->text().toInt()==0){
        ui->ezz_LE->setEnabled(true);
        ui->eyz_LE->setEnabled(true);
        ui->exz_LE->setEnabled(true);
        ui->ezz_LB->setEnabled(true);
        ui->eyz_LB->setEnabled(true);
        ui->exz_LB->setEnabled(true);
        ui->flagElasConstrain_Combo->setEnabled(true);
        ui->flagElasConstrain_LB->setEnabled(true);
    }else{
        ui->ezz_LE->setEnabled(false);
        ui->eyz_LE->setEnabled(false);
        ui->exz_LE->setEnabled(false);
        ui->ezz_LB->setEnabled(false);
        ui->eyz_LB->setEnabled(false);
        ui->exz_LB->setEnabled(false);
        ui->flagElasConstrain_Combo->setEnabled(false);
        ui->flagElasConstrain_LB->setEnabled(false);
    }
    qDebug()<<"flagElastic:"<<flagElastic;
}

void magnetic::on_flagElasConstrain_Combo_currentIndexChanged(int index)
{
    flagConstrained=index;

    qDebug()<<"flagConstrain:"<<flagConstrained;
}

void magnetic::on_outputH_CB_stateChanged(int arg1)
{
    flagOutH=arg1;
    qDebug()<<"flagOutHEff:"<<flagOutH;
}

void magnetic::on_outputS_CB_stateChanged(int arg1)
{
    flagOutS=arg1;
    qDebug()<<"flagOutHStr:"<<flagOutS;
}

//void magnetic::on_choiceInitial_Combo_activated(int index)
//{
//    choiceInitialMag=index;
//    if(choiceInitialMag==2){
//        ui->axisInitialM1_LE->setEnabled(true);
//        ui->axisInitialM2_LE->setEnabled(true);
//        ui->axisInitialM3_LE->setEnabled(true);
//    }
//    else{
//        ui->axisInitialM1_LE->setEnabled(false);
//        ui->axisInitialM2_LE->setEnabled(false);
//        ui->axisInitialM3_LE->setEnabled(false);
//    }
//}

void magnetic::on_flagST_CB_stateChanged(int arg1)
{
    flagST=arg1;
    if (flagST){
        ui->choiceST_Combo->setEnabled(true);
        ui->choiceST_LB->setEnabled(true);
//        ui->angleSH_LE->setEnabled(true);
//        ui->angleSH_LB->setEnabled(true);
//        ui->etaSP_LB->setEnabled(true);
//        ui->etaSP_LE->setEnabled(true);
//        ui->jElect1_LB->setEnabled(true);
//        ui->jElect1_LE->setEnabled(true);
//        ui->jElect2_LB->setEnabled(true);
//        ui->jElect2_LE->setEnabled(true);
//        ui->jElect3_LB->setEnabled(true);
//        ui->jElect3_LE->setEnabled(true);
//        ui->sigmaFixed_LB->setEnabled(true);
//        ui->sigmaFixed1_LE->setEnabled(true);
//        ui->sigmaFixed2_LE->setEnabled(true);
//        ui->sigmaFixed3_LE->setEnabled(true);
//        ui->sigmaFixed1_LB->setEnabled(true);
//        ui->sigmaFixed2_LB->setEnabled(true);
//        ui->sigmaFixed3_LB->setEnabled(true);
//        ui->KsiSTT_LB->setEnabled(true);
//        ui->KsiSTT_LE->setEnabled(true);
    }else{
        ui->choiceST_Combo->setEnabled(false);
        ui->choiceST_LB->setEnabled(false);
        ui->angleSH_LE->setEnabled(false);
        ui->angleSH_LB->setEnabled(false);
        ui->etaSP_LB->setEnabled(false);
        ui->etaSP_LE->setEnabled(false);
        ui->jElect1_LB->setEnabled(false);
        ui->jElect1_LE->setEnabled(false);
        ui->jElect2_LB->setEnabled(false);
        ui->jElect2_LE->setEnabled(false);
        ui->jElect3_LB->setEnabled(false);
        ui->jElect3_LE->setEnabled(false);
        ui->sigmaFixed_LB->setEnabled(false);
        ui->sigmaFixed1_LE->setEnabled(false);
        ui->sigmaFixed2_LE->setEnabled(false);
        ui->sigmaFixed3_LE->setEnabled(false);
        ui->sigmaFixed1_LB->setEnabled(false);
        ui->sigmaFixed2_LB->setEnabled(false);
        ui->sigmaFixed3_LB->setEnabled(false);
        ui->KsiSTT_LB->setEnabled(false);
        ui->KsiSTT_LE->setEnabled(false);
    }
    qDebug()<<"flagST:"<<flagST;
    updateCheckBox();
}

void magnetic::on_choiceGrainStruct_Combo_currentIndexChanged(int index)
{
    choiceGrainStruct=index;
    if(choiceGrainStruct==1){
        ui->phi_LB->setEnabled(true);
        ui->theta_LB->setEnabled(true);
        ui->psi_LB->setEnabled(true);
        ui->phi_LE->setEnabled(true);
        ui->theta_LE->setEnabled(true);
        ui->psi_LE->setEnabled(true);
    }else{
        ui->phi_LB->setEnabled(false);
        ui->theta_LB->setEnabled(false);
        ui->psi_LB->setEnabled(false);
        ui->phi_LE->setEnabled(false);
        ui->theta_LE->setEnabled(false);
        ui->psi_LE->setEnabled(false);
    }
    qDebug()<<"choiceGrainStruct:"<<choiceGrainStruct;
}

void magnetic::on_choiceIslandShape_Combo_currentIndexChanged(int index)
{
    choiceIslandShape=index;
    if((choiceIslandShape==1 || choiceIslandShape==2)&&ui->ni3_LE->text().toInt()!=0){
        ui->ni1_LB->setEnabled(true);
        ui->ni2_LB->setEnabled(true);
        ui->ni1_LE->setEnabled(true);
        ui->ni2_LE->setEnabled(true);
    }else{
        ui->ni1_LB->setEnabled(false);
        ui->ni2_LB->setEnabled(false);
        ui->ni1_LE->setEnabled(false);
        ui->ni2_LE->setEnabled(false);
    }
    qDebug()<<"choiceIslandShape:"<<choiceIslandShape;
}

void magnetic::on_choiceHext_Combo_currentIndexChanged(int index)
{
    choiceHext=index;
    if(choiceHext==1){
        ui->hdc1_LE->setEnabled(true);
        ui->hdc2_LE->setEnabled(true);
        ui->hdc3_LE->setEnabled(true);
        ui->hac1_LE->setEnabled(true);
        ui->hac1_LE->setEnabled(true);
        ui->hac1_LE->setEnabled(true);
    }else if(choiceHext==0){
        ui->hdc1_LE->setEnabled(false);
        ui->hdc2_LE->setEnabled(false);
        ui->hdc3_LE->setEnabled(false);
        ui->hac1_LE->setEnabled(false);
        ui->hac1_LE->setEnabled(false);
        ui->hac1_LE->setEnabled(false);
    }
}

void magnetic::on_choiceST_Combo_currentIndexChanged(int index)
{
    choiceST=index+1;
    ui->angleSH_LB->setEnabled(false);
    ui->angleSH_LE->setEnabled(false);
    ui->etaSP_LB->setEnabled(false);
    ui->etaSP_LE->setEnabled(false);
    ui->KsiSTT_LB->setEnabled(false);
    ui->KsiSTT_LE->setEnabled(false);
    ui->jElect1_LB->setEnabled(true);
    ui->jElect1_LE->setEnabled(true);
    ui->jElect2_LB->setEnabled(false);
    ui->jElect2_LE->setEnabled(false);
    ui->jElect3_LB->setEnabled(false);
    ui->jElect3_LE->setEnabled(false);
    if(choiceST==1 && ui->flagST_CB->isChecked()){
        ui->angleSH_LB->setEnabled(true);
        ui->angleSH_LE->setEnabled(true);

    }else if(choiceST==2 && ui->flagST_CB->isChecked()){
        ui->etaSP_LB->setEnabled(true);
        ui->etaSP_LE->setEnabled(true);
    }else if(choiceST==3 && ui->flagST_CB->isChecked()){
        ui->KsiSTT_LB->setEnabled(true);
        ui->KsiSTT_LE->setEnabled(true);
        ui->jElect2_LB->setEnabled(true);
        ui->jElect2_LE->setEnabled(true);
        ui->jElect3_LB->setEnabled(true);
        ui->jElect3_LE->setEnabled(true);
    }
}

void magnetic::on_flagDMI_CB_stateChanged(int arg1)
{
    flagDMI=arg1;
    if(flagDMI){
        ui->dDMI_LE->setEnabled(true);
        ui->dDMI_LB->setEnabled(true);
    }else{
        ui->dDMI_LB->setEnabled(false);
        ui->dDMI_LE->setEnabled(false);
    }
}

void magnetic::on_flagThermalFluc_CB_stateChanged(int arg1)
{
    flagThermalFluc=arg1;
    if(flagThermalFluc){
        ui->temperature_LE->setEnabled(true);
        ui->temperature_LB->setEnabled(true);
    }else{
        ui->temperature_LB->setEnabled(false);
        ui->temperature_LE->setEnabled(false);
    }
}

void magnetic::on_choiceInitial_Combo_currentIndexChanged(int index)
{
    choiceInitialMag=index;
    if(choiceInitialMag==2 || choiceInitialMag==3){
        ui->axisInitialM1_LE->setEnabled(true);
        ui->axisInitialM2_LE->setEnabled(true);
        ui->axisInitialM3_LE->setEnabled(true);
        ui->axisInitialM1_LB->setEnabled(true);
        ui->axisInitialM2_LB->setEnabled(true);
        ui->axisInitialM3_LB->setEnabled(true);
        ui->axisInitialM_LB->setEnabled(true);
    }else{
        ui->axisInitialM1_LE->setEnabled(false);
        ui->axisInitialM2_LE->setEnabled(false);
        ui->axisInitialM3_LE->setEnabled(false);
        ui->axisInitialM1_LB->setEnabled(false);
        ui->axisInitialM2_LB->setEnabled(false);
        ui->axisInitialM3_LB->setEnabled(false);
        ui->axisInitialM_LB->setEnabled(false);
    }
}

void magnetic::on_ni3_LE_editingFinished()
{
    ni3=ui->ni3_LE->text().toInt();
    if(ni3==0){
        ui->ni1_LB->setEnabled(true);
        ui->ni2_LB->setEnabled(true);
        ui->ni1_LE->setEnabled(true);
        ui->ni2_LE->setEnabled(true);
    }else{
        ui->ni1_LB->setEnabled(false);
        ui->ni2_LB->setEnabled(false);
        ui->ni1_LE->setEnabled(false);
        ui->ni2_LE->setEnabled(false);
    }
}

void magnetic::on_flagStrayField_CB_stateChanged(int arg1)
{
    flagStrayField=arg1;
    if(flagStrayField){
        ui->flagPeriodic_CB->setEnabled(true);
    }else{
        ui->flagPeriodic_CB->setEnabled(false);
    }
    if(flagStrayField&&ui->flagPeriodic_CB->isChecked()){

        ui->demag_LB->setEnabled(true);
        ui->nd11_LB->setEnabled(true);
        ui->nd11_LE->setEnabled(true);
        ui->nd22_LB->setEnabled(true);
        ui->nd22_LE->setEnabled(true);
        ui->nd33_LB->setEnabled(true);
        ui->nd33_LE->setEnabled(true);
        ui->nd13_LB->setEnabled(true);
        ui->nd13_LE->setEnabled(true);
        ui->nd12_LB->setEnabled(true);
        ui->nd12_LE->setEnabled(true);
        ui->nd23_LB->setEnabled(true);
        ui->nd23_LE->setEnabled(true);
    }else{
        ui->demag_LB->setEnabled(false);
        ui->nd11_LB->setEnabled(false);
        ui->nd11_LE->setEnabled(false);
        ui->nd22_LB->setEnabled(false);
        ui->nd22_LE->setEnabled(false);
        ui->nd33_LB->setEnabled(false);
        ui->nd33_LE->setEnabled(false);
        ui->nd12_LB->setEnabled(false);
        ui->nd12_LE->setEnabled(false);
        ui->nd13_LB->setEnabled(false);
        ui->nd13_LE->setEnabled(false);
        ui->nd23_LB->setEnabled(false);
        ui->nd23_LE->setEnabled(false);
    }
}

void magnetic::on_createBatch_PB_released()
{
    generateBatch *batch=new generateBatch(this,integerList,doubleList,booleanList);
    if(batch->exec()==QDialog::Accepted){
        batchList=batch->batchList;
        qDebug()<<batchList[0]<<batchList[1];
    }
}
