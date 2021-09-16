#ifndef BARRIER_H
#define BARRIER_H

#include <mutex>
#include <condition_variable>

class Barrier {
public:
    Barrier(){
        this->waiting = 0;
    }
    Barrier(unsigned int size){
        this->capacity = size;
        this->waiting = 0;
    }
    void Wait(void);
    void setCapacity(unsigned int size){
        this->capacity = size;
    }
private:
    std::mutex bMutex;
    std::condition_variable bCv;
    unsigned int waiting;
    unsigned int capacity;
};


#endif //BARRIER_H
