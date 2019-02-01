#include "phasetab.h"
#include "ui_phasetab.h"
#include "QListView"
#include <QDebug>

phaseTab::phaseTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::phaseTab)
{
    ui->setupUi(this);
}

phaseTab::~phaseTab()
{
    delete ui;
}


void phaseTab::passCPhase(double C[6][6]=0)
{
    double a;
    a=1000000000;
    C[0][0]=C11*a;C[0][1]=C12*a;C[0][2]=C13*a;C[0][3]=C14*a;C[0][4]=C15*a;C[0][5]=C16*a;
    C[1][0]=C21*a;C[1][1]=C22*a;C[1][2]=C23*a;C[1][3]=C24*a;C[1][4]=C25*a;C[1][5]=C26*a;
    C[2][0]=C31*a;C[2][1]=C32*a;C[2][2]=C33*a;C[2][3]=C34*a;C[2][4]=C35*a;C[2][5]=C36*a;
    C[3][0]=C41*a;C[3][1]=C42*a;C[3][2]=C43*a;C[3][3]=C44*a;C[3][4]=C45*a;C[3][5]=C46*a;
    C[4][0]=C51*a;C[4][1]=C52*a;C[4][2]=C53*a;C[4][3]=C54*a;C[4][4]=C55*a;C[4][5]=C56*a;
    C[5][0]=C61*a;C[5][1]=C62*a;C[5][2]=C63*a;C[5][3]=C64*a;C[5][4]=C65*a;C[5][5]=C66*a;

    qDebug()<<"passing"<<C[0][0]<<C11<<&C11<<this;
}

void phaseTab::passEpsPhase(double Eps[3][3]){
    Eps[0][0]=Eps11;Eps[0][1]=Eps12;Eps[0][2]=Eps13;
    Eps[1][0]=Eps21;Eps[1][1]=Eps22;Eps[1][2]=Eps23;
    Eps[2][0]=Eps31;Eps[2][1]=Eps32;Eps[2][2]=Eps33;
}

void phaseTab::passDPiezE(double DPiezE[3][6]){
    double a=1e12;
    DPiezE[0][0]=DPiezE11/a;DPiezE[0][1]=DPiezE12/a;DPiezE[0][2]=DPiezE13/a;DPiezE[0][3]=DPiezE14/a;DPiezE[0][4]=DPiezE15/a;DPiezE[0][5]=DPiezE16/a;
    DPiezE[1][0]=DPiezE21/a;DPiezE[1][1]=DPiezE22/a;DPiezE[1][2]=DPiezE23/a;DPiezE[1][3]=DPiezE24/a;DPiezE[1][4]=DPiezE25/a;DPiezE[1][5]=DPiezE26/a;
    DPiezE[2][0]=DPiezE31/a;DPiezE[2][1]=DPiezE32/a;DPiezE[2][2]=DPiezE33/a;DPiezE[2][3]=DPiezE34/a;DPiezE[2][4]=DPiezE35/a;DPiezE[2][5]=DPiezE36/a;}

void phaseTab::passMuPhase(double Mu[3][3]){
    Mu[0][0]=Mu11;Mu[0][1]=Mu12;Mu[0][2]=Mu13;
    Mu[1][0]=Mu21;Mu[1][1]=Mu22;Mu[1][2]=Mu23;
    Mu[2][0]=Mu31;Mu[2][1]=Mu32;Mu[2][2]=Mu33;
}

void phaseTab::passQPiezM(double QPiezM[3][6]){
    double a=100000000;
    QPiezM[0][0]=QPiezM11/a;QPiezM[0][1]=QPiezM12/a;QPiezM[0][2]=QPiezM13/a;QPiezM[0][3]=QPiezM14/a;QPiezM[0][4]=QPiezM15/a;QPiezM[0][5]=QPiezM16/a;
    QPiezM[1][0]=QPiezM21/a;QPiezM[1][1]=QPiezM22/a;QPiezM[1][2]=QPiezM23/a;QPiezM[1][3]=QPiezM24/a;QPiezM[1][4]=QPiezM25/a;QPiezM[1][5]=QPiezM26/a;
    QPiezM[2][0]=QPiezM31/a;QPiezM[2][1]=QPiezM32/a;QPiezM[2][2]=QPiezM33/a;QPiezM[2][3]=QPiezM34/a;QPiezM[2][4]=QPiezM35/a;QPiezM[2][5]=QPiezM36/a;
}

void phaseTab::passAlphaMEPhase(double AlphaME[3][3]){
    AlphaME[0][0]=AlphaME11;AlphaME[0][1]=AlphaME12;AlphaME[0][2]=AlphaME13;
    AlphaME[1][0]=AlphaME21;AlphaME[1][1]=AlphaME22;AlphaME[1][2]=AlphaME23;
    AlphaME[2][0]=AlphaME31;AlphaME[2][1]=AlphaME32;AlphaME[2][2]=AlphaME33;
}

void phaseTab::passDPhase(double D[3][3]){
    double a=100000;
    D[0][0]=D11/a;D[0][1]=D12/a;D[0][2]=D13/a;
    D[1][0]=D21/a;D[1][1]=D22/a;D[1][2]=D23/a;
    D[2][0]=D31/a;D[2][1]=D32/a;D[2][2]=D33/a;
}

void phaseTab::passKPhase(double K[3][3]){
    K[0][0]=K11;K[0][1]=K12;K[0][2]=K13;
    K[1][0]=K21;K[1][1]=K22;K[1][2]=K23;
    K[2][0]=K31;K[2][1]=K32;K[2][2]=K33;
}

void phaseTab::updateCPhase(double C[6][6])
{
    double a;
    a=1000000000;
    C11=C[0][0]/a;C12=C[0][1]/a;C13=C[0][2]/a;C14=C[0][3]/a;C15=C[0][4]/a;C16=C[0][5]/a;
    C21=C[1][0]/a;C22=C[1][1]/a;C23=C[1][2]/a;C24=C[1][3]/a;C25=C[1][4]/a;C26=C[1][5]/a;
    C31=C[2][0]/a;C32=C[2][1]/a;C33=C[2][2]/a;C34=C[2][3]/a;C35=C[2][4]/a;C36=C[2][5]/a;
    C41=C[3][0]/a;C42=C[3][1]/a;C43=C[3][2]/a;C44=C[3][3]/a;C45=C[3][4]/a;C46=C[3][5]/a;
    C51=C[4][0]/a;C52=C[4][1]/a;C53=C[4][2]/a;C54=C[4][3]/a;C55=C[4][4]/a;C56=C[4][5]/a;
    C61=C[5][0]/a;C62=C[5][1]/a;C63=C[5][2]/a;C64=C[5][3]/a;C65=C[5][4]/a;C66=C[5][5]/a;
    qDebug()<<"passing"<<C[0][0]<<C11<<a<<this;
    ui->c11->setText(QString::number(C11));
    ui->c12->setText(QString::number(C12));
    ui->c13->setText(QString::number(C13));
    ui->c14->setText(QString::number(C14));
    ui->c15->setText(QString::number(C15));
    ui->c16->setText(QString::number(C16));
    ui->c22->setText(QString::number(C22));
    ui->c23->setText(QString::number(C23));
    ui->c24->setText(QString::number(C24));
    ui->c25->setText(QString::number(C25));
    ui->c26->setText(QString::number(C26));
    ui->c33->setText(QString::number(C33));
    ui->c34->setText(QString::number(C34));
    ui->c35->setText(QString::number(C35));
    ui->c36->setText(QString::number(C36));
    ui->c44->setText(QString::number(C44));
    ui->c45->setText(QString::number(C45));
    ui->c46->setText(QString::number(C46));
    ui->c55->setText(QString::number(C55));
    ui->c56->setText(QString::number(C56));
    ui->c66->setText(QString::number(C66));
}

void phaseTab::updateEpsPhase(double Eps[3][3]){
    Eps11=Eps[0][0];Eps12=Eps[0][1];Eps13=Eps[0][2];
    Eps21=Eps[1][0];Eps22=Eps[1][1];Eps23=Eps[1][2];
    Eps31=Eps[2][0];Eps32=Eps[2][1];Eps33=Eps[2][2];
    ui->eps11->setText(QString::number(Eps11));
    ui->eps12->setText(QString::number(Eps12));
    ui->eps13->setText(QString::number(Eps13));
    ui->eps22->setText(QString::number(Eps22));
    ui->eps23->setText(QString::number(Eps23));
    ui->eps33->setText(QString::number(Eps33));
    qDebug()<<"eps"<<Eps[0][0]<<Eps11;
}

void phaseTab::updateMuPhase(double Mu[3][3]){
    Mu11=Mu[0][0];Mu12=Mu[0][1];Mu13=Mu[0][2];
    Mu21=Mu[1][0];Mu22=Mu[1][1];Mu23=Mu[1][2];
    Mu31=Mu[2][0];Mu32=Mu[2][1];Mu33=Mu[2][2];
    ui->mu11->setText(QString::number(Mu11));
    ui->mu12->setText(QString::number(Mu12));
    ui->mu13->setText(QString::number(Mu13));
    ui->mu22->setText(QString::number(Mu22));
    ui->mu23->setText(QString::number(Mu23));
    ui->mu33->setText(QString::number(Mu33));
    qDebug()<<"Mu"<<Mu[0][0]<<Mu11;
}

void phaseTab::updateDPhase(double D[3][3]){
    double a=100000;
    D11=D[0][0]*a;D12=D[0][1]*a;D13=D[0][2]*a;
    D21=D[1][0]*a;D22=D[1][1]*a;D23=D[1][2]*a;
    D31=D[2][0]*a;D32=D[2][1]*a;D33=D[2][2]*a;
    ui->dPhase11->setText(QString::number(D11));
    ui->dPhase12->setText(QString::number(D12));
    ui->dPhase13->setText(QString::number(D13));
    ui->dPhase22->setText(QString::number(D22));
    ui->dPhase23->setText(QString::number(D23));
    ui->dPhase33->setText(QString::number(D33));
    qDebug()<<"D"<<D[0][0]<<D11;
}

void phaseTab::updateKPhase(double K[3][3]){
    K11=K[0][0];K12=K[0][1];K13=K[0][2];
    K21=K[1][0];K22=K[1][1];K23=K[1][2];
    K31=K[2][0];K32=K[2][1];K33=K[2][2];
    ui->kPhase11->setText(QString::number(K11));
    ui->kPhase12->setText(QString::number(K12));
    ui->kPhase13->setText(QString::number(K13));
    ui->kPhase22->setText(QString::number(K22));
    ui->kPhase23->setText(QString::number(K23));
    ui->kPhase33->setText(QString::number(K33));
    qDebug()<<"K"<<K[0][0]<<K11;
}

void phaseTab::updateAlphaMEPhase(double AlphaME[3][3]){
    AlphaME11=AlphaME[0][0];AlphaME12=AlphaME[0][1];AlphaME13=AlphaME[0][2];
    AlphaME21=AlphaME[1][0];AlphaME22=AlphaME[1][1];AlphaME23=AlphaME[1][2];
    AlphaME31=AlphaME[2][0];AlphaME32=AlphaME[2][1];AlphaME33=AlphaME[2][2];
    ui->alphaME11->setText(QString::number(AlphaME11));
    ui->alphaME12->setText(QString::number(AlphaME12));
    ui->alphaME13->setText(QString::number(AlphaME13));
    ui->alphaME21->setText(QString::number(AlphaME21));
    ui->alphaME22->setText(QString::number(AlphaME22));
    ui->alphaME23->setText(QString::number(AlphaME23));
    ui->alphaME31->setText(QString::number(AlphaME31));
    ui->alphaME32->setText(QString::number(AlphaME32));
    ui->alphaME33->setText(QString::number(AlphaME33));
    qDebug()<<"alphaME"<<AlphaME[0][0]<<AlphaME11;
}

void phaseTab::updateDPiezE(double DPiezE[3][6]){
    double a=10000000000;
    DPiezE11=DPiezE[0][0]*a;DPiezE12=DPiezE[0][1]*a;DPiezE13=DPiezE[0][2]*a;DPiezE14=DPiezE[0][3]*a;DPiezE15=DPiezE[0][4]*a;DPiezE16=DPiezE[0][5]*a;
    DPiezE21=DPiezE[1][0]*a;DPiezE22=DPiezE[1][1]*a;DPiezE23=DPiezE[1][2]*a;DPiezE24=DPiezE[1][3]*a;DPiezE25=DPiezE[1][4]*a;DPiezE26=DPiezE[1][5]*a;
    DPiezE31=DPiezE[2][0]*a;DPiezE32=DPiezE[2][1]*a;DPiezE33=DPiezE[2][2]*a;DPiezE34=DPiezE[2][3]*a;DPiezE35=DPiezE[2][4]*a;DPiezE36=DPiezE[2][5]*a;
    ui->dPiezE11->setText(QString::number(DPiezE11));
    ui->dPiezE12->setText(QString::number(DPiezE12));
    ui->dPiezE13->setText(QString::number(DPiezE13));
    ui->dPiezE14->setText(QString::number(DPiezE14));
    ui->dPiezE15->setText(QString::number(DPiezE15));
    ui->dPiezE16->setText(QString::number(DPiezE16));
    ui->dPiezE21->setText(QString::number(DPiezE21));
    ui->dPiezE22->setText(QString::number(DPiezE22));
    ui->dPiezE23->setText(QString::number(DPiezE23));
    ui->dPiezE24->setText(QString::number(DPiezE24));
    ui->dPiezE25->setText(QString::number(DPiezE25));
    ui->dPiezE26->setText(QString::number(DPiezE26));
    ui->dPiezE31->setText(QString::number(DPiezE31));
    ui->dPiezE32->setText(QString::number(DPiezE32));
    ui->dPiezE33->setText(QString::number(DPiezE33));
    ui->dPiezE34->setText(QString::number(DPiezE34));
    ui->dPiezE35->setText(QString::number(DPiezE35));
    ui->dPiezE36->setText(QString::number(DPiezE36));
    qDebug()<<"dpiezE"<<DPiezE[0][0]<<DPiezE11;
}

void phaseTab::updateQPiezM(double QPiezM[3][6]){
    double a=100000000;
    QPiezM11=QPiezM[0][0]*a;QPiezM12=QPiezM[0][1]*a;QPiezM13=QPiezM[0][2]*a;QPiezM14=QPiezM[0][3]*a;QPiezM15=QPiezM[0][4]*a;QPiezM16=QPiezM[0][5]*a;
    QPiezM21=QPiezM[1][0]*a;QPiezM22=QPiezM[1][1]*a;QPiezM23=QPiezM[1][2]*a;QPiezM24=QPiezM[1][3]*a;QPiezM25=QPiezM[1][4]*a;QPiezM26=QPiezM[1][5]*a;
    QPiezM31=QPiezM[2][0]*a;QPiezM32=QPiezM[2][1]*a;QPiezM33=QPiezM[2][2]*a;QPiezM34=QPiezM[2][3]*a;QPiezM35=QPiezM[2][4]*a;QPiezM36=QPiezM[2][5]*a;
    ui->qPiezM11->setText(QString::number(QPiezM11));
    ui->qPiezM12->setText(QString::number(QPiezM12));
    ui->qPiezM13->setText(QString::number(QPiezM13));
    ui->qPiezM14->setText(QString::number(QPiezM14));
    ui->qPiezM15->setText(QString::number(QPiezM15));
    ui->qPiezM16->setText(QString::number(QPiezM16));
    ui->qPiezM21->setText(QString::number(QPiezM21));
    ui->qPiezM22->setText(QString::number(QPiezM22));
    ui->qPiezM23->setText(QString::number(QPiezM23));
    ui->qPiezM24->setText(QString::number(QPiezM24));
    ui->qPiezM25->setText(QString::number(QPiezM25));
    ui->qPiezM26->setText(QString::number(QPiezM26));
    ui->qPiezM31->setText(QString::number(QPiezM31));
    ui->qPiezM32->setText(QString::number(QPiezM32));
    ui->qPiezM33->setText(QString::number(QPiezM33));
    ui->qPiezM34->setText(QString::number(QPiezM34));
    ui->qPiezM35->setText(QString::number(QPiezM35));
    ui->qPiezM36->setText(QString::number(QPiezM36));
    qDebug()<<"QPiezM"<<QPiezM[0][0]<<QPiezM11;
}



void phaseTab::on_c12_textChanged(const QString &arg1)
{
    C12=arg1.toDouble();
    C21=arg1.toDouble();
    ui->c21->setText(arg1);
}

void phaseTab::on_c13_textChanged(const QString &arg1)
{
    C13=arg1.toDouble();
    C31=arg1.toDouble();
    ui->c31->setText(arg1);
}

void phaseTab::on_c14_textChanged(const QString &arg1)
{
    C14=arg1.toDouble();
    C41=arg1.toDouble();
    ui->c41->setText(arg1);
}

void phaseTab::on_c15_textChanged(const QString &arg1)
{
    C15=arg1.toDouble();
    C51=arg1.toDouble();
    ui->c51->setText(arg1);
}

void phaseTab::on_c16_textChanged(const QString &arg1)
{
    C16=arg1.toDouble();
    C61=arg1.toDouble();
    ui->c61->setText(arg1);
}

void phaseTab::on_c23_textChanged(const QString &arg1)
{
    C23=arg1.toDouble();
    C32=arg1.toDouble();
    ui->c32->setText(arg1);
}

void phaseTab::on_c24_textChanged(const QString &arg1)
{
    C24=arg1.toDouble();
    C42=arg1.toDouble();
    ui->c42->setText(arg1);
}

void phaseTab::on_c25_textChanged(const QString &arg1)
{
    C25=arg1.toDouble();
    C52=arg1.toDouble();
    ui->c52->setText(arg1);
}

void phaseTab::on_c26_textChanged(const QString &arg1)
{
    C26=arg1.toDouble();
    C62=arg1.toDouble();
    ui->c62->setText(arg1);
}

void phaseTab::on_c34_textChanged(const QString &arg1)
{
    C34=arg1.toDouble();
    C43=arg1.toDouble();
    ui->c43->setText(arg1);
}

void phaseTab::on_c35_textChanged(const QString &arg1)
{
    C35=arg1.toDouble();
    C53=arg1.toDouble();
    ui->c53->setText(arg1);
}

void phaseTab::on_c36_textChanged(const QString &arg1)
{
    C36=arg1.toDouble();
    C63=arg1.toDouble();
    ui->c63->setText(arg1);
}

void phaseTab::on_c45_textChanged(const QString &arg1)
{
    C45=arg1.toDouble();
    C54=arg1.toDouble();
    ui->c54->setText(arg1);
}

void phaseTab::on_c46_textChanged(const QString &arg1)
{
    C46=arg1.toDouble();
    C64=arg1.toDouble();
    ui->c64->setText(arg1);
}

void phaseTab::on_c56_textChanged(const QString &arg1)
{
    C56=arg1.toDouble();
    C65=arg1.toDouble();
    ui->c65->setText(arg1);
}

void phaseTab::on_c11_editingFinished()
{
    C11=ui->c11->text().toDouble();
    qDebug()<<"c11="<<C11<<&C11<<this;
}

void phaseTab::on_eps12_textChanged(const QString &arg1)
{
    Eps12=arg1.toDouble();
    Eps21=arg1.toDouble();
    ui->eps21->setText(arg1);
}

void phaseTab::on_eps13_textChanged(const QString &arg1)
{
    Eps13=arg1.toDouble();
    Eps31=arg1.toDouble();
    ui->eps31->setText(arg1);
}

void phaseTab::on_eps23_textChanged(const QString &arg1)
{
    Eps23=arg1.toDouble();
    Eps32=arg1.toDouble();
    ui->eps32->setText(arg1);
}

void phaseTab::on_dPiezE11_textChanged(const QString &arg1)
{
    DPiezE11=arg1.toDouble();
}

void phaseTab::on_dPiezE12_textChanged(const QString &arg1)
{
    DPiezE12=arg1.toDouble();
}

void phaseTab::on_dPiezE13_textChanged(const QString &arg1)
{
    DPiezE13=arg1.toDouble();
}

void phaseTab::on_dPiezE14_textChanged(const QString &arg1)
{
    DPiezE14=arg1.toDouble();
}

void phaseTab::on_dPiezE15_textChanged(const QString &arg1)
{
    DPiezE15=arg1.toDouble();
}

void phaseTab::on_dPiezE16_textChanged(const QString &arg1)
{
    DPiezE16=arg1.toDouble();
}

void phaseTab::on_dPiezE21_textChanged(const QString &arg1)
{
    DPiezE21=arg1.toDouble();
}

void phaseTab::on_dPiezE22_textChanged(const QString &arg1)
{
    DPiezE22=arg1.toDouble();
}

void phaseTab::on_dPiezE23_textChanged(const QString &arg1)
{
    DPiezE23=arg1.toDouble();
}

void phaseTab::on_dPiezE24_textChanged(const QString &arg1)
{
    DPiezE24=arg1.toDouble();
}

void phaseTab::on_dPiezE25_textChanged(const QString &arg1)
{
    DPiezE25=arg1.toDouble();
}

void phaseTab::on_dPiezE26_textChanged(const QString &arg1)
{
    DPiezE26=arg1.toDouble();
}

void phaseTab::on_dPiezE31_textChanged(const QString &arg1)
{
    DPiezE31=arg1.toDouble();
}

void phaseTab::on_dPiezE32_textChanged(const QString &arg1)
{
    DPiezE32=arg1.toDouble();
}

void phaseTab::on_dPiezE33_textChanged(const QString &arg1)
{
    DPiezE33=arg1.toDouble();
}

void phaseTab::on_dPiezE34_textChanged(const QString &arg1)
{
    DPiezE34=arg1.toDouble();
}

void phaseTab::on_dPiezE35_textChanged(const QString &arg1)
{
    DPiezE35=arg1.toDouble();
}

void phaseTab::on_dPiezE36_textChanged(const QString &arg1)
{
    DPiezE36=arg1.toDouble();
}

void phaseTab::on_mu11_textChanged(const QString &arg1)
{
    Mu11=arg1.toDouble();
}

void phaseTab::on_mu12_textChanged(const QString &arg1)
{
    Mu12=arg1.toDouble();
    Mu21=arg1.toDouble();
    ui->mu21->setText(arg1);
}

void phaseTab::on_mu13_textChanged(const QString &arg1)
{
    Mu13=arg1.toDouble();
    Mu31=arg1.toDouble();
    ui->mu31->setText(arg1);
}

void phaseTab::on_mu23_textChanged(const QString &arg1)
{
    Mu23=arg1.toDouble();
    Mu32=arg1.toDouble();
    ui->mu32->setText(arg1);
}

void phaseTab::on_mu22_textChanged(const QString &arg1)
{
    Mu22=arg1.toDouble();
}

void phaseTab::on_mu33_textChanged(const QString &arg1)
{
    Mu33=arg1.toDouble();
}

void phaseTab::on_qPiezM11_textChanged(const QString &arg1)
{
    QPiezM11=arg1.toDouble();
}

void phaseTab::on_qPiezM12_textChanged(const QString &arg1)
{
    QPiezM12=arg1.toDouble();
}

void phaseTab::on_qPiezM13_textChanged(const QString &arg1)
{
    QPiezM13=arg1.toDouble();
}

void phaseTab::on_qPiezM14_textChanged(const QString &arg1)
{
    QPiezM14=arg1.toDouble();
}

void phaseTab::on_qPiezM15_textChanged(const QString &arg1)
{
    QPiezM15=arg1.toDouble();
}

void phaseTab::on_qPiezM16_textChanged(const QString &arg1)
{
    QPiezM16=arg1.toDouble();
}

void phaseTab::on_qPiezM21_textChanged(const QString &arg1)
{
    QPiezM21=arg1.toDouble();
}

void phaseTab::on_qPiezM22_textChanged(const QString &arg1)
{
    QPiezM22=arg1.toDouble();
}

void phaseTab::on_qPiezM23_textChanged(const QString &arg1)
{
    QPiezM23=arg1.toDouble();
}

void phaseTab::on_qPiezM24_textChanged(const QString &arg1)
{
    QPiezM24=arg1.toDouble();
}

void phaseTab::on_qPiezM25_textChanged(const QString &arg1)
{
    QPiezM25=arg1.toDouble();
}

void phaseTab::on_qPiezM26_textChanged(const QString &arg1)
{
    QPiezM26=arg1.toDouble();
}

void phaseTab::on_qPiezM31_textChanged(const QString &arg1)
{
    QPiezM31=arg1.toDouble();
}

void phaseTab::on_qPiezM32_textChanged(const QString &arg1)
{
    QPiezM32=arg1.toDouble();
}

void phaseTab::on_qPiezM33_textChanged(const QString &arg1)
{
    QPiezM33=arg1.toDouble();
}

void phaseTab::on_qPiezM34_textChanged(const QString &arg1)
{
    QPiezM34=arg1.toDouble();
}

void phaseTab::on_qPiezM35_textChanged(const QString &arg1)
{
    QPiezM35=arg1.toDouble();
}

void phaseTab::on_qPiezM36_textChanged(const QString &arg1)
{
    QPiezM36=arg1.toDouble();
}

void phaseTab::on_alphaME11_textChanged(const QString &arg1)
{
    AlphaME11=arg1.toDouble();
}

void phaseTab::on_alphaME12_textChanged(const QString &arg1)
{
    AlphaME12=arg1.toDouble();
}

void phaseTab::on_alphaME13_textChanged(const QString &arg1)
{
    AlphaME13=arg1.toDouble();
}

void phaseTab::on_alphaME21_textChanged(const QString &arg1)
{
    AlphaME21=arg1.toDouble();
}

void phaseTab::on_alphaME22_textChanged(const QString &arg1)
{
    AlphaME22=arg1.toDouble();
}

void phaseTab::on_alphaME23_textChanged(const QString &arg1)
{
    AlphaME23=arg1.toDouble();
}

void phaseTab::on_alphaME31_textChanged(const QString &arg1)
{
    AlphaME31=arg1.toDouble();
}

void phaseTab::on_alphaME32_textChanged(const QString &arg1)
{
    AlphaME32=arg1.toDouble();
}

void phaseTab::on_alphaME33_textChanged(const QString &arg1)
{
    AlphaME33=arg1.toDouble();
}

void phaseTab::on_dPhase12_textChanged(const QString &arg1)
{
    D12=arg1.toDouble();
    D21=arg1.toDouble();
    ui->dPhase21->setText(arg1);
}

void phaseTab::on_dPhase13_textChanged(const QString &arg1)
{
    D13=arg1.toDouble();
    D31=arg1.toDouble();
    ui->dPhase31->setText(arg1);
}

void phaseTab::on_dPhase23_textChanged(const QString &arg1)
{
    D23=arg1.toDouble();
    D32=arg1.toDouble();
    ui->dPhase32->setText(arg1);
}

void phaseTab::on_dPhase11_textChanged(const QString &arg1)
{
    D11=arg1.toDouble();
}

void phaseTab::on_dPhase22_textChanged(const QString &arg1)
{
    D22=arg1.toDouble();
}

void phaseTab::on_dPhase33_textChanged(const QString &arg1)
{
    D33=arg1.toDouble();
}

void phaseTab::on_kPhase12_textChanged(const QString &arg1)
{
    K12=arg1.toDouble();
    K21=arg1.toDouble();
    ui->kPhase21->setText(arg1);
}

void phaseTab::on_kPhase13_textChanged(const QString &arg1)
{
    K13=arg1.toDouble();
    K31=arg1.toDouble();
    ui->kPhase31->setText(arg1);
}

void phaseTab::on_kPhase23_textChanged(const QString &arg1)
{
    K23=arg1.toDouble();
    K32=arg1.toDouble();
    ui->kPhase32->setText(arg1);
}

void phaseTab::on_kPhase11_textChanged(const QString &arg1)
{
    K11=arg1.toDouble();
}

void phaseTab::on_kPhase22_textChanged(const QString &arg1)
{
    K22=arg1.toDouble();
}

void phaseTab::on_kPhase33_textChanged(const QString &arg1)
{
    K33=arg1.toDouble();
}
