# Deploy the Fleet ESP32 Arduino Library
This changelog is updated with each release and should contain the following sections if applicable:
  - **Added**: For any new features that have been added since the last version was released 
  - **Changed**: To note any changes to the software's existing functionality 
  - **Deprecated**: To note any features that were once stable but are no longer and have thus been removed 
  - **Fixed**: Any bugs or errors that have been fixed should be so noted 
  - **Removed**: This notes any features that have been deleted and removed from the software 
  - **Security**: This notes any security-related changes

----
# 2.0.0
Initial version to support v2 of Deploy the Fleet

### Changed
  - `getFirmwareUpdate` now accepts a product ID instead of a full update URL
  - `DTF_ESP32Update::UpdateResponse` enum values differ from old `DTF_UpdateResponse` which may break existing code

### Deprecated
  - `DTF_UpdateResponse` has been deprecated in favor of `DTF_ESP32Update::UpdateResponse`
  - `DTF_RebootOption` has been deprecated in favor of `DTF_ESP32Update::RebootOption`
  - `DTF_SetTimeOption` has been full deprecated and removed from the API

----
# 1.0.8
### Fixed
  - Bundle ID not being sent on initial OTA attempt

----
# 1.0.7
### Added
  - Option to prevent automatic reboot of device after successful update
  - Additional fallback server with Deploy the Fleet operated TLS certificate
  - Library sends certificate bundle id

### Changed
  - NTP timeout reduced to 10 minutes from 16 hours
  - Use Arduino Core logging library mechanism instead of `Serial.println` and `DTF_DEBUG` define.
  
----
# 1.0.6
### Fixed
  - Added support for newer versions of ESP32 Arduino Core

----
# 1.0.5
### Added
  - Fallback certificate in the event primary pinned cert fails

### Changed
  - Primary pinned cert is now Let's Encrypt ISRG Root X1 instead of intermediate R3

----
# 1.0.4

### Changed
  - `setTime` defaults to false. Will not try to set time via NTP by default.

### Fixed
  - Compiler error when newer versions of arduino_esp32 library is pulled in.

----
# 1.0.3
This is the first release tracked in the changelog.

### Fixed
  - Compile issues in new versions of Arduino IDE
  - Examples were not showing in menu