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

#include "ipc_cmd_register.h"

#include "device_manager_errno.h"
#include "device_manager_log.h"

namespace OHOS {
namespace DistributedHardware {
IMPLEMENT_SINGLE_INSTANCE(IpcCmdRegister);

int32_t IpcCmdRegister::SetRequest(int32_t cmdCode, std::shared_ptr<IpcReq> pBaseReq, IpcIo &request,
    uint8_t *buffer, size_t buffLen)
{
    auto setRequestMapIter = setIpcRequestFuncMap_.find(cmdCode);
    if (setRequestMapIter == setIpcRequestFuncMap_.end()) {
        DMLOG(DM_LOG_ERROR, "cmdCode:%d not register SetRequestFunc", cmdCode);
        return DEVICEMANAGER_IPC_NOT_REGISTER_FUNC;
    }
    return (setRequestMapIter->second)(pBaseReq, request, buffer, buffLen);
}

int32_t IpcCmdRegister::ReadResponse(int32_t cmdCode, IpcIo &reply, std::shared_ptr<IpcRsp> pBaseRsp)
{
    auto readResponseMapIter = readResponseFuncMap_.find(cmdCode);
    if (readResponseMapIter == readResponseFuncMap_.end()) {
        DMLOG(DM_LOG_ERROR, "cmdCode:%d not register ReadResponseFunc", cmdCode);
        return DEVICEMANAGER_IPC_NOT_REGISTER_FUNC;
    }
    return (readResponseMapIter->second)(reply, pBaseRsp);
}

int32_t IpcCmdRegister::OnIpcCmd(int32_t cmdCode, IpcIo &reply, const IpcContext &ctx, void *ipcMsg)
{
    auto onIpcCmdMapIter = onIpcCmdFuncMap_.find(cmdCode);
    if (onIpcCmdMapIter == onIpcCmdFuncMap_.end()) {
        DMLOG(DM_LOG_ERROR, "cmdCode:%d not register OnIpcCmdFunc", cmdCode);
        return DEVICEMANAGER_IPC_NOT_REGISTER_FUNC;
    }
    (onIpcCmdMapIter->second)(reply, ctx, ipcMsg);
    return DEVICEMANAGER_OK;
}

int32_t IpcCmdRegister::OnIpcServerCmd(int32_t cmdCode, IpcIo &req, IpcIo &reply)
{
    auto onIpcServerCmdMapIter = onIpcServerCmdFuncMap_.find(cmdCode);
    if (onIpcServerCmdMapIter == onIpcServerCmdFuncMap_.end()) {
        DMLOG(DM_LOG_ERROR, "cmdCode:%d not register OnIpcCmdFunc", cmdCode);
        return DEVICEMANAGER_IPC_NOT_REGISTER_FUNC;
    }
    (onIpcServerCmdMapIter->second)(req, reply);
    return DEVICEMANAGER_OK;
}
} // namespace DistributedHardware
} // namespace OHOS
