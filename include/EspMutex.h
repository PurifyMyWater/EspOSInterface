#ifndef ESPMUTEX_H
#define ESPMUTEX_H

#include "EspOSInterface.h"
#include <freertos/FreeRTOS.h>

class EspMutex final : public OSInterface_Mutex
{
public:
    EspMutex();

    ~EspMutex() override;

    void signal() override;

    bool wait(uint32_t max_time_to_wait_ms) override;

private:
    SemaphoreHandle_t mutex{};
};


#endif //ESPMUTEX_H
