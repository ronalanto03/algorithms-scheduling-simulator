#include "graphdialog.h"
#include "ui_graphdialog.h"
#include <multSimData.h>
#include <qfiledialog.h>
#include <QString>
#include<fstream>
#include<iostream>

GraphDialog::GraphDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphDialog)
{
    ui->setupUi(this);


    connect(ui->pButtonSave, SIGNAL(released()),this, SLOT(saveAs()));
    connect(ui->pButtonClose, SIGNAL(released()),this, SLOT(close()));

}

GraphDialog::~GraphDialog()
{
    delete ui;
}

void GraphDialog::gnuplot(QString *file,string name, int cant,bool * enabled,double a,int np){
    int j=0;
    string nfile[4];
    nfile[0]=file[0].toStdString();
    nfile[1]=file[1].toStdString();
    nfile[2]=file[2].toStdString();
    nfile[3]=file[3].toStdString();


std::cout<<"CANT :"<<QString::number(a).toStdString()<<" "<<a<<" \n";
    string * commandsForGnuplot= new string[cant+5];
    commandsForGnuplot[0] ="set title \""+name+"\"";
    commandsForGnuplot[1] = "set terminal png ";
    commandsForGnuplot[2] ="set xr [0:"+QString::number(a).toStdString()+"]";
    commandsForGnuplot[3] ="set yr [0:"+QString::number(np).toStdString()+"]";
    commandsForGnuplot[4] ="set output \""+imagePath.toStdString()+".png\"";
    for(int i=0;i<4;i++){
        if(enabled[i]){

            commandsForGnuplot[5+j] ="plot '"+nfile[i]+"' w impulses title '"+name+"'";
            j++;
        }
    }


    std::ofstream plott;
    string pa;


    pa=imagePath.toStdString()+".plt";
    plott.open(pa.c_str());
    qDebug(pa.c_str());

    int i;
      for (i=0; i < cant+5; i++)
          plott<<commandsForGnuplot[i].c_str()<<"\n";

      plott.close();
      string po="gnuplot "+pa;
      system(po.c_str());

      //remove(pa.c_str());
      //remove(file.c_str());

}

void GraphDialog::plot(MutlSimData *msd,bool *enabled,QString name,int index,int np){

    std::ofstream file[4];

    QString nfile[4];
    int i,j;
    int cant=0;
    double a=0.1;
    int ampl;
    imagePath="";
    imagePath+="vs/";
    imagePath+=name.toStdString().c_str();

    nfile[0]=(string("vs/FCFS")+name.toStdString()+(QString::number(index)).toStdString()+string(".log")).c_str();
    nfile[1]=(string("vs/SJF")+name.toStdString()+(QString::number(index)).toStdString()+string(".log")).c_str();
    nfile[2]=(string("vs/PSJF")+name.toStdString()+(QString::number(index)).toStdString()+string(".log")).c_str();
    nfile[3]=(string("vs/RR")+name.toStdString()+(QString::number(index)).toStdString()+string(".log")).c_str();

   file[0].open(nfile[0].toStdString().c_str());
   file[1].open(nfile[1].toStdString().c_str());
   file[2].open(nfile[2].toStdString().c_str());
   file[3].open(nfile[3].toStdString().c_str());

    if(index==0){
        for(i<0;i<4;i++){
            a=0.1;
            if(enabled[i]){
                ampl=10*msd[i].waitingTimeAmplitude;
                cant++;
                for(j=0;j<10;j++){
                    file[i]<< a<<" ";
                    if(msd[i].waitingTimeClasses[j]==0)
                        file[i]<<"0.1"<<"\n";
                    else
                        file[i]<<msd[i].waitingTimeClasses[j]<<"\n";
                    a+=msd[i].waitingTimeAmplitude;
                }

                file[i]<< a<<" ";
                if(msd[i].waitingTimeClasses[9]==0)
                    file[i]<<"0.1"<<"\n";
                else
                    file[i]<<msd[i].waitingTimeClasses[9]<<"\n";
            }
        }
    }

    if(index==1){
        for(i<0;i<4;i++){
            a=0.1;
            if(enabled[i]){
                cant++;
                ampl=10*msd[i].usedTimeAmplitude;
                for(j=0;j<10;j++){

                    file[i]<< a<<" ";
                    if(msd[i].usedTimeClasses[j]==0)
                        file[i]<<"0.1"<<"\n";
                    else
                        file[i]<<msd[i].usedTimeClasses[j]<<"\n";
                    a+=msd[i].usedTimeAmplitude;
                }
                file[i]<< a<<" ";
                if(msd[i].usedTimeClasses[9]==0)
                    file[i]<<"0.1"<<"\n";
                else
                    file[i]<<msd[i].usedTimeClasses[9]<<"\n";
            }
        }
    }

    else{
        for(i<0;i<4;i++){
            a=0.1;
            if(enabled[i]){
                ampl=10*msd[i].turnAroundTimeAmplitude;
                cant++;
                for(j=0;j<10;j++){

                    file[i]<< a<<" ";
                    if(msd[i].turnAroundTimeClasses[j]==0)
                        file[i]<<"0.1"<<"\n";
                    else
                        file[i]<<msd[i].turnAroundTimeClasses[j]<<"\n";
                    a+=msd[i].turnAroundTimeAmplitude;
                }
                file[i]<< a<<" ";
                if(msd[i].turnAroundTimeClasses[9]==0)
                    file[i]<<"0.1"<<"\n";
                else
                    file[i]<<msd[i].turnAroundTimeClasses[9]<<"\n";
            }
        }
    }

    gnuplot(nfile,name.toStdString(),cant,enabled,ampl,np);
}


void GraphDialog::saveAs(){

    QString name;
    QString path="cp ";

//    if(ui->cBoxAlgorithm->currentIndex()==0)
//        name=gPw.data+".png";
//    if(ui->cBoxAlgorithm->currentIndex()==1)
//        name=gPu.data+".png";
//    else
//        name=gPt.data+".png";

    path+=name;
    path+="\ ";

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(name),
               tr("Text Files (*.png)"));
               if (!fileName.isEmpty()) {
                   path+=fileName;
                    system(path.toStdString().c_str());
                   }
               }
