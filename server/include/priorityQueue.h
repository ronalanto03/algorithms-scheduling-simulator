/**
 * @file priorityQueue.h
 * @brief Declaración de la clase PriorityQueue.
 * @author Ronald Sulbaran. ronalanto03@gmail.com.
 * @date 26-05-2013
 */

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include"node.h"
#include<iostream>


/**
 * @class PriorityQueue
 * @brief Cola de prioridad
 */
template <typename T,typename CompareLess,typename CompareGreaterOrEqual>
class PriorityQueue
{
   private:

      Node<T> * rear_ptr;/**< Ultimo nodo de la cola*/

      size_t num_nodes;/**< numero de nodos que hay en la cola*/

   public:

      /**
       * Constructor por defecto
       */
      PriorityQueue( ) : rear_ptr(NULL), num_nodes(0)
      {
         /* empty */
      }

      /**
       * Crea un nuevo nodo con el valor que se le pase, y lo inserta en la cola.
       * @param _data valor a almacenar en el nodo
       */
      void put(T _data)
      {
         Node<T> * node = new Node<T> (_data);

         if (num_nodes > 0)
         {
            //si se debe insertar al inicio
            if(CompareLess()(_data,rear_ptr->get_next()->getData()))
            {
               node->get_next()=rear_ptr->get_next();
               rear_ptr->get_next()=node;
            }
            //si se debe insertar al final
            else if(CompareGreaterOrEqual()(_data,rear_ptr->getData()))
            {
               rear_ptr->insert_next(node);
               rear_ptr = node;
            }

            //si se debe insertar en el medio
            else
            {
               Node<T> * last=rear_ptr->get_next();
               Node<T> * current=last->get_next();

               while(current!=rear_ptr->get_next())
               {
                  if(CompareGreaterOrEqual()(_data,last->getData()) and \
                        CompareLess()(_data,current->getData() ) )
                  {
                     node->get_next()=current;
                     last->get_next()=node;
                     break;
                  }

                  last = current;
                  current = current->get_next();
               }
            }
         }

         else
            rear_ptr = node;

         num_nodes++;//aumenta el numero de nodos
      }

      /**
       * @return El valor del nodo que esta por salir
       */
      T watch()
      {
         Node<T> * ret_val = rear_ptr->get_next();
         T _data=ret_val->getData();
         return _data;
      }

      /**
       * Borra el nodo que tiene que salir(el tope).
       * @return El valor del nodo que esta por salir
       */
      T get()
      {
         Node<T> * ret_val = rear_ptr->remove_next();
         num_nodes--;
         T _data=ret_val->getData();
         delete ret_val;
         return _data;
      }

      /**
       * @return El numero de nodos que tiene la cola
       */
      size_t size() const
      {
         return num_nodes;
      }

      /**
       * @return true si la cola esta vacia, 0 de lo contrario
       */

      bool is_empty() const
      {
         return num_nodes == 0;
      }

      /**
       * Decrementa los tiempos de bloqueado y tiempos de espera de todos los procesos.
       * @param time tiempo en el que se decrementara.
       * @param b si es false solo se aumentara el tiempo de espera,
       * si es true se aumentara el tiempo de espera y decrementara el tiempo de bloqueo
       */

      void decrementTime(double time, bool b)
      {
         Node<T> * current=rear_ptr;
         if(b)
            current->getData().setBlockingTime(current->getData().getBlockingTime() - time );

         current->getData().setWaitingTime(current->getData().getWaitingTime() + time );

         current=current->get_next();

         while(current!=rear_ptr)
         {
            if(b)
               current->getData().setBlockingTime(current->getData().getBlockingTime() - time );

            current->getData().setWaitingTime(current->getData().getWaitingTime() + time );
            current=current->get_next();

         }

      }

      /**
       * Elimina todos los nodos de la cola
       */
      ~PriorityQueue()
      {
         while (not this->is_empty())
            get();
      }

};

/* PRIORITYQUEUE_H */
# endif
