#ifndef ESPTIMER_H
#define ESPTIMER_H

#include <freertos/FreeRTOS.h>
#include "OSInterface.h"
#include "OSInterface_Timer.h"

class EspTimer final : public OSInterface_Timer
{
public:
    EspTimer(const char* pcTimerName, uint32_t timerPeriod, Mode mode, OSInterfaceProcess callback, void* callbackArgs,
             bool& result);

    ~EspTimer() override;

    bool start() override;

    bool startFromISR() override;

    bool stop() override;

    bool stopFromISR() override;

    [[nodiscard]] bool isRunning() const override;

    bool setPeriod(uint32_t newPeriod_ms) override;

    bool setPeriodFromISR(uint32_t newPeriod_ms) override;

    [[nodiscard]] uint32_t getPeriod() const override;

    [[nodiscard]] Mode getMode() const override;

    [[nodiscard]] uint32_t getTimeout() const override;

    [[nodiscard]] uint32_t getTimeoutTime() const override;

private:
    TimerHandle_t timer{};

    OSInterfaceProcess callbackFunction{};
    void*              callbackArgs{};

    static void callbackWrapper(TimerHandle_t xTimer);
};

#endif // ESPTIMER_H
