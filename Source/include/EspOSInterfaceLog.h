#ifndef ESPOSINTERFACELOG_H
#define ESPOSINTERFACELOG_H

#include "esp_log.h"

#ifdef OSInterfaceLogVerbose
#undef OSInterfaceLogVerbose
#endif
#define OSInterfaceLogVerbose(tag, format, ...) ESP_LOGV(tag, format, ##__VA_ARGS__)

#ifdef OSInterfaceLogDebug
#undef OSInterfaceLogDebug
#endif
#define OSInterfaceLogDebug(tag, format, ...) ESP_LOGD(tag, format, ##__VA_ARGS__)

#ifdef OSInterfaceLogInfo
#undef OSInterfaceLogInfo
#endif
#define OSInterfaceLogInfo(tag, format, ...) ESP_LOGI(tag, format, ##__VA_ARGS__)

#ifdef OSInterfaceLogWarning
#undef OSInterfaceLogWarning
#endif
#define OSInterfaceLogWarning(tag, format, ...) ESP_LOGW(tag, AT format, ##__VA_ARGS__)

#ifdef OSInterfaceLogError
#undef OSInterfaceLogError
#endif
#define OSInterfaceLogError(tag, format, ...) ESP_LOGE(tag, AT format, ##__VA_ARGS__)

#ifdef OSInterfaceSetLogLevel
#undef OSInterfaceSetLogLevel
#endif
#define OSInterfaceSetLogLevel(tag, level) esp_log_level_set(tag, static_cast<esp_log_level_t>(level))

#ifdef OSInterfaceGetLogLevel
#undef OSInterfaceGetLogLevel
#endif
#define OSInterfaceGetLogLevel(tag) esp_log_get_level(tag)

#endif //ESPOSINTERFACELOG_H
