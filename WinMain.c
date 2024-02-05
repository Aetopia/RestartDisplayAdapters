#include <initguid.h>
#include <windows.h>
#include <setupapi.h>
#include <devguid.h>

int WinMainCRTStartup()
{
    HDEVINFO DeviceInfoSet = SetupDiGetClassDevsW(&GUID_DEVCLASS_DISPLAY, NULL, NULL, DIGCF_PRESENT);
    SP_DEVINFO_DATA DeviceInfoData = {.cbSize = sizeof(SP_DEVINFO_DATA)};
    SP_PROPCHANGE_PARAMS PropChangeParams = {
        .ClassInstallHeader = {.cbSize = sizeof(SP_CLASSINSTALL_HEADER), .InstallFunction = DIF_PROPERTYCHANGE},
        .Scope = DICS_FLAG_GLOBAL,
        .HwProfile = 0};

    for (DWORD MemberIndex = 0; SetupDiEnumDeviceInfo(DeviceInfoSet, MemberIndex, &DeviceInfoData); MemberIndex++)
    {
        PropChangeParams.StateChange = DICS_DISABLE;
        SetupDiSetClassInstallParamsW(DeviceInfoSet, &DeviceInfoData, &PropChangeParams.ClassInstallHeader,
                                      sizeof(SP_PROPCHANGE_PARAMS));
        SetupDiChangeState(DeviceInfoSet, &DeviceInfoData);

        PropChangeParams.StateChange = DICS_ENABLE;
        SetupDiSetClassInstallParamsW(DeviceInfoSet, &DeviceInfoData, &PropChangeParams.ClassInstallHeader,
                                      sizeof(SP_PROPCHANGE_PARAMS));
        SetupDiChangeState(DeviceInfoSet, &DeviceInfoData);
    }
    
    SetupDiDestroyDeviceInfoList(DeviceInfoSet);
    ExitProcess(0);
    return 0;
}
