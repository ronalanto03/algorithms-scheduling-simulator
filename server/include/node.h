/**
 * @file node.h
 * @brief Declaración de la clase Node.
 * @author Ronald Sulbaran. ronalanto03@gmail.com.
 * @date 13-08-2013
 */

#ifndef NODE_H
#define NODE_H


template<typename T>
class Node
{
   private:
      Node<T> * next;/**< Proximo nodo*/
      T data;/**< Dato guardado en el nodo*/

   public:

      /**
         * @brief Constructor parametrico.
         * @param _data, dato a almacenaren el nodo.
         */
      Node(const T & _data) : next(this),data(_data)
      {
         /* Empty */
      }

      /**
       * @return true si el nodo esta vacio, false de lo contrario.
       */
      bool is_empty() const
      {
         return next == this;
      }

      /**
       * @return Una referencia al dato almacenado en el nodo
       */
      T & getData()
      {
         return data;
      }


      /**
       * @return una referencia al puntero del siguiente nodo.
       */
      Node<T> * & get_next()
      {
         return next;
      }


      /**
       * @brief Inserta el nodo siguiente a this.
       */
      void insert_next(Node * p)
      {
         p->next = next;
         next = p;
      }

      /**
       * @brief Elimina el nodo siguiente a this.
       */
      Node<T> * remove_next()
      {
         Node<T> * ret_val = next;
         next = ret_val->next;
         return ret_val;
      }

};
/* Node_H */
# endif
