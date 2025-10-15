
#include "EspMutex.h"

EspMutex::EspMutex()
{
    mutex = xSemaphoreCreateMutex();
}

EspMutex::~EspMutex()
{
    vSemaphoreDelete(mutex);
}

void EspMutex::signal()
{
    if (xSemaphoreGive(mutex) == pdFALSE)
    {
        // Crash if we can't give the semaphore.
        OSInterfaceLogError("EspOSInterface", "Failed to give mutex");
        abort();
    }
}

bool EspMutex::wait(const uint32_t max_time_to_wait_ms)
{
    return xSemaphoreTake(mutex, pdMS_TO_TICKS(max_time_to_wait_ms)) == pdTRUE;
}
