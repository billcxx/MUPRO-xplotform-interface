#ifndef EFFECTIVEPROPERTYINPUT_H
#define EFFECTIVEPROPERTYINPUT_H

#include <QDialog>
#include "phasetab.h"
#include "patternreco.h"

namespace Ui {
class effectivePropertyInput;
}

class effectivePropertyInput : public QDialog
{
    Q_OBJECT

public:
    explicit effectivePropertyInput(QWidget *parent = 0);
    ~effectivePropertyInput();

private slots:

    void outputData(QString filedir);

    void loadData(QString filedir);

    void on_numberofPhase_LE_editingFinished();

    void updateTab(int number);

//    void on_nx_LE_editingFinished();

//    void on_ny_LE_editingFinished();

//    void on_nz_LE_editingFinished();

//    void on_lx_LE_editingFinished();

//    void on_ly_LE_editingFinished();

//    void on_lz_LE_editingFinished();

//    void on_systemCombo_currentIndexChanged(int index);

//    void on_strucInputCombo_currentIndexChanged(int index);

    void on_Generate_pressed();

    void on_loadFile_clicked();

    void on_choiceCalcTypecombo_activated(int index);

    void on_Cancel_clicked();

    void on_elasticBCcombo_activated(int index);

    void on_readImage_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::effectivePropertyInput *ui;
    int nx,ny,nz;
    double lx,ly,lz;
    int choiceSystem,choiceStructFormat,nPhase;
    int choiceCalcType;
    double sTotApp11,sTotApp22,sTotApp33,sTotApp23,sTotApp13,sTotApp12;
    double eTotApp1,eTotApp2,eTotApp3;
    double hTotApp1,hTotApp2,hTotApp3;
    double cTotApp1,cTotApp2,cTotApp3;
    double tTotApp1,tTotApp2,tTotApp3;
    bool Cnstrnd,flagDistribution;
    phaseTab tab[6];
};

#endif // EFFECTIVEPROPERTYINPUT_H
