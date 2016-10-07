#include "basealgorithm.h"

BaseAlgorithm::BaseAlgorithm()
{

}

BaseAlgorithm::BaseAlgorithm(IQueue & _priorityBlockQueue, IQueue & _readyQueue, int _numOfProcesses,\
                             BaseProcess & _baseProcess,EventData _eventData, int _nSocket, bool _connected):
    priorityBlockQueue(NULL),
    readyQueue(NULL),
    numOfProcesses(_baseProcess),
    baseProcess(_baseProcess),\
    eventData(_eventData),
    nSocket(_nSocket);
{
}
