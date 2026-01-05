#include "EspTimer.h"
#include "EspOSInterfaceLog.h"

void EspTimer::callbackWrapper(TimerHandle_t xTimer)
{
    if (EspTimer* espTimer = static_cast<EspTimer*>(pvTimerGetTimerID(xTimer));
        espTimer != nullptr && espTimer->callbackFunction != nullptr)
    {
        OSInterfaceLogInfo(EspOSInterfaceLogTag, "Timer callback invoked for timer %s", pcTimerGetName(xTimer));
        espTimer->callbackFunction(espTimer->callbackArgs);
    }
    else
    {
        OSInterfaceLogWarning(EspOSInterfaceLogTag, "Timer callback invoked but %s%s",
                              espTimer == nullptr ? "EspTimer instance is null" : "callback function is null for timer ",
                              espTimer == nullptr ? "" : pcTimerGetName(xTimer));
    }
}

EspTimer::EspTimer(const char* const pcTimerName, const uint32_t timerPeriod, const Mode mode,
                   const OSInterfaceProcess callback, void* callbackArgs, bool& result)
{
    this->callbackFunction = callback;
    this->callbackArgs     = callbackArgs;
    this->timer = xTimerCreate(pcTimerName, pdMS_TO_TICKS(timerPeriod), mode == PERIODIC ? pdTRUE : pdFALSE, this,
                               callbackWrapper);
    result      = (this->timer != nullptr);
}

EspTimer::~EspTimer()
{
    if (timer != nullptr)
    {
        xTimerDelete(timer, 0);
    }
}

bool EspTimer::start()
{
    return xTimerStart(timer, 0) == pdPASS;
}

bool EspTimer::startFromISR()
{
    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
    BaseType_t res                       = xTimerStartFromISR(timer, &pxHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);
    return res == pdPASS;
}

bool EspTimer::stop()
{
    return xTimerStop(timer, 0) == pdPASS;
}

bool EspTimer::stopFromISR()
{
    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
    BaseType_t res                       = xTimerStopFromISR(timer, &pxHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);
    return res == pdPASS;
}

[[nodiscard]] bool EspTimer::isRunning() const
{
    return xTimerIsTimerActive(timer) != pdFALSE;
}

bool EspTimer::setPeriod(const uint32_t newPeriod_ms)
{
    return xTimerChangePeriod(timer, pdMS_TO_TICKS(newPeriod_ms), 0) == pdPASS;
}

bool EspTimer::setPeriodFromISR(const uint32_t newPeriod_ms)
{
    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
    BaseType_t res = xTimerChangePeriodFromISR(timer, pdMS_TO_TICKS(newPeriod_ms), &pxHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);
    return res == pdPASS;
}

[[nodiscard]] uint32_t EspTimer::getPeriod() const
{
    return pdTICKS_TO_MS(xTimerGetPeriod(timer));
}

[[nodiscard]] EspTimer::Mode EspTimer::getMode() const
{
    return (xTimerGetReloadMode(timer) == pdTRUE) ? PERIODIC : ONE_SHOT;
}

[[nodiscard]] uint32_t EspTimer::getTimeout() const
{
    int64_t ticksLeft = static_cast<int64_t>(xTimerGetExpiryTime(timer)) - static_cast<int64_t>(xTaskGetTickCount());
    if (ticksLeft < 0)
    {
        ticksLeft = __UINT32_MAX__ - xTaskGetTickCount() + xTimerGetExpiryTime(timer); // Take into account overflow
    }
    return pdTICKS_TO_MS(ticksLeft);
}

[[nodiscard]] uint32_t EspTimer::getTimeoutTime() const
{
    return pdTICKS_TO_MS(xTimerGetExpiryTime(timer));
}
