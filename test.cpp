/* generic system includes */
#include <ctime>
#include <unistd.h>
#include <iostream>
#include <cstdint>
#include <cstring>
#include <cstdlib>

/* Include tested library header */
#include <LoggingPulseCounterBase.hpp>

uint8_t buffer[512] = {0};

int main(int argc, char const *argv[])
{

    std::srand(0xAAAAAAAA);
    LoggingPulseCounterConfiguration config =
    {
        .pulseWeight = 0.125,
        .initialValue = 100.,
        .storagePageSize = 512,
        .storageBuffer = static_cast<void*>(buffer)
    };

    LoggingPulseCounterBase counter;
    counter.Initialize(config);

    for (int i = 1; i <= 280; i++ ) {
        counter.PulseCapture();
        std::cout << '|' << std::flush;
        if(i%32 == 0 )
        {
            std::cout << std::endl;
        }
    }

    counter.FlushLogToStorage();
    std::cout << "TotalValue is: " << counter.GetCurrentValue() << std::endl;

    return 0;
}

// just returns dummied value as a time stamp
uint32_t LoggingPulseCounterBase::GetTimeStamp()
{
    static int callCount = 0;
    uint32_t time  = 0xAAAAAAAA;
    int rndShift = std::rand() % 14;

    time += callCount++ * 15 + rndShift;

    return time;
}

// Print storage containing on to console
void LoggingPulseCounterBase::FlushLogToStorage()
{
    struct tmpStorage
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
    } tmpStorage;

    struct tmpStorage * alias  = reinterpret_cast<struct tmpStorage*>(buffer);


    std::cout << std::endl << "Here is how data struct looks like:" << std::endl;
    // Print Header:
    std::cout << "=======================================" << std::endl;
    std::cout << "HEADER CONTENT:" << std::endl;
    std::cout << "Size: "  << alias->header.unitSize;
    std::cout << " Free: " << alias->header.free;
    std::cout << " Used: " << alias->header.count << std::endl;
    std::cout << "Pulse weight: " << alias->header.pulseWeight << std::endl;
    std::cout << "Value: "        << alias->header.value;
    std::cout << " Total: "        << alias->header.total << std::endl;
    std::cout << "=======================================" << std::endl;
    std::cout << "LOGGED PULSES:" << std::endl;
    std::cout << "=======================================" << std::endl;

    for(int i = 1; i <= alias->header.count; i++ )
    {
        std::cout << i << ":\t" << std::hex << alias->timeLog[i-1] << std::dec << " | ";
        if(i % 4 == 0)
        {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
    std::cout << "=======================================" << std::endl;
    std::cout << "END OF FRAME" << std::endl;

    // Clear buffer
    std::memset(alias, 0x00, alias->header.unitSize);
}