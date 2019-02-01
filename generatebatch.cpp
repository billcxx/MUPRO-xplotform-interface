#include "generatebatch.h"
#include "ui_generatebatch.h"
#include "QDebug"
#include "QListView"
#include "QFileDialog"
#include "fstream"

generateBatch::generateBatch(QWidget *parent,QVector<QString> intList, QVector<QString> douList,QVector<QString> boolList) :
    QDialog(parent),
    ui(new Ui::generateBatch)
{
    integerList=intList;
    doubleList=douList;
    booleanList=boolList;
    ui->setupUi(this);
    this->ui->parameter_Combo->setView(new QListView());
    for(int i=0; i<booleanList.length();i++){
        this->ui->parameter_Combo->addItem(booleanList[i]);
        qDebug()<<i<<booleanList[i]<<booleanList.length();
    }
    for(int i=0; i< integerList.length(); i++){
        this->ui->parameter_Combo->addItem(integerList[i]);
        qDebug()<<integerList[i];
    }
    for(int i=0; i< doubleList.length(); i++){
        this->ui->parameter_Combo->addItem(doubleList[i]);
        qDebug()<<doubleList[i];
    }
}

generateBatch::~generateBatch()
{
    delete ui;
}

void generateBatch::on_add_PB_released()
{
    if(this->ui->parameter_Table->findItems(this->ui->parameter_Combo->currentText(), Qt::MatchExactly).count()!=0){
        qDebug()<<"already in the table";
    }else{
        if(booleanList.indexOf(this->ui->parameter_Combo->currentText())!=-1){
            qDebug()<<"belongs to the boolean";
            this->ui->parameter_Table->insertRow(0);
            this->ui->parameter_Table->setItem(0,0,new QTableWidgetItem(this->ui->parameter_Combo->currentText()));
            this->ui->parameter_Table->setItem(0,1,new QTableWidgetItem("true"));
            this->ui->parameter_Table->setItem(0,2,new QTableWidgetItem("false"));
            this->ui->parameter_Table->setItem(0,3,new QTableWidgetItem("-"));
        }else{
            qDebug()<<"belongs to others than boolean";
            this->ui->parameter_Table->insertRow(0);
            this->ui->parameter_Table->setItem(0,0,new QTableWidgetItem(this->ui->parameter_Combo->currentText()));
            this->ui->parameter_Table->setItem(0,1,new QTableWidgetItem(this->ui->start_LE->text()));
            this->ui->parameter_Table->setItem(0,2,new QTableWidgetItem(this->ui->end_LE->text()));
            this->ui->parameter_Table->setItem(0,3,new QTableWidgetItem(this->ui->delta_LE->text()));
        }
    }
}

void generateBatch::on_parameter_Combo_currentIndexChanged(const QString &arg1)
{
    if(booleanList.indexOf(arg1)!=-1){
        this->ui->start_LE->setEnabled(false);
        this->ui->delta_LE->setEnabled(false);
        this->ui->end_LE->setEnabled(false);
        this->ui->to_LB->setEnabled(false);
        this->ui->every_LB->setEnabled(false);
        this->ui->type_LB->setText("Type: boolean");
    }else{
        this->ui->start_LE->setEnabled(true);
        this->ui->delta_LE->setEnabled(true);
        this->ui->end_LE->setEnabled(true);
        this->ui->to_LB->setEnabled(true);
        this->ui->every_LB->setEnabled(true);
        if(integerList.indexOf(arg1)!=-1){
            this->ui->type_LB->setText("Type: integer");
        }else if(doubleList.indexOf(arg1)!=-1){
            this->ui->type_LB->setText("Type: float");
        }
    }
}

void generateBatch::on_delete_PB_released()
{
    if(this->ui->parameter_Table->rowCount()>0){
        this->ui->parameter_Table->removeRow(this->ui->parameter_Table->currentRow());
    }
}

void generateBatch::on_pushButton_released()
{
    QFileDialog filedialog;
    filedialog.setAcceptMode(QFileDialog::AcceptSave);
    filedialog.setDefaultSuffix("sh");
    QString load=filedialog.getSaveFileName(0,tr("Save file"),0,tr("Bash script (*.sh)"));
    qDebug()<<load;
    std::ofstream output;
    output.open(load.toStdString().c_str(),std::ios_base::binary);
    output << "#!/bin/bash" <<"\n";
    output << "inputFile=\"parameter.in\"" << "\n";
    output << "pbsFile=\"run.pbs\"" << "\n";
    for(int i=0; i< this->ui->parameter_Table->rowCount();i++){
        batchList.append(this->ui->parameter_Table->item(i,0)->text());

        std::string parameterName=this->ui->parameter_Table->item(i,0)->text().toStdString();
        output << std::string(i,'\t');
        if(booleanList.indexOf(QString::fromStdString(parameterName))!=-1){
            output << "for " << parameterName<< " in " << "true false;do"<<"\n";
        }
        if(integerList.indexOf(QString::fromStdString(parameterName))!=-1){
            int start=this->ui->parameter_Table->item(i,1)->text().toInt();
            int end=this->ui->parameter_Table->item(i,2)->text().toInt();
            int delta=this->ui->parameter_Table->item(i,3)->text().toInt();
//            output << parameterName << "=$(awk 'BEGIN{for(i="<<start<<";i<="<<end<<";i=i+"<<delta<<")print i}')"<<"\n";
//            output << "for " << parameterName<< " in $(" << parameterName << ");do"<<"\n";
            output << "for (( " << parameterName<< "=" << start << "; " << parameterName << " <= " << end << "; " << parameterName <<"="<<parameterName<<"+"<<delta <<" ));do"<<"\n";
        }
        if(doubleList.indexOf(QString::fromStdString(parameterName))!=-1){
            double start=this->ui->parameter_Table->item(i,1)->text().toDouble();
            double end=this->ui->parameter_Table->item(i,2)->text().toDouble();
            double delta=this->ui->parameter_Table->item(i,3)->text().toDouble();
            output << parameterName << "List=$(echo \"for(i="<<start<<";i<="<<end<<";i=i+"<<delta<<") i\" | bc | awk '{printf \"%f \",$0}')"<<"\n";
            output << "for " << parameterName<< " in $" << parameterName << "List;do"<<"\n";
//            output << "for (( " << parameterName<< "=" << start << "; " << parameterName << " <= " << end << "; " << parameterName <<"="<<parameterName<<"+"<<delta <<" ));do"<<"\n";
        }
        output << std::string(i,'\t') << "\tmkdir " << parameterName <<"-"<< "${" << parameterName << "}" << "\n";
        output << std::string(i,'\t') << "\tcd " << parameterName <<"-" << "${" << parameterName << "}" << "\n";
        output << std::string(i,'\t') << "\tcp ../${inputFile} ." << "\n";
        output << std::string(i,'\t') << "\tsed \"s/" << parameterName << "/${" << parameterName << "}/g\" ${inputFile} > ${inputFile}_temp" << "\n";
        output << std::string(i,'\t') << "\tmv ${inputFile}_temp ${inputFile}" << "\n";

        output << std::string(i,'\t') << "\tcp ../${pbsFile} ." << "\n";
        if(i==this->ui->parameter_Table->rowCount()-1){
            output << std::string(i,'\t') << "\tsed \"s/jobName/" << parameterName << ":${" << parameterName << "}/g\" ${pbsFile} > ${pbsFile}_temp" << "\n";
        }else{
            output << std::string(i,'\t') << "\tsed \"s/jobName/" << parameterName << ":${" << parameterName << "}-jobName/g\" ${pbsFile} > ${pbsFile}_temp" << "\n";
        }
        output << std::string(i,'\t') << "\tmv ${pbsFile}_temp ${pbsFile}"<< "\n";
        if(i==this->ui->parameter_Table->rowCount()-1){
            output << std::string(i,'\t') << "\tcd .." << "\n";
        }
    }

    for(int i=this->ui->parameter_Table->rowCount()-1; i>=0; i--){
        output << std::string(i,'\t');
        output << "done" << "\n";
        if(i>0){
            output << std::string(i,'\t') << "cd .." << "\n";
        }
    }
    output.close();


    QFileInfo fileInfo(load);
    QString load1=fileInfo.absolutePath()+"/submit.sh";
    qDebug()<<load1<<"load1";
    output.open(load1.toStdString().c_str(),std::ios_base::binary);
    output << "#!/bin/bash" <<"\n";
    output << "pbsFile=\"run.pbs\"" << "\n";
    for(int i=0; i< this->ui->parameter_Table->rowCount();i++){
        batchList.append(this->ui->parameter_Table->item(i,0)->text());

        std::string parameterName=this->ui->parameter_Table->item(i,0)->text().toStdString();
        output << std::string(i,'\t');
        if(booleanList.indexOf(QString::fromStdString(parameterName))!=-1){
            output << "for " << parameterName<< " in " << "true false;do"<<"\n";
        }
        if(integerList.indexOf(QString::fromStdString(parameterName))!=-1){
            int start=this->ui->parameter_Table->item(i,1)->text().toInt();
            int end=this->ui->parameter_Table->item(i,2)->text().toInt();
            int delta=this->ui->parameter_Table->item(i,3)->text().toInt();
//            output << parameterName << "=$(awk 'BEGIN{for(i="<<start<<";i<="<<end<<";i=i+"<<delta<<")print i}')"<<"\n";
//            output << "for " << parameterName<< " in $(" << parameterName << ");do"<<"\n";
            output << "for (( " << parameterName<< "=" << start << "; " << parameterName << " <= " << end << "; " << parameterName <<"="<<parameterName<<"+"<<delta <<" ));do"<<"\n";
        }
        if(doubleList.indexOf(QString::fromStdString(parameterName))!=-1){
            double start=this->ui->parameter_Table->item(i,1)->text().toDouble();
            double end=this->ui->parameter_Table->item(i,2)->text().toDouble();
            double delta=this->ui->parameter_Table->item(i,3)->text().toDouble();
            output << parameterName << "List=$(echo \"for(i="<<start<<";i<="<<end<<";i=i+"<<delta<<") i\" | bc | awk '{printf \"%f \",$0}')"<<"\n";
            output << "for " << parameterName<< " in $" << parameterName << "List;do"<<"\n";
        }
        output << std::string(i,'\t') << "\tcd " << parameterName <<"-" << "${" << parameterName << "}" << "\n";
        if(i==this->ui->parameter_Table->rowCount()-1){
            output << std::string(i,'\t') << "\tqsub ${pbsFile}" << "\n";
        }
        if(i==this->ui->parameter_Table->rowCount()-1){
            output << std::string(i,'\t') << "\tcd .." << "\n";
        }
    }

    for(int i=this->ui->parameter_Table->rowCount()-1; i>=0; i--){
        output << std::string(i,'\t');
        output << "done" << "\n";
        if(i>0){
            output << std::string(i,'\t') << "cd .." << "\n";
        }
    }
    output.close();
}
