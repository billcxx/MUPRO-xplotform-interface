#include "effectivepropertyinput.h"
#include "ui_effectivepropertyinput.h"

#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QListView>
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;




effectivePropertyInput::effectivePropertyInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::effectivePropertyInput)
{
    ui->setupUi(this);
    int index;
    index=ui->choiceCalcTypecombo->currentIndex();
    if (index==1){
        ui->Appliedfield->show();
        ui->tabWidget->setMinimumHeight(720);
        ui->tabWidget->setMaximumHeight(720);
//        ui->System->setMinimumHeight(400);
//        ui->System->setMaximumHeight(400);
    }else if(index==0){
        ui->Appliedfield->hide();
        ui->tabWidget->setMinimumHeight(350);
        ui->tabWidget->setMaximumHeight(350);
//        ui->System->setMinimumHeight(205);
//        ui->System->setMaximumHeight(205);
    }
    this->adjustSize();
    this->ui->choiceCalcTypecombo->setView(new QListView());
    this->ui->systemCombo->setView(new QListView());
    this->ui->strucInputCombo->setView(new QListView());
    this->ui->elasticBCcombo->setView(new QListView());
}

effectivePropertyInput::~effectivePropertyInput()
{
    delete ui;
}

void effectivePropertyInput::outputData(QString filedir){
    double c[6][6]={{0}};
    double eps[3][3]={{0}};
    double dpiezE[3][6]={{0}};
    double mu[3][3]={{0}};
    double qpiezM[3][6]={{0}};
    double alphaME[3][3]={{0}};
    double d[3][3]={{0}};
    double k[3][3]={{0}};
    int id=1;
    std::ofstream out;
    //get the values

    nx=ui->nx_LE->text().toInt();
    ny=ui->ny_LE->text().toInt();
    nz=ui->nz_LE->text().toInt();
    lx=ui->lx_LE->text().toDouble();
    ly=ui->ly_LE->text().toDouble();
    lz=ui->lz_LE->text().toDouble();
    choiceSystem=ui->systemCombo->currentIndex()+1;
    nPhase = ui->numberofPhase_LE->text().toInt();
    choiceStructFormat=ui->strucInputCombo->currentIndex()+1;
    choiceCalcType=ui->choiceCalcTypecombo->currentIndex()+1;
    if (choiceCalcType==2){
        if (ui->elasticBCcombo->currentIndex()==0){
            Cnstrnd=true;
        }else if(ui->elasticBCcombo->currentIndex()==1){
            Cnstrnd=false;
        }
        sTotApp11=ui->s11_LE->text().toDouble();
        sTotApp22=ui->s22_LE->text().toDouble();
        sTotApp33=ui->s33_LE->text().toDouble();
        sTotApp23=ui->s23_LE->text().toDouble();
        sTotApp13=ui->s13_LE->text().toDouble();
        sTotApp12=ui->s12_LE->text().toDouble();
        eTotApp1=ui->ex_LE->text().toDouble();
        eTotApp2=ui->ey_LE->text().toDouble();
        eTotApp3=ui->ez_LE->text().toDouble();
        hTotApp1=ui->hx_LE->text().toDouble();
        hTotApp2=ui->hy_LE->text().toDouble();
        hTotApp3=ui->hz_LE->text().toDouble();
        cTotApp1=ui->cx_LE->text().toDouble();
        cTotApp2=ui->cy_LE->text().toDouble();
        cTotApp3=ui->cz_LE->text().toDouble();
        tTotApp1=ui->tx_LE->text().toDouble();
        tTotApp2=ui->ty_LE->text().toDouble();
        tTotApp3=ui->tz_LE->text().toDouble();
    }

//  output the data
    const char *dir=filedir.toLatin1();
    out.open(dir);
    out << left;
    out << setw(11) << lx << setw(11) << ly << setw(11) << lz << "\n";
    out << setw(11) << nx << setw(11) << ny << setw(11) << nz << "\n";
    out << choiceSystem << "\n" ;
    out << nPhase << "\n";
    out << choiceStructFormat << "\n";
    while (id<=nPhase){
        tab[id-1].passCPhase(c);
        out << id << "\n";
        out << scientific;
        out << setprecision(3);
        out << setw(11) << c[0][0] << setw(11) << c[0][1] << setw(11) << c[0][2]
            << setw(11) << c[0][3] << setw(11) << c[0][4] << setw(11) << c[0][5] << " \n";
        out << setw(11) << "     " << setw(11) << c[1][1] << setw(11) << c[1][2]
            << setw(11) << c[1][3] << setw(11) << c[1][4] << setw(11) << c[1][5] << " \n";
        out << setw(11) << "     " << setw(11) << "     " << setw(11) << c[2][2]
            << setw(11) << c[2][3] << setw(11) << c[2][4] << setw(11) << c[2][5] << " \n";
        out << setw(11) << "     " << setw(11) << "     " << setw(11) << "     "
            << setw(11) << c[3][3] << setw(11) << c[3][4] << setw(11) << c[3][5] << " \n";
        out << setw(11) << "     " << setw(11) << "     " << setw(11) << "     "
            << setw(11) << "     " << setw(11) << c[4][4] << setw(11) << c[4][5] << " \n";
        out << setw(11) << "     " << setw(11) << "     " << setw(11) << "     "
            << setw(11) << "     " << setw(11) << "     " << setw(11) << c[5][5] << " \n";

        tab[id-1].passEpsPhase(eps);
        out << setw(11) << eps[0][0] << setw(11) << eps[1][1] << setw(11) << eps[2][2]
            << setw(11) << eps[1][2] << setw(11) << eps[0][2] << setw(11) << eps[0][1] << " \n";

        tab[id-1].passDPiezE(dpiezE);
        out << setw(11) << dpiezE[0][0] << setw(11) << dpiezE[0][1] << setw(11) << dpiezE[0][2]
            << setw(11) << dpiezE[0][3] << setw(11) << dpiezE[0][4] << setw(11) << dpiezE[0][5] << " \n";
        out << setw(11) << dpiezE[1][0] << setw(11) << dpiezE[1][1] << setw(11) << dpiezE[1][2]
            << setw(11) << dpiezE[1][3] << setw(11) << dpiezE[1][4] << setw(11) << dpiezE[1][5] << " \n";
        out << setw(11) << dpiezE[2][0] << setw(11) << dpiezE[2][1] << setw(11) << dpiezE[2][2]
            << setw(11) << dpiezE[2][3] << setw(11) << dpiezE[2][4] << setw(11) << dpiezE[2][5] << " \n";

        tab[id-1].passMuPhase(mu);
        out << setw(11) << mu[0][0] << setw(11) << mu[1][1] << setw(11) << mu[2][2]
            << setw(11) << mu[1][2] << setw(11) << mu[0][2] << setw(11) << mu[0][1] << " \n";

        tab[id-1].passQPiezM(qpiezM);
        out << setw(11) << qpiezM[0][0] << setw(11) << qpiezM[0][1] << setw(11) << qpiezM[0][2]
            << setw(11) << qpiezM[0][3] << setw(11) << qpiezM[0][4] << setw(11) << qpiezM[0][5] << " \n";
        out << setw(11) << qpiezM[1][0] << setw(11) << qpiezM[1][1] << setw(11) << qpiezM[1][2]
            << setw(11) << qpiezM[1][3] << setw(11) << qpiezM[1][4] << setw(11) << qpiezM[1][5] << " \n";
        out << setw(11) << qpiezM[2][0] << setw(11) << qpiezM[2][1] << setw(11) << qpiezM[2][2]
            << setw(11) << qpiezM[2][3] << setw(11) << qpiezM[2][4] << setw(11) << qpiezM[2][5] << " \n";

        tab[id-1].passAlphaMEPhase(alphaME);
        out << setw(11) << alphaME[0][0] << setw(11) << alphaME[0][1] << setw(11) << alphaME[0][2] << " \n";
        out << setw(11) << alphaME[1][0] << setw(11) << alphaME[1][1] << setw(11) << alphaME[1][2] << " \n";
        out << setw(11) << alphaME[2][0] << setw(11) << alphaME[2][1] << setw(11) << alphaME[2][2] << " \n";

        tab[id-1].passDPhase(d);
        out << setw(11) << d[0][0] << setw(11) << d[1][1] << setw(11) << d[2][2]
            << setw(11) << d[1][2] << setw(11) << d[0][2] << setw(11) << d[0][1] << " \n";

        tab[id-1].passKPhase(k);
        out << setw(11) << k[0][0] << setw(11) << k[1][1] << setw(11) << k[2][2]
            << setw(11) << k[1][2] << setw(11) << k[0][2] << setw(11) << k[0][1] << " \n";
        id++;
    }

//    out << choiceCalcType << " \n";
    out << boolalpha << flagDistribution << " \n";
    if (flagDistribution){
        out << std::boolalpha << Cnstrnd << " \n";
        out << fixed;
        out << setw(11) << sTotApp11 << setw(11) << sTotApp22 << setw(11) << sTotApp33
            << setw(11) << sTotApp23 << setw(11) << sTotApp13 << setw(11) << sTotApp12 << " \n";
        out << setw(11) << eTotApp1 << setw(11) << eTotApp2 << setw(11) << eTotApp3 << " \n";
        out << setw(11) << hTotApp1 << setw(11) << hTotApp2 << setw(11) << hTotApp3 << " \n";
        out << setw(11) << cTotApp1 << setw(11) << cTotApp2 << setw(11) << cTotApp3 << " \n";
        out << setw(11) << tTotApp1 << setw(11) << tTotApp2 << setw(11) << tTotApp3 << " \n";
    }
    out.close();
}

void effectivePropertyInput::loadData(QString filedir){
    std::ifstream in;
    double c[6][6]={{0}};
    double eps[3][3]={{0}};
    double dpiezE[3][6]={{0}};
    double mu[3][3]={{0}};
    double qpiezM[3][6]={{0}};
    double alphaME[3][3]={{0}};
    double d[3][3]={{0}};
    double k[3][3]={{0}};
    int id=1;
    int nothing;
    QByteArray dir1=filedir.toLatin1();
    const char *dir=dir1.data();

    qDebug()<<"filedir"<<filedir;
    in.open(dir);
    in.ignore(0,'\n');
    qDebug()<<in.is_open();
    in >> lx>>ly>>lz;
    in.ignore(100000,'\n');
    in >> nx>>ny>>nz;
    in.ignore(100000,'\n');
    in >> choiceSystem;
    in.ignore(100000,'\n');
    in >> nPhase;
    in.ignore(100000,'\n');
    in >> choiceStructFormat;
    in.ignore(100000,'\n');
    in >> scientific;

    ui->nx_LE->setText(QString::number(nx));
    ui->ny_LE->setText(QString::number(ny));
    ui->nz_LE->setText(QString::number(nz));
    ui->lx_LE->setText(QString::number(lx));
    ui->ly_LE->setText(QString::number(ly));
    ui->lz_LE->setText(QString::number(lz));
    ui->systemCombo->setCurrentIndex(choiceSystem-1);
    ui->numberofPhase_LE->setText(QString::number(nPhase));
    ui->strucInputCombo->setCurrentIndex(choiceStructFormat-1);
    qDebug()<<lx<<ly<<lz<<nPhase<<choiceSystem<<nx<<ny<<nz<<choiceStructFormat;
    updateTab(nPhase);
    while (id<=nPhase){
        in >> nothing;
        in.ignore(100000,'\n');
        in >> setw(11) >> c[0][0] >> setw(11) >> c[0][1] >> setw(11) >> c[0][2]
            >> setw(11) >> c[0][3] >> setw(11) >> c[0][4] >> setw(11) >> c[0][5];
        in.ignore(100000,'\n');
        in >> setw(11) >> c[1][1] >> setw(11) >> c[1][2]
            >> setw(11) >> c[1][3] >> setw(11) >> c[1][4] >> setw(11) >> c[1][5];
        in.ignore(100000,'\n');
        in >> setw(11) >> c[2][2]
            >> setw(11) >> c[2][3] >> setw(11) >> c[2][4] >> setw(11) >> c[2][5];
        in.ignore(100000,'\n');
        in >> setw(11) >> c[3][3] >> setw(11) >> c[3][4] >> setw(11) >> c[3][5];
        in.ignore(100000,'\n');
        in >> setw(11) >> c[4][4] >> setw(11) >> c[4][5];
        in.ignore(100000,'\n');
        in >> setw(11) >> c[5][5];
        in.ignore(100000,'\n');
        qDebug()<<"to update c phase"<<id<<nothing<<c[0][0]<<c[0][1]<<c;
        tab[id-1].updateCPhase(c);


        in >> eps[0][0] >> eps[1][1] >> eps[2][2]
           >> eps[1][2] >> eps[0][2] >> eps[0][1];
        in.ignore(100000,'\n');
        tab[id-1].updateEpsPhase(eps);


        in >> setw(11) >> dpiezE[0][0] >> setw(11) >> dpiezE[0][1] >> setw(11) >> dpiezE[0][2]
           >> setw(11) >> dpiezE[0][3] >> setw(11) >> dpiezE[0][4] >> setw(11) >> dpiezE[0][5];
        in.ignore(100000,'\n');
        in >> setw(11) >> dpiezE[1][0] >> setw(11) >> dpiezE[1][1] >> setw(11) >> dpiezE[1][2]
           >> setw(11) >> dpiezE[1][3] >> setw(11) >> dpiezE[1][4] >> setw(11) >> dpiezE[1][5];
        in.ignore(100000,'\n');
        in >> setw(11) >> dpiezE[2][0] >> setw(11) >> dpiezE[2][1] >> setw(11) >> dpiezE[2][2]
           >> setw(11) >> dpiezE[2][3] >> setw(11) >> dpiezE[2][4] >> setw(11) >> dpiezE[2][5];
        in.ignore(100000,'\n');
        tab[id-1].updateDPiezE(dpiezE);

        in >> mu[0][0] >> mu[1][1] >> mu[2][2]
           >> mu[1][2] >> mu[0][2] >> mu[0][1];
        in.ignore(100000,'\n');
        tab[id-1].updateMuPhase(mu);

        in >> setw(11) >> qpiezM[0][0] >> setw(11) >> qpiezM[0][1] >> setw(11) >> qpiezM[0][2]
           >> setw(11) >> qpiezM[0][3] >> setw(11) >> qpiezM[0][4] >> setw(11) >> qpiezM[0][5];
        in.ignore(100000,'\n');
        in >> setw(11) >> qpiezM[1][0] >> setw(11) >> qpiezM[1][1] >> setw(11) >> qpiezM[1][2]
           >> setw(11) >> qpiezM[1][3] >> setw(11) >> qpiezM[1][4] >> setw(11) >> qpiezM[1][5];
        in.ignore(100000,'\n');
        in >> setw(11) >> qpiezM[2][0] >> setw(11) >> qpiezM[2][1] >> setw(11) >> qpiezM[2][2]
           >> setw(11) >> qpiezM[2][3] >> setw(11) >> qpiezM[2][4] >> setw(11) >> qpiezM[2][5];
        in.ignore(100000,'\n');
        tab[id-1].updateQPiezM(qpiezM);

        in >> setw(11) >> alphaME[0][0] >> setw(11) >> alphaME[0][1] >> setw(11) >> alphaME[0][2];
        in.ignore(100000,'\n');
        in >> setw(11) >> alphaME[1][0] >> setw(11) >> alphaME[1][1] >> setw(11) >> alphaME[1][2];
        in.ignore(100000,'\n');
        in >> setw(11) >> alphaME[2][0] >> setw(11) >> alphaME[2][1] >> setw(11) >> alphaME[2][2];
        in.ignore(100000,'\n');
        tab[id-1].updateAlphaMEPhase(alphaME);

        in >> d[0][0] >> d[1][1] >> d[2][2]
           >> d[1][2] >> d[0][2] >> d[0][1];
        in.ignore(100000,'\n');
        tab[id-1].updateDPhase(d);

        in >> k[0][0] >> k[1][1] >> k[2][2]
           >> k[1][2] >> k[0][2] >> k[0][1];
        in.ignore(100000,'\n');
        tab[id-1].updateKPhase(k);
        qDebug()<<"fine here"<<id;
        id++;
    }

//    in >> choiceCalcType;
    in >> boolalpha >> flagDistribution;
    in.ignore(100000,'\n');
    choiceCalcType=1;
    if (flagDistribution){
        choiceCalcType=2;
        in >> boolalpha >> Cnstrnd;
        in.ignore(100000,'\n');
        in >> fixed;
        in >> sTotApp11 >> sTotApp22 >> sTotApp33 >> sTotApp23 >> sTotApp13 >> sTotApp12 ;
        in.ignore(100000,'\n');
        in >> eTotApp1 >> eTotApp2 >> eTotApp3 ;
        in.ignore(100000,'\n');
        in >> hTotApp1 >> hTotApp2 >> hTotApp3 ;
        in.ignore(100000,'\n');
        in >> cTotApp1 >> cTotApp2 >> cTotApp3 ;
        in.ignore(100000,'\n');
        in >> tTotApp1 >> tTotApp2 >> tTotApp3 ;
        in.ignore(100000,'\n');
    }
    in.close();
    ui->choiceCalcTypecombo->setCurrentIndex(choiceCalcType-1);
    ui->elasticBCcombo->setCurrentIndex(1-Cnstrnd);
    ui->s11_LE->setText(QString::number(sTotApp11));
    ui->s22_LE->setText(QString::number(sTotApp22));
    ui->s33_LE->setText(QString::number(sTotApp33));
    ui->s23_LE->setText(QString::number(sTotApp23));
    ui->s13_LE->setText(QString::number(sTotApp13));
    ui->s12_LE->setText(QString::number(sTotApp12));
    ui->ex_LE->setText(QString::number(eTotApp1));
    ui->ey_LE->setText(QString::number(eTotApp2));
    ui->ez_LE->setText(QString::number(eTotApp3));
    ui->hx_LE->setText(QString::number(hTotApp1));
    ui->hy_LE->setText(QString::number(hTotApp2));
    ui->hz_LE->setText(QString::number(hTotApp3));
    ui->cx_LE->setText(QString::number(cTotApp1));
    ui->cy_LE->setText(QString::number(cTotApp2));
    ui->cz_LE->setText(QString::number(cTotApp3));
    ui->tx_LE->setText(QString::number(tTotApp1));
    ui->ty_LE->setText(QString::number(tTotApp2));
    ui->tz_LE->setText(QString::number(tTotApp3));

    if (flagDistribution){
        ui->Appliedfield->show();
        ui->tabWidget->setMinimumHeight(480);
        ui->tabWidget->setMaximumHeight(480);
//        ui->System->setMinimumHeight(400);
//        ui->System->setMaximumHeight(400);
    }else{
        ui->Appliedfield->hide();
        ui->tabWidget->setMinimumHeight(205);
        ui->tabWidget->setMaximumHeight(205);
//        ui->System->setMinimumHeight(205);
//        ui->System->setMaximumHeight(205);
    }
    ui->elasticBCcombo->activated(1-Cnstrnd);
    this->adjustSize();

    qDebug()<< "C:" << c[0][0] << c[0][1] << endl;
}

void effectivePropertyInput::on_numberofPhase_LE_editingFinished()
{
    int number;
    number = ui->numberofPhase_LE->text().toInt();
    qDebug()<<number;
    if (number > 6){
        number=6;
        ui->numberofPhase_LE->setText(QString::number(number));
        QMessageBox::information(this,tr("Notice"),tr("The total number of phases is too large, we now only accept a maximum of 6 phases."));
    }else if (number<1){
        number=1;
        ui->numberofPhase_LE->setText(QString::number(number));
        QMessageBox::information(this,tr("Notice"),tr("There must be at least one phase in the system. Don't forget to set the number of phases."));
    }
    updateTab(number);
    nPhase=number;
    qDebug()<<"nPhase="<<nPhase;
}


void effectivePropertyInput::updateTab(int number)
{
    QString name;
    QIcon icon;
    int tabnumber;
    tabnumber=ui->tabWidget->count();
    qDebug()<<tabnumber;
    if (number>=1){
        while (number >= tabnumber){
            name=tr("phase ")+QString::number(tabnumber);
            ui->tabWidget->addTab(&tab[tabnumber-1],icon,name);
            qDebug()<<"tab number1"<<number<<tabnumber<<&tab[tabnumber-1];
            tabnumber=ui->tabWidget->count();

        }

        while (number < tabnumber-1){
            //qDebug()<<"tab number2"<<number<<tabnumber<<&tab[tabnumber];
            ui->tabWidget->removeTab(tabnumber-1);
            tabnumber=ui->tabWidget->count();
        }
    }
    qDebug()<<"1"<<&tab[0];
}


void effectivePropertyInput::on_Generate_pressed()
{
    QFileDialog filedialog(this);
    bool modal=1;
    filedialog.setFileMode(QFileDialog::Directory);
    filedialog.setOption(QFileDialog::ShowDirsOnly);
    filedialog.setModal(modal);

    QString generateDir=filedialog.getExistingDirectory();
    qDebug()<<"Filename:"<<generateDir;
    QString filedir=generateDir+"/parameter.in";

    qDebug()<<"Filedir:"<<filedir;

    outputData(filedir);
    qDebug()<<filedialog.AcceptSave << filedialog.Rejected << filedialog.Accepted ;
    if (!generateDir.isNull()){
        this->accept();
    }
}

void effectivePropertyInput::on_loadFile_clicked()
{
    QFileDialog filedialog;
    filedialog.setFileMode(QFileDialog::AnyFile);
    filedialog.setNameFilter(tr("Input (*.in)"));
    filedialog.setOption(QFileDialog::ReadOnly);
    QString load=filedialog.getOpenFileName();
    qDebug()<<"Filename:"<<load;
    loadData(load);
    this->raise();
    int index=ui->tabWidget->currentIndex();
    on_tabWidget_currentChanged(index);

}

void effectivePropertyInput::on_choiceCalcTypecombo_activated(int index)
{
    if (index==1){
        ui->Appliedfield->show();
        flagDistribution=true;
        ui->tabWidget->setMinimumHeight(720);
        ui->tabWidget->setMaximumHeight(720);
    }else if(index==0){
        ui->Appliedfield->hide();
        flagDistribution=false;
        ui->tabWidget->setMinimumHeight(350);
        ui->tabWidget->setMaximumHeight(350);
    }
    this->adjustSize();
}

void effectivePropertyInput::on_Cancel_clicked()
{
    this->reject();
}

void effectivePropertyInput::on_elasticBCcombo_activated(int index)
{
    if(index==1){
        ui->appliedS->setText(tr("Applied stress (Pa):"));
        ui->s11->setText(tr("Stress11:"));
        ui->s22->setText(tr("Stress22:"));
        ui->s33->setText(tr("Stress33:"));
        ui->s23->setText(tr("Stress23:"));
        ui->s13->setText(tr("Stress13:"));
        ui->s12->setText(tr("Stress12:"));
    }else if(index==0){
        ui->appliedS->setText(tr("Applied strain (unitless):"));
        ui->s11->setText(tr("Strain11:"));
        ui->s22->setText(tr("Strain22:"));
        ui->s33->setText(tr("Strain33:"));
        ui->s23->setText(tr("Strain23:"));
        ui->s13->setText(tr("Strain13:"));
        ui->s12->setText(tr("Strain12:"));
    }
}

void effectivePropertyInput::on_readImage_clicked()
{
    patternReco *pattern=new patternReco;
    pattern->show();

}

void effectivePropertyInput::on_tabWidget_currentChanged(int index)
{
    int choice;
    choice=ui->choiceCalcTypecombo->currentIndex();
    if (index==0 && choice==0){
       ui->tabWidget->setMinimumHeight(350);
        ui->tabWidget->setMaximumHeight(350);
    }else if (index==0 &&choice==1){
        ui->tabWidget->setMinimumHeight(720);
        ui->tabWidget->setMaximumHeight(720);
    }else if (index!=0){
        ui->tabWidget->setMinimumHeight(450);
        ui->tabWidget->setMaximumHeight(450);
    }
    this->adjustSize();
}
