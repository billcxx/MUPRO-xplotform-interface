#ifndef MAGNETIC_H
#define MAGNETIC_H

#include <QDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QKeyEvent>
namespace Ui {
class magnetic;
}

class magnetic : public QDialog
{
    Q_OBJECT

public:
    explicit magnetic(QWidget *parent = 0);
    ~magnetic();

private slots:
    void loadData(QString filedir);

    void keyPressEvent(QKeyEvent *ke);

    void setData();

    void outputData(QString filedir);

    void on_choiceAnis_Combo_activated(int index);

    void on_choiceHext_Combo_activated(int index);

    void on_tabWidget_currentChanged(int index);

    void on_flagAnisotropy_CB_stateChanged(int arg1);

    void on_flagPeriodic_CB_stateChanged(int arg1);

    void on_flagElastic_CB_stateChanged(int arg1);

    void on_flagElasConstrain_Combo_currentIndexChanged(int index);


    void on_outputH_CB_stateChanged(int arg1);

    void on_outputS_CB_stateChanged(int arg1);


    void on_choiceInitial_Combo_activated(int index);

    void on_loadFile_pressed();

    void on_Generate_pressed();


    void on_flagST_CB_stateChanged(int arg1);

    void on_choiceGrainStruct_Combo_currentIndexChanged(int index);


    void on_choiceIslandShape_Combo_currentIndexChanged(int index);
    void on_nf_LE_editingFinished();

    void on_choiceHext_Combo_currentIndexChanged(int index);

    void on_choiceST_Combo_currentIndexChanged(int index);

    void on_flagDMI_CB_stateChanged(int arg1);

    void on_flagThermalFluc_CB_stateChanged(int arg1);

    void on_choiceInitial_Combo_currentIndexChanged(int index);

    void on_ni3_LE_editingFinished();

    void updateCheckBox();

    void on_flagStrayField_CB_stateChanged(int arg1);

private:
    Ui::magnetic *ui;
    double lx,ly,lz;
    int nx,ny,nz,nf,ns;
    double M0,gamma,alphaM;
    double dDMI;
    int kt0,ktmax,ktOutTable,ktOutDist;
    int choiceAnisotropy;
    double kc1,kc2,kc3;
    double fhd1,fhd2,fhd3;
    double lam100,lam111;
    double c11,c12,c44;
    double cs11,cs12,cs44;
    double Aexch;
    int choiceHext;
    double hdc1,hdc2,hdc3;
    double hac1,hac2,hac3;
    double frequence;
    bool flagAnisotropy;
    bool flagConstrained;
    bool flagDMI;
    bool flagPeriodic;
    bool flagStrayField;
    bool flagThermalFluc;
    bool flagElastic;
    bool flagST;
    double jElect;
    double thetaHE;
    double sigmaFixed1,sigmaFixed2,sigmaFixed3;
    double exx,eyy,exy;
    double ezz,exz,eyz;
    double dt;
    double temperature;
    int choiceInitialMag;
    int choiceST;
    double angleSH;
    double etaSP;
    double thetaC,phiC,psiC;
    double axisInitialM1,axisInitialM2,axisInitialM3;
    bool flagOutH,flagOutHEff,flagOutHStr,flagOutHAni,flagOutHEla;
    bool flagOutS,flagOutSEign,flagOutStrain,flagOutStress;
    int choiceGrainStruct;
    int choiceIslandShape;
    int recursionLimit;
    double errorTolerance;
    int ni1,ni2,ni3;

};

#endif // MAGNETIC_H
