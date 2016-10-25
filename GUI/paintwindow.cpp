/**
  * @file paintwindow.cpp
  * @brief Definicion de los metodos de la clase PaintWindow.
  * @author Cesar Vielma & Ronald Sulbaran. cesarlvielma@gmail.com,ronalanto03@gmail.com.
  * @date 13-08-2013
  */
#include "paintwindow.h"
#include "ui_paintwindow.h"
#include <iostream>
PaintWindow::PaintWindow(QWidget *parent,QString n ,DataSocket1 * ds):
    QMainWindow(parent),
    ui(new Ui::PaintWindow)
{
    ui->setupUi(this);
    setPos();

    simulationSettings= ds;

    iconName=n;

    ui->labelAlgorithm->setText(n+"\nAlgorithm");

    timer = new QTimer(this);
    timerP = new QTimer(this);

    timerFr = new QTimer(this);

    qDialogRQ = new QueueDialog(this);
    qDialogBQ = new QueueDialog(this);
    qDialogFQ = new QueueDialog(this);

    labelFinished = new MyLabel(this);

    labelPrAnimation[0] = new MyLabel(this);
    labelPrAnimation[1] = new MyLabel(this);
    labelPrAnimation[2] = new MyLabel(this);

    labelAlgorithmIcon = new MyLabel(this);

    processRQ[0]= new UiProcess(this);
    processRQ[1]= new UiProcess(this);
    processRQ[2]= new UiProcess(this);
    processRQ[3]= new UiProcess(this);

    processBQ[0]= new UiProcess(this);
    processBQ[1]= new UiProcess(this);
    processBQ[2]= new UiProcess(this);
    processBQ[3]= new UiProcess(this);

    processPRP1 = new UiProcess(this);

    for(int i =0 ;i< 7;i++){
        labelRQ[i] = new MyLabel(this);
        labelBQ[i] = new MyLabel(this);
    }



    labelG1 = new MyLabel(this);
    labelG2 = new MyLabel(this);
    labelPRP1 = new MyLabel(this);
    labelPlusRQ = new MyLabel(this);
    labelPlusBQ = new MyLabel(this);
    labelPlusPR = new MyLabel(this);
    labelPlusF = new MyLabel(this);
    labelBox = new MyLabel(this);
    labelFQ = new MyLabel(this);
    labelInput = new MyLabel(this);
    labelInput2 = new MyLabel(this);
    labelOutput = new MyLabel(this);
    labelOutput2 = new MyLabel(this);
    labelClock = new MyLabel(this);

    //SMProcess ShowMessageProcess
    QSignalMapper * SMProcess;
    SMProcess = new QSignalMapper(this);
    SMProcess->setMapping(labelRQ[0],processRQ[0]);
    SMProcess->setMapping(labelRQ[1],processRQ[1]);
    SMProcess->setMapping(labelRQ[5],processRQ[2]);
    SMProcess->setMapping(labelRQ[6],processRQ[3]);

    SMProcess->setMapping(labelBQ[0],processBQ[0]);
    SMProcess->setMapping(labelBQ[1],processBQ[1]);
    SMProcess->setMapping(labelBQ[5],processBQ[2]);
    SMProcess->setMapping(labelBQ[6],processBQ[3]);

    SMProcess->setMapping(labelPRP1,processPRP1);

    QMainWindow::connect(labelRQ[0], SIGNAL(leftButtonAction()),SMProcess, SLOT(map()));
    QMainWindow::connect(labelRQ[1], SIGNAL(leftButtonAction()),SMProcess, SLOT(map()));
    QMainWindow::connect(labelRQ[5], SIGNAL(leftButtonAction()),SMProcess, SLOT(map()));
    QMainWindow::connect(labelRQ[6], SIGNAL(leftButtonAction()),SMProcess, SLOT(map()));

    QMainWindow::connect(labelBQ[0], SIGNAL(leftButtonAction()),SMProcess, SLOT(map()));
    QMainWindow::connect(labelBQ[1], SIGNAL(leftButtonAction()),SMProcess, SLOT(map()));
    QMainWindow::connect(labelBQ[5], SIGNAL(leftButtonAction()),SMProcess, SLOT(map()));
    QMainWindow::connect(labelBQ[6], SIGNAL(leftButtonAction()),SMProcess, SLOT(map()));

    QMainWindow::connect(labelPRP1, SIGNAL(leftButtonAction()),SMProcess, SLOT(map()));

    QMainWindow::connect(SMProcess, SIGNAL(mapped(QObject*)),this, SLOT(processProperties(QObject*)));



    QMainWindow::connect(ui->pButtonAnimation, SIGNAL(released()),this, SLOT(nextEventSlot()));
    QMainWindow::connect(ui->pButtonFreeRun, SIGNAL(released()),this, SLOT(startFreeRun()));
    QMainWindow::connect(ui->pButtonStop, SIGNAL(released()),this, SLOT(stopFreeRun()));

    QMainWindow::connect(labelRQ[2], SIGNAL(leftButtonAction()),this, SLOT(showRQueueDialog()));
    QMainWindow::connect(labelRQ[3], SIGNAL(leftButtonAction()),this, SLOT(showRQueueDialog()));
    QMainWindow::connect(labelRQ[4], SIGNAL(leftButtonAction()),this, SLOT(showRQueueDialog()));

    QMainWindow::connect(labelBQ[2], SIGNAL(leftButtonAction()),this, SLOT(showBQueueDialog()));
    QMainWindow::connect(labelBQ[3], SIGNAL(leftButtonAction()),this, SLOT(showBQueueDialog()));
    QMainWindow::connect(labelBQ[4], SIGNAL(leftButtonAction()),this, SLOT(showBQueueDialog()));

    QMainWindow::connect(labelFQ, SIGNAL(leftButtonAction()),this, SLOT(showFQueueDialog()));


    QMainWindow::connect(timer, SIGNAL(timeout()),this, SLOT(rotateAnimation()));

    QMainWindow::connect(timerP, SIGNAL(timeout()),this, SLOT(processAnimation()));

    QMainWindow::connect(timerFr, SIGNAL(timeout()),this, SLOT(nextEventSlot()));

    anglePR1 =0;
    anglePR2 =90;

    settings();

}

PaintWindow::~PaintWindow()
{
    delete ui;
    delete labelPrAnimation[0];
    delete labelPrAnimation[1];
    delete labelPrAnimation[2];


    for(int i =0 ;i< 7;i++){
        delete labelRQ[i];
        delete labelBQ[i];
    }
}

void PaintWindow::closeEvent(QCloseEvent *event) {
    emit closed();
    close();
}

void PaintWindow::processProperties(QObject* obj){

    UiProcess * process = (UiProcess*)obj;
    ProcessPropertiesDialog p(this,process);
    p.exec();

}
void PaintWindow::processAnimation(){


    paintLabel(labelPrAnimation[(posStop-pos)%3],QString(":/images/images/processGray.png"),posMat[pos][0],posMat[pos][1],20,20,"");
    plusHide(labelPrAnimation[(posStop-pos)%3],0);
    pos++;
    if(pos==posStop){
        timerP->stop();
        plusHide(labelPlus,1);
    }
}


void PaintWindow::rotateAnimation(){

    anglePR1+=45;
    rotate(labelG1,anglePR1);
    anglePR2-=45;
    rotate(labelG2,anglePR2);
}


void PaintWindow::rotate(MyLabel *label, int angle){

    QPixmap* pixmap = new QPixmap(":/images/images/gear2.png");
    QPixmap* rotatedPixmap= new QPixmap(label->pixmap()->size());
    rotatedPixmap->fill(QColor::fromRgb(0, 0, 0, 0)); //the new pixmap must be transparent.
    QPainter* p = new QPainter(rotatedPixmap);
    QSize size = label->pixmap()->size();
    p->translate(size.height()/2,size.height()/2);

    p->rotate(angle);
    p->translate(-size.height()/2,-size.height()/2);
    p->drawPixmap(0, 0,(*pixmap));
    p->end();
    label->setPixmap(*rotatedPixmap);
    delete p;
    delete pixmap;
    delete rotatedPixmap;
}


void PaintWindow::plusHide(MyLabel * label,int val){

    QGraphicsOpacityEffect * opacityEffect = new QGraphicsOpacityEffect(this);
    opacityEffect->setOpacity(0);
    label->setGraphicsEffect(opacityEffect);
    label->setVisible(true);
    QPropertyAnimation* anim= new QPropertyAnimation(this);
    anim->setTargetObject(opacityEffect);
    anim->setPropertyName("opacity");
    anim->setDuration(800);

    anim->setKeyValueAt(0.0,0.0);
    anim->setKeyValueAt(0.10,0.2);
    anim->setKeyValueAt(0.20,0.5);
    anim->setKeyValueAt(0.30,0.7);
    anim->setKeyValueAt(0.40,0.9);
    anim->setKeyValueAt(0.50,1);
    anim->setKeyValueAt(0.60,1);
    anim->setKeyValueAt(0.70,1);
    anim->setKeyValueAt(0.80,1);
    anim->setKeyValueAt(0.90,1);
    anim->setKeyValueAt(1,val);

    anim->setEasingCurve(QEasingCurve::OutQuad);
    anim->start(QAbstractAnimation::DeleteWhenStopped);


}

void PaintWindow::showRQueueDialog(){

    qDialogRQ->updateData();
    qDialogRQ->exec();
}

void PaintWindow::showBQueueDialog(){

    qDialogBQ->updateData();
    qDialogBQ->exec();
}

void PaintWindow::showFQueueDialog(){

    qDialogFQ->updateData();
    qDialogFQ->exec();
}

void PaintWindow::paintLabel(QLabel * label , QString path,int x,int y,int w,int h,QString text){

    QPixmap p(path);
    label->setScaledContents(true);
    label->setPixmap(p);
    label->setGeometry(x,y,w,h);
    label->setToolTip(text);
    label->show();
}

void PaintWindow::setPos(){

    posMat[0][0]=80;
    posMat[0][1]=130;
    posMat[1][0]=107;
    posMat[1][1]=98;
    posMat[2][0]=140;
    posMat[2][1]=80;
    posMat[3][0]=395;
    posMat[3][1]=70;
    posMat[4][0]=425;
    posMat[4][1]=80;
    posMat[5][0]=450;
    posMat[5][1]=100;
    posMat[6][0]=490;
    posMat[6][1]=210;
    posMat[7][0]=470;
    posMat[7][1]=240;
    posMat[8][0]=440;
    posMat[8][1]=260;
    posMat[9][0]=190;
    posMat[9][1]=230;
    posMat[10][0]=170;
    posMat[10][1]=160;
    posMat[11][0]=170;
    posMat[11][1]=100;


    posMat[12][0]=500;
    posMat[12][1]=220;
    posMat[13][0]=520;
    posMat[13][1]=240;
    posMat[14][0]=500;
    posMat[14][1]=260;

    posMat[15][0]=450;
    posMat[15][1]=125;
    posMat[16][0]=270;
    posMat[16][1]=150;
    posMat[17][0]=170;
    posMat[17][1]=90;
}

void PaintWindow::setEvent(EventData eData){

    UiProcess *p;

    if(ui->labelTime->text()!="" && (eData.time-ui->labelTime->text().toDouble())!=0){
        if(!qDialogBQ->isEmpty()){
            qDialogBQ->updateBlockedTime(eData.time-ui->labelTime->text().toDouble());
            qDialogBQ->updateWaitingTime(eData.time-ui->labelTime->text().toDouble());
            updateQueue(qDialogBQ,processBQ,labelBQ);
        }
        if(!qDialogRQ->isEmpty()){
            qDialogRQ->updateWaitingTime(eData.time-ui->labelTime->text().toDouble());
            updateQueue(qDialogRQ,processRQ,labelRQ);
        }
    }


    labelClock->setToolTip("Event Time: "+QString::number(eData.time));
    ui->labelTime->setText(QString::number(eData.time));

    if(labelBef)
    labelBef->setVisible(false);


    switch(eData.event){
    case 0:
        //llega proceso
        pos=0;
        posStop =3;
        labelPlus=labelPlusRQ;
        p = new UiProcess(this);
        p->seteData(eData);
        pushGraphicQueue(qDialogRQ,processRQ,labelRQ,p,0);


    break;
    case 1:
        //cpu a listo
        if(simulationSettings->algorithm==4 || simulationSettings->algorithm==3){
            pos=15;
            posStop =18;
            labelPlus=labelPlusRQ;
            p = new UiProcess(this);
            p->seteData(eData);
            pushGraphicQueue(qDialogRQ,processRQ,labelRQ,p,0);
            processPRP1->setDefault();
            putGraphicPr(processPRP1,0);


        }
        //llega proceso para todos menos RR
        else{
            pos=0;
            posStop =3;
            labelPlus=labelPlusRQ;
            p = new UiProcess(this);
            p->seteData(eData);
            pushGraphicQueue(qDialogRQ,processRQ,labelRQ,p,0);


        }
    break;

    case 2:
        //finaliza proceso
        pos=12;
        posStop =15;
        labelPlus=labelPlusF;
        p = new UiProcess(this);
        p->seteData(eData);
        processPRP1->setDefault();
        p->setEndingTime(eData.time);
        putGraphicPr(processPRP1,0);
        qDialogFQ->insertProcess(p);

    break;

    case 3:
        //cpu a bloquedo
        pos=6;
        posStop =9;
        labelPlus=labelPlusBQ;
        p = new UiProcess(this);
        p->seteData(eData);

        pushGraphicQueue(qDialogBQ,processBQ,labelBQ,p,1);
        processPRP1->setDefault();
        putGraphicPr(processPRP1,0);
    break;

    case 4:
        //de bloqueado a listo
        pos=9;
        posStop =11;
        labelPlus=labelPlusRQ;
        p=popGraphicQueue(qDialogBQ,processBQ,labelBQ);
        p->seteData(eData);
        pushGraphicQueue(qDialogRQ,processRQ,labelRQ,p,0);

    break;

    case 5:
        //de listo a cpu
        pos=3;
        posStop =6;
        labelPlus=labelPlusPR;
        p =popGraphicQueue(qDialogRQ,processRQ,labelRQ);
        p->seteData(eData);
        putGraphicPr(p,1);

    break;

    }

    labelBef=labelPlus;
    timerP->start(150);
    processAnimation();

}

void PaintWindow::nextEventSlot(){
    emit nextEventSignal();
}

void PaintWindow::pushGraphicQueue(QueueDialog * qDialogQ,UiProcess **process,MyLabel **label ,UiProcess * p,int type){
  //1:FCFS.2:SJF.3:PSJF.4:RR*

    if(type == 1)
    qDialogQ->insertProcessPriority(p,0);
    if(type == 0){
        if(simulationSettings->algorithm==1||simulationSettings->algorithm==4 )
            qDialogQ->insertProcess(p);
        else
            qDialogQ->insertProcessPriority(p,1);
    }

    updateQueue(qDialogQ,process,label);

    if(qDialogQ->queue.size()>0){
        label[2]->setToolTip(QString::number(qDialogQ->queue.size())+" Process in the Queue");
        label[3]->setToolTip(QString::number(qDialogQ->queue.size())+" Process in the Queue");
        label[4]->setToolTip(QString::number(qDialogQ->queue.size())+" Process in the Queue");
    }
}

UiProcess* PaintWindow::popGraphicQueue(QueueDialog * qDialogQ,UiProcess **process,MyLabel** label){


    switch(qDialogQ->queue.size()){

    case 1:
    process[0]->setDefault();
    label[0]->setPixmap(QString(":/images/images/processGray.png"));
    setLabelToolTip(label[0],process[0]);

    break;

    case 2:
        process[0]->setProcess(process[1]);
        process[1]->setDefault();
       label[1]->setPixmap(QString(":/images/images/processGray.png"));
       setLabelToolTip(label[0],process[0]);
       setLabelToolTip(label[1],process[1]);
    break;

    case 3:
        process[0]->setProcess(process[1]);
        process[1]->setProcess(process[2]);
        process[2]->setDefault();
        label[5]->setPixmap(QString(":/images/images/processGray.png"));
        label[4]->setPixmap(QString(":/images/images/processGray.png"));
        label[3]->setPixmap(QString(":/images/images/processGray.png"));
        label[2]->setPixmap(QString(":/images/images/processGray.png"));
        setLabelToolTip(label[0],process[0]);
        setLabelToolTip(label[1],process[1]);
        setLabelToolTip(label[5],process[2]);

    break;

    case 4:
        process[0]->setProcess(process[1]);
        process[1]->setProcess(process[2]);
        process[2]->setProcess(process[3]);
        process[3]->setDefault();
        label[6]->setPixmap(QString(":/images/images/processGray.png"));
        setLabelToolTip(label[0],process[0]);
        setLabelToolTip(label[1],process[1]);
        setLabelToolTip(label[5],process[2]);
        setLabelToolTip(label[6],process[3]);

    break;

    default:
        process[0]->setProcess(process[1]);
        process[1]->setProcess(qDialogQ->queue.value(3));
        setLabelToolTip(label[0],process[0]);
        setLabelToolTip(label[1],process[1]);
    break;

    }
    if(!qDialogQ->queue.isEmpty())
        return qDialogQ->removeProcess();
    if(qDialogQ->queue.size()==0){
        label[2]->setToolTip("Empty Queue");
        label[3]->setToolTip("Empty Queue");
        label[4]->setToolTip("Empty Queue");
    }


}

void PaintWindow::setLabelToolTip(MyLabel * label,UiProcess * p){

    if(p->getPid()!=-1)
        label->setToolTip("-pid:"+QString::number(p->getPid())+\
                  "\n-arrivedTime:"+QString::number(p->getArrTime())+\
                  "\n-cpuBurstTime:"+QString::number(p->getCpuBurstTime())+\
                  "\n-remainingTime:"+QString::number(p->getRemainingTime())+\
                  "\n-blockingTime:"+QString::number(p->getBlockingTime())+\
                  "\n-waitingTime:"+QString::number(p->getWaitingTime())+\
                  "\n-usedTime:"+QString::number(p->getUsedTime())+\
                  "\n-CpuEntries:"+QString::number(p->getnT())+\
                  "\n-I/O Entries:"+QString::number(p->getnB())+\
                  "\n-TotalBlockingTime:"+QString::number(p->getallBlockingTime())+\
                  "\n-durationTime:"+QString::number(p->getDurationTime()));
    else
        label->setToolTip("Null Process");
}

void PaintWindow::putGraphicPr(UiProcess *p,int c){

    processPRP1->setProcess(p);
    setLabelToolTip(labelPRP1,processPRP1);
    if(c){
        labelPRP1->setPixmap(QString(":/images/images/processOrange.png"));
         timer->start(150);
         labelG1->setToolTip("Running Processor");
         labelG2->setToolTip("Running Processor");
    }
    else{
        labelPRP1->setPixmap(QString(":/images/images/processGray.png"));
        timer->stop();
        labelG1->setToolTip("Stoped Processor");
        labelG1->setToolTip("Stoped Processor");
    }
}


void PaintWindow::settings(){

    qDialogRQ->setPathColor(QString(":/images/images/processGreen.png"));
    qDialogBQ->setPathColor(QString(":/images/images/processBlue.png"));
    for(int i =0 ;i< 7;i++){
        labelRQ[i]->setToolTip("Null Process");
        labelBQ[i]->setToolTip("Null Process");
    }

    paintLabel(labelFinished,QString(":/images/images/finished.png"),185,140,220,60,"Finished Simulation");
    labelFinished->setVisible(false);

    paintLabel(labelRQ[0],QString(":/images/images/processGray.png"),350,60,41,41,"Null Process");
    paintLabel(labelRQ[1],QString(":/images/images/processGray.png"),310,60,41,41,"Null Process");
    paintLabel(labelRQ[2],QString(":/images/images/processGray.png"),290,70,20,20,"Empty Queue");
    paintLabel(labelRQ[3],QString(":/images/images/processGray.png"),270,70,20,20,"Empty Queue");
    paintLabel(labelRQ[4],QString(":/images/images/processGray.png"),250,70,20,20,"Empty Queue");
    paintLabel(labelRQ[5],QString(":/images/images/processGray.png"),210,60,41,41,"Null Process");
    paintLabel(labelRQ[6],QString(":/images/images/processGray.png"),170,60,41,41,"Null Process");

    paintLabel(labelBQ[0],QString(":/images/images/processGray.png"),200,250,41,41,"Null Process");
    paintLabel(labelBQ[1],QString(":/images/images/processGray.png"),240,250,41,41,"Null Process");
    paintLabel(labelBQ[2],QString(":/images/images/processGray.png"),280,260,20,20,"Empty Queue");
    paintLabel(labelBQ[3],QString(":/images/images/processGray.png"),300,260,20,20,"Empty Queue");
    paintLabel(labelBQ[4],QString(":/images/images/processGray.png"),320,260,20,20,"Empty Queue");
    paintLabel(labelBQ[5],QString(":/images/images/processGray.png"),340,250,41,41,"Null Process");
    paintLabel(labelBQ[6],QString(":/images/images/processGray.png"),380,250,41,41,"Null Process");

    paintLabel(labelG1,QString(":/images/images/gear.png"),470,100,70,70,"Stopped Processor");
    paintLabel(labelG2,QString(":/images/images/gear.png"),500,150,70,70,"Stopped Processor");
    paintLabel(labelPRP1,QString(":/images/images/processGray.png"),480,150,51,51,"Emptyrocessor");
    labelPRP1->setToolTip("Empty Processor");
    paintLabel(labelPlusRQ,QString(":/images/images/plusGreen.png"),150,40,41,41,"");
    labelPlusRQ->setVisible(false);
    paintLabel(labelPlusBQ,QString(":/images/images/plusBlue.png"),400,230,41,41,"");
    labelPlusBQ->setVisible(false);
    paintLabel(labelPlusPR,QString(":/images/images/plusOrange.png"),470,70,41,41,"");
    labelPlusPR->setVisible(false);

    paintLabel(labelFQ,QString(":/images/images/exitBox.png"),480,300,81,81,"Exit");
    paintLabel(labelBox,QString(":/images/images/box.png"),40,150,81,81,"Magic Box");

    paintLabel(labelInput,QString(":/images/images/input.png"),20,170,31,31,"");
    paintLabel(labelInput2,QString(":/images/images/input.png"),5,170,31,31,"");
    paintLabel(labelOutput,QString(":/images/images/input.png"),555,320,31,31,"");
    paintLabel(labelOutput2,QString(":/images/images/input.png"),570,320,31,31,"");
    paintLabel(labelClock,QString(":/images/images/clock.png"),480,10,40,40,"Event Time: 0");

    paintLabel(labelPlusF,QString(":/images/images/check.png"),475,280,41,41,"");
    labelPlusF->setVisible(false);
    labelBef=0;
    paintLabel(labelAlgorithmIcon,QString(":/images/images/"+iconName+".png"),35,285,70,60,iconName+" Algorithm\n"+\
                "N.Processes: "+QString::number(simulationSettings->n)+\
                "\nDist.Arrival Time: "+selectDist(simulationSettings->arrTimeD)+\
                "\nDist.Duration Time: "+selectDist(simulationSettings->durationTimeD)+\
                "\nDist.CPU Burst Time: "+selectDist(simulationSettings->cpuBusrtTimeD)+\
                "\nDist.Blocking Time: "+selectDist(simulationSettings->blockingTimeD));

    ui->labelTime->setText("");
    qDialogRQ->cleanQueue();
    qDialogBQ->cleanQueue();
    qDialogFQ->cleanQueue();

    timer->stop();


    ui->pButtonAnimation->setEnabled(true);
    ui->pButtonFreeRun->setEnabled(true);
    ui->pButtonStop->setEnabled(false);
}

QString PaintWindow::selectDist(DistributionData dd){
    QString str;

    switch(dd.t){
        case 1:
        str+= "Constant ";
        str+="[";
        str+=QString::number(dd.left);
        str+="]";
        break;
        case 2:
        str+= "Uniform ";
        str+="[";
        str+=QString::number(dd.left);
        str+=",";
        str+=QString::number(dd.right);
        str+="]";
        break;
        case 3:
        str+= "Exponential ";
        str+="[";
        str+=QString::number(dd.left);
        str+=",";
        str+=QString::number(dd.right);
        str+="]";
        break;
        case 4:
        str+= "Normal ";
        str+="[";
        str+=QString::number(dd.left);
        str+=",";
        str+=QString::number(dd.right);
        str+="]";
        break;
    }

    return str;

}

void PaintWindow::updateQueue(QueueDialog * qDialogQ,UiProcess **process,MyLabel **label){

    switch(qDialogQ->queue.size()){

    case 1:

        process[0]->setProcess(qDialogQ->queue.value(0));
        label[0]->setPixmap(qDialogQ->getPathColor());
        setLabelToolTip(label[0],qDialogQ->queue.value(0));
    break;

    case 2:
        process[0]->setProcess(qDialogQ->queue.value(0));
        label[0]->setPixmap(qDialogQ->getPathColor());
        setLabelToolTip(label[0],qDialogQ->queue.value(0));

        process[1]->setProcess(qDialogQ->queue.value(1));
        label[1]->setPixmap(qDialogQ->getPathColor());
        setLabelToolTip(label[1],qDialogQ->queue.value(1));
    break;

    case 3:
        process[0]->setProcess(qDialogQ->queue.value(0));
        label[0]->setPixmap(qDialogQ->getPathColor());
        setLabelToolTip(label[0],qDialogQ->queue.value(0));

        process[1]->setProcess(qDialogQ->queue.value(1));
        label[1]->setPixmap(qDialogQ->getPathColor());
        setLabelToolTip(label[1],qDialogQ->queue.value(1));

        process[2]->setProcess(qDialogQ->queue.value(2));
        label[2]->setPixmap(qDialogQ->getPathColor());
        label[3]->setPixmap(qDialogQ->getPathColor());
        label[4]->setPixmap(qDialogQ->getPathColor());
        label[5]->setPixmap(qDialogQ->getPathColor());
        setLabelToolTip(label[5],qDialogQ->queue.value(2));
    break;

    case 4:
        process[0]->setProcess(qDialogQ->queue.value(0));
        label[0]->setPixmap(qDialogQ->getPathColor());
        setLabelToolTip(label[0],qDialogQ->queue.value(0));

        process[1]->setProcess(qDialogQ->queue.value(1));
        label[1]->setPixmap(qDialogQ->getPathColor());
        setLabelToolTip(label[1],qDialogQ->queue.value(1));

        process[2]->setProcess(qDialogQ->queue.value(2));
        label[2]->setPixmap(qDialogQ->getPathColor());
        label[3]->setPixmap(qDialogQ->getPathColor());
        label[4]->setPixmap(qDialogQ->getPathColor());
        label[5]->setPixmap(qDialogQ->getPathColor());
        setLabelToolTip(label[5],qDialogQ->queue.value(2));

        process[3]->setProcess(qDialogQ->queue.value(3));
        label[6]->setPixmap(qDialogQ->getPathColor());
        setLabelToolTip(label[6],qDialogQ->queue.value(3));
    break;

    default:
        process[0]->setProcess(qDialogQ->queue.value(0));
        label[0]->setPixmap(qDialogQ->getPathColor());
        setLabelToolTip(label[0],qDialogQ->queue.value(0));

        process[1]->setProcess(qDialogQ->queue.value(1));
        label[1]->setPixmap(qDialogQ->getPathColor());
        setLabelToolTip(label[1],qDialogQ->queue.value(1));

        process[2]->setProcess(qDialogQ->queue.value(qDialogQ->queue.size()-2));
        setLabelToolTip(label[5],qDialogQ->queue.value(qDialogQ->queue.size()-2));
        process[3]->setProcess(qDialogQ->queue.value(qDialogQ->queue.size()-1));
        setLabelToolTip(label[6],qDialogQ->queue.value(qDialogQ->queue.size()-1));
    break;
    }
}

void PaintWindow::setFinished(){

    plusHide(labelFinished,1);
    ui->pButtonAnimation->setEnabled(false);
    ui->pButtonFreeRun->setEnabled(false);
    ui->pButtonStop->setEnabled(false);
    timerFr->stop();

}

void PaintWindow::startFreeRun(){

    ui->pButtonAnimation->setEnabled(false);
    ui->pButtonFreeRun->setEnabled(false);
    ui->pButtonStop->setEnabled(true);
    timerFr->start(100);

}


void PaintWindow::stopFreeRun(){

    ui->pButtonAnimation->setEnabled(true);
    ui->pButtonFreeRun->setEnabled(true);
    ui->pButtonStop->setEnabled(false);
    timerFr->stop();

}
