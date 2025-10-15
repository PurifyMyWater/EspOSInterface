#ifndef OSESPINTERFACE_H
#define OSESPINTERFACE_H

#include "OSInterface.h"
#include "EspOSInterfaceLog.h"

class EspOSInterface : public OSInterface
{
public:
    void osSleep(uint32_t ms) override;

    uint32_t osMillis() override;

    OSInterface_Mutex* osCreateMutex() override;

    OSInterface_BinarySemaphore* osCreateBinarySemaphore() override;

    void* osMalloc(uint32_t size) override;

    void osFree(void* ptr) override;

    void osRunProcess(OSInterfaceProcess process, void* arg) override;

    void osRunProcess(OSInterfaceProcess process, const char* processName, void* arg) override;

private:
    static constexpr uint32_t processDefaultStackSize = 2048;
    static constexpr uint8_t processDefaultPriority = 5;
    using ProcessData = struct
    {
        OSInterfaceProcess process;
        void* arg;
        const char* processName;
    };

    static void osRunProcessLauncher(void* data);
};

#endif // OSESPINTERFACE_H
