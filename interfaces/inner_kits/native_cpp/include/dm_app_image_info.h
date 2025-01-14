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

#ifndef OHOS_DEVICE_MANAGER_APP_IMAGE_INFO_H
#define OHOS_DEVICE_MANAGER_APP_IMAGE_INFO_H

#include <cstdint>

#include "securec.h"

namespace OHOS {
namespace DistributedHardware {
class DmAppImageInfo {
public:
    DmAppImageInfo() = default;
    explicit DmAppImageInfo(uint8_t *appIcon_, int32_t appIconLen_, uint8_t *appThumbnail_, int32_t appThumbnailLen_)
    {
        SaveData(appIcon_, appIconLen_, appThumbnail_, appThumbnailLen_);
    }

    void Reset(uint8_t *appIcon_, int32_t appIconLen_, uint8_t *appThumbnail_, int32_t appThumbnailLen_)
    {
        SaveData(appIcon_, appIconLen_, appThumbnail_, appThumbnailLen_);
    }

    ~DmAppImageInfo()
    {
        if (appIcon != nullptr) {
            delete[] appIcon;
            appIcon = nullptr;
        }
        if (appThumbnail != nullptr) {
            delete[] appThumbnail;
            appThumbnail = nullptr;
        }
    }

    DmAppImageInfo(const DmAppImageInfo &other)
    {
        if (this != &other) {
            *this = other;
        }
    }

    DmAppImageInfo& operator=(const DmAppImageInfo &other)
    {
        if (this != &other) {
            SaveData(other.GetAppIcon(), other.GetAppIconLen(), other.GetAppThumbnail(), other.GetAppThumbnailLen());
        }
        return *this;
    }

    DmAppImageInfo(DmAppImageInfo&&) = delete;
    DmAppImageInfo& operator=(DmAppImageInfo&&) = delete;

    int32_t GetAppIconLen() const
    {
        return appIconLen;
    }

    const uint8_t *GetAppIcon() const
    {
        return appIcon;
    }

    int32_t GetAppThumbnailLen() const
    {
        return appThumbnailLen;
    }

    const uint8_t *GetAppThumbnail() const
    {
        return appThumbnail;
    }
private:
    void SaveData(const uint8_t *appIcon_, int32_t appIconLen_, const uint8_t *appThumbnail_, int32_t appThumbnailLen_)
    {
        if (appIconLen_ > 0 && appIconLen_ < ICON_MAX_LEN && appIcon_ != nullptr) {
            if (appIconLen < appIconLen_) {
                if (appIcon != nullptr && appIconLen > 0) {
                    delete[] appIcon;
                    appIcon = nullptr;
                    appIconLen = 0;
                }
                appIcon = new (std::nothrow) uint8_t[appIconLen_] {0};
            }
            if (appIcon != nullptr) {
                appIconLen = appIconLen_;
                (void)memcpy_s(appIcon, appIconLen, appIcon_, appIconLen_);
            }
        }
        if (appThumbnailLen_ > 0 && appThumbnailLen_ < THUMB_MAX_LEN && appThumbnail_ != nullptr) {
            if (appThumbnailLen < appThumbnailLen_) {
                if (appThumbnail != nullptr && appThumbnailLen > 0) {
                    delete[] appThumbnail;
                    appThumbnail = nullptr;
                    appThumbnailLen = 0;
                }
                appThumbnail = new (std::nothrow) uint8_t[appThumbnailLen_] {0};
            }
            if (appThumbnail != nullptr) {
                appThumbnailLen = appThumbnailLen_;
                (void)memcpy_s(appThumbnail, appThumbnailLen, appThumbnail_, appThumbnailLen_);
            }
        }
    }
private:
    int32_t appIconLen {0};
    uint8_t *appIcon {nullptr};
    int32_t appThumbnailLen {0};
    uint8_t *appThumbnail {nullptr};
    const int32_t ICON_MAX_LEN = 32 * 1024;
    const int32_t THUMB_MAX_LEN = 153 * 1024;
};
} // namespace DistributedHardware
} // namespace OHOS
#endif // OHOS_DEVICE_MANAGER_APP_IMAGE_INFO_H
