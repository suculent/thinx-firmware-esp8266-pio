# thinx-esp8266-firmware-pio

Firmware for automatic device registration and OTA updates.
Can be assembled and managed by [Remote Things Management](https://rtm.thinx.cloud) based on [THiNX OpenSource IoT platform](https://thinx.cloud).

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/391e02d431bc45b5a1c7a59e48b109a6)](https://www.codacy.com/app/suculent/thinx-firmware-esp8266-pio?utm_source=github.com&utm_medium=referral&utm_content=suculent/thinx-firmware-esp8266-pio&utm_campaign=badger)

Arduino firmware for THiNX providing device management and automatic (webhook-based) OTA (over-the-air) firmware builds and updates.

Provides example implementations for ESP8266 with PlatformIO.

* This is a work in progress.
* 100% functionality is not guaranteed for all the time.

# Requirements

### IDE

- Platform.io
- Open this folder using Atom with installed Platform.io

# Installation

### Arduino IDE

Search for `THiNXLib` in Arduino Library Manager and install all other dependencies... or you can just copy then from the `lib` folder if you prefer tested versions before the latest.

### PlatformIO Library Manager

Library Review in progress at: `http://images.thinx.cloud/platformio/library.json`

# Usage

1. Create account on the RTM [https://rtm.thinx.cloud/](https://rtm.thinx.cloud/) site
2. Create an API Key
3. Clone [ESP8266 app repository](https://github.com/suculent/thinx-firmware-esp8266-pio)
4. You can store Owner ID and API Key in Thinx.h file in case your project is NOT stored in public repository. Otherwise insert API key using WiFiManager AP portal and owner will be fetched from backend.
5. Build and upload the code to your device.
6. After restart, connect with some device to WiFi AP 'AP-THiNX' and copy-paste the API Key and Owner ID, if you haven't hardcoded it in step 4
7. Device will connect to WiFi and register itself. Check your thinx.cloud dashboard for new device.

... Then you can add own git source, add ssh-keys to access those sources if not public, attach the source to device to dashboard and click the last icon in row to build/update the device.

Note: In case you'll build/upload your project (e.g. the library) using thinx.cloud, API key will be injected automatically by THiNX CI and you should not need to set it up anymore.

# More Examples

[THiNX Device API Wiki](https://github.com/suculent/thinx-device-api/wiki)

# Environment Variable Support

You provide callback receiving String using `setPushConfigCallback()` method. Whenever device receives MQTT update with `configuration` key, it will provide all environment variables to you.

> This may be also used for the WiFi Migration procedure.
