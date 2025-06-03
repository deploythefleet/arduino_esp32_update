#include "DTF_ESP32Update.h"
#include "dtf_ota.h"
#include <stdint.h>

DTF_ESP32Update::UpdateResponse DTF_ESP32Update::getFirmwareUpdate(
    const char* productId, 
    const char* currentVersion, 
    DTF_ESP32Update::RebootOption rebootOption 
)
{
    const dtf_ota_cfg_t cfg = {
        .product_id = productId,
        .custom_version = currentVersion,
        .reboot_option = static_cast<DTF_RebootOption>(rebootOption)
    };
    DTF_OtaResponse response = (DTF_OtaResponse)dtf_get_firmware_update(&cfg);
    return static_cast<DTF_ESP32Update::UpdateResponse>(response);
}