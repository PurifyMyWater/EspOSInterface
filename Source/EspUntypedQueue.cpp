#include "EspUntypedQueue.h"

EspUntypedQueue::EspUntypedQueue(uint32_t maxMessages, uint32_t messageSize, bool& result)
{
    queue             = xQueueCreate(maxMessages, messageSize);
    result            = (queue != nullptr);
    this->maxMessages = maxMessages;
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
    return uxQueueMessagesWaiting(queue);
}
uint32_t EspUntypedQueue::size()
{
    return maxMessages;
}
uint32_t EspUntypedQueue::available()
{
    return uxQueueSpacesAvailable(queue);
}
bool EspUntypedQueue::isEmpty()
{
    return uxQueueMessagesWaiting(queue) == 0;
}
bool EspUntypedQueue::isFull()
{
    return uxQueueSpacesAvailable(queue) == 0;
}
void EspUntypedQueue::reset()
{
    xQueueReset(queue);
}
bool EspUntypedQueue::receive(void* message, uint32_t maxTimeToWait_ms)
{
    return xQueueReceive(queue, message, maxTimeToWait_ms) == pdTRUE;
}
bool EspUntypedQueue::receiveFromISR(void* message)
{
    BaseType_t higherPriorityTaskWoken = pdFALSE;
    BaseType_t res                     = xQueueReceiveFromISR(queue, message, &higherPriorityTaskWoken);
    portYIELD_FROM_ISR(higherPriorityTaskWoken);
    return res == pdTRUE;
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
    return xQueueSendToFront(queue, message, pdMS_TO_TICKS(maxTimeToWait_ms)) == pdTRUE;
}
bool EspUntypedQueue::sendToFrontFromISR(const void* message)
{
    BaseType_t higherPriorityTaskWoken = pdFALSE;
    BaseType_t res                     = xQueueSendToFrontFromISR(queue, message, &higherPriorityTaskWoken);
    portYIELD_FROM_ISR(higherPriorityTaskWoken);
    return res == pdTRUE;
}
