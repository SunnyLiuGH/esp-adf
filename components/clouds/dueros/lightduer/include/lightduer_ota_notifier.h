/**
 * Copyright (2017) Baidu Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*
 * File: lightduer_ota_notifier.h
 * Auth: Zhong Shuai (zhongshuai@baidu.com)
 * Desc: OTA Notifier Head File
 */

#ifndef BAIDU_DUER_LIGHTDUER_INCLUDE_LIGHTDUER_OTA_NOTIFIER_H
#define BAIDU_DUER_LIGHTDUER_INCLUDE_LIGHTDUER_OTA_NOTIFIER_H

#include "lightduer_dev_info.h"
#include "lightduer_ota_updater.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NAME_LEN   24
#define BATCH_LEN  4

#define OTA_PROTOCOL_VERSION "0.9"

typedef enum _duer_ota_state {
    OTA_IDLE = 0,
    OTA_DOWNLOADING,
    OTA_DOWNLOADED,
    OTA_INSTALLING,
    OTA_INSTALLED
} duer_ota_state;

typedef enum _duer_ota_event {
    OTA_EVENT_BEGIN,
    OTA_EVENT_CONNECT_FAIL,
    OTA_EVENT_CONNECTION_LOST,
    OTA_EVENT_TIMEOUT,
    OTA_EVENT_DOWNLOADING,
    OTA_EVENT_DOWNLOAD_COMPLETE,
    OTA_EVENT_DOWNLOAD_FAIL,
    OTA_EVENT_INSTALLING,
    OTA_EVENT_IMAGE_INVALID,
    OTA_EVENT_WRITE_ERROR,
    OTA_EVENT_INSTALLED,
    OTA_EVENT_DELETED,
    OTA_EVENT_REJECT,
} duer_ota_event;

typedef struct _duer_os_info_s {
    char os_name[NAME_LEN + 1];
    char developer[NAME_LEN + 1];
    char os_version[FIRMWARE_VERSION_LEN + 1];
    char staged_version[NAME_LEN + 1];
} duer_os_info_t;

typedef struct _duer_package_info_s {
    char product[NAME_LEN + 1];
    char batch[BATCH_LEN + 1];
    duer_os_info_t os_info;
} duer_package_info_t;

typedef struct _duer_package_info_ops_s {
    int (*get_package_info)(duer_package_info_t *info);
} duer_package_info_ops_t;

/*
 * Notify the package information to the Duer Cloud
 *
 * @param void:
 *
 * @return int: Success: DUER_OK
 *              Failed:  Other
 */
extern int duer_ota_notify_package_info(void);

/*
 * Get the package information that about the current system
 *
 * @param info: Pointer to Package information
 *
 * @return int: Success: DUER_OK
 *              Failed:  Other
 */
extern int duer_ota_get_package_info(duer_package_info_t *info);

/*
 * Register get package information OPS
 *
 * @param ops: duer_package_info_ops_t * which you need to implement
 *
 * @return int: Success: DUER_OK
 *              Failed:  Other
 */
extern int duer_ota_register_package_info_ops(duer_package_info_ops_t *ops);

/*
 * Notifier the OTA state to Duer Cloud
 *
 * @param updater: OTA updater object
 *
 * @param state: OTA state
 *
 * @return int: Success: DUER_OK
 *              Failed:  Other
 */
extern int duer_ota_notifier_state(duer_ota_updater_t *updater, duer_ota_state state);

/*
 * Notifier OTA event to Duer Cloud
 *
 * @param updater: OTA updater object
 *
 * @param event: OTA event
 *
 * @param progress: It can pass information about installing progress information
 *                  or downloading progress information
 *
 * @return int: Success: DUER_OK
 *              Failed:  Other
 */
extern int duer_ota_notifier_event(duer_ota_updater_t *updater, duer_ota_event event, double progress);

#ifdef __cplusplus
}
#endif

#endif // BAIDU_DUER_LIGHTDUER_INCLUDE_LIGHTDUER_OTA_NOTIFIER_H
