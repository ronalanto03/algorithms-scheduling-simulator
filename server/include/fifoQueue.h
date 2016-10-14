/**
 * @file fifoQueue.h
 * @brief Declaración de la clase FifoQueue.
 * @author Ronald Sulbaran. ronalanto03@gmail.com.
 * @date 01-07-2013
 */

#ifndef FIFOQUEUE_H
#define FIFOQUEUE_H

#include <node.h>
#include<iqueue.h>

/**
  * @class FifoQueue
  * @brief Cola de tipo fifo.Representa la cola de listo en algunos de los algoritmos de planificacion de procesos.
  */
template <typename T>
class FifoQueue : public IQueue <T>
{
   private:

      Node<T> * rear_ptr;/**< ultimo nodo de la cola*/
      size_t num_nodes;/**< numero de elementos de la cola*/

   public:

      /**
       * @brief Inicializa a rear_ptr en NULL y el num_nodes en 0
       */

   FifoQueue() : rear_ptr(NULL), num_nodes(0)
      {
         /* empty */
      }

      /**
       * Inserta un nuevo elemento en la cola(al final)
       * @param _data el elemento a insertar
       */
      void put(T _data)
      {
         Node<T> * node = new Node<T> (_data);

         if (num_nodes > 0)
            rear_ptr->insert_next(node);
         num_nodes++;
         rear_ptr = node;
      }

      /**
       * @brief Obtiene el tope de la cola(sin eliminarlo)
       * @return un objeto de tipo T
       */
      T watch()
      {
         Node<T> * ret_val = rear_ptr->get_next();
         T _data=ret_val->getData();
         return _data;
      }

      /**
       * @brief Obtiene el tope de la cola eliminandolo de la misma
       * Un objeto de tipo T
       */
      T get()
      {
         Node<T> * ret_val = rear_ptr->remove_next();
         num_nodes--;
         T _data = ret_val->getData();
         delete ret_val;
         return _data;
      }


      /**
       * @brief Obtiene el numero de elementos de la cola.
       * @return num_nodes
       */
      size_t size() const
      {
         return num_nodes;
      }

      /**
       * @return true si la cola esta vacia, false de lo contrario
       */
      bool is_empty() const
      {
         return num_nodes == 0;
      }

      /**
       * Especialmente para el uso de los algoritmos de planificacion de procesos.
       * @brief Decrementa el los tiempos de espera de los procesos que estan en la cola
       */
      void decrementTime(double time, bool b = false)
      {
          (void)b;
         Node<T> * current=rear_ptr;
         current->getData().setWaitingTime(current->getData().getWaitingTime() + time );

         current = current->get_next();

         while(current != rear_ptr)
         {
            current->getData().setWaitingTime(current->getData().getWaitingTime() + time );
            current=current->get_next();
         }
      }




      /**
       * @brief Elimina los elementos de la cola
       */
      ~FifoQueue()
      {
         while (not this->is_empty())
            get();
      }

};



/* FIFOQUEUE_H */
# endif
