#include "CustomMatAllocator.h"
//#include <iostream>

#ifdef OPENCV4NODEJS_ENABLE_EXTERNALMEMTRACKING

cv::UMatData* CustomMatAllocator::allocate(int dims, const int* sizes, int type,
                       void* data0, size_t* step, int flags, cv::UMatUsageFlags usageFlags) const
{
    cv::UMatData* u = stdAllocator->allocate(dims, sizes, type, data0, step, flags, usageFlags);

    if (NULL != u){
        u->prevAllocator = u->currAllocator = this;
        if( !(u->flags & cv::UMatData::USER_ALLOCATED) ){
            // make mem change atomic
            try {
                variables->MemTotalChangeMutex.lock();
                variables->TotalMem += u->size;
                variables->CountMemAllocs ++;
                variables->MemTotalChangeMutex.unlock();
                this->FixupJSMem();
            } catch (...){
                printf("CustomMatAllocator::allocate - exception adjusting memory\n");
            }
        }
    }
    return u;
}

bool CustomMatAllocator::allocate(cv::UMatData* u, int accessFlags, cv::UMatUsageFlags usageFlags) const
{
    // this does not seem to change memory allocation?
    return stdAllocator->allocate(u, accessFlags, usageFlags);
}


void CustomMatAllocator::deallocate(cv::UMatData* u) const
{
    if (NULL != u){
        if( !(u->flags & cv::UMatData::USER_ALLOCATED) ){
            // make mem change atomic
            variables->MemTotalChangeMutex.lock();
            variables->TotalMem -= u->size;
            variables->CountMemDeAllocs ++;
            variables->MemTotalChangeMutex.unlock();
        }
    }
    stdAllocator->deallocate(u);
    this->FixupJSMem();
}


// method to read the total mem, but mutex protected.
int64_t CustomMatAllocator::readtotalmem(){
    int64_t Total;
    variables->MemTotalChangeMutex.lock();
    Total = variables->TotalMem;
    variables->MemTotalChangeMutex.unlock();
    return Total;
}

int64_t CustomMatAllocator::readmeminformed(){
    int64_t Total;
    variables->MemTotalChangeMutex.lock();
    Total = variables->TotalJSMem;
    variables->MemTotalChangeMutex.unlock();
    return Total;
}

int64_t CustomMatAllocator::readnumallocated(){
    int64_t Total;
    variables->MemTotalChangeMutex.lock();
    Total = variables->CountMemAllocs;
    variables->MemTotalChangeMutex.unlock();
    return Total;
}

int64_t CustomMatAllocator::readnumdeallocated(){
    int64_t Total;
    variables->MemTotalChangeMutex.lock();
    Total = variables->CountMemDeAllocs;
    variables->MemTotalChangeMutex.unlock();
    return Total;
}


void CustomMatAllocator::FixupJSMem() const {
    // we can only do this IF we are on the main thread.
    std::thread::id this_id = std::this_thread::get_id();

    if (variables->main_thread_id == this_id){
        //std::cout << "thead is main " << this_id << "\n";
        variables->MemTotalChangeMutex.lock();
        int64_t adjust = variables->TotalMem - variables->TotalJSMem;
        variables->TotalJSMem += adjust;
        variables->MemTotalChangeMutex.unlock();

        if (adjust){
            //printf("will call Nan ajust by %d\n", (int)adjust);
            Nan::AdjustExternalMemory(adjust);
            //printf("done ajust by %d\n", (int)adjust);
        }
    } else {
        //std::cout << "thead not main " << this_id << "\n";
    }
}

// end only valid for 3.1.0+
#endif

