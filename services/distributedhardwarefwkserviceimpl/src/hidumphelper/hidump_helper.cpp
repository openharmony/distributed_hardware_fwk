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
#include "component_manager.h"
#include "distributed_hardware_errno.h"
#include "distributed_hardware_log.h"
#include "task_board.h"

namespace OHOS {
namespace DistributedHardware {
IMPLEMENT_SINGLE_INSTANCE(HidumpHelper);
namespace {
const std::string ARGS_HELP = "-h";
const std::string LOADED_COMP_LIST = "-l";
const std::string ENABLED_COMP_LIST = "-e";
const std::string TASK_LIST = "-t";
const std::string CAPABILITY_LIST = "-c";

const std::unordered_map<std::string, HidumpFlag> MAP_ARGS = {
    { ARGS_HELP, HidumpFlag::GET_HELP },
    { LOADED_COMP_LIST, HidumpFlag::GET_LOADED_COMP_LIST },
    { ENABLED_COMP_LIST, HidumpFlag::GET_ENABLED_COMP_LIST },
    { TASK_LIST, HidumpFlag::GET_TASK_LIST },
    { CAPABILITY_LIST, HidumpFlag::GET_CAPABILITY_LIST },
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
    { TaskStep::WAIT_UNREGISTGER_COMPLETE, "WAIT_UNREGISTGER_COMPLETE" },
};

std::unordered_map<TaskState, std::string> g_mapTaskState = {
    { TaskState::INIT, "INIT" },
    { TaskState::RUNNING, "RUNNING" },
    { TaskState::SUCCESS, "SUCCESS" },
    { TaskState::FAIL, "FAIL" },
};
}

int32_t HidumpHelper::Dump(const std::vector<std::string>& args, std::string &result)
{
    DHLOGI("HidumpHelper Dump args.size():%d.", args.size());
    result.clear();
    int32_t errCode = ERR_DH_FWK_HIDUMP_ERROR;

    if (args.empty()) {
        return ProcessDump(HidumpFlag::GET_HELP, result);
    }

    auto flag = MAP_ARGS.find(args[0]);
    if ((args.size() > 1) || (flag == MAP_ARGS.end())) {
        errCode = ProcessDump(HidumpFlag::UNKNOW, result);
    } else {
        errCode = ProcessDump(flag->second, result);
    }

    return errCode;
}

int32_t HidumpHelper::ProcessDump(const HidumpFlag &flag, std::string &result)
{
    DHLOGI("ProcessDump  Dump.");
    int32_t errCode = ERR_DH_FWK_HIDUMP_ERROR;
    switch (flag) {
        case HidumpFlag::GET_HELP: {
            errCode = ShowHelp(result);
            break;
        }
        case HidumpFlag::GET_LOADED_COMP_LIST: {
            errCode = ShowAllLoadedComps(result);
            break;
        }
        case HidumpFlag::GET_ENABLED_COMP_LIST : {
            errCode = ShowAllEnabledComps(result);
            break;
        }
        case HidumpFlag::GET_TASK_LIST : {
            errCode = ShowAllTaskInfos(result);
            break;
        }
        case HidumpFlag::GET_CAPABILITY_LIST : {
            errCode = ShowAllCapabilityInfos(result);
            break;
        }
        default: {
            errCode = ShowIllealInfomation(result);
            break;
        }
    }

    return errCode;
}

int32_t HidumpHelper::ShowAllLoadedComps(std::string &result)
{
    DHLOGI("Dump AllLoadedCompTypes.");
    std::set<DHType> loadedCompSource;
    std::set<DHType> loadedCompSink;
    ComponentManager::GetInstance().DumpLoadedComps(loadedCompSource, loadedCompSink);

    result.append("Local Loaded Components:\n{");
    result.append("\n    Source     : [");
    for (auto compSource : loadedCompSource) {
        result.append(" ");
        result.append(g_mapDhTypeName[compSource]);
        result.append(",");
    }
    result.replace(result.size() - 1, 1, " ");
    result.append("]");

    result.append("\n    Sink       : [");
    for (auto compSink : loadedCompSink) {
        result.append(" ");
        result.append(g_mapDhTypeName[compSink]);
        result.append(",");
    }
    result.replace(result.size() - 1, 1, " ");
    result.append("]");
    result.append("\n}\n");
    return DH_FWK_SUCCESS;
}

int32_t HidumpHelper::ShowAllEnabledComps(std::string &result)
{
    DHLOGI("Dump AllEnabledComps.");
    std::set<HidumpCompInfo> compInfoSet;
    EnabledCompsDump::GetInstance().Dump(compInfoSet);

    result.append("Enabled Components:");
    for (auto info : compInfoSet) {
        result.append("\n{");
        result.append("\n    DHType   : ");
        result.append(g_mapDhTypeName[info.dhType_]);
        result.append("\n    DHId     : ");
        result.append(GetAnonyString(info.dhId_));
        result.append("\n},");
    }
    result.replace(result.size() - 1, 1, "\n");
    return DH_FWK_SUCCESS;
}

int32_t HidumpHelper::ShowAllTaskInfos(std::string &result)
{
    DHLOGI("Dump AllTaskInfos.");
    std::unordered_map<std::string, std::shared_ptr<Task>> tasks;
    TaskBoard::GetInstance().DumpAllTasks(tasks);

    result.append("All Task Infos:");
    for (auto task : tasks) {
        result.append("\n{");
        result.append("\n    TaskType   : ");
        result.append(g_mapTaskType[task.second->GetTaskType()]);
        result.append("\n    DHType     : ");
        result.append(g_mapDhTypeName[task.second->GetDhType()]);
        result.append("\n    DHId       : ");
        result.append(GetAnonyString(task.second->GetDhId()));
        result.append("\n    TaskState  : ");
        result.append(g_mapTaskState[task.second->GetTaskState()]);
        result.append("\n    TaskStep   : [ ");
        std::vector<TaskStep> taskStep = task.second->GetTaskSteps();
        for (auto step : taskStep) {
            result.append(g_mapTaskStep[step]);
            result.append(" ");
        }
        result.append("]\n");
        result.append("},");
    }
    result.replace(result.size() - 1, 1, "\n");
    return DH_FWK_SUCCESS;
}

int32_t HidumpHelper::ShowAllCapabilityInfos(std::string &result)
{
    DHLOGI("GetAllAllCapabilityInfos  Dump.");
    CapabilityInfoMap capInfoMap;
    CapabilityInfoManager::GetInstance()->DumpCapabilityInfos(capInfoMap);
    
    result.append("All Capability Infos:");
    for (auto info : capInfoMap) {
        result.append("\n{");
        result.append("\n    DeviceName     : ");
        result.append(GetAnonyString(info.second->GetDeviceName()));
        result.append("\n    DeviceId       : ");
        result.append(GetAnonyString(info.second->GetDeviceId()));
        result.append("\n    DeviceType     : ");
        result.append(std::to_string(info.second->GetDeviceType()));
        result.append("\n    DHType         : ");
        result.append(g_mapDhTypeName[info.second->GetDHType()]);
        result.append("\n    DHId           : ");
        result.append(GetAnonyString(info.second->GetDHId()));
        result.append("\n    DHAttrs        : ");
        result.append(info.second->GetDHAttrs());
        result.append("\n},");
    }
    result.replace(result.size() - 1, 1, "\n");
    return DH_FWK_SUCCESS;
}

int32_t HidumpHelper::ShowHelp(std::string &result)
{
    DHLOGI("Show Dump Help.");
    result.append("Usage:dump  <options>\n");
    result.append("Description:\n");
    result.append(" -h    ");
    result.append(": Show help\n");
    result.append(" -l    ");
    result.append(": Show all loaded components\n");
    result.append(" -e    ");
    result.append(": Show all enabled components\n");
    result.append(" -t    ");
    result.append(": Show all tasks\n");
    result.append(" -c    ");
    result.append(": Show all capability infos\n\n");

    return DH_FWK_SUCCESS;
}

int32_t HidumpHelper::ShowIllealInfomation(std::string &result)
{
    DHLOGI("ShowIllealInfomation  Dump.");
    result.clear();
    result.append("unrecognized option, -h for help");
    return ERR_DH_FWK_HIDUMP_INVALID_ARGS;
}
} // namespace DistributedHardware
} // namespace OHOS