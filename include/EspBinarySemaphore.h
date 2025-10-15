#ifndef ESPBINARYSEMAPHORE_H
#define ESPBINARYSEMAPHORE_H

#include "EspOSInterface.h"
#include <freertos/FreeRTOS.h>

class EspBinarySemaphore final : public OSInterface_BinarySemaphore
{
public:
    EspBinarySemaphore();

    ~EspBinarySemaphore() override;

    void signal() override;

    bool wait(uint32_t max_time_to_wait_ms) override;

private:
    SemaphoreHandle_t semaphore{};
};

#endif //ESPBINARYSEMAPHORE_H
