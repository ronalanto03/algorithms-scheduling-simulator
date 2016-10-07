#include<iostream>
#include<processGenerator.h>
#include<distributions.h>

int main(){
	Distribution * dArrTime=new Distribution(Distribution::uniform ,5,20);
	Distribution * dDurationTime=new Distribution(Distribution::constant,1,0);

	ProcessGenerator p(200);
	p.generateTimes(dArrTime,dDurationTime);
//	p.print();

	return 0;
}
