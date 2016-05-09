#include "magnetic.h"
#include "ui_magnetic.h"
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
    ui->ezz_LB->setEnabled(false);
    ui->ezz_LE->setEnabled(false);
    ui->exz_LB->setEnabled(false);
    ui->exz_LE->setEnabled(false);
    ui->eyz_LB->setEnabled(false);
    ui->eyz_LE->setEnabled(false);
    lx=400;
    ly=300;
    lz=5;
    nx=80;
    ny=60;
    nz=1;
    ns=0;
    nf=0;
    choiceIslandShape=2;
    ni1=6;
    ni2=4;
    ni3=0;
    choiceGrainStruct=1;
    phiC=0;
    thetaC=0;
    psiC=0;
    M0=4.85e5;
    gamma=2.21e5;
    alphaM=0.5;
    flagAnisotropy=false;
    choiceAnisotropy=1;
    kc1=3e5;
    kc2=3e5;
    kc3=3e5;
    flagStrayField=false;
    flagPeriodic=true;
    fhd1=0.1;
    fhd2=0.2;
    fhd3=0.3;
    choiceHext=0;
    hdc1=0.01;
    hdc2=0.3;
    hdc3=0.5;
    hac1=0.7;
    hac2=0.8;
    hac3=0.9;
    frequence=0.8e9;
    Aexch=0;
    flagElastic=true;
    lam100=-32.9e6;
    lam111=-32.9e6;
    c11=246.5e9;
    c12=147.3e9;
    c44=59.6e9;
    cs11=246.5e9;
    cs12=147.3e9;
    cs44=59.6e9;
    flagConstrained=true;
    exx=0.003;
    eyy=0;
    exy=0;
    ezz=-0.003;
    exz=0;
    eyz=0;
    recursionLimit=1000;
    errorTolerance=1.0e-4;
    flagST=false;
    choiceST=2;
    angleSH=0.0924;
    etaSP=0.5;
    jElect=2.0e13;
    sigmaFixed1=1;
    sigmaFixed2=0;
    sigmaFixed3=0;
    flagDMI=false;
    dDMI=3.0e-3;
    flagThermalFluc=false;
    temperature=298;
    dt=1.0e-14;
    kt0=0;
    ktmax=1000;
    ktOutTable=10;
    ktOutDist=100;
    choiceInitialMag=2;
    axisInitialM1=1;
    axisInitialM2=0;
    axisInitialM3=0;
    flagOutH=true;
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
    in >> fhd1 >> fhd2 >> fhd3;
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
    in >>jElect;
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

    in >> std::boolalpha >> flagOutH;
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
    qDebug()<<"in fhd1,fhd2,fhd3:"<<fhd1<<fhd2<<fhd3;
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
        ui->nd1_LE->setEnabled(true);
        ui->nd2_LE->setEnabled(true);
        ui->nd3_LE->setEnabled(true);
        ui->nd1_LB->setEnabled(true);
        ui->nd2_LB->setEnabled(true);
        ui->nd3_LB->setEnabled(true);
        ui->demag_LB->setEnabled(true);
    }
    else{
        ui->nd1_LE->setEnabled(false);
        ui->nd2_LE->setEnabled(false);
        ui->nd3_LE->setEnabled(false);
        ui->nd1_LB->setEnabled(false);
        ui->nd2_LB->setEnabled(false);
        ui->nd3_LB->setEnabled(false);
        ui->demag_LB->setEnabled(false);
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
    }
    else{
        ui->axisInitialM1_LE->setEnabled(false);
        ui->axisInitialM2_LE->setEnabled(false);
        ui->axisInitialM3_LE->setEnabled(false);
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
    ui->nd1_LE->setText(QString::number(fhd1));
    ui->nd2_LE->setText(QString::number(fhd2));
    ui->nd3_LE->setText(QString::number(fhd3));
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
    ui->jElect_LE->setText(QString::number(jElect));
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
    ui->outputS_CB->setChecked(flagOutS);

    ui->theta_LE->setText(QString::number(thetaC));
    ui->phi_LE->setText(QString::number(phiC));
    ui->psi_LE->setText(QString::number(psiC));

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

void magnetic::outputData(QString filedir){
    std::ofstream out;
    const char *dir=filedir.toLatin1();
    out.open(dir);
    out << std::fixed;
    out << lx << " "<< ly << " "<<lz <<"\n";
    out << nx << " " <<ny << " "<<nz <<"\n";
    out << ns <<" "<<nf<<"\n";
    out << choiceIslandShape <<"\n";
    out << ni1 << " " << ni2 << " " << ni3<<"\n";
    out << choiceGrainStruct << "\n";
    out << phiC << " " << thetaC << " " << psiC <<"\n";
    out << std::scientific << M0 << " "<<gamma<<" "<<alphaM<<"\n";
    out << std::boolalpha<<flagAnisotropy <<"\n";
    out << choiceAnisotropy <<"\n";
    out << std::scientific << kc1 <<" "<<kc2<<" "<<kc3<<"\n";
    out << std::boolalpha << flagStrayField <<"\n";
    out << std::boolalpha << flagPeriodic <<"\n";
    out << std::fixed<<fhd1<<" "<<fhd2<<" "<<fhd3<<"\n";
    out <<choiceHext<<"\n";
    out <<hdc1<<" "<<hdc2<<" "<<hdc3<<"\n";
    out <<hac1<<" "<<hac2<<" "<<hac3<<"\n";
    out << std::scientific<<frequence<<"\n";
    out <<Aexch<<"\n";
    out << std::boolalpha << flagElastic <<"\n";
    out << std::scientific<<lam100<<" "<<lam111<<"\n";
    out << std::scientific<<c11<<" "<<c12<<" "<<c44<<"\n";
    out << std::scientific<<cs11<<" "<<cs12<<" "<<cs44<<"\n";
    out << std::boolalpha<<flagConstrained<<"\n";
    out << exx<<" "<<eyy<<" "<<exy<<"\n";
    out << ezz<<" "<<exz<<" "<<eyz<<"\n";
    out << recursionLimit << " " << errorTolerance<<"\n";
    out << std::boolalpha << flagST<<"\n";
    out << choiceST << "\n";
    out << angleSH << "\n";
    out << etaSP << "\n";
    out << std::scientific << jElect<<"\n";
    out << std::fixed << sigmaFixed1 << " " << sigmaFixed2 << " " << sigmaFixed3<<"\n";
    out << std::boolalpha << flagDMI << "\n";
    out << std::scientific << dDMI << "\n";
    out << std::boolalpha << flagThermalFluc << "\n";
    out << std::fixed << temperature << "\n";
    out << std::scientific << dt<<"\n";
    out << kt0<<" "<<ktmax<<"\n";
    out <<ktOutTable<< " " << ktOutDist << "\n";
    out << choiceInitialMag <<"\n";
    out << std::fixed << axisInitialM1<<" "<<axisInitialM2<< " " << axisInitialM3 <<"\n";
    out << std::boolalpha << flagOutH<<"\n";
    out << std::boolalpha << flagOutS<<"\n";
    out.close();
}

void magnetic::on_Generate_pressed()
{
    QFileDialog filedialog;
    filedialog.setFileMode(QFileDialog::Directory);
    filedialog.setOption(QFileDialog::ShowDirsOnly);
    QString generateDir=filedialog.getExistingDirectory();
    qDebug()<<"Filename:"<<generateDir;
    QString filedir=generateDir+"/parameter.in";

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
    fhd1=ui->nd1_LE->text().toDouble();
    fhd2=ui->nd2_LE->text().toDouble();
    fhd3=ui->nd3_LE->text().toDouble();
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
    jElect=ui->jElect_LE->text().toDouble();
    sigmaFixed1=ui->sigmaFixed1_LE->text().toDouble();
    sigmaFixed2=ui->sigmaFixed2_LE->text().toDouble();
    sigmaFixed3=ui->sigmaFixed3_LE->text().toDouble();
    flagDMI=ui->flagDMI_CB->isChecked();
    dDMI=ui->dDMI_LE->text().toDouble();
    flagThermalFluc=ui->flagThermalFluc_CB->isChecked();

    dt=ui->dt_LE->text().toDouble();
    kt0=ui->kt0_LE->text().toInt();
    ktmax=ui->ktmax_LE->text().toInt();
    ktOutTable=ui->ktOutTable_LE->text().toInt();
    ktOutDist=ui->ktOutDist_LE->text().toInt();


    if (!generateDir.isNull()){
        outputData(filedir);
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
        ui->nd1_LE->setEnabled(true);
        ui->nd2_LE->setEnabled(true);
        ui->nd3_LE->setEnabled(true);
        ui->nd1_LB->setEnabled(true);
        ui->nd2_LB->setEnabled(true);
        ui->nd3_LB->setEnabled(true);
        ui->demag_LB->setEnabled(true);
    }
    else{
        ui->nd1_LE->setEnabled(false);
        ui->nd2_LE->setEnabled(false);
        ui->nd3_LE->setEnabled(false);
        ui->nd1_LB->setEnabled(false);
        ui->nd2_LB->setEnabled(false);
        ui->nd3_LB->setEnabled(false);
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
    }else{
        ui->lam100_LB->setEnabled(false);
        ui->lam111_LB->setEnabled(false);
        ui->lam100_LE->setEnabled(false);
        ui->lam111_LE->setEnabled(false);
        ui->c11_LE->setEnabled(false);
        ui->c12_LE->setEnabled(false);
        ui->c44_LE->setEnabled(false);
        ui->cs11_LE->setEnabled(false);
        ui->cs11_LE->setEnabled(false);
        ui->cs11_LE->setEnabled(false);
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

void magnetic::on_choiceInitial_Combo_activated(int index)
{
    choiceInitialMag=index;
    if(choiceInitialMag==2){
        ui->axisInitialM1_LE->setEnabled(true);
        ui->axisInitialM2_LE->setEnabled(true);
        ui->axisInitialM3_LE->setEnabled(true);
    }
    else{
        ui->axisInitialM1_LE->setEnabled(false);
        ui->axisInitialM2_LE->setEnabled(false);
        ui->axisInitialM3_LE->setEnabled(false);
    }
}

void magnetic::on_flagST_CB_stateChanged(int arg1)
{
    flagST=arg1;
    if (flagST){
        ui->choiceST_Combo->setEnabled(true);
        ui->choiceST_LB->setEnabled(true);
        ui->angleSH_LE->setEnabled(true);
        ui->angleSH_LB->setEnabled(true);
        ui->etaSP_LB->setEnabled(true);
        ui->etaSP_LE->setEnabled(true);
        ui->jElect_LB->setEnabled(true);
        ui->jElect_LE->setEnabled(true);
        ui->sigmaFixed_LB->setEnabled(true);
        ui->sigmaFixed1_LE->setEnabled(true);
        ui->sigmaFixed2_LE->setEnabled(true);
        ui->sigmaFixed3_LE->setEnabled(true);
        ui->sigmaFixed1_LB->setEnabled(true);
        ui->sigmaFixed2_LB->setEnabled(true);
        ui->sigmaFixed3_LB->setEnabled(true);
    }else{
        ui->choiceST_Combo->setEnabled(false);
        ui->choiceST_LB->setEnabled(false);
        ui->angleSH_LE->setEnabled(false);
        ui->angleSH_LB->setEnabled(false);
        ui->etaSP_LB->setEnabled(false);
        ui->etaSP_LE->setEnabled(false);
        ui->jElect_LB->setEnabled(false);
        ui->jElect_LE->setEnabled(false);
        ui->sigmaFixed_LB->setEnabled(false);
        ui->sigmaFixed1_LE->setEnabled(false);
        ui->sigmaFixed2_LE->setEnabled(false);
        ui->sigmaFixed3_LE->setEnabled(false);
        ui->sigmaFixed1_LB->setEnabled(false);
        ui->sigmaFixed2_LB->setEnabled(false);
        ui->sigmaFixed3_LB->setEnabled(false);
    }
    qDebug()<<"flagST:"<<flagST;
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
    if(choiceST==1 && ui->flagST_CB->isChecked()){
        ui->angleSH_LB->setEnabled(true);
        ui->angleSH_LE->setEnabled(true);
        ui->etaSP_LB->setEnabled(false);
        ui->etaSP_LE->setEnabled(false);
    }else if(choiceST==2 && ui->flagST_CB->isChecked()){
        ui->angleSH_LB->setEnabled(false);
        ui->angleSH_LE->setEnabled(false);
        ui->etaSP_LB->setEnabled(true);
        ui->etaSP_LE->setEnabled(true);
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
        ui->demag_LB->setEnabled(true);
        ui->nd1_LB->setEnabled(true);
        ui->nd1_LE->setEnabled(true);
        ui->nd2_LB->setEnabled(true);
        ui->nd2_LE->setEnabled(true);
        ui->nd3_LB->setEnabled(true);
        ui->nd3_LE->setEnabled(true);
        ui->flagPeriodic_CB->setEnabled(true);
    }else{
        ui->flagPeriodic_CB->setEnabled(false);
        ui->demag_LB->setEnabled(false);
        ui->nd1_LB->setEnabled(false);
        ui->nd1_LE->setEnabled(false);
        ui->nd2_LB->setEnabled(false);
        ui->nd2_LE->setEnabled(false);
        ui->nd3_LB->setEnabled(false);
        ui->nd3_LE->setEnabled(false);
        ui->flagPeriodic_CB->setEnabled(false);
    }
}
