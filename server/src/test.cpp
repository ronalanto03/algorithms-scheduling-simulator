#include<simulator.h>
#include<stdlib.h>

int main(int argc,char* argv[])
{
   (void)argc;
   (void)argv;
   Simulator sim;
   sim.simulate(31010);
   return 0;
}
