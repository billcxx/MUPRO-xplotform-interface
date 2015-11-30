#include "mupromain.h"
#include "ui_mupromain.h"
#include "ferroinput.h"
#include "effectivepropertyinput.h"
#include <QDebug>
#include <QPixmap>


const QString effective_property_intro="A variaty of properties could be calculated using our mu-pro package, "
                                       "also including several coupled properties, such as elastic, Piezoelectric, "
                                       "magnetic, piezomagnetic, magnetoelectric, and even static state diffusion properties. "
                                       "And our package provides you with an easy and highly customizable way to visualize the "
                                       "output data, with the aid of vtk wrapped by python.";
const QString ferroelectric_intro="ferroelectric";
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

    QPixmap effective_property_img1(":/img/piezo-logo.png");
    QPixmap effective_property_img2(":/img/property-logo.png");
    effective_property_img1= effective_property_img1.scaledToWidth(ui->featureImg1_LB->width());
    effective_property_img2= effective_property_img2.scaledToWidth(ui->featureImg2_LB->width());

    qDebug()<<e->x()<<e->y();
    mousePosLabel->setText("("+QString::number(e->x())+","+QString::number(e->y())+")");
    if(e->x()>=0 && e->x()<=260 ){

        int y=e->y();
        if(y>=120 && y<170){
            ui->brief_intro_LB->setText(effective_property_intro);
            ui->featureImg1_LB->setPixmap(effective_property_img1);
            ui->featureImg2_LB->setPixmap(effective_property_img2);
        }else if(y>=170&&y<220){
            ui->brief_intro_LB->setText(ferroelectric_intro);
            ui->featureImg1_LB->pixmap();
            ui->featureImg2_LB->pixmap();
        }else if(y>=220&&y<270){
            ui->brief_intro_LB->setText(ferromagnetic_intro);
            ui->featureImg1_LB->pixmap();
            ui->featureImg2_LB->pixmap();
        }else if(y>=270&&y<320){
            ui->brief_intro_LB->setText(precipitation_intro);
            ui->featureImg1_LB->pixmap();
            ui->featureImg2_LB->pixmap();
        }else if(y>=320&&y<370){
            ui->brief_intro_LB->setText(solidification_intro);
            ui->featureImg1_LB->pixmap();
            ui->featureImg2_LB->pixmap();
        }else if(y>=370&&y<420){
            ui->brief_intro_LB->setText(grain_growth_intro);
            ui->featureImg1_LB->pixmap();
            ui->featureImg2_LB->pixmap();
        }else if(y>=420&&y<470){
            ui->brief_intro_LB->setText(defect_transportation_intro);
            ui->featureImg1_LB->pixmap();
            ui->featureImg2_LB->pixmap();
        }
    }
}

void muproMain::on_button_effect_clicked()
{
    effectivePropertyInput *effect=new effectivePropertyInput;
    effect->show();
}
