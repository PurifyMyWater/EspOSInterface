#include "EspTimer.h"

EspTimer::EspTimer(uint32_t period, Mode mode, OSInterfaceProcess callback, void* callbackArg, const char* timerName)
{
}

EspTimer::~EspTimer()
{
}

bool EspTimer::start()
{
}

bool EspTimer::stop()
{
}

bool EspTimer::isRunning() const
{
}

bool EspTimer::setPeriod(uint32_t newPeriod_ms)
{
}

uint32_t EspTimer::getPeriod() const
{
}

OSInterface_Timer::Mode EspTimer::getMode() const
{
}

uint32_t EspTimer::getTimeout() const
{
}

uint32_t EspTimer::getTimeoutTime() const
{
}
