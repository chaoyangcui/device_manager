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

#ifndef OHOS_DEVICE_MANAGER_IPC_NOTIFY_CHECK_AUTH_RESULT_REQ_H
#define OHOS_DEVICE_MANAGER_IPC_NOTIFY_CHECK_AUTH_RESULT_REQ_H

#include <cstdint>

#include "ipc_req.h"

namespace OHOS {
namespace DistributedHardware {
class IpcNotifyCheckAuthResultReq : public IpcReq {
DECLARE_IPC_MODEL(IpcNotifyCheckAuthResultReq);
public:
    std::string GetDeviceId() const
    {
        return deviceId_;
    }

    void SetDeviceId(std::string& deviceId)
    {
        deviceId_ = deviceId;
    }

    int32_t GetResult() const
    {
        return result_;
    }

    void SetResult(int32_t result)
    {
        result_ = result;
    }

    int32_t GetFlag() const
    {
        return flag_;
    }

    void SetFlag(int32_t flag)
    {
        flag_ = flag;
    }
private:
    std::string deviceId_;
    int32_t result_;
    int32_t flag_;
};
} // namespace DistributedHardware
} // namespace OHOS
#endif // OHOS_DEVICE_MANAGER_IPC_NOTIFY_CHECK_AUTH_RESULT_REQ_H
