/*
 * Copyright (c) 2022-2022 Huawei Device Co., Ltd.
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

#include "hidump_helper.h"

#include <unordered_map>

#include "capability_info_manager.h"
#include "distributed_hardware_log.h"
#include "task_board.h"

namespace OHOS {
namespace DistributedHardware {
IMPLEMENT_SINGLE_INSTANCE(HidumpHelper);
namespace {
const int32_t MIN_ARGS_SIZE = 0;
const int32_t MAX_ARGS_SIZE = 1;
const int32_t FIRST_PARAM = 0;
const std::string SEPARATOR = " | ";
const std::string TAB = "    ";
const std::string ARGS_HELP = "-h";
const std::string LOADED_COMP_LIST = "-loaded-list";

std::unordered_map<std::string, HidumpFlag> g_mapArgs = {
    { ARGS_HELP, HidumpFlag::GET_HELP },
    { LOADED_COMP_LIST, HidumpFlag::GET_LOADED_COMP_LIST },
};

std::unordered_map<DHType, std::string> g_mapDhTypeName = {
    { DHType::UNKNOWN, "UNKNOWN" },
    { DHType::CAMERA, "CAMERA" },
    { DHType::MIC, "MIC" },
    { DHType::SPEAKER, "SPEAKER" },
    { DHType::DISPLAY, "DISPLAY" },
    { DHType::GPS, "GPS" },
    { DHType::BUTTON, "BUTTON" },
    { DHType::HFP, "HFP" },
    { DHType::A2D, "A2D" },
    { DHType::VIRMODEM_MIC, "VIRMODEM_MIC" },
    { DHType::VIRMODEM_SPEAKER, "VIRMODEM_SPEAKER" },
};

std::unordered_map<TaskType, std::string> g_mapTaskType = {
    { TaskType::UNKNOWN, "UNKNOWN" },
    { TaskType::ENABLE, "ENABLE" },
    { TaskType::DISABLE, "DISABLE" },
    { TaskType::ON_LINE, "ON_LINE" },
    { TaskType::OFF_LINE, "OFF_LINE" },
};

std::unordered_map<TaskStep, std::string> g_mapTaskStep = {
    { TaskStep::DO_ENABLE, "DO_ENABLE" },
    { TaskStep::DO_DISABLE, "DO_DISABLE" },
    { TaskStep::SYNC_ONLINE_INFO, "SYNC_ONLINE_INFO" },
    { TaskStep::REGISTER_ONLINE_DISTRIBUTED_HARDWARE, "REGISTER_ONLINE_DISTRIBUTED_HARDWARE" },
    { TaskStep::UNREGISTER_OFFLINE_DISTRIBUTED_HARDWARE, "UNREGISTER_OFFLINE_DISTRIBUTED_HARDWARE" },
    { TaskStep::CLEAR_OFFLINE_INFO, "CLEAR_OFFLINE_INFO" },
    { TaskStep::WAIT_UNREGISTGER_COMPLET, "WAIT_UNREGISTGER_COMPLET" },
};

const std::unordered_map<TaskState, std::string> g_mapTaskState = {
    { TaskState::INIT, "INIT" },
    { TaskState::RUNNING, "RUNNING" },
    { TaskState::SUCCESS, "SUCCESS" },
    { TaskState::FAI, "FAILL" },
};
}

int32_t HidumpHelper::Dump(const std::vector<std::string>& args, std::string &result)
{
    DHLOGI("HidumpHelper Dump args.size():%d.", args.size());
    result.clear();
    int32_t errCode = DH_SUCCESS;
    int32_t argsSize = static_cast<int32_t>(args.size());
    for (int i = 0; i < args.size(); i++) {
        DHLOGI("HidumpHelper Dump args[%d]: %s.", i, args.at(i).c_str());
    }
    switch (argsSize) {
        case MIN_ARGS_SIZE: {
            errCode = ProcessDump(HidumpFlag::GET_HELP, result);
            break;
        }
        case MAX_ARGS_SIZE: {
            errCode = ProcessDump(g_mapArgs[args[FIRST_PARAM]], result);
            break;
        }
        default: {
            errCode = ERR_DH_SCREEN_HIDUMP_INVALID_ARGS;
            break;
        }
    }

    switch (errCode) {
        case DH_SUCCESS: {
            break;
        }
        case ERR_DH_FWK_HIDUMP_INVALID_ARGS: {
            ShowIllealInfomation(result);
            break;
        }
        default: {
            break;
        }
    }
    return errCode;
}

int32_t HidumpHelper::ProcessDump(const HidumpFlag &flag, std::string &result)
{
    DHLOGI("ProcessDump  Dump.");
    result.clear();
    int32_t errCode = ERR_DH_FWK_HIDUMP_ERROR;
    switch (flag) {
        case HidumpFlag::GET_HELP: {
            errCode = ShowHelp(result);
            break;
        }
        case HidumpFlag::GET_LOADED_COMP_LIST: {
            errCode = ShowAllLoadCompTypes(result);
            break;
        }
        default: {
            errCode = ERR_DH_FWK_HIDUMP_INVALID_ARGS;
            break;
        }
    }

    return errCode;
}
/*
void DumpLoadedComps(const DHType dhType)
{
    loadedCompsSet_.emplace(dhType);
}

void DumpUnloadedComps(const DHType dhType)
{
    auto it = loadedCompsSet_.find(dhType);
    if (it != loadedCompsSet_.end()) {
        loadedCompsSet_.earse(it);
    }
}
int32_t HidumpHelper::ShowAllLoadCompTypes(std::string &result)
{
    DHLOGI("GetAllLoadCompTypes  Dump.");
    result.append("loaded components:\n");
    result.append("    ");
    for (auto comp : loadedCompsSet_) {
        result.append(g_mapDhTypeName[comp]);
        result.append(SEPARATOR);
    }
    result.append("\n");
    return DH_SUCCESS;
}
*/

void HidumpHelper::ShowAllLoadedCompTypes(std::string &result)
{
    DHLOGI("Dump AllLoadedCompTypes.");
    std::set<DHType> loadedCompSource;
    std::set<DHType> loadedCompSink;
    ComponentManager::GetInstance().DumpLoadedComps(loadedCompSource, loadedCompSink);

    result.append("Local Loaded Components:\n");
    result.append("    Source: ");
    for (auto compSource : loadedCompSource) {
        result.append(g_mapDhTypeName[compSource]);
        result.append(SEPARATOR);
    }
    result.replce(result.size() - SEPARATOR.size(), SEPARATOR.size(), "  \n");

    result.append("    Sink: ");
    for (auto compSink : loadedCompSink) {
        result.append(g_mapDhTypeName[compSink]);
        result.append(SEPARATOR);
    }
    result.replce(result.size() - SEPARATOR.size(), SEPARATOR.size(), " \n\n");
}

/*
void HidumpHelper::DumpEnabledComps(const DHType dhType, const std::string &dhId)
{
    HidumpDeviceInfo info = {
        .dhId_ = dhId,
        .dhType_ = dhType,
    }
    deviceInfoSet_.emplace(info);
}

void HidumpHelper::DumpDisabledComps(const DHType dhType, const std::string &dhId)
{
    HidumpDeviceInfo info = {
        .dhId_ = dhId,
        .dhType_ = dhType,
    }
    auto it = enabledDeviceInfoSet_.find(info);
    if (it != enabledDeviceInfoSet_.end()) {
        deviceInfoSet_.earse(it);
    }
}
*/

void HidumpHelper::ShowAllEnabledComps(std::string &result)
{
    DHLOGI("Dump AllEnabledComps.");
    std::set<HidumpCompInfo> deviceInfoSet;
    EnabledCompsDump::GetInstance.Dump(deviceInfoSet);
    result.append("Enabled Components:\n");
    result.append(TAB);
    for (auto info : deviceInfoSet) {
        result.append(" DHType :");
        result.append(g_mapDhTypeName[info.dhType_]);
        result.append(" DHId :");
        result.append(GetAnonyString(info.dhId_));
        result.append(SEPARATOR);
    }
    result.replce(result.size() - SEPARATOR.size(), SEPARATOR.size(), " \n\n");
    return DH_SUCCESS;
}

int32_t HidumpHelper::ShowAllTaskInfos(std::string &result)
{
    DHLOGI("Dump AllTaskInfos.");
    std::unordered_map<std::string, std::shared_ptr<Task>> tasks;
    TaskBoard::GetInstance().DumpAllTask(tasks);

    result.append("All Task Infos:\n");
    
    for (auto task : tasks) {
        // std::string taskId = task.GetId();
        // std::string task.GetNetworkId();
        // std::string task.GetUUID();
        result.append(TAB);
        result.append(" TaskType :");
        // TaskType taskType = task.GetTaskType();
        result.append(g_mapTaskType[task.GetTaskType()]);
        result.append(" DHType :");
        result.append(g_mapDhTypeName[task.GetDhType()]);
        // std::string dhId = 
        result.append(" DHId :");
        result.append(GetAnonyString(task.GetDhId()));

        // TaskState taskState = GetTaskState();
        result.append(" TaskState :");
        result.append(g_mapTaskState[GetTaskState()]);

        result.append(" TaskStep :[ ");
        std::vector<TaskStep> taskStep = GetTaskSteps();
        for (auto step : taskStep) {
            result.append(g_mapTaskStep[step]);
            result.append(" ");
        }
        result.append("]\n");
    }
    result.append("\n");
}

void HidumpHelper::ShowAllCapabilityInfos(std::string &result)
{
    DHLOGI("GetAllAllCapabilityInfos  Dump.");
    // std::map<std::string, std::shared_ptr<CapabilityInfo>>;
    CapabilityInfoMap capInfoMap;
    CapabilityInfoManager::GetInstance()->DumpCapabilityInfos(capInfoMap);
    
    result.append("All Capability Infos:\n");
    for (auto info : capInfoMap) {
        result.append(TAB);
        result.append(" DeviceName :");
        result.append(GetAnonyString(info->GetDeviceName()));
        result.append(" DeviceId :");
        result.append(GetAnonyString(info->GetDeviceId()));        
        result.append(" DeviceType :");
        result.append(std::string(GetDeviceType()));
        result.append(" DHType :");
        result.append(g_mapDhTypeName[info->GetDhType()]);
        result.append(" DHId :");
        result.append(GetAnonyString(info->GetDHId()));
        result.append(" DHAttrs :");
        result.append(GetAnonyString(info->GetDHAttrs()));
        result.append("\n");
    }
    result.append("\n");
}

void HidumpHelper::ShowHelp(std::string &result)
{
    DHLOGI("ShowHelp  Dump.");
    result.append("Usage:dump  <options>\n")
          .append("Description:\n")
          .append("-loaded-comp-list    ")
          .append(": Show loaded components\n");

    return DH_SUCCESS;
}

void HidumpHelper::ShowIllealInfomation(std::string &result)
{
    DHLOGI("ShowIllealInfomation  Dump.");
    result.append("unrecognized option, -h for help");
}
} // namespace DistributedHardware
} // namespace OHOS