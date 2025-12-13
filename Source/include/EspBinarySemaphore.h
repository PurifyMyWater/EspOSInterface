#ifndef ESPBINARYSEMAPHORE_H
#define ESPBINARYSEMAPHORE_H

#include <freertos/FreeRTOS.h>
#include "OSInterface.h"

class EspBinarySemaphore final : public OSInterface_BinarySemaphore
{
public:
    EspBinarySemaphore(bool& result);

    ~EspBinarySemaphore() override;

    void signal() override;

    bool wait(uint32_t max_time_to_wait_ms) override;

private:
    SemaphoreHandle_t semaphore{};
};

#endif // ESPBINARYSEMAPHORE_H
