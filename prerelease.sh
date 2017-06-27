#!/bin/bash

echo
echo "-=[ THiNX: Overriding header ]=-"
echo

# Use this before your own internal releases. Build server does it automatically.

THINX_FILE=$(find . | grep "/Thinx.h")
THINX_OWNER="eaabae0d5165c5db4c46c3cb6f062938802f58d9b88a1b46ed69421809f0bf7f" # todo: override with parameter
THINX_ALIAS="vanilla" # todo: override with parameter
THINX_CLOUD_URL="rtm.thinx.cloud" # IP causes crashes
THINX_MQTT_URL="${THINX_CLOUD_URL}" # mqtt://?

REPO_NAME='thinx-firmware-esp8266'
VERSION=$(git rev-list HEAD --count)
REPO_VERSION="1.6.${VERSION}"
BUILD_DATE=`date +%Y-%m-%d`

echo "//" > $THINX_FILE
echo "// This is an auto-generated file, it will be re-written by THiNX on cloud build." >> $THINX_FILE
echo "//" >> $THINX_FILE

echo "" >> $THINX_FILE

echo "#define THINX_COMMIT_ID \"$(git rev-parse HEAD)\"" >> $THINX_FILE
echo "#define THINX_MQTT_URL \"${THINX_MQTT_URL}\"" >> $THINX_FILE
echo "#define THINX_CLOUD_URL \"${THINX_CLOUD_URL}\"" >> $THINX_FILE
echo "#define THINX_FIRMWARE_VERSION = \"${REPO_NAME}-${REPO_VERSION}:${BUILD_DATE}\"" >> $THINX_FILE
echo "#define THINX_FIRMWARE_VERSION_SHORT = \"${REPO_VERSION}\""; >> $THINX_FILE
echo "#define THINX_APP_VERSION = \"${REPO_NAME}-${REPO_VERSION}:${BUILD_DATE}\"" >> $THINX_FILE

// dynamic variables
echo "#define THINX_OWNER \"${THINX_OWNER}\"" >> $THINX_FILE
echo "#define THINX_ALIAS \"${THINX_ALIAS}\"" >> $THINX_FILE
echo "#define THINX_API_KEY \"\"" >> $THINX_FILE

// debug only
echo "#define THINX_UDID \"\"" >> $THINX_FILE

echo "" >> $THINX_FILE

echo "#define THINX_MQTT_PORT 1883" >> $THINX_FILE
echo "#define THINX_API_PORT 7442" >> $THINX_FILE
