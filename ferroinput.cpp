#include "ferroinput.h"
#include "ui_ferroinput.h"
#include "QDebug.h"
#include <iostream>
#include <fstream>



ferroInput::ferroInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ferroInput)
{
    ui->setupUi(this);
}

ferroInput::~ferroInput()
{
    delete ui;
}




void ferroInput::outputData(QString filedir)
{
    std::ofstream out;
    const char *dir=filedir.toLatin1();
    out.open(dir);
    out << choice_material << " " <<xf<<" "<<temperature<<"\n";
    out << nx <<" "<<ny<<" "<<nz<<"\n";
    out << lx<<" "<<ly<< " "<<lz<<"\n";
    out << nf<<" "<<ns<<" "<<ns1<<"\n";
    out << ksteps<< " "<<kprint<<" "<<kprint<<" "<<kstart<<"\n";
    out << dt << " "<<l0<<" "<<"\n";
    out << "\n";
    out << std::boolalpha << flag_restart << " "<<choice_domain<<" "<<domain_width<<" "<<domain_nx<<" "<<domain_ny<<" "<<domain_magnitude<<"\n";
    out << choice_nuclei<<" "<< std::boolalpha << flag_noise<<" "<<noise_magnitude<<" "<<random_seed<<" "<<"\n";
    out << "\n";
    out << "FALSE" << " " << 0<< "\n";
    out << "\n";
    out << std::boolalpha << flag_gradient << " "<< g11 <<" " << g12 << " " << g44<<" "<< g44m<<" "<<"\n";
    out << "\n";
    out << "FALSE" << " " << 0 << " "<<0 <<" "<<0<<" "<<0<<"\n";
    out << "\n";
    out << std::boolalpha << flag_elastic << " "<< "1"<<"\n";
    out << exx << " " << eyy << " " << exy<<"\n";
    out << choice_indenter << " " << indenter_radius << " " << indenter_shape << " " << indenter_nx << " " << indenter_ny << " "<<"\n";
    out << load_start << " " << load_delta << " " << load_end<<"\n";
    out << "\n";
    out << std::boolalpha << flag_electric << " " << electric_BC <<"\n";
    out << eka1 << " " << eka2 << " " << eka3 << "\n";
    out << voltage_shape << " " << electrode_shape << "\n";
    out << electrode_radius << " " << electrode_path_radius << " "<< electrode_nx << " " << electrode_ny << " " << gamma << " " << mdis <<"\n";
    out << phi_start << " " << phi_delta << " " << phi_end << "\n";
    out << "\n";
    out << std::boolalpha << output_pstart << " " << output_elastic << " " << output_landau << " " << output_electric << " " << output_gradient <<
           " " << output_flexo << " " << output_driving << "\n";
//    out << "\n";
//    out << "0.0 0.0 0.0 1.0" << "\n";
//    out << "0.0 0.0 0.0 1.0" << "\n";
//    out << "\n";
//    out << "FALSE FALSE -1 1"<< "\n";
//    out << "0 1" << "\n";
//    out << "0.1" << "\n";
//    out << "5.d18" << "\n";
//    out << "-1 -1" << "\n";
//    out << "-1 -1" << "\n";
//    out << "\n";
//    out << "0 0" << "\n";
    out.close();
}

void ferroInput::loadData(QString filedir)
{
    std::ifstream in;
    int nothing;
    QByteArray dir1=filedir.toLatin1();
    const char *dir=dir1.data();
    qDebug()<<dir;
    in.open(dir);
    qDebug()<<in.is_open();
    in >> choice_material >>xf>>temperature;
    in.ignore(1000000,'\n');
    in >> nx >>ny>>nz;
    in.ignore(1000000,'\n');
    in >> lx>>ly>>lz;
    in.ignore(1000000,'\n');
    in >> nf>>ns>>ns1;
    in.ignore(1000000,'\n');
    in >> ksteps>>kprint>>kprint>>kstart;
    in.ignore(1000000,'\n');
    in >> dt>>l0;
    in.ignore(1000000,'\n');

    in >> std::boolalpha >> flag_restart>>choice_domain>>domain_width>>domain_nx>>domain_ny>>domain_magnitude;
    in.ignore(1000000,'\n');
    in >> choice_nuclei>> flag_noise>>noise_magnitude>>random_seed;
    in.ignore(1000000,'\n');

    in >> std::boolalpha >> flag_poly >>thetaBi;
    in.ignore(1000000,'\n');

    in >> std::boolalpha >> flag_gradient >> g11 >> g12 >> g44>> g44m;
    in.ignore(1000000,'\n');

    in >> std::boolalpha >> flag_flexo >>  choice_fdmfft >> f11 >>f12>>f44;
    in.ignore(1000000,'\n');

    in >> std::boolalpha >> flag_elastic >> nothing ;
    in.ignore(1000000,'\n');
    in >> exx >> eyy >> exy;
    in.ignore(1000000,'\n');
    in >> choice_indenter >> indenter_radius >> indenter_shape >> indenter_nx >> indenter_ny ;
    in.ignore(1000000,'\n');
    in >> load_start >> load_delta >> load_end;
    in.ignore(1000000,'\n');

    in >> std::boolalpha >> flag_electric >> electric_BC ;
    in.ignore(1000000,'\n');
    in >> eka1 >> eka2 >> eka3 ;
    in.ignore(1000000,'\n');
    in >> voltage_shape >> electrode_shape ;
    in.ignore(1000000,'\n');
    in >> electrode_radius >> electrode_path_radius >> electrode_nx >> electrode_ny >> gamma >> mdis ;
    in.ignore(1000000,'\n');
    in >> phi_start >> phi_delta >> phi_end ;
    in.ignore(1000000,'\n');

    in >> std::boolalpha >> output_pstart >>  output_elastic >>  output_landau >> output_electric >> output_gradient >>
           output_flexo >> output_driving ;
    in.ignore(1000000,'\n');
//    in << endl;
//    in << "0.0 0.0 0.0 1.0" << endl;
//    in << "0.0 0.0 0.0 1.0" << endl;
//    in << endl;
//    in << "FALSE FALSE -1 1"<< endl;
//    in << "0 1" << endl;
//    in << "0.1" << endl;
//    in << "5.d18" << endl;
//    in << "-1 -1" << endl;
//    in << "-1 -1" << endl;
//    in << endl;
//    in << "0 0" << endl;
    in.close();
    qDebug()<< choice_material << electric_BC << choice_fdmfft <<flag_noise<< endl;
}





void ferroInput::on_gradient_CB_stateChanged(int arg1)
{
    if(arg1==2){
        ui->gradient_widget->setEnabled(1);
    }
    else{
        ui->gradient_widget->setEnabled(0);
    }
    flag_gradient=arg1;
    qDebug()<<"flag_gradient"<<flag_gradient;
}

void ferroInput::on_elastic_CB_stateChanged(int arg1)
{

    if(arg1==2){
        ui->elastic_widget->setEnabled(1);
    }
    else{
        ui->elastic_widget->setEnabled(0);
    }
    flag_elastic=arg1;
    qDebug()<<"flag_elastic"<<flag_elastic;
}

void ferroInput::on_nx_LE_editingFinished()
{
    nx=ui->nx_LE->text().toInt();
    qDebug()<<"nx="<<nx;
}

void ferroInput::on_ny_LE_editingFinished()
{
    ny=ui->ny_LE->text().toInt();
    qDebug()<<"ny="<<ny;
}

void ferroInput::on_nz_LE_editingFinished()
{
    nz=ui->nz_LE->text().toInt();
    qDebug()<<"nz="<<nz;
}

void ferroInput::on_ns_LE_editingFinished()
{
    ns=ui->ns_LE->text().toInt();
    qDebug()<<"ns="<<ns;
}

void ferroInput::on_nf_LE_editingFinished()
{
    nf=ui->nf_LE->text().toInt();
    qDebug()<<"nf="<<nf;
}

void ferroInput::on_ns1_LE_editingFinished()
{
    ns1=ui->ns1_LE->text().toInt();
    qDebug()<<"ns1="<<ns1;
}

void ferroInput::on_lx_LE_editingFinished()
{
    lx=ui->lx_LE->text().toDouble();
    qDebug()<<"lx="<<lx;
}

void ferroInput::on_ly_LE_editingFinished()
{
    ly=ui->ly_LE->text().toDouble();
    qDebug()<<"ly="<<ly;
}

void ferroInput::on_lz_LE_editingFinished()
{
    lz=ui->lz_LE->text().toDouble();
    qDebug()<<"lz="<<lz;
}

void ferroInput::on_kstart_LE_editingFinished()
{
    kstart=ui->kstart_LE->text().toInt();
    qDebug()<<"kstart="<<kstart;
}

void ferroInput::on_ksteps_LE_editingFinished()
{
    ksteps=ui->ksteps_LE->text().toInt();
    qDebug()<<"ksteps="<<ksteps;
}

void ferroInput::on_kprint_LE_editingFinished()
{
    kprint=ui->kprint_LE->text().toInt();
    qDebug()<<"kprint="<<kprint;
}

void ferroInput::on_restart_CB_stateChanged(int arg1)
{
    flag_restart=arg1;
    qDebug()<<"restart:"<<flag_restart;
}

void ferroInput::on_noise_CB_stateChanged(int arg1)
{
    flag_noise=arg1;
    qDebug()<<"noise:"<<flag_noise;
}

void ferroInput::on_nuclei_LE_editingFinished()
{
    choice_nuclei=ui->nuclei_LE->text().toInt();
    qDebug()<<"choice_nuclei="<<choice_nuclei;
}

void ferroInput::on_domain_LE_editingFinished()
{
    choice_domain=ui->domain_LE->text().toInt();
    qDebug()<<"choice_domain="<<choice_domain;
}

void ferroInput::on_domainWidth_LE_editingFinished()
{
    domain_width=ui->domainWidth_LE->text().toInt();
    qDebug()<<"domain_width="<<domain_width;
}

void ferroInput::on_domainMag_LE_editingFinished()
{
    domain_magnitude=ui->domainMag_LE->text().toInt();
    qDebug()<<"domain_magnitude="<<domain_magnitude;
}

void ferroInput::on_domainNx_LE_editingFinished()
{
    domain_nx=ui->domainNx_LE->text().toInt();
    qDebug()<<"domain_nx="<<domain_nx;
}

void ferroInput::on_domainNy_LE_editingFinished()
{
    domain_ny=ui->domainNy_LE->text().toInt();
    qDebug()<<"domain_ny="<<domain_ny;
}

//void ferroInput::on_domainNz_LE_editingFinished()
//{
//    domain_nz=ui->domainNz_LE->text().toInt();
//    qDebug()<<"domain_nz="<<domain_nz;
//}

void ferroInput::on_noiseMag_LE_editingFinished()
{
    noise_magnitude=ui->noiseMag_LE->text().toDouble();
    qDebug()<<"noise_magnitude="<<noise_magnitude;
}

void ferroInput::on_randSeed_LE_editingFinished()
{
    random_seed=ui->randSeed_LE->text().toInt();
    qDebug()<<"random_seed="<<random_seed;
}

//void ferroInput::on_material_LE_editingFinished()
//{
//    choice_material=ui->material_LE->text().toInt();
//    qDebug()<<"choice_materail="<<choice_material;
//}

void ferroInput::on_temperature_LE_editingFinished()
{
    temperature=ui->temperature_LE->text().toDouble();
    qDebug()<<"temperature="<<temperature;
}

void ferroInput::on_dt_LE_editingFinished()
{
    dt=ui->dt_LE->text().toDouble();
    qDebug()<<"dt="<<dt;
}

void ferroInput::on_l0_LE_editingFinished()
{
    l0=ui->l0_LE->text().toDouble();
    qDebug()<<"l0="<<l0;
}

void ferroInput::on_g11_LE_editingFinished()
{
    g11=ui->g11_LE->text().toDouble();
    qDebug()<<"g11="<<g11;
}

void ferroInput::on_g12_LE_editingFinished()
{
    g12=ui->g12_LE->text().toDouble();
    qDebug()<<"g12="<<g12;
}

void ferroInput::on_g44_LE_editingFinished()
{
    g44=ui->g44_LE->text().toDouble();
    qDebug()<<"g44="<<g44;
}

void ferroInput::on_exx_LE_editingFinished()
{
    exx=ui->exx_LE->text().toDouble();
    qDebug()<<"exx="<<exx;
}

void ferroInput::on_eyy_LE_editingFinished()
{
    eyy=ui->eyy_LE->text().toDouble();
    qDebug()<<"eyy="<<eyy;
}

void ferroInput::on_exy_LE_editingFinished()
{
    exy=ui->exy_LE->text().toDouble();
    qDebug()<<"exy="<<exy;
}

void ferroInput::on_indenterType_LE_editingFinished()
{
    choice_indenter=ui->indenterType_LE->text().toInt();
    qDebug()<<"choice_indenter="<<choice_indenter;
}

void ferroInput::on_indenterRadius_LE_editingFinished()
{
    indenter_radius=ui->indenterRadius_LE->text().toDouble();
    qDebug()<<"indenter_radius="<<indenter_radius;
}

void ferroInput::on_indenterSF_LE_editingFinished()
{
    indenter_shape=ui->indenterSF_LE->text().toDouble();
    qDebug()<<"indenter_shape="<<indenter_shape;
}

void ferroInput::on_indenterNx_LE_editingFinished()
{
    indenter_nx=ui->indenterNx_LE->text().toInt();
    qDebug()<<"indenter_nx="<<indenter_nx;
}

void ferroInput::on_indenterNy_LE_editingFinished()
{
    indenter_ny=ui->indenterNy_LE->text().toInt();
    qDebug()<<"indenter_ny="<<indenter_ny;
}

void ferroInput::on_indenterStart_LE_editingFinished()
{
    load_start=ui->indenterStart_LE->text().toDouble();
    qDebug()<<"load_start="<<load_start;
}

void ferroInput::on_indenterDelta_LE_editingFinished()
{
    load_delta=ui->indenterDelta_LE->text().toDouble();
    qDebug()<<"load_delta="<<load_delta;
}

void ferroInput::on_indenterEnd_LE_editingFinished()
{
    load_end=ui->indenterEnd_LE->text().toDouble();
    qDebug()<<"load_end="<<load_end;
}

void ferroInput::on_electric_CB_stateChanged(int arg1)
{
    ui->electric_Widget->setEnabled(arg1);
    flag_electric=arg1;
    qDebug()<<"flag_electric"<<flag_electric;
}

void ferroInput::on_elecBC_Combo_activated(int index)
{
    electric_BC=index+1;
    qDebug()<<"electric_BC="<<electric_BC;
}

void ferroInput::on_eka1_LE_editingFinished()
{
    eka1=ui->eka1_LE->text().toDouble();
    qDebug()<<"eka1="<<eka1;
}

void ferroInput::on_eka2_LE_editingFinished()
{
    eka2=ui->eka2_LE->text().toDouble();
    qDebug()<<"eka2="<<eka2;
}

void ferroInput::on_eka3_LE_editingFinished()
{
    eka3=ui->eka3_LE->text().toDouble();
    qDebug()<<"eka3="<<eka3;
}

void ferroInput::on_voltageShape_LE_editingFinished()
{
    voltage_shape=ui->voltageShape_LE->text().toInt();
    qDebug()<<"voltage_shape="<<voltage_shape;
}

void ferroInput::on_electrodeShape_LE_editingFinished()
{
    electrode_shape=ui->electrodeShape_LE->text().toInt();
    qDebug()<<"electrode_shape="<<electrode_shape;
}

void ferroInput::on_electrodeRadius_LE_editingFinished()
{
    electrode_radius=ui->electrodeRadius_LE->text().toDouble();
    qDebug()<<"electrode_radius="<<electrode_radius;
}

void ferroInput::on_pathRadius_LE_editingFinished()
{
    electrode_path_radius=ui->pathRadius_LE->text().toDouble();
    qDebug()<<"electrode_path_radius="<<electrode_path_radius;
}

void ferroInput::on_electrodeNx_LE_editingFinished()
{
    electrode_nx=ui->electrodeNx_LE->text().toInt();
    qDebug()<<"electrode_nx="<<electrode_nx;
}

void ferroInput::on_electrodeNy_LE_editingFinished()
{
    electrode_ny=ui->electrodeNy_LE->text().toInt();
    qDebug()<<"electrode_ny="<<electrode_ny;
}

void ferroInput::on_gamma_LE_editingFinished()
{
    gamma=ui->gamma_LE->text().toDouble();
    qDebug()<<"gamma="<<gamma;
}

//void ferroInput::on_mdis_LE_editingFinished()
//{
//    mdis=ui->mdis_LE->text().toDouble();
//    qDebug()<<"mdis="<<mdis;
//}

void ferroInput::on_phiStart_LE_editingFinished()
{
    phi_start=ui->phiStart_LE->text().toDouble();
    qDebug()<<"phi_start="<<phi_start;
}

void ferroInput::on_phiDelta_LE_editingFinished()
{
    phi_delta=ui->phiDelta_LE->text().toDouble();
    qDebug()<<"phi_delta="<<phi_delta;
}

void ferroInput::on_phiEnd_LE_editingFinished()
{
    phi_end=ui->phiEnd_LE->text().toDouble();
    qDebug()<<"phi_end="<<phi_end;
}

void ferroInput::on_flexo_CB_stateChanged(int arg1)
{
    ui->flexo_Widget->setEnabled(arg1);
    flag_flexo=arg1;
    qDebug()<<"flexo_widget"<<flag_flexo;
}

void ferroInput::on_derivative_Combo_activated(int index)
{
    choice_fdmfft=index+1;
    qDebug()<<"choice_fdmfft"<<choice_fdmfft;
}

void ferroInput::on_f11_LE_editingFinished()
{
    f11=ui->f11_LE->text().toDouble();
    qDebug()<<"f11="<<f11;
}

void ferroInput::on_f12_LE_editingFinished()
{
    f12=ui->f12_LE->text().toDouble();
    qDebug()<<"f12="<<f12;
}

void ferroInput::on_f44_LE_editingFinished()
{
    f44=ui->f44_LE->text().toDouble();
    qDebug()<<"f44="<<f44;
}

void ferroInput::on_Generate_pressed()
{
    QFileDialog filedialog;
    filedialog.setFileMode(QFileDialog::Directory);
    filedialog.setOption(QFileDialog::ShowDirsOnly);
    QString generateDir=filedialog.getExistingDirectory();
    qDebug()<<"Filename:"<<generateDir;
    QString filedir=generateDir+"/inputN.in";

    qDebug()<<"Filedir:"<<filedir;

    outputData(filedir);

    if (!generateDir.isNull()){
        this->accept();
    }
}

void ferroInput::on_xf_LE_editingFinished()
{
    xf=ui->xf_LE->text().toDouble();
    qDebug()<<"xf="<<xf;
}

void ferroInput::on_g44m_LE_editingFinished()
{
    g44m=ui->g44m_LE->text().toDouble();
    qDebug()<<"g44m="<<g44m;
}

void ferroInput::on_outputFlexo_CB_stateChanged(int arg1)
{
    output_flexo=arg1;
    qDebug()<<"output_flexo="<<output_flexo;
}

void ferroInput::on_pStart_CB_stateChanged(int arg1)
{
    output_pstart=arg1;
    qDebug()<<"output_pstart="<<output_pstart;
}

void ferroInput::on_outputElastic_CB_stateChanged(int arg1)
{
    output_elastic=arg1;
    qDebug()<<"output_elastic="<<output_elastic;
}

void ferroInput::on_outputElectric_CB_stateChanged(int arg1)
{
    output_electric=arg1;
    qDebug()<<"output_electric="<<output_electric;
}

void ferroInput::on_outputLandau_CB_stateChanged(int arg1)
{
    output_landau=arg1;
    qDebug()<<"output_landau="<<output_landau;
}

void ferroInput::on_outputGradient_CB_stateChanged(int arg1)
{
    output_gradient=arg1;
    qDebug()<<"output_gradient="<<output_gradient;
}

void ferroInput::on_outputDriving_CB_stateChanged(int arg1)
{
    output_driving=arg1;
    qDebug()<<"output_driving="<<output_driving;
}

void ferroInput::on_loadFile_pressed()
{
    QFileDialog filedialog;
    filedialog.setFileMode(QFileDialog::AnyFile);
    filedialog.setNameFilter(tr("Input (*.in)"));
    filedialog.setOption(QFileDialog::ReadOnly);
    QString load=filedialog.getOpenFileName();
    qDebug()<<"Filename:"<<load;
    loadData(load);
    this->raise();
    ui->nx_LE->setText(QString::number(nx));
    ui->ny_LE->setText(QString::number(ny));
    ui->nz_LE->setText(QString::number(nz));
    ui->ns_LE->setText(QString::number(ns));
    ui->nf_LE->setText(QString::number(nf));
    ui->ns1_LE->setText(QString::number(ns1));
    ui->lx_LE->setText(QString::number(lx));
    ui->ly_LE->setText(QString::number(ly));
    ui->lz_LE->setText(QString::number(lz));
    ui->kstart_LE->setText(QString::number(kstart));
    ui->ksteps_LE->setText(QString::number(ksteps));
    ui->kprint_LE->setText(QString::number(kprint));
    ui->restart_CB->setChecked(flag_restart);
    ui->noise_CB->setChecked(flag_noise);
    ui->nuclei_LE->setText(QString::number(choice_nuclei));
    ui->domain_LE->setText(QString::number(choice_domain));
    ui->domainWidth_LE->setText(QString::number(domain_width));
    ui->domainMag_LE->setText(QString::number(domain_magnitude));
    ui->domainNx_LE->setText(QString::number(domain_nx));
    ui->domainNy_LE->setText(QString::number(domain_ny));
//    ui->domainNz_LE->setText(QString::number(0));
    ui->noiseMag_LE->setText(QString::number(noise_magnitude));
    ui->randSeed_LE->setText(QString::number(random_seed));
//    ui->material_LE->setText(QString::number(choice_material));
    ui->material_combo->setCurrentIndex(choice_material);
    ui->temperature_LE->setText(QString::number(temperature));
    ui->xf_LE->setText(QString::number(xf));
    ui->dt_LE->setText(QString::number(dt));
    ui->l0_LE->setText(QString::number(l0));
    ui->gradient_CB->setChecked(flag_gradient);
    ui->g11_LE->setText(QString::number(g11));
    ui->g12_LE->setText(QString::number(g12));
    ui->g44_LE->setText(QString::number(g44));
    ui->g44m_LE->setText(QString::number(g44m));
    ui->elastic_CB->setChecked(flag_elastic);
    ui->exx_LE->setText(QString::number(exx));
    ui->eyy_LE->setText(QString::number(eyy));
    ui->exy_LE->setText(QString::number(exy));
    ui->indenterType_LE->setText(QString::number(choice_indenter));
    ui->indenterRadius_LE->setText(QString::number(indenter_radius));
    ui->indenterSF_LE->setText(QString::number(indenter_shape));
    ui->indenterNx_LE->setText(QString::number(indenter_nx));
    ui->indenterNy_LE->setText(QString::number(indenter_ny));
    ui->indenterStart_LE->setText(QString::number(load_start));
    ui->indenterDelta_LE->setText(QString::number(load_delta));
    ui->indenterEnd_LE->setText(QString::number(load_end));
    ui->electric_CB->setChecked(flag_electric);
    ui->elecBC_Combo->setCurrentIndex(electric_BC-1);
    ui->eka1_LE->setText(QString::number(eka1));
    ui->eka2_LE->setText(QString::number(eka2));
    ui->eka3_LE->setText(QString::number(eka3));
    ui->voltageShape_LE->setText(QString::number(voltage_shape));
    ui->electrodeShape_LE->setText(QString::number(electrode_shape));
    ui->electrodeRadius_LE->setText(QString::number(electrode_radius));
    ui->pathRadius_LE->setText(QString::number(electrode_path_radius));
    ui->electrodeNx_LE->setText(QString::number(electrode_nx));
    ui->electrodeNy_LE->setText(QString::number(electrode_ny));
    ui->gamma_LE->setText(QString::number(gamma));
//    ui->mdis_LE->setText(QString::number(mdis));
    ui->phiStart_LE->setText(QString::number(phi_start));
    ui->phiDelta_LE->setText(QString::number(phi_delta));
    ui->phiEnd_LE->setText(QString::number(phi_end));
    ui->pStart_CB->setChecked(output_pstart);
    ui->outputElastic_CB->setChecked(output_elastic);
    ui->outputElectric_CB->setChecked(output_electric);
    ui->outputLandau_CB->setChecked(output_landau);
    ui->outputGradient_CB->setChecked(output_gradient);
    ui->outputDriving_CB->setChecked(output_driving);
    ui->flexo_CB->setChecked(flag_flexo);
    ui->outputFlexo_CB->setChecked(output_flexo);
        qDebug()<<ui->derivative_Combo->currentIndex()<<choice_fdmfft;
    ui->derivative_Combo->setCurrentIndex(choice_fdmfft-1);
    qDebug()<<ui->derivative_Combo->currentIndex()<<choice_fdmfft;
    ui->f11_LE->setText(QString::number(f11));
    ui->f12_LE->setText(QString::number(f12));
    ui->f44_LE->setText(QString::number(f44));
}

void ferroInput::on_material_combo_activated(int index)
{
    choice_material=index+1;
    qDebug()<<"choice_material"<<choice_material;
}
