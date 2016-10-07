/**
 * @file iqueue.h
 * @brief  Interface for Queue
 * @author Ronald Sulbaran and Julio Jaimes R. ronalanto03@gmail.com , carlosjuliojr@hotmail.com.
 * @date 06-10-2016
 */

#ifndef IQUEUE_H
#define IQUEUE_H
#include<iostream>

/**
  * @class IQueue
  * @brief Interface for Queue
  * @details This interface will be use for the Queues fifo and priority respectly.
  */
template <typename T>
class IQueue
{
public:
    IQueue();

    /**
     * Insert a new element in the Queue.
     * @param _data the element to be inserted.
     */
    virtual void put(T _data) = 0;

    /**
     * @brief Gets the top of the Queue.
     * @return An object of Type T.
     */
    virtual T watch() = 0;

    /**
     * @brief Gets the top of the Queue and deleted.
     * @return An object of type T
     */
    virtual T get() = 0;

    /**
     * @brief Gets the element number of the Queue.
     * @return The number of nodes.
     */
   virtual size_t size() const = 0;

    /**
     * @retval true  if the Queue is empty, false otherwise.
     */
   virtual bool is_empty() const = 0;

    /**
     * It is used by the sheduling algorithms.
     * @brief Decrements the waiting time of the processes in the Queue.
     */
    virtual void decrementTime(double time) = 0;

};

#endif // IQUEUE_H
