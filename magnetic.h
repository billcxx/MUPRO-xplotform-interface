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
    template <typename T> void outFixed(QString filedir,std::string parameterName,T parameter);
    void outScientific(QString filedir,std::string parameterName,double parameter);
    void outBoolean(QString filedir,std::string parameterName,bool parameter);
    void outEndl(QString filedir);
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


//    void on_choiceInitial_Combo_activated(int index);

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
    void getData();

    void on_flagStrayField_CB_stateChanged(int arg1);

    void on_createBatch_PB_released();
    void outputPbs(QString filedir);



private:
    Ui::magnetic *ui;
    double lx,ly,lz;
    int nx,ny,nz,nf,ns;
    double M0,gamma,alphaM;
    double dDMI;
    int kt0,ktmax,ktOutTable,ktOutDist;
    int choiceAnisotropy;
    double kc1,kc2,kc3;
    //double fhd1,fhd2,fhd3;
    double nd11,nd22,nd33,nd23,nd13,nd12;
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
    double jElect1,jElect2,jElect3;
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
    double KsiSTT;
    double thetaC,phiC,psiC;
    double axisInitialM1,axisInitialM2,axisInitialM3;
    bool flagOutH,flagOutE;//,flagOutHEff,flagOutHStr,flagOutHAni,flagOutHEla;
    bool flagOutS;//,flagOutSEign,flagOutStrain,flagOutStress;
    int choiceGrainStruct;
    int choiceIslandShape;
    int choiceLLGSolver;
    int recursionLimit;
    double errorTolerance;
    int ni1,ni2,ni3;
    QVector<QString> integerList = QVector<QString>()<<"nx"<<"ny"<<"nz"<<"ns"<<"nf"<<"choiceIsland"\
                                                    <<"ni1"<<"ni2"<<"ni3"<<"choiceGrain"<<"choiceAnisotropy" \
                                                    <<"choiceExternalH"<<"elasRecursionMax"<<"choiceSpinTorque"\
                                                    <<"choiceLLG"<<"stepStart"<<"stepFinish"<<"intervalTableOut"\
                                                    <<"intervalDistOut"<<"choiceInitialMagnDist";
    QVector<QString> doubleList = QVector<QString>()<<"lx" <<"ly"<<"lz"<<"phi"<<"theta"<<"psi" \
                                                    <<"saturateMagn"<<"gyromagneticRatio"<<"dampingConst" \
                                                    <<"anisotropy1"<<"anisotropy2"<<"anisotropy3"<<"demagn11" \
                                                    <<"demagn22" << "demagn33" << "demagn23" <<"demagn13" << "demagn12" \
                                                    <<"externalHDC1"<<"externalHDC2"<<"externalHDC3" \
                                                    <<"externalHAC1"<<"externalHAC2"<<"externalHAC3"<<"frequency" \
                                                    <<"exchangeEnergyCoeff"<<"magnetoStriction100"<<"magnetoStriction111" \
                                                    <<"CFilm11"<<"CFilm12"<<"CFilm44"<<"CSub11"<<"CSub12"<<"CSub44" \
                                                    <<"epsilon11"<<"epsilon22"<<"epsilon12"<<"epsilon33"<<"epsilon13"<<"epsilon23"\
                                                    <<"elasTolerance"<<"spinHallAngle"<<"spinPolarConst"<<"nonAdiabaticity" \
                                                    <<"spinPolarCurrentDensity1"<<"spinPolarCurrentDensity2"<<"spinPolarCurrentDensity3"\
                                                    <<"fixedLayerNormalizedMagn1"<<"fixedLayerNormalizedMagn2"<<"fixedLayerNormalizedMagn3" \
                                                    <<"effectiveDMConst"<<"temperature"<<"deltaT"<<"axis1"<<"axis2"<<"axis3";
    QVector<QString> booleanList = QVector<QString>()<<"flagAnisotropy"<<"flagStray"<<"flagPeriodic"<<"flagMagnetoElastic"\
                                                     <<"flagStrainBC"<<"flagSpinTorque"<<"flagDMI"<<"flagThermo"<<"flagOutH"<<"flagOutE"<<"flagOutS";

    QVector<QString> batchList;
};

#endif // MAGNETIC_H
