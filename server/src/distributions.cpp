/**
 * @file distributions.cpp
 * @brief Definicion de los metodos de la clase Distribution.
 * @author Cesar Vielma & Ronald Sulbaran.ronalanto03@hotmail.com
 * @date 01-07-2013
 */

#include<distributions.h>


Distribution::Distribution(enum Type _t,double a, double b, double seed):generator(seed),t(_t)
{
   switch(t)
   {
      case constant:
         lamda=a;
         break;

      case uniform:
         distribution_u=new std::uniform_real_distribution<double>(a,b);
         break;

      case exponential:
         distribution_u=new std::uniform_real_distribution<double>(0,1);
         lamda=a;
         break;

      case normal:
         distribution_n=new std::normal_distribution<double>(a,b);
         break;

   }

}

Distribution::~Distribution()
{
   switch(t)
   {

      case uniform:
         delete distribution_u;
         break;

      case exponential:
         delete distribution_u;;
         break;

      case normal:
         delete distribution_n;
         break;

      case constant:
         break;

   }

}
