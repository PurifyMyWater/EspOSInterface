#include "EspTimer.h"

void EspTimer::callbackWrapper(TimerHandle_t xTimer)
{
    EspTimer* espTimer = static_cast<EspTimer*>(pvTimerGetTimerID(xTimer));
    if (espTimer != nullptr && espTimer->callbackFunction != nullptr)
    {
        espTimer->callbackFunction(espTimer->callbackArgs);
    }
}

EspTimer::EspTimer(const char* const pcTimerName, const uint32_t timerPeriod, const OSInterface_Timer::Mode mode,
                   OSInterfaceProcess callback, void* callbackArgs, bool& result)
{
    this->callbackFunction = callback;
    this->callbackArgs     = callbackArgs;
    this->timer            = xTimerCreate(pcTimerName, pdMS_TO_TICKS(timerPeriod),
                               mode == OSInterface_Timer::PERIODIC ? pdTRUE : pdFALSE, this, callbackWrapper);
    result                 = (this->timer != nullptr);
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

bool EspTimer::setPeriod(uint32_t newPeriod_ms)
{
    return xTimerChangePeriod(timer, pdMS_TO_TICKS(newPeriod_ms), 0) == pdPASS;
}

bool EspTimer::setPeriodFromISR(uint32_t newPeriod_ms)
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
    return (xTimerGetReloadMode(timer) == pdTRUE) ? Mode::PERIODIC : Mode::ONE_SHOT;
}

[[nodiscard]] uint32_t EspTimer::getTimeout() const
{
    return pdTICKS_TO_MS(xTimerGetExpiryTime(timer) - xTaskGetTickCount());
}

[[nodiscard]] uint32_t EspTimer::getTimeoutTime() const
{
    return pdTICKS_TO_MS(xTimerGetExpiryTime(timer));
}
