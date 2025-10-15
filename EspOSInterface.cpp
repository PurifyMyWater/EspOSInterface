#include "EspOSInterface.h"
#include "EspBinarySemaphore.h"
#include "EspMutex.h"
#include "EspTimer.h"

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


uint32_t EspOSInterface::osMillis()
{
    return pdTICKS_TO_MS(xTaskGetTickCount());
}

void EspOSInterface::osSleep(const uint32_t ms)
{
    vTaskDelay(pdMS_TO_TICKS(ms));
}

OSInterface_Mutex* EspOSInterface::osCreateMutex()
{
    return new EspMutex();
}

OSInterface_BinarySemaphore* EspOSInterface::osCreateBinarySemaphore()
{
    return new EspBinarySemaphore();
}

OSInterface_Timer* EspOSInterface::osCreateTimer(const uint32_t period, const OSInterface_Timer::Mode mode,
    const OSInterfaceProcess callback, void* callbackArg, const char* timerName)
{
    return new EspTimer(period, mode, callback, callbackArg, timerName);
}

void* EspOSInterface::osMalloc(const uint32_t size)
{
    return heap_caps_malloc_prefer(size, 2,MALLOC_CAP_8BIT | MALLOC_CAP_SPIRAM, MALLOC_CAP_8BIT | MALLOC_CAP_DEFAULT);
}

void EspOSInterface::osFree(void* ptr)
{
    heap_caps_free(ptr);
}

void EspOSInterface::osRunProcess(const OSInterfaceProcess process, void* arg)
{
    osRunProcess(process, "NewProcess", arg);
}

void EspOSInterface::osRunProcess(const OSInterfaceProcess process, const char* processName, void* arg)
{
    ProcessData* processData = new ProcessData{.process = process, .arg = arg, .processName = processName};
    const auto res = xTaskCreate(osRunProcessLauncher, processName, processDefaultStackSize, processData, processDefaultPriority,
                nullptr);
    if (res != pdPASS)
    {
        OSInterfaceLogError("EspOSInterface", "Failed to create task for process %s", processName);
        delete processData;
    }
}

void EspOSInterface::osRunProcessLauncher(void* data)
{
    auto* processData = static_cast<ProcessData*>(data);
    OSInterfaceLogInfo("OSInterface", "Running process %s", processData->processName);
    processData->process(processData->arg);
    delete processData;
    vTaskDelete(nullptr);
}
