// SPDX-License-Identifier: MIT

// SPDX-FileCopyrightText: 2019-2020 Stefan Schmidt
// SPDX-FileCopyrightText: 2020 Kosmas Raptis
// Modified by EqUiNoX

#include "dash_mount.h"
#include <stdio.h>
#include <winbase.h>
#include <xboxkrnl/xboxkrnl.h>

bool dashIsDriveMounted (char* driveName)
{
    NTSTATUS status;
    HANDLE handle;
    ANSI_STRING drivePath;
    CHAR drivePathBuffer[16];
    OBJECT_ATTRIBUTES objattr;

    sprintf(drivePathBuffer, "\\??\\%s:", driveName);
    RtlInitAnsiString(&drivePath, drivePathBuffer);

    InitializeObjectAttributes(&objattr, &drivePath, OBJ_CASE_INSENSITIVE, NULL, NULL);
    status = NtOpenSymbolicLinkObject(&handle, &objattr);
    if (NT_SUCCESS(status)) {
        NtClose(handle);
        return true;
    }

    return false;
}

bool dashMountDrive (char* driveName, const char *path)
{
    NTSTATUS status;
    ANSI_STRING drivePath;
    CHAR drivePathBuffer[16];
    ANSI_STRING mountPath;

    sprintf(drivePathBuffer, "\\??\\%s:", driveName);
    RtlInitAnsiString(&drivePath, drivePathBuffer);

    RtlInitAnsiString(&mountPath, path);

    status = IoCreateSymbolicLink(&drivePath, &mountPath);
    if (!NT_SUCCESS(status)) {
        SetLastError(RtlNtStatusToDosError(status));
        return false;
    }

    return true;
}

bool dashUnmountDrive (char* driveName)
{
    NTSTATUS status;
    ANSI_STRING drivePath;
    CHAR drivePathBuffer[16];

    sprintf(drivePathBuffer, "\\??\\%s:", driveName);
    RtlInitAnsiString(&drivePath, drivePathBuffer);

    status = IoDeleteSymbolicLink(&drivePath);
    if (!NT_SUCCESS(status)) {
        SetLastError(RtlNtStatusToDosError(status));
        return false;
    }

    return true;
}
