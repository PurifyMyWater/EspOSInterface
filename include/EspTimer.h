#ifndef ESPTIMER_H
#define ESPTIMER_H

#include "EspOSInterface.h"
#include <freertos/FreeRTOS.h>

class EspTimer final : public OSInterface_Timer
{
public:
    EspTimer(uint32_t period, Mode mode,
    OSInterfaceProcess callback, void* callbackArg, const char* timerName);
    ~EspTimer() override;
    bool     start() override;
    bool     stop() override;
    [[nodiscard]] bool     isRunning() const override;
    bool     setPeriod(uint32_t newPeriod_ms) override;
    [[nodiscard]] uint32_t getPeriod() const override;
    [[nodiscard]] Mode     getMode() const override;
    [[nodiscard]] uint32_t getTimeout() const override;
    [[nodiscard]] uint32_t getTimeoutTime() const override;

private:

};

#endif //ESPTIMER_H
