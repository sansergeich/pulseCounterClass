
#include "LoggingPulseCounterBase.hpp"

/**
 *  Class instance initialization function.
 *
 *  @param[in]   config    link to configuration of counter and it's storage
 *
 *  @return   none
 */
void LoggingPulseCounterBase::Initialize(LoggingPulseCounterConfiguration &config)
{

    mPulseWeight = config.pulseWeight;
    mStoragePageSize = config.storagePageSize;
    mStorageBuffer =  config.storageBuffer;

    StorageInitialize();

}

/**
 *  Initialize main storage structure
 *
 *  @return   none
 */
void LoggingPulseCounterBase::StorageInitialize()
{
    mStorage = mStorageBuffer;

    mStorage.header.value = 0;
    mStorage.header.count = 0;
    mStorage.header.free = (mStoragePageSize - sizeof(mStrage.header))/sizeof(uint32_t);
    mStorage.header.pulseWeight = mPulseWeight;

}

/**
 *  Update storage structure during pulse registration process
 *
 *  @return   none
 */
void LoggingPulseCounterBase::UpdateStorage()
{
    mStorage.timeLog[mStorage.header.count] = GetTimeStamp();
    mStorage.header.count++;
    mStorage.header.free--;
    mStrage.header.value += pulseWeight;

}

