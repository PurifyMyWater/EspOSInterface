#include "EspBinarySemaphore.h"

EspBinarySemaphore::EspBinarySemaphore()
{
    semaphore = xSemaphoreCreateBinary();
}

EspBinarySemaphore::~EspBinarySemaphore()
{
    vSemaphoreDelete(semaphore);
}

void EspBinarySemaphore::signal()
{
    if (xSemaphoreGive(semaphore) == pdFALSE)
    {
        // Crash if we can't give the semaphore.
        OSInterfaceLogError("EspOSInterface", "Failed to give semaphore");
        abort();
    }
}

bool EspBinarySemaphore::wait(const uint32_t max_time_to_wait_ms)
{
    return xSemaphoreTake(semaphore, pdMS_TO_TICKS(max_time_to_wait_ms)) == pdTRUE;
}
