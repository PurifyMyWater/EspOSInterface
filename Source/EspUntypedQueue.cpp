#include "EspUntypedQueue.h"

EspUntypedQueue::EspUntypedQueue(uint32_t maxMessages, uint32_t messageSize, bool& result)
{
    queue  = xQueueCreate(maxMessages, messageSize);
    result = (queue != nullptr);
}

EspUntypedQueue::~EspUntypedQueue()
{
    if (queue != nullptr)
    {
        vQueueDelete(queue);
    }
}

uint32_t EspUntypedQueue::length()
{
    return 0;
}
uint32_t EspUntypedQueue::size()
{
    return 0;
}
uint32_t EspUntypedQueue::available()
{
    return 0;
}
bool EspUntypedQueue::isEmpty()
{
    return false;
}
bool EspUntypedQueue::isFull()
{
    return false;
}
void EspUntypedQueue::reset()
{}
bool EspUntypedQueue::receive(void* message, uint32_t maxTimeToWait_ms)
{
    return false;
}
bool EspUntypedQueue::receiveFromISR(void* message)
{
    return false;
}
bool EspUntypedQueue::sendToBack(const void* message, uint32_t maxTimeToWait_ms)
{
    return xQueueSendToBack(queue, message, pdMS_TO_TICKS(maxTimeToWait_ms)) == pdTRUE;
}
bool EspUntypedQueue::sendToBackFromISR(const void* message)
{
    BaseType_t higherPriorityTaskWoken = pdFALSE;
    BaseType_t res                     = xQueueSendToBackFromISR(queue, message, &higherPriorityTaskWoken);
    portYIELD_FROM_ISR(higherPriorityTaskWoken);
    return res == pdTRUE;
}
bool EspUntypedQueue::sendToFront(const void* message, uint32_t maxTimeToWait_ms)
{
    return false;
}
bool EspUntypedQueue::sendToFrontFromISR(const void* message)
{
    return false;
}
