# VERBOSE := 1
SINGLE_THREAD := 1
USE_PREBUILD := 1

ESP_ADDR := "192.168.0.112"
ESP_PORT := 8266
ESP_PWD  := "a74dcez"

EA_DIR := C:/Users/nari/AppData/Local/Arduino15/packages/esp8266/
HLIB_DIR := $(EA_DIR)/hardware/esp8266/2.3.0/libraries
ULIB_DIR := C:/Users/nari/documents/Arduino/libraries

LIBS := $(HLIB_DIR)/ESP8266WiFi
LIBS += $(HLIB_DIR)/ESP8266mDNS
LIBS += $(HLIB_DIR)/ArduinoOTA

LIBS += $(ULIB_DIR)/Fontx

include makeEspArduino.mk

