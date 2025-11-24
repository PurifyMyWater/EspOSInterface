//
// Created by victor on 22/11/25.
//

#ifndef TEST_PROJECT_ESPUNTYPEDQUEUE_H
#define TEST_PROJECT_ESPUNTYPEDQUEUE_H

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include "OSInterface.h"

class EspUntypedQueue final : public OSInterface_UntypedQueue
{
public:
    EspUntypedQueue(uint32_t maxMessages, uint32_t messageSize, bool& result);
    ~EspUntypedQueue();

    uint32_t length() override;
    uint32_t size() override;
    uint32_t available() override;
    bool     isEmpty() override;
    bool     isFull() override;
    void     reset() override;
    bool     receive(void* message, uint32_t maxTimeToWait_ms) override;
    bool     receiveFromISR(void* message) override;
    bool     sendToBack(const void* message, uint32_t maxTimeToWait_ms) override;
    bool     sendToBackFromISR(const void* message) override;
    bool     sendToFront(const void* message, uint32_t maxTimeToWait_ms) override;
    bool     sendToFrontFromISR(const void* message) override;

private:
    QueueHandle_t   queue;
    uint32_t        maxMessages;
};

#endif // TEST_PROJECT_ESPUNTYPEDQUEUE_H
