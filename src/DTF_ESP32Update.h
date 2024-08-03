#ifndef DTF_ESP32Update_H
#define DTF_ESP32Update_H

enum class DTF_UpdateResponse
{
    UPDATE_FAILED = -1,
    NO_UPDATE_AVAILABLE = 1,
    UPDATE_SUCCEEDED = 2,
};

enum class DTF_SetTimeOption : int
{
    DO_NOT_SET_TIME = 0,
    SET_TIME = 1,
};

enum class DTF_RebootOption : int
{
    NO_REBOOT = 0,
    REBOOT = 1,
};

class DTF_ESP32Update
{
    public:
        static DTF_UpdateResponse getFirmwareUpdate(
            const char* updateUrl, 
            const char* currentVersion, 
            DTF_RebootOption rebootOption = DTF_RebootOption::REBOOT, 
            DTF_SetTimeOption setTimeOption = DTF_SetTimeOption::DO_NOT_SET_TIME
        );   
};

#endif // DTF_ESP32Update_H