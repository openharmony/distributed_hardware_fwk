/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OHOS_DISTRIBUTED_HARDWARE_ERRNO
#define OHOS_DISTRIBUTED_HARDWARE_ERRNO

#include <cstdint>

namespace OHOS {
namespace DistributedHardware {
    /*
     * The distributed hardware module define errno, range: [-10000, -19999]
     * Here's common errno, range: [-10000, -10199]
     */
    constexpr int32_t DH_FWK_SUCCESS = 0;
    constexpr int32_t ERR_DH_FWK_PARA_INVALID = -10000;
    constexpr int32_t ERR_DH_FWK_REMOTE_NETWORK_ID_IS_EMPTY = -10001;
    constexpr int32_t ERR_DH_FWK_REMOTE_DEVICE_ID_IS_EMPTY = -10002;
    constexpr int32_t ERR_DH_FWK_TYPE_NOT_EXIST = -10003;

    /* VersionManager errno, range: [-10200, -10299] */
    constexpr int32_t ERR_DH_FWK_VERSION_DEVICE_ID_NOT_EXIST = -10200;

    /* ComponentManager errno, range: [-10300, -10399] */
    constexpr int32_t ERR_DH_FWK_COMPONENT_INIT_SOURCE_FAILED = -10300;
    constexpr int32_t ERR_DH_FWK_COMPONENT_INIT_SINK_FAILED = -10301;
    constexpr int32_t ERR_DH_FWK_COMPONENT_ENABLE_FAILED = -10302;
    constexpr int32_t ERR_DH_FWK_COMPONENT_DISABLE_FAILED = -10303;
    constexpr int32_t ERR_DH_FWK_COMPONENT_ENABLE_TIMEOUT = -10304;
    constexpr int32_t ERR_DH_FWK_COMPONENT_DISABLE_TIMEOUT = -10305;
    constexpr int32_t ERR_DH_FWK_COMPONENT_REGISTER_FAILED = -10306;
    constexpr int32_t ERR_DH_FWK_COMPONENT_UNREGISTER_FAILED = -10007;
    constexpr int32_t ERR_DH_FWK_COMPONENT_GET_REMOTE_SA_FAILED = -10008;
    constexpr int32_t ERR_DH_FWK_COMPONENT_GET_SINK_VERSION_FAILED = -10009;

    /* ResourceManager errno, range: [-10400, -10499] */
    constexpr int32_t ERR_DH_FWK_RESOURCE_DB_ADAPTER_POINTER_NULL = -10400;
    constexpr int32_t ERR_DH_FWK_RESOURCE_KV_STORAGE_POINTER_NULL = -10401;
    constexpr int32_t ERR_DH_FWK_RESOURCE_DB_ADAPTER_OPERATION_FAIL = -10402;
    constexpr int32_t ERR_DH_FWK_RESOURCE_KV_STORAGE_OPERATION_FAIL = -10403;
    constexpr int32_t ERR_DH_FWK_RESOURCE_CAPABILITY_MAP_NOT_FOUND = -10404;
    constexpr int32_t ERR_DH_FWK_RESOURCE_DB_MANUAL_SYNC_FAIL = -10405;
    constexpr int32_t ERR_DH_FWK_RESOURCE_INIT_DB_FAILED = -10406;
    constexpr int32_t ERR_DH_FWK_RESOURCE_UNINIT_DB_FAILED = -10407;
    constexpr int32_t ERR_DH_FWK_RESOURCE_REGISTER_DB_FAILED = -10408;
    constexpr int32_t ERR_DH_FWK_RESOURCE_UNREGISTER_DB_FAILED = -10409;
    constexpr int32_t ERR_DH_FWK_RESOURCE_KEY_IS_EMPTY = -10410;

    /* DistributedHardwareManager errno, range: [-10500, -10599] */
    constexpr int32_t ERR_DH_FWK_HARDWARE_MANAGER_DEVICE_REPEAT_ONLINE = -10500;
    constexpr int32_t ERR_DH_FWK_HARDWARE_MANAGER_DEVICE_REPEAT_OFFLINE = -10501;
    constexpr int32_t ERR_DH_FWK_HARDWARE_MANAGER_LOAD_IMPL_FAILED = -10502;
    constexpr int32_t ERR_DH_FWK_HARDWARE_MANAGER_LIB_IMPL_OPEN_FAILED = -10503;
    constexpr int32_t ERR_DH_FWK_HARDWARE_MANAGER_LIB_IMPL_GET_INSTANCE_FAILED = -10504;
    constexpr int32_t ERR_DH_FWK_HARDWARE_MANAGER_LIB_IMPL_IS_NULL = -10505;

    /* ComponentLoader errno, range: [-10600, -10699] */
    constexpr int32_t ERR_DH_FWK_LOADER_HANDLER_IS_NULL = -10600;
    constexpr int32_t ERR_DH_FWK_LOADER_COMPONENT_PROFILE_IS_EMPTY = -10601;
    constexpr int32_t ERR_DH_FWK_LOADER_GET_LOCAL_VERSION_FAIL = -10602;
    constexpr int32_t ERR_DH_FWK_LOADER_DLCLOSE_FAIL = -10603;

    /* Task errno, range: [-10700, -10799] */
    constexpr int32_t ERR_DH_FWK_TASK_TIMEOUT = -10700;

    /* DistributedHardwareService errno, range: [-10800, -10899] */
    constexpr int32_t ERR_DH_FWK_SERVICE_IPC_WRITE_PARA_FAIL = -10800;
    constexpr int32_t ERR_DH_FWK_SERVICE_IPC_SEND_REQUEST_FAIL = -10801;
    constexpr int32_t ERR_DH_FWK_SERVICE_IPC_READ_PARA_FAIL = -10802;
    constexpr int32_t ERR_DH_FWK_SERVICE_STRING_IS_EMPTY = -10803;
    constexpr int32_t ERR_DH_FWK_SERVICE_LOCAL_VERSION_NOT_EXIST = -10804;
    constexpr int32_t ERR_DH_FWK_SERVICE_WRITE_TOKEN_FAIL = -10805;
    constexpr int32_t ERR_DH_FWK_SERVICE_REMOTE_IS_NULL = -10806;

    /* AccessManager errno, range: [-10900, -10999] */
    constexpr int32_t ERR_DH_FWK_ACCESS_INIT_DM_FAILED = -10900;
    constexpr int32_t ERR_DH_FWK_ACCESS_UNINIT_DM_FAILED = -10901;
    constexpr int32_t ERR_DH_FWK_ACCESS_REGISTER_DM_FAILED = -10902;
    constexpr int32_t ERR_DH_FWK_ACCESS_UNREGISTER_DM_FAILED = -10903;

    /* Hidump errno, range: [-11000, -11000] */
    constexpr int32_t ERR_DH_FWK_HIDUMP_ERROR = -11000;
    constexpr int32_t ERR_DH_FWK_HIDUMP_INVALID_ARGS = -11001;
    constexpr int32_t ERR_DH_FWK_HIDUMP_DPRINTF_ERROR = -11002;
} // namespace DistributedHardware
} // namespace OHOS
#endif
