
#include "LoggingPulseCounterBase.hpp"

/**
 *  Class instance initialization function.
 *
 *  @param[in]   config    link to configuration of counter and it's storage
 *
 *  @return   none
 */
void LoggingPulseCounterBase::Initialize(const LoggingPulseCounterConfiguration &config)
{

    mPulseWeight = config.pulseWeight;
    mStoragePageSize = config.storagePageSize;
    mStorageBuffer =  config.storageBuffer;
    mTotalValue = config.initialValue;
    StorageInitialize();

}

/**
 *  Initialize main storage structure
 *
 *  @return   none
 */
void LoggingPulseCounterBase::StorageInitialize()
{
    mStorage = static_cast<struct mStorage *>(mStorageBuffer);
    mStorage->header.value = 0;
    mStorage->header.count = 0;
    mStorage->header.unitSize = mStoragePageSize;
    mStorage->header.total = mTotalValue;
    mStorage->header.free = (mStoragePageSize - sizeof(mStorage->header))/sizeof(uint32_t);
    mStorage->header.pulseWeight = mPulseWeight;

}

/**
 *  Return current integrated value of counter.
 *
 *  @return   value in counted items
 */
double LoggingPulseCounterBase::GetCurrentValue()
{
    return mTotalValue;
}

/**
 *  Update storage structure during pulse registration process
 *
 *  @return   none
 */
void LoggingPulseCounterBase::UpdateStorage()
{
    mStorage->timeLog[mStorage->header.count++] = GetTimeStamp();
    mStorage->header.free--;
    mStorage->header.value += mStorage->header.pulseWeight;
    mStorage->header.total += mStorage->header.pulseWeight;
    mTotalValue = mStorage->header.total;
}

/**
 *  Function just registers current pulse in to working log
 *
 *  @return   none
 */
void LoggingPulseCounterBase::PulseCapture()
{
    UpdateStorage();

    if(mStorage->header.free == 0)
    {
        FlushLogToStorage();
        StorageInitialize();
    }
}