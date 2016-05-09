#include "mupromain.h"
#include "ui_mupromain.h"
#include "ferroinput.h"
#include "effectivepropertyinput.h"
#include "magnetic.h"
#include <QDebug>
#include <QPixmap>

const QString main_intro="    µ-pro, microstructure-property modeling package, is a series of phase-field models"
                         " solved by spectral method and implemented with modern fortran along with MPI, thus gaining "
                         "native numerical and performance advantages. It excels in dealing with numerous types of problems, "
                         "ranging from grain growth, precipitation in alloys to domain structure evolution in ferroelectric/ferromagnetic/ferroelastic system.";

const QString effective_property_intro="A variaty of properties could be calculated using our mu-pro package, "
                                       "also including several coupled properties, such as elastic, Piezoelectric, "
                                       "magnetic, piezomagnetic, magnetoelectric, and even static state diffusion properties. "
                                       "And our package provides you with an easy and highly customizable way to visualize the "
                                       "output data, with the aid of vtk wrapped by python.";
const QString ferroelectric_intro=" Our package enables you to evolve the domain structure under a variety of "
                                  "conditions in both bulk and thin film. We can apply force and electric field to the material, and "
                                  "calculate both effective property and domain configuration under such stimulation. We can consider "
                                  "defects, such as dislocation, inclusion and charged defects within the material. We are also capable of "
                                  "simulating polycrystal and superlattice cases. ";
const QString ferromagnetic_intro="ferromagnetic";
const QString precipitation_intro="precipitation";
const QString solidification_intro="solidification";
const QString grain_growth_intro="grain growth";
const QString defect_transportation_intro="defect transportation";


muproMain::muproMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::muproMain)
{
    ui->setupUi(this);
    qDebug()<<"the mupromain initialized"<<this->size();
    statusLabel=new QLabel;
    statusLabel->setText(tr("status"));
    statusLabel->setFixedWidth(100);
    mousePosLabel=new QLabel;
    mousePosLabel->setText(tr("position"));
    mousePosLabel->setFixedWidth(100);
//    statusBar()->addPermanentWidget(statusLabel);
//    statusBar()->addPermanentWidget(mousePosLabel);
    this->setMouseTracking(true);
    qDebug()<<"not crashed yet";
//    QMouseEvent *e;
//    qDebug()<<e->x()<<e->y()<<hasMouseTracking();
}

muproMain::~muproMain()
{
    delete ui;
}


void muproMain::on_button_ferroelectric_clicked()
{
    ferroInput *ferro=new ferroInput;
    ferro->show();
}

void muproMain::mouseMoveEvent(QMouseEvent *e){

    QPixmap main_img1(":/img/interface.png");
    QPixmap main_img2(":/img/magnetic-composite.png");
    main_img1= main_img1.scaledToWidth(ui->featureImg1_LB->width());
    main_img2= main_img2.scaledToWidth(ui->featureImg2_LB->width());

    QPixmap effective_property_img1(":/img/d33.png");
    QPixmap effective_property_img2(":/img/mechanical-property.png");
    effective_property_img1= effective_property_img1.scaledToWidth(ui->featureImg1_LB->width());
    effective_property_img2= effective_property_img2.scaledToWidth(ui->featureImg2_LB->width());

    QPixmap ferroelectric_img1(":/img/superlattic.png");
    QPixmap ferroelectric_img2(":/img/Taa.png");
    ferroelectric_img1= ferroelectric_img1.scaledToWidth(ui->featureImg1_LB->width());
    ferroelectric_img2= ferroelectric_img2.scaledToWidth(ui->featureImg2_LB->width());

    QPixmap ferromagnetic_img1(":/img/ferromagnetic_ring.png");
    QPixmap ferromagnetic_img2(":/img/magnetic-composite.png");
    ferromagnetic_img1= ferromagnetic_img1.scaledToWidth(ui->featureImg1_LB->width());
    ferromagnetic_img2= ferromagnetic_img2.scaledToWidth(ui->featureImg2_LB->width());

    QPixmap precipitate_img1(":/img/precipitate.png");
    QPixmap precipitate_img2(":/img/Ni-alloy.png");
    precipitate_img1= precipitate_img1.scaledToWidth(ui->featureImg1_LB->width());
    precipitate_img2= precipitate_img2.scaledToWidth(ui->featureImg2_LB->width());

    QPixmap solidification_img1(":/img/dentrite.png");
    QPixmap solidification_img2(":/img/li-dentrite-sim.png");
    solidification_img1= solidification_img1.scaledToWidth(ui->featureImg1_LB->width());
    solidification_img2= solidification_img2.scaledToWidth(ui->featureImg2_LB->width());

    qDebug()<<e->x()<<e->y();
    mousePosLabel->setText("("+QString::number(e->x())+","+QString::number(e->y())+")");
    if(e->x()>=0 && e->x()<=260 ){

        int y=e->y();
        if(y>=0 && y<120){
            ui->brief_intro_LB->setText(main_intro);
            ui->featureImg1_LB->setPixmap(main_img1);
            ui->featureImg2_LB->setPixmap(main_img2);
        }else if(y>=120 && y<170){
            ui->brief_intro_LB->setText(effective_property_intro);
            ui->featureImg1_LB->setPixmap(effective_property_img1);
            ui->featureImg2_LB->setPixmap(effective_property_img2);
        }else if(y>=170&&y<220){
            ui->brief_intro_LB->setText(ferroelectric_intro);
            ui->featureImg1_LB->setPixmap(ferroelectric_img1);
            ui->featureImg2_LB->setPixmap(ferroelectric_img2);
        }else if(y>=220&&y<270){
            ui->brief_intro_LB->setText(ferromagnetic_intro);
            ui->featureImg1_LB->setPixmap(ferromagnetic_img1);
            ui->featureImg2_LB->setPixmap(ferromagnetic_img2);
        }else if(y>=270&&y<320){
            ui->brief_intro_LB->setText(precipitation_intro);
            ui->featureImg1_LB->setPixmap(precipitate_img1);
            ui->featureImg2_LB->setPixmap(precipitate_img2);
        }else if(y>=320&&y<370){
            ui->brief_intro_LB->setText(solidification_intro);
            ui->featureImg1_LB->setPixmap(solidification_img1);
            ui->featureImg2_LB->setPixmap(solidification_img2);
        }else if(y>=370&&y<420){
            ui->brief_intro_LB->setText(grain_growth_intro);
//            ui->featureImg1_LB->setPixmap();
//            ui->featureImg2_LB->setPixmap();
        }else if(y>=420&&y<470){
            ui->brief_intro_LB->setText(defect_transportation_intro);
//            ui->featureImg1_LB->setPixmap();
//            ui->featureImg2_LB->setPixmap();
        }
    }
}

void muproMain::on_button_effect_clicked()
{
    effectivePropertyInput *effect=new effectivePropertyInput;
    effect->show();
}

void muproMain::on_button_ferromagnetic_clicked()
{
    magnetic *magneticbutton=new magnetic;
    magneticbutton->show();
}
