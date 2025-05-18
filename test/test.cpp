#include <unity.h>
#include <EspOSInterface.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

EspOSInterface espOSInterface;

TEST_CASE("timeTest", "[EspOSInterface]")
{
    uint32_t timeToSleep = 10;
    uint32_t repeat = 10;
    bool flag = false;

    for (uint32_t i = 0; i < repeat; i++)
    {
        uint32_t millis = espOSInterface.osMillis();
        espOSInterface.osSleep(timeToSleep);
        uint32_t millis2 = espOSInterface.osMillis();

        TEST_ASSERT_GREATER_OR_EQUAL(millis + timeToSleep, millis2);
        if (millis2 >= (millis + timeToSleep + 100))
        {
            flag = true;
        }
    }

    if (flag)
    {
        TEST_FAIL_MESSAGE("Sleep slept for too long");
    }
}

TEST_CASE("osMallocSimpleAlloc", "[espOSInterface]")
{
    void* ptr = espOSInterface.osMalloc(100);
    TEST_ASSERT_NOT_NULL(ptr);
    espOSInterface.osFree(ptr);
}

TEST_CASE("osMallocZeroAlloc", "[espOSInterface]")
{
    void* ptr = espOSInterface.osMalloc(0);
    TEST_ASSERT_NULL(ptr);
    espOSInterface.osFree(ptr);
}

TEST_CASE("osMallocLargeAlloc", "[espOSInterface]")
{
    void* ptr = espOSInterface.osMalloc(1024 * 100);
    ESP_LOGE("TEST", "XXX large ptr: %p", ptr);
    TEST_ASSERT_NOT_NULL(ptr);
    espOSInterface.osFree(ptr);
}

TEST_CASE("osMallocMultipleAlloc", "[espOSInterface]")
{
    void* ptr1 = espOSInterface.osMalloc(100);
    void* ptr2 = espOSInterface.osMalloc(100);
    void* ptr3 = espOSInterface.osMalloc(100);
    TEST_ASSERT_NOT_NULL(ptr1);
    TEST_ASSERT_NOT_NULL(ptr2);
    TEST_ASSERT_NOT_NULL(ptr3);
    espOSInterface.osFree(ptr1);
    espOSInterface.osFree(ptr2);
    espOSInterface.osFree(ptr3);
}

// **** Mutex Tests ****

TEST_CASE("mutexWait", "[espOSInterface]")
{
    OSInterface_Mutex* mutex = espOSInterface.osCreateMutex();
    TEST_ASSERT_NOT_NULL(mutex);
    TEST_ASSERT_TRUE(mutex->wait(10));
    delete mutex;
}

// Task for normal mutex lock test
static bool secondThreadLocked = false;
static OSInterface_Mutex* s_mutex = nullptr;

static void secondMutexTask(void* arg)
{
    if (s_mutex->wait(10000))
    {
        secondThreadLocked = true;
        s_mutex->signal();
    }
    vTaskDelete(nullptr);
}

TEST_CASE("mutexTestNormal", "[espOSInterface]")
{
    s_mutex = espOSInterface.osCreateMutex();
    TEST_ASSERT_NOT_NULL(s_mutex);
    TEST_ASSERT_TRUE(s_mutex->wait(10000));

    secondThreadLocked = false;
    xTaskCreate(secondMutexTask, "secondMutexTask", 2048, nullptr, 5, nullptr);
    vTaskDelay(pdMS_TO_TICKS(50));
    TEST_ASSERT_FALSE(secondThreadLocked);

    s_mutex->signal();
    vTaskDelay(pdMS_TO_TICKS(50));
    TEST_ASSERT_TRUE(secondThreadLocked);

    delete s_mutex;
    s_mutex = nullptr;
}

// Task for mutex timeout test
static bool secondThreadLockedTimeout = false;

static void secondMutexTimeoutTask(void* arg)
{
    bool res = s_mutex->wait(50);
    if (res)
    {
        secondThreadLockedTimeout = true;
        s_mutex->signal();
    }
    vTaskDelete(nullptr);
}

TEST_CASE("mutexTestTimeout", "[espOSInterface]")
{
    s_mutex = espOSInterface.osCreateMutex();
    TEST_ASSERT_NOT_NULL(s_mutex);
    TEST_ASSERT_TRUE(s_mutex->wait(10000));

    secondThreadLockedTimeout = false;
    xTaskCreate(secondMutexTimeoutTask, "secondMutexTimeoutTask", 2048, nullptr, 5, nullptr);
    vTaskDelay(pdMS_TO_TICKS(100));
    TEST_ASSERT_FALSE(secondThreadLockedTimeout);

    s_mutex->signal();
    vTaskDelay(pdMS_TO_TICKS(50));
    TEST_ASSERT_FALSE(secondThreadLockedTimeout);

    delete s_mutex;
    s_mutex = nullptr;
}

// **** Binary Semaphore Tests ****

TEST_CASE("binarySemaphoreInit", "[espOSInterface]")
{
    OSInterface_BinarySemaphore* semaphore = espOSInterface.osCreateBinarySemaphore();
    TEST_ASSERT_NOT_NULL(semaphore);
    TEST_ASSERT_FALSE(semaphore->wait(10));
    delete semaphore;
}

TEST_CASE("binarySemaphoreWaitSignal", "[espOSInterface]")
{
    OSInterface_BinarySemaphore* semaphore = espOSInterface.osCreateBinarySemaphore();
    TEST_ASSERT_NOT_NULL(semaphore);
    semaphore->signal();
    TEST_ASSERT_TRUE(semaphore->wait(10));
    delete semaphore;
}

TEST_CASE("binarySemaphoreWaitSignalWait", "[espOSInterface]")
{
    OSInterface_BinarySemaphore* semaphore = espOSInterface.osCreateBinarySemaphore();
    TEST_ASSERT_NOT_NULL(semaphore);
    semaphore->signal();
    TEST_ASSERT_TRUE(semaphore->wait(10));
    TEST_ASSERT_FALSE(semaphore->wait(10));
    delete semaphore;
}

// Task for normal semaphore test
static bool secondSemLocked = false;
static OSInterface_BinarySemaphore* s_semaphore = nullptr;

static void secondSemTask(void* arg)
{
    if (s_semaphore->wait(10000))
    {
        secondSemLocked = true;
        s_semaphore->signal();
    }
    vTaskDelete(nullptr);
}

TEST_CASE("semaphoreTestNormal", "[espOSInterface]")
{
    s_semaphore = espOSInterface.osCreateBinarySemaphore();
    TEST_ASSERT_NOT_NULL(s_semaphore);
    s_semaphore->signal();
    TEST_ASSERT_TRUE(s_semaphore->wait(10000));

    secondSemLocked = false;
    xTaskCreate(secondSemTask, "secondSemTask", 2048, nullptr, 5, nullptr);
    vTaskDelay(pdMS_TO_TICKS(50));
    TEST_ASSERT_FALSE(secondSemLocked);

    s_semaphore->signal();
    vTaskDelay(pdMS_TO_TICKS(50));
    TEST_ASSERT_TRUE(secondSemLocked);

    delete s_semaphore;
    s_semaphore = nullptr;
}

// Task for semaphore timeout test
static bool secondSemLockedTimeout = false;

static void secondSemTimeoutTask(void* arg)
{
    bool res = s_semaphore->wait(50);
    if (res)
    {
        secondSemLockedTimeout = true;
        s_semaphore->signal();
    }
    vTaskDelete(nullptr);
}

TEST_CASE("semaphoreTestTimeout", "[espOSInterface]")
{
    s_semaphore = espOSInterface.osCreateBinarySemaphore();
    TEST_ASSERT_NOT_NULL(s_semaphore);
    s_semaphore->signal();
    TEST_ASSERT_TRUE(s_semaphore->wait(10000));

    secondSemLockedTimeout = false;
    xTaskCreate(secondSemTimeoutTask, "secondSemTimeoutTask", 2048, nullptr, 5, nullptr);
    vTaskDelay(pdMS_TO_TICKS(100));
    TEST_ASSERT_FALSE(secondSemLockedTimeout);

    s_semaphore->signal();
    vTaskDelay(pdMS_TO_TICKS(50));
    TEST_ASSERT_FALSE(secondSemLockedTimeout);

    delete s_semaphore;
    s_semaphore = nullptr;
}

void runProcessTest(void* arg)
{
    volatile bool* processRun = static_cast<bool*>(arg);
    espOSInterface.osSleep(100);
    *processRun = true;
}

TEST_CASE("runProcessTest", "[espOSInterface]")
{
    volatile bool processRun = false;
    void* arg = (void*) (&processRun);

    auto millis = espOSInterface.osMillis();
    espOSInterface.osRunProcess(runProcessTest, arg);

    while (!processRun && (millis + 1000 > espOSInterface.osMillis()))
    {
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    TEST_ASSERT_TRUE(processRun);
}
