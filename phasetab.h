#ifndef PHASETAB_H
#define PHASETAB_H

#include <QWidget>

namespace Ui {
class phaseTab;
}

class phaseTab : public QWidget
{
    Q_OBJECT

public:
    explicit phaseTab(QWidget *parent = 0);
    ~phaseTab();
    void passCPhase(double c[6][6]);
    void passEpsPhase(double Eps[3][3]);
    void passDPiezE(double DPiezE[3][6]);
    void passMuPhase(double Mu[3][3]);
    void passQPiezM(double QPiezM[3][6]);
    void passAlphaMEPhase(double AlphaME[3][3]);
    void passDPhase(double D[3][3]);
    void passKPhase(double K[3][3]);
    void updateCPhase(double C[6][6]);
    void updateEpsPhase(double Eps[3][3]);
    void updateDPiezE(double DPiezE[3][6]);
    void updateMuPhase(double Mu[3][3]);
    void updateQPiezM(double QPiezM[3][6]);
    void updateAlphaMEPhase(double AlphaME[3][3]);
    void updateDPhase(double D[3][3]);
    void updateKPhase(double K[3][3]);


private slots:
    void on_c12_textChanged(const QString &arg1);

    void on_c13_textChanged(const QString &arg1);

    void on_c14_textChanged(const QString &arg1);

    void on_c15_textChanged(const QString &arg1);

    void on_c16_textChanged(const QString &arg1);

    void on_c23_textChanged(const QString &arg1);

    void on_c24_textChanged(const QString &arg1);

    void on_c25_textChanged(const QString &arg1);

    void on_c26_textChanged(const QString &arg1);

    void on_c34_textChanged(const QString &arg1);

    void on_c35_textChanged(const QString &arg1);

    void on_c36_textChanged(const QString &arg1);

    void on_c45_textChanged(const QString &arg1);

    void on_c46_textChanged(const QString &arg1);

    void on_c56_textChanged(const QString &arg1);

    void on_c11_editingFinished();

    void on_eps12_textChanged(const QString &arg1);

    void on_eps13_textChanged(const QString &arg1);

    void on_eps23_textChanged(const QString &arg1);

    void on_dPiezE11_textChanged(const QString &arg1);

    void on_dPiezE12_textChanged(const QString &arg1);

    void on_dPiezE13_textChanged(const QString &arg1);

    void on_dPiezE14_textChanged(const QString &arg1);

    void on_dPiezE15_textChanged(const QString &arg1);

    void on_dPiezE16_textChanged(const QString &arg1);

    void on_dPiezE21_textChanged(const QString &arg1);

    void on_dPiezE22_textChanged(const QString &arg1);

    void on_dPiezE23_textChanged(const QString &arg1);

    void on_dPiezE24_textChanged(const QString &arg1);

    void on_dPiezE25_textChanged(const QString &arg1);

    void on_dPiezE26_textChanged(const QString &arg1);

    void on_dPiezE31_textChanged(const QString &arg1);

    void on_dPiezE32_textChanged(const QString &arg1);

    void on_dPiezE33_textChanged(const QString &arg1);

    void on_dPiezE34_textChanged(const QString &arg1);

    void on_dPiezE35_textChanged(const QString &arg1);

    void on_dPiezE36_textChanged(const QString &arg1);

    void on_mu11_textChanged(const QString &arg1);

    void on_mu12_textChanged(const QString &arg1);

    void on_mu13_textChanged(const QString &arg1);

    void on_mu23_textChanged(const QString &arg1);

    void on_mu22_textChanged(const QString &arg1);

    void on_mu33_textChanged(const QString &arg1);

    void on_qPiezM11_textChanged(const QString &arg1);

    void on_qPiezM12_textChanged(const QString &arg1);

    void on_qPiezM13_textChanged(const QString &arg1);

    void on_qPiezM14_textChanged(const QString &arg1);

    void on_qPiezM15_textChanged(const QString &arg1);

    void on_qPiezM16_textChanged(const QString &arg1);

    void on_qPiezM21_textChanged(const QString &arg1);

    void on_qPiezM22_textChanged(const QString &arg1);

    void on_qPiezM23_textChanged(const QString &arg1);

    void on_qPiezM24_textChanged(const QString &arg1);

    void on_qPiezM25_textChanged(const QString &arg1);

    void on_qPiezM26_textChanged(const QString &arg1);

    void on_qPiezM31_textChanged(const QString &arg1);

    void on_qPiezM32_textChanged(const QString &arg1);

    void on_qPiezM33_textChanged(const QString &arg1);

    void on_qPiezM34_textChanged(const QString &arg1);

    void on_qPiezM35_textChanged(const QString &arg1);

    void on_qPiezM36_textChanged(const QString &arg1);

    void on_alphaME11_textChanged(const QString &arg1);

    void on_alphaME12_textChanged(const QString &arg1);

    void on_alphaME13_textChanged(const QString &arg1);

    void on_alphaME21_textChanged(const QString &arg1);

    void on_alphaME22_textChanged(const QString &arg1);

    void on_alphaME23_textChanged(const QString &arg1);

    void on_alphaME31_textChanged(const QString &arg1);

    void on_alphaME32_textChanged(const QString &arg1);

    void on_alphaME33_textChanged(const QString &arg1);

    void on_dPhase12_textChanged(const QString &arg1);

    void on_dPhase13_textChanged(const QString &arg1);

    void on_dPhase23_textChanged(const QString &arg1);

    void on_dPhase11_textChanged(const QString &arg1);

    void on_dPhase22_textChanged(const QString &arg1);

    void on_dPhase33_textChanged(const QString &arg1);

    void on_kPhase12_textChanged(const QString &arg1);

    void on_kPhase13_textChanged(const QString &arg1);

    void on_kPhase23_textChanged(const QString &arg1);

    void on_kPhase11_textChanged(const QString &arg1);

    void on_kPhase22_textChanged(const QString &arg1);

    void on_kPhase33_textChanged(const QString &arg1);

private:
    Ui::phaseTab *ui;
    double C11,C12,C13,C14,C15,C16;
    double C21,C22,C23,C24,C25,C26;
    double C31,C32,C33,C34,C35,C36;
    double C41,C42,C43,C44,C45,C46;
    double C51,C52,C53,C54,C55,C56;
    double C61,C62,C63,C64,C65,C66;
    double Eps11,Eps12,Eps13;
    double Eps21,Eps22,Eps23;
    double Eps31,Eps32,Eps33;
    double DPiezE11,DPiezE12,DPiezE13,DPiezE14,DPiezE15,DPiezE16;
    double DPiezE21,DPiezE22,DPiezE23,DPiezE24,DPiezE25,DPiezE26;
    double DPiezE31,DPiezE32,DPiezE33,DPiezE34,DPiezE35,DPiezE36;
    double Mu11,Mu12,Mu13;
    double Mu21,Mu22,Mu23;
    double Mu31,Mu32,Mu33;
    double QPiezM11,QPiezM12,QPiezM13,QPiezM14,QPiezM15,QPiezM16;
    double QPiezM21,QPiezM22,QPiezM23,QPiezM24,QPiezM25,QPiezM26;
    double QPiezM31,QPiezM32,QPiezM33,QPiezM34,QPiezM35,QPiezM36;
    double AlphaME11,AlphaME12,AlphaME13;
    double AlphaME21,AlphaME22,AlphaME23;
    double AlphaME31,AlphaME32,AlphaME33;
    double D11,D12,D13;
    double D21,D22,D23;
    double D31,D32,D33;
    double K11,K12,K13;
    double K21,K22,K23;
    double K31,K32,K33;
};

#endif // PHASETAB_H
