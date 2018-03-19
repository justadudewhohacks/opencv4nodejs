#include "CustomAllocator.h"



cv::UMatData* CustomMatAllocator::allocate(int dims, const int* sizes, int type,
                       void* data0, size_t* step, int flags, cv::UMatUsageFlags usageFlags) const
{
    cv::UMatData* u = stdAllocator->allocate(dims, sizes, type, data0, step, flags, usageFlags);
   
    if (NULL != u){
        u->prevAllocator = u->currAllocator = this;
        if( !(u->flags & cv::UMatData::USER_ALLOCATED) ){
            // make mem change atomic
            variables->MemTotalChangeMutex.lock();
            variables->TotalMem += u->size;
            variables->CountMemAllocs ++;
            variables->MemTotalChangeMutex.unlock();
            this->FixupJSMem();
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
__int64 CustomMatAllocator::readtotalmem(){
    __int64 Total;
    variables->MemTotalChangeMutex.lock();
    Total = variables->TotalMem;
    variables->MemTotalChangeMutex.unlock();
    return Total;
}

__int64 CustomMatAllocator::readmeminformed(){
    __int64 Total;
    variables->MemTotalChangeMutex.lock();
    Total = variables->TotalJSMem;
    variables->MemTotalChangeMutex.unlock();
    return Total;
}

__int64 CustomMatAllocator::readnumallocated(){
    __int64 Total;
    variables->MemTotalChangeMutex.lock();
    Total = variables->CountMemAllocs;
    variables->MemTotalChangeMutex.unlock();
    return Total;
}

__int64 CustomMatAllocator::readnumdeallocated(){
    __int64 Total;
    variables->MemTotalChangeMutex.lock();
    Total = variables->CountMemDeAllocs;
    variables->MemTotalChangeMutex.unlock();
    return Total;
}


void CustomMatAllocator::FixupJSMem() const {
    // we can only do this IF we are on the main thread.
    uv_thread_t me = uv_thread_self();
    
    if (uv_thread_equal(&(variables->main_thread), &me)){
        variables->MemTotalChangeMutex.lock();
        __int64 adjust = variables->TotalMem - variables->TotalJSMem;
        variables->TotalJSMem += adjust;
        variables->MemTotalChangeMutex.unlock();
        
        if (adjust){
            Nan::AdjustExternalMemory(adjust);
        }
    }
}

