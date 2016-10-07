#ifndef FINALREPORT_H
#define FINALREPORT_H
struct FinalReport{

    double averageUsedTime;

    double averageWaitingTime;

    double sdUsedTime;

    double sdWaitingTime;

    double maxUsedTime;

    double minUsedTime;

    double maxWaitingTime;

    double minWaitingTime;

    FinalReport(){
        averageUsedTime=0;
        averageWaitingTime=0;
        sdUsedTime=0;
        sdWaitingTime=0;
    }


};

#endif // FINALREPORT_H
