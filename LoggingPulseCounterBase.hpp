
#include <cstdint>

#pragma once

/**
 * This structure represents configuration for pulse counter initialization
 */
typedef struct {
    double pulseWeight;             //< Count of measured stuff per one captured pulse
    double initialValue;            //< Initial counter value
    uint32_t storagePageSize;       //< Size of one flash storage page (just, data chunk size, should be aligned by 4 Bytes)
    void * storageBuffer;           //< Pointer to allocated buffer for accumulating data before it will be written.
                                    //  Can be used some kind of backup memory, or other memory, safe during device sleeping period.

} LoggingPulseCounterConfiguration;



/**
 * Pulse Counter class
 *
 * This class implements pulse counter behavior and internal data structures.
 *
 */
class LoggingPulseCounterBase
{
public:
    // remove constructor (method is not using it)
    LoggingPulseCounterBase() = default;

    // Initialization method
    void Initialize(const LoggingPulseCounterConfiguration &config);

    // function, implemented by user for providing current time stamp
    virtual uint32_t GetTimeStamp();

    // function, implemented by user for writing memory buffer to flash storage, when it full.
    virtual void FlushLogToStorage();

    // function, for reading current value from counter.
    double GetCurrentValue();

    // function, for registering one more captured pulse.
    void PulseCapture();

private:

    double   mPulseWeight;
    uint32_t mStoragePageSize;
    void *   mStorageBuffer;
    double   mTotalValue;

    struct mStorage
    {
        struct header {
            uint16_t count;
            uint16_t unitSize;
            uint16_t free;
            double pulseWeight;
            double value;
            double total;
        } header;
        uint32_t timeLog[];
    } * mStorage;


    // updates storage item with captured data
    void UpdateStorage();

    // initialize and clear storage item
    void StorageInitialize();

    // flush storage
    void StorageFlush();

};