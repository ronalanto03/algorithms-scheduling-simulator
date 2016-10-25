/**
  * @file mainwindow.cpp
  * @brief Definicion de los metodos de la clase MainWindow.
  * @author Cesar Vielma & Ronald Sulbaran. cesarlvielma@gmail.com,ronalanto03@gmail.com.
  * @date 13-08-2013
  */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h>

using namespace std;

MainWindow::MainWindow(char * ip, int port) :
    QMainWindow(0),
    ui(new Ui::MainWindow)
{

   Q_INIT_RESOURCE(images);
    ui->setupUi(this);

    this->port=port;
    this->ip = ip;

    for(int i=0;i<5;i++){
        simulationSettings[i] = new DataSocket1(i+1);
        simulationSettings[i]->n=3;
        simulationSettings[i]->arrTimeD.left=3;
        simulationSettings[i]->arrTimeD.t=3;
        simulationSettings[i]->durationTimeD.left=500;
        simulationSettings[i]->durationTimeD.right=1000;
        simulationSettings[i]->durationTimeD.t=2;
        simulationSettings[i]->cpuBusrtTimeD.left=100;
        simulationSettings[i]->cpuBusrtTimeD.right=150;
        simulationSettings[i]->cpuBusrtTimeD.t=2;
        simulationSettings[i]->blockingTimeD.t=1;
        simulationSettings[i]->blockingTimeD.left=1;

//        simulationSettings[i]->arrTimeD.left=1;
//        simulationSettings[i]->arrTimeD.t=1;
//        simulationSettings[i]->durationTimeD.left=1;
//        simulationSettings[i]->durationTimeD.right=1;
//        simulationSettings[i]->durationTimeD.t=1;
//        simulationSettings[i]->cpuBusrtTimeD.left=1;
//        simulationSettings[i]->cpuBusrtTimeD.right=1;
//        simulationSettings[i]->cpuBusrtTimeD.t=1;
//        simulationSettings[i]->blockingTimeD.t=1;
//        simulationSettings[i]->blockingTimeD.left=1;

    }

    dwvs= new DataWindow(this,simulationSettings[4]);



    tsvs = new ThreadSocketVs(this,dwvs);

    pwRR = new PaintWindow(this,"RoundRobin",simulationSettings[3]);
    pwFCFS = new PaintWindow(this,"FirstComeFirstServe",simulationSettings[0]);
    pwSJF = new PaintWindow(this,"ShortestJobFirst",simulationSettings[1]);
    pwPSJF = new PaintWindow(this,"Pre.ShortestJobFirst",simulationSettings[2]);

    gwRR = new GraphsWindow(this,"RoundRobin");
    gwFCFS = new GraphsWindow(this,"FirstComeFirstServe");
    gwSJF = new GraphsWindow(this,"ShortestJobFirst");
    gwPSJF = new GraphsWindow(this,"Pre.ShortestJobFirst");

    tsRR = new ThreadSocket(this,ui->labelLoadingbarRR,pwRR,ui->hLayoutRR,simulationSettings[3],gwRR,"sf/RoundRobin");
    tsFCFS = new ThreadSocket(this,ui->labelLoadingbarFCFS,pwFCFS,ui->hLayoutFCFS,simulationSettings[0],gwFCFS,"sf/FirstComeFirstServe");
    tsSJF = new ThreadSocket(this,ui->labelLoadingbarSJF,pwSJF,ui->hLayoutSJF,simulationSettings[1],gwSJF,"sf/ShortestJobFirst");
    tsPSJF = new ThreadSocket(this,ui->labelLoadingbarPSJF,pwPSJF,ui->hLayoutPSJF,simulationSettings[2],gwPSJF,"sf/Pre.ShortestJobFirst");

    SMrunTrheads = new QSignalMapper(this);
    SMrunTrheads->setMapping(ui->pButtonRR_R,tsRR);
    SMrunTrheads->setMapping(ui->pButtonFCFS_R,tsFCFS);
    SMrunTrheads->setMapping(ui->pButtonSJF_R,tsSJF);
    SMrunTrheads->setMapping(ui->pButtonPSJF_R,tsPSJF);

    SMrunTrheads->setMapping(ui->pButtonRR_Se,3);
    SMrunTrheads->setMapping(ui->pButtonFCFS_Se,0);
    SMrunTrheads->setMapping(ui->pButtonSJF_Se,1);
    SMrunTrheads->setMapping(ui->pButtonPSJF_Se,2);
    //SMrunTrheads->setMapping(ui->pButtonSettingsvs,4);

    QMainWindow::connect(ui->pButtonRR_R, SIGNAL(released()),SMrunTrheads, SLOT(map()));
    QMainWindow::connect(ui->pButtonFCFS_R, SIGNAL(released()),SMrunTrheads, SLOT(map()));
    QMainWindow::connect(ui->pButtonSJF_R, SIGNAL(released()),SMrunTrheads, SLOT(map()));
    QMainWindow::connect(ui->pButtonPSJF_R, SIGNAL(released()),SMrunTrheads, SLOT(map()));

    QMainWindow::connect(ui->pButtonRR_Se, SIGNAL(released()),SMrunTrheads, SLOT(map()));
    QMainWindow::connect(ui->pButtonFCFS_Se, SIGNAL(released()),SMrunTrheads, SLOT(map()));
    QMainWindow::connect(ui->pButtonSJF_Se, SIGNAL(released()),SMrunTrheads, SLOT(map()));
    QMainWindow::connect(ui->pButtonPSJF_Se, SIGNAL(released()),SMrunTrheads, SLOT(map()));

    connect(SMrunTrheads, SIGNAL(mapped(QObject*)),this, SLOT(runThreadSocketSelf(QObject*)));
    connect(SMrunTrheads, SIGNAL(mapped(int)),this, SLOT(showSettings(int)));


    SMcancelSimulation = new QSignalMapper(this);

    SMcancelSimulation->setMapping(ui->pButtonRR_St,tsRR);
    SMcancelSimulation->setMapping(ui->pButtonFCFS_St,tsFCFS);
    SMcancelSimulation->setMapping(ui->pButtonSJF_St,tsSJF);
    SMcancelSimulation->setMapping(ui->pButtonPSJF_St,tsPSJF);

    QMainWindow::connect(ui->pButtonRR_St, SIGNAL(released()),SMcancelSimulation, SLOT(map()));
    QMainWindow::connect(ui->pButtonFCFS_St, SIGNAL(released()),SMcancelSimulation, SLOT(map()));
    QMainWindow::connect(ui->pButtonSJF_St, SIGNAL(released()),SMcancelSimulation, SLOT(map()));
    QMainWindow::connect(ui->pButtonPSJF_St, SIGNAL(released()),SMcancelSimulation, SLOT(map()));

    QMainWindow::connect(SMcancelSimulation, SIGNAL(mapped(QObject*)),this, SLOT(cancelSimulation(QObject*)));

    SMcancelSimulation2 = new QSignalMapper(this);

    SMcancelSimulation2->setMapping(tsRR,tsRR);
    SMcancelSimulation2->setMapping(tsFCFS,tsFCFS);
    SMcancelSimulation2->setMapping(tsSJF,tsSJF);
    SMcancelSimulation2->setMapping(tsPSJF,tsPSJF);

    QMainWindow::connect(tsRR, SIGNAL(finishedConnection()),SMcancelSimulation2, SLOT(map()));
    QMainWindow::connect(tsFCFS, SIGNAL(finishedConnection()),SMcancelSimulation2, SLOT(map()));
    QMainWindow::connect(tsSJF, SIGNAL(finishedConnection()),SMcancelSimulation2, SLOT(map()));
    QMainWindow::connect(tsPSJF, SIGNAL(finishedConnection()),SMcancelSimulation2, SLOT(map()));

    QMainWindow::connect(SMcancelSimulation2, SIGNAL(mapped(QObject*)),this, SLOT(setIcons(QObject*)));

    SMenableOptions = new QSignalMapper(this);
    SMenableOptions->setMapping(ui->cBoxRR,ui->hLayoutRR);
    SMenableOptions->setMapping(ui->cBoxFCFS,ui->hLayoutFCFS);
    SMenableOptions->setMapping(ui->cBoxSJF,ui->hLayoutSJF);
    SMenableOptions->setMapping(ui->cBoxPSJF,ui->hLayoutPSJF);

    QMainWindow::connect(ui->cBoxRR, SIGNAL(stateChanged(int)),SMenableOptions, SLOT(map()));
    QMainWindow::connect(ui->cBoxFCFS, SIGNAL(stateChanged(int)),SMenableOptions, SLOT(map()));
    QMainWindow::connect(ui->cBoxSJF, SIGNAL(stateChanged(int)),SMenableOptions, SLOT(map()));
    QMainWindow::connect(ui->cBoxPSJF, SIGNAL(stateChanged(int)),SMenableOptions, SLOT(map()));

    QMainWindow::connect(SMenableOptions, SIGNAL(mapped(QObject*)),this, SLOT(enableOptions(QObject*)));

    //QMainWindow::connect(ui->pButtonRunvs, SIGNAL(released()),this, SLOT(runThreadSocketVs()));

    //QMainWindow::connect(ui->pButtonCancelvs, SIGNAL(released()),this, SLOT(cancelSimulationVs()));

    //QMainWindow::connect(ui->cBoxAllvs, SIGNAL(stateChanged(int)),this, SLOT(selectAll()));

   QMainWindow::connect(tsvs, SIGNAL(finishedConnection()),this, SLOT(setIconsVs()));

   for(int i=0;i<4;i++){
       gw[i] = new GraphsWindow(this,dwvs->names[i]);
       tsvs->gw[i]=gw[i];
   }


    QAction *aboutAct = new QAction(tr("&About ProSimRC..."), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    QMainWindow::connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
    QMainWindow::connect(ui->pButtonAbout, SIGNAL(released()), this, SLOT(about()));

    ui->menuHelp->addAction(aboutAct);

    enableOptions(ui->hLayoutRR);
    enableOptions(ui->hLayoutFCFS);
    enableOptions(ui->hLayoutSJF);
    enableOptions(ui->hLayoutPSJF);
}

MainWindow::~MainWindow()
{
    EventData eDataSend;
    DataSocket1 ds(-1);
    eDataSend.event=-1;
    if(tsRR->connected){
        ::close(tsRR->socketId);
        write(tsRR->socketId,(char*)(&eDataSend), sizeof(struct EventData));
    }
    if(tsFCFS->connected){
        write(tsFCFS->socketId,(char*)(&eDataSend), sizeof(struct EventData));
        ::close(tsFCFS->socketId);
    }
    if(tsSJF->connected){
        write(tsSJF->socketId,(char*)(&eDataSend), sizeof(struct EventData));
        ::close(tsSJF->socketId);
    }
    if(tsPSJF->connected){
        write(tsPSJF->socketId,(char*)(&eDataSend), sizeof(struct EventData));
       ::close(tsPSJF->socketId);
    }

    tsRR->setConnection(this->ip,this->port);
    write(tsRR->socketId,(char*)(&ds), sizeof(struct DataSocket1));
    ::close(tsRR->socketId);

    delete ui;
    delete pwRR;
    delete pwFCFS;
    delete pwSJF;
    delete pwPSJF;
    delete tsRR;
    delete tsFCFS;
    delete tsSJF;
    delete tsPSJF;
}


void MainWindow::cancelSimulation(QObject * obj){

    ThreadSocket * ts = (ThreadSocket *)obj;
    QPixmap  pixmapAsk(":/images/images/ask.png",0);
    QPixmap  pixmapStop(":/images/images/stop.png",0);

    if(!ts->connected){
        ts->label->setPixmap(pixmapAsk.scaled ( 30, 30, Qt::IgnoreAspectRatio));
        ((QLabel *)ts->layout->itemAt(12)->widget())->setText("Not active\n Simulation 1");
    }
    else{
        ts->abort();
        ts->label->setPixmap(pixmapStop .scaled ( 30, 30, Qt::IgnoreAspectRatio));
        ((QLabel *)ts->layout->itemAt(12)->widget())->setText(" Simulation aborted");
        ((QLabel *)ts->layout->itemAt(7)->widget())->setEnabled(true);
    }

}


int MainWindow::runThreadSocketSelf(QObject* obj ){

    ThreadSocket * ts = (ThreadSocket *)obj;
    QMovie *movie;
    QPixmap  pixmapRunning(":/images/images/running.png",0);
    QPixmap  pixmapAsk(":/images/images/ask.png",0);

    if( ((QRadioButton *)ts->layout->itemAt(6)->widget())->isChecked() ){
        if(ts->setConnection(this->ip,this->port)){
            ts->label->setPixmap(pixmapAsk.scaled ( 30, 30, Qt::IgnoreAspectRatio));
            ((QLabel *)ts->layout->itemAt(12)->widget())->setText("Connection Socket\n error");
            return 1;
             }

        movie = new QMovie(":/images/images/loadingbar.gif");
        ts->label->setMovie(movie);
        ((QLabel *)ts->layout->itemAt(12)->widget())->setText("Loading");
        ((QLabel *)ts->layout->itemAt(7)->widget())->setEnabled(false);
        movie->start();
        ts->start();

    }

    else if( ((QRadioButton *)ts->layout->itemAt(4)->widget())->isChecked() ){
        if(ts->setConnection(this->ip,this->port)){
            ts->label->setPixmap(pixmapAsk.scaled ( 30, 30, Qt::IgnoreAspectRatio));
            ((QLabel *)ts->layout->itemAt(12)->widget())->setText("Connection Socket\n error");
            return 1;
         }

        ((QLabel *)ts->layout->itemAt(12)->widget())->setText("Running Simulation");
        ((QLabel *)ts->layout->itemAt(7)->widget())->setEnabled(false);
        ts->label->setPixmap(pixmapRunning.scaled ( 30, 30, Qt::IgnoreAspectRatio));
        ts->paintWindow->show();
        ts->startSimulation();

     }

    else{
        ((QLabel *)ts->layout->itemAt(12)->widget())->setText("Select Simulator\n or Graphics");
        ts->label->setPixmap(pixmapAsk.scaled ( 30, 30, Qt::IgnoreAspectRatio));
    }
    return 0;
}

void MainWindow::showSettings(int alg){

    SettingsDialog sDialog(this,simulationSettings[alg]);
    sDialog.exec();
}

void MainWindow::enableOptions(QObject * obj){


    QHBoxLayout * layout = (QHBoxLayout *)obj;

    if(((QCheckBox *)layout->itemAt(2)->widget())->checkState()){
        ((QRadioButton *)layout->itemAt(4)->widget())->setEnabled(true);
        ((QRadioButton *)layout->itemAt(6)->widget())->setEnabled(true);
        ((QPushButton *)layout->itemAt(7)->widget())->setEnabled(true);
        ((QPushButton *)layout->itemAt(8)->widget())->setEnabled(true);
        ((QPushButton *)layout->itemAt(9)->widget())->setEnabled(true);

   }
    else{
        ((QRadioButton *)layout->itemAt(4)->widget())->setEnabled(false);
        ((QRadioButton *)layout->itemAt(6)->widget())->setEnabled(false);
        ((QPushButton *)layout->itemAt(7)->widget())->setEnabled(false);
        ((QPushButton *)layout->itemAt(8)->widget())->setEnabled(false);
        ((QPushButton *)layout->itemAt(9)->widget())->setEnabled(false);
        ((QRadioButton *)layout->itemAt(4)->widget())->setChecked(false);
        ((QRadioButton *)layout->itemAt(6)->widget())->setChecked(false);
    }

}

void MainWindow::setIcons(QObject *obj){

    ThreadSocket * ts = (ThreadSocket *)obj;
    QPixmap  pixmapStop(":/images/images/stop.png",0);
    QPixmap  pixmapCheck(":/images/images/check.png",0);


    if(ts->fs==-1){
        ((QLabel *)ts->layout->itemAt(12)->widget())->setText(" Simulation aborted");
        ((QLabel *)ts->layout->itemAt(7)->widget())->setEnabled(true);
        ts->label->setPixmap(pixmapStop.scaled ( 30, 30, Qt::IgnoreAspectRatio));
    }

    else if(ts->fs==0){
        ((QLabel *)ts->layout->itemAt(12)->widget())->setText("Successfully finished");
        ((QLabel *)ts->layout->itemAt(7)->widget())->setEnabled(true);
        ts->label->setPixmap(pixmapCheck.scaled ( 30, 30, Qt::IgnoreAspectRatio));
        ts->graphsWindow->plot();
        ts->graphsWindow->show();
    }
    else{
        ((QLabel *)ts->layout->itemAt(12)->widget())->setText("Successfully finished");
        ((QLabel *)ts->layout->itemAt(7)->widget())->setEnabled(true);
        ts->label->setPixmap(pixmapCheck.scaled ( 30, 30, Qt::IgnoreAspectRatio));
    }
    ts->fs=0;


}

void MainWindow::about(){

    AboutDialog dialog(this);
    dialog.exec();

}

int MainWindow::runThreadSocketVs(){
    }

void MainWindow::setIconsVs(){


}

void MainWindow::cancelSimulationVs(){


}

void MainWindow::selectAll(){

}

