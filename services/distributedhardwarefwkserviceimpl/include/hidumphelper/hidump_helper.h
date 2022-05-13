/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef OHOS_DISTRIBUTED_HARDWARE_HIDUMP_HELPER_H
#define OHOS_DISTRIBUTED_HARDWARE_HIDUMP_HELPER_H
#include <cstdint>
#include <set>
#include <string>

#include "enabled_comps_dump.h"
#include "device_type.h"
#include "single_instance.h"
#include "task.h"

namespace OHOS {
namespace DistributedHardware {

// class HidumpDeviceInfo {
// public:
//     HidumpDeviceInfo()
//     std::string dhId_;
//     DHType dhType_;

//     bool operator == (const DHInfo& other) const {
//         return ((this->dhId == other.dhId) && (this->dhType == other.dhType));
//     }
// private:
//     std::string dhId_;
//     DHType dhType_;
// };

class HidumpHelper {
DECLARE_SINGLE_INSTANCE_BASE(HidumpHelper);
public:
    int32_t Dump(const std::vector<std::string>& args, std::string &result);
    // void DumpLoadedComps(const DHType dhType);
    // void DumpUnloadedComps(const DHType dhType);

private:
    explicit HidumpHelper() = default;
    ~HidumpHelper() = default;

    // int32_t ProcessOneParam(const std::string& args, std::string &result);
    int32_t ProcessDump(const HidumpParam& hidumpParam, std::string &result);
    void ShowHelp(std::string &result);
    void ShowIllealInfomation(std::string &result);

// private:
//     std::set<HidumpDeviceInfo> deviceInfoSet_;
};

} // namespace DistributedHardware
} // namespace OHOS
#endif