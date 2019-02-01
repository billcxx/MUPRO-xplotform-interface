#ifndef FERROINPUT_H
#define FERROINPUT_H

#include <QDialog>
#include <QFileDialog>
#include <QFile>



namespace Ui {
class ferroInput;
}

class ferroInput : public QDialog
{
    Q_OBJECT

public:
    explicit ferroInput(QWidget *parent = 0);
    ~ferroInput();

private slots:

    void outputData(QString filedir);

    void loadData(QString filedir);

    void on_gradient_CB_stateChanged(int arg1);

    void on_elastic_CB_stateChanged(int arg1);

    void on_nx_LE_editingFinished();

    void on_ny_LE_editingFinished();

    void on_nz_LE_editingFinished();

    void on_ns_LE_editingFinished();

    void on_nf_LE_editingFinished();

    void on_ns1_LE_editingFinished();

    void on_lx_LE_editingFinished();

    void on_ly_LE_editingFinished();

    void on_lz_LE_editingFinished();

    void on_kstart_LE_editingFinished();

    void on_ksteps_LE_editingFinished();

    void on_kprint_LE_editingFinished();

    void on_restart_CB_stateChanged(int arg1);

    void on_noise_CB_stateChanged(int arg1);

    void on_nuclei_LE_editingFinished();

    void on_domain_LE_editingFinished();

    void on_domainWidth_LE_editingFinished();

    void on_domainMag_LE_editingFinished();

    void on_domainNx_LE_editingFinished();

    void on_domainNy_LE_editingFinished();

//    void on_domainNz_LE_editingFinished();

    void on_noiseMag_LE_editingFinished();

    void on_randSeed_LE_editingFinished();

//    void on_material_LE_editingFinished();

    void on_temperature_LE_editingFinished();

    void on_dt_LE_editingFinished();

    void on_l0_LE_editingFinished();

    void on_g11_LE_editingFinished();

    void on_g12_LE_editingFinished();

    void on_g44_LE_editingFinished();

    void on_exx_LE_editingFinished();

    void on_eyy_LE_editingFinished();

    void on_exy_LE_editingFinished();

    void on_indenterType_LE_editingFinished();

    void on_indenterRadius_LE_editingFinished();

    void on_indenterSF_LE_editingFinished();

    void on_indenterNx_LE_editingFinished();

    void on_indenterNy_LE_editingFinished();

    void on_indenterStart_LE_editingFinished();

    void on_indenterDelta_LE_editingFinished();

    void on_indenterEnd_LE_editingFinished();

    void on_electric_CB_stateChanged(int arg1);

    void on_elecBC_Combo_activated(int index);

    void on_eka1_LE_editingFinished();

    void on_eka2_LE_editingFinished();

    void on_eka3_LE_editingFinished();

    void on_voltageShape_LE_editingFinished();

    void on_electrodeShape_LE_editingFinished();

    void on_electrodeRadius_LE_editingFinished();

    void on_pathRadius_LE_editingFinished();

    void on_electrodeNx_LE_editingFinished();

    void on_electrodeNy_LE_editingFinished();

    void on_gamma_LE_editingFinished();

//    void on_mdis_LE_editingFinished();

    void on_phiStart_LE_editingFinished();

    void on_phiDelta_LE_editingFinished();

    void on_phiEnd_LE_editingFinished();

    void on_flexo_CB_stateChanged(int arg1);

    void on_derivative_Combo_activated(int index);

    void on_f11_LE_editingFinished();

    void on_f12_LE_editingFinished();

    void on_f44_LE_editingFinished();

    void on_Generate_pressed();

    void on_xf_LE_editingFinished();

    void on_g44m_LE_editingFinished();

    void on_outputFlexo_CB_stateChanged(int arg1);

    void on_pStart_CB_stateChanged(int arg1);

    void on_outputElastic_CB_stateChanged(int arg1);

    void on_outputElectric_CB_stateChanged(int arg1);

    void on_outputLandau_CB_stateChanged(int arg1);

    void on_outputGradient_CB_stateChanged(int arg1);

    void on_outputDriving_CB_stateChanged(int arg1);

    void on_loadFile_pressed();

    void on_material_combo_activated(int index);

    void on_readImage_PB_released();

private:
    Ui::ferroInput *ui;
    int nx,ny,nz;
    int ns,nf,ns1;
    double lx,ly,lz;
    int kstart,ksteps,kprint;
    bool flag_restart,flag_noise;
    int choice_nuclei,choice_domain,random_seed;
    int domain_width,domain_nx,domain_ny,domain_nz;
    double noise_magnitude,domain_magnitude;

    int choice_material;
    double dt,l0,temperature,xf;

    bool flag_gradient;
    double g11,g12,g44,g44m;

    bool flag_elastic;
    double exx,eyy,exy;
    int choice_indenter,indenter_nx,indenter_ny;
    double indenter_radius,indenter_shape;
    double load_start,load_delta,load_end;

    bool flag_electric;
    int electric_BC,voltage_shape,electrode_shape;
    double eka1,eka2,eka3,electrode_radius;
    double electrode_path_radius,gamma,mdis;
    int electrode_nx,electrode_ny;
    double phi_start,phi_delta,phi_end;

    bool flag_flexo;
    int choice_fdmfft;
    double f11,f12,f44;

    bool output_elastic,output_electric,output_flexo;
    bool output_pstart,output_landau,output_gradient,output_driving;

    bool flag_poly;
    double thetaBi;

};



#endif // FERROINPUT_H
