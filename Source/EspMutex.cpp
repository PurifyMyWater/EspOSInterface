#include "EspOSInterfaceLog.h"
#include "EspMutex.h"

EspMutex::EspMutex(bool& result)
{
    mutex  = xSemaphoreCreateMutex();
    result = (mutex != nullptr);
}

EspMutex::~EspMutex()
{
    if (mutex != nullptr)
    {
        vSemaphoreDelete(mutex);
    }
}

void EspMutex::signal()
{
    if (xSemaphoreGive(mutex) == pdFALSE)
    {
        // Crash if we can't give the semaphore.
        OSInterfaceLogError(EspOSInterfaceLogTag, "Failed to give mutex");
        abort();
    }
}

bool EspMutex::wait(const uint32_t max_time_to_wait_ms)
{
    return xSemaphoreTake(mutex, pdMS_TO_TICKS(max_time_to_wait_ms)) == pdTRUE;
}
