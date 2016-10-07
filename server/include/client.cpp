#include"clientSock.h"
#include"eventData.h"
#include"DataSocket1.h"
int main(){

	ClientSock c;
	DataSocket1 data;
	EventData e;

    data.algorithm=4;

    data.quantum=5;

    data.n=1000;

    data.arrTimeD.t=3;
    data.arrTimeD.left=3;

    data.durationTimeD.t=2;
	 data.durationTimeD.left=500;
	 data.durationTimeD.right=1000;

    data.cpuBusrtTimeD.t=2;
    data.cpuBusrtTimeD.left=2;
    data.cpuBusrtTimeD.right=10;

    data.blockingTimeD.t=1;
    data.blockingTimeD.left=50;

	write(c.s, (char *)(&data), sizeof(struct DataSocket1));


	while(true){
	c.readSock();
	c.writeSock(e);
		
	}
	return 0;
}
