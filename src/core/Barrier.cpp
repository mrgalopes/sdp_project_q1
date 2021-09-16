#include "Barrier.h"

void Barrier::Wait(void){
    std::unique_lock<std::mutex> mLock{this->bMutex};
    if (++waiting == capacity){ // wake up all
        waiting = 0; // reset barrier
        this->bCv.notify_all();
    } else { // wait
        this->bCv.wait(mLock);
    }
}