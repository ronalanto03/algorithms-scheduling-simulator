/**
 * @file distributions.h
 * @brief Declaracion de las estructura Distribution
 * @author Ronald Sulbaran. ronalanto03@gmail.com.
 * @date 24-05-2013
 */

#ifndef DISTRIBUTIONS_H
#define DISTRIBUTIONS_H
#include<cmath>
#include <random>
#include <chrono>

/**
 * @struct DistributionData
 * @brief Distribuciones usadas para hacer las simulaciones.
 */

class Distribution
{
   private:


      std::default_random_engine generator;/**< Motor de números aleatorios que genera números pseudo-aleatorios*/

      double  lamda;/**< Parametro lamda de la distribucion exponencial*/

      std::uniform_real_distribution<double> * distribution_u;/**< Distribución de números aleatorios que produce valores de punto flotante de acuerdo con una distribución uniforme*/

      std::normal_distribution<double> * distribution_n;/**< Distribución de números aleatorios que produce valores de punto flotante de acuerdo con una distribución normal*/


   public:

      enum Type
      {
         constant = 0,
         uniform = 1,
         exponential = 2,
         normal = 3
      };

      enum Type t;

      /**
       * @brief Constructor parametrico
       * @param _t tipo de generador
       * @param _t a usado de diferentes formas dependiendo del tipo de distribucion
       * @param _t b usado de diferentes formas dependiendo del tipo de distribucion
       */
      Distribution(enum Type _t,double a, double b,double seed);


      /**
       * @brief Borra la memoria ocupada por el generador asociado a la distribucion
       */
      ~Distribution();


      /**
       * @return un numero aleatorio distribuido de acuerdo a la distribucion elegida
       */

      inline double getVal()
      {
         switch(t)
         {
            case constant:
               return lamda;

            case uniform:
               return (*distribution_u)(generator);

            case exponential:
               return -log((*distribution_u)(generator))*lamda;

            case normal:
               return (*distribution_n)(generator);
         }
         return 0.0;//This should not ever be reached
      }
};

#endif
