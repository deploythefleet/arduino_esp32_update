#ifndef DTF_ESP32Update_H
#define DTF_ESP32Update_H

namespace DTF_ESP32Update
{

enum class UpdateResponse
{
    UnknownError = -1,
    NewFirmwareFlashed = 0,
    InvalidFirmwareImage = 1,
    NotEnoughMemory = 2,
    FirmwareWriteFailed = 3,
    NoUpdatesAvailable = 4,
    CertValidationFailed = 5,
};

enum class RebootOption : int
{
    NO_REBOOT = 0,
    REBOOT = 1,
};

UpdateResponse getFirmwareUpdate(
            const char* productId, 
            const char* currentVersion,
            RebootOption rebootOption = RebootOption::REBOOT
        );   

}  // namespace DTF_Arduino

#endif // DTF_ESP32Update_H