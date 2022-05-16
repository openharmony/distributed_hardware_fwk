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

#ifndef OHOS_DISTRIBUTED_ENABLED_COMPS_DUMP_H
#define OHOS_DISTRIBUTED_ENABLED_COMPS_DUMP_H
#include <cstdint>
#include <set>
#include <string>

#include "device_type.h"
#include "single_instance.h"

namespace OHOS {
namespace DistributedHardware {

struct HidumpCompInfo {
    std::string dhId_;
    DHType dhType_;

    bool operator < (const HidumpCompInfo &other) const {
        return (((this->dhType_ == other.dhType_) && (this->dhId_ < other.dhId_)) ||
            (this->dhType_ < other.dhType_));
    }
};

class EnabledCompsDump {
DECLARE_SINGLE_INSTANCE_BASE(EnabledCompsDump);
public:
    void DumpEnabledComp(const DHType dhType, const std::string &dhId);
    void DumpDisabledComp(const DHType dhType, const std::string &dhId);

    void Dump(std::set<HidumpCompInfo> &compInfoSet);

private:
    explicit EnabledCompsDump() = default;
    ~EnabledCompsDump() = default;

    std::set<HidumpCompInfo> compInfoSet_;
};

} // namespace DistributedHardware
} // namespace OHOS
#endif