# ESP32 Arduino Core Deploy the Fleet Library

This library simplifies integration with the [Deploy the Fleet](https://deploythefleet.io) update service enabling secure OTA updates. It is meant for projects that currently use the [ESP32 Arduino Core](https://github.com/espressif/arduino-esp32) library.

## Requirements

  * Project built using [ESP32 Arduino Core](https://github.com/espressif/arduino-esp32) library
  * A [Deploy the Fleet](https://deploythefleet.io/docs/create-account/) account
  * Product Update URL from Deploy the Fleet dashboard

## Usage

The library's main class implements a static `getFirmwareUpdate` function that checks for a firmware update from Deploy the Fleet and automatically loads it if available. It then resets the device to run the new firmware if an update occurs. You can call this function from a button press handler or other location in your project where it makes sense to trigger an update.

```cpp
# define DTF_UPDATE_URL "[YOUR PRODUCT UPDATE URL]"

DTF_ESP32Update::getFirmwareUpdate(DTF_UPDATE_URL, "[CURRENT VERSION OF YOUR FIRMWARE]");
```

## License
MIT License

Copyright © 2020 MakerCrew, LLC

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.