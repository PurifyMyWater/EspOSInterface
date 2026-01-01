#ifndef ESPOSINTERFACELOG_H
#define ESPOSINTERFACELOG_H

#include "esp_log.h"

constexpr const char* EspOSInterfaceLogTag = "EspOSInterface";

#ifndef OSInterfaceLogVerbose
    #define OSInterfaceLogVerbose(tag, format, ...) ESP_LOGV(tag, format, ##__VA_ARGS__)
#endif

#ifndef OSInterfaceLogDebug
    #define OSInterfaceLogDebug(tag, format, ...) ESP_LOGD(tag, format, ##__VA_ARGS__)
#endif

#ifndef OSInterfaceLogInfo
    #define OSInterfaceLogInfo(tag, format, ...) ESP_LOGI(tag, format, ##__VA_ARGS__)
#endif

#ifndef OSInterfaceLogWarning
    #define OSInterfaceLogWarning(tag, format, ...) ESP_LOGW(tag, AT format, ##__VA_ARGS__)
#endif

#ifndef OSInterfaceLogError
    #define OSInterfaceLogError(tag, format, ...) ESP_LOGE(tag, AT format, ##__VA_ARGS__)
#endif

#ifndef OSInterfaceSetLogLevel
    #define OSInterfaceSetLogLevel(tag, level) esp_log_level_set(tag, static_cast<esp_log_level_t>(level))
#endif

#ifndef OSInterfaceGetLogLevel
    #define OSInterfaceGetLogLevel(tag) esp_log_get_level(tag)
#endif

#include "OSInterface_Log.h"

#endif // ESPOSINTERFACELOG_H
