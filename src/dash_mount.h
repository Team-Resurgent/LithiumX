// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: 2019-2020 Stefan Schmidt
// Modified by EqUiNoX

#ifndef __NXDK_MOUNT_H__
#define __NXDK_MOUNT_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __cplusplus
#include <stdbool.h>
#endif

bool dashIsDriveMounted (char* driveName);
bool dashMountDrive (char* driveName, const char *path);
bool dashUnmountDrive (char* driveName);

#ifdef __cplusplus
}
#endif

#endif
