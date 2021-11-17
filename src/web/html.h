const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<!DOCTYPE html>
<html class="no-js" lang="">

<head>
    <title>ESP8266 Thermostat Config</title>
    <meta charset="utf-8">
    <meta http-equiv="x-ua-compatible" content="ie=edge">
    <meta name="description" content="">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="vendor/google-fonts.css">
    <link rel="stylesheet" href="vendor/material.css">
    <link rel="stylesheet" href="asset/espconfig.css">
    <script src="vendor/material.js"></script>
    <script src="lib/espconfig.js"></script>
    <script src="lib/home.js"></script>
</head>

<body>
    <div class="mdl-layout mdl-js-layout mdl-layout--fixed-header">
        <header class="mdl-layout__header">
            <div class="mdl-layout__header-row">
                <span class="mdl-layout-title">Home</span>
            </div>
        </header>
        <div class="mdl-layout__drawer">
            <span class="mdl-layout-title">Thermostat Config</span>
            <nav class="mdl-navigation">
                <a class="mdl-navigation__link" href="/">Home</a>
                <a class="mdl-navigation__link" href="config-wifi.html">WiFi Config</a>
                <a class="mdl-navigation__link" href="config-mqtt.html">MQTT Config</a>
                <a class="mdl-navigation__link" href="config-thermostat.html">Thermostat Config</a>
                <a class="mdl-navigation__link" href="reboot.html">Reboot</a>
                <a class="mdl-navigation__link" href="reset.html">Reset</a>
            </nav>
        </div>
        <main class="mdl-layout__content">
            <div class="page-content">
                <div class="mdl-grid">
                    <div class="mdl-cell mdl-cell--12-col">
                        <h4>WiFi</h4>
                        <p><b>Status:</b> <span id="wifiStatus">WL_IDLE_STATUS</span></p>
                        <div style="display: none" id="wifiConfig">
                            <p><b>SSID:</b> <span id="wifiSSID"></span></p>
                            <p><b>IP:</b> <span id="wifiIP"></span></p>
                            <p style="display: none" id="softAPMessage"><span>To turn off the internal access point <a href="reboot.html">reboot</a> the device or toggle WiFi button.</span></p>
                        </div>
                    </div>
                </div>
                <div class="mdl-grid">
                    <div class="mdl-cell mdl-cell--12-col">
                        <h4>MQTT</h4>
                        <p><b>Status:</b> <span id="mqttStatus">MQTT_DISCONNECTED</span></p>
                        <div style="display: none" id="mqttConfig">
                            <p><b>Server:</b> <span id="mqttServer"></span></p>
                            <p><b>Port:</b> <span id="mqttPort"></span></p>
                            <p><b>Client id:</b> <span id="mqttClientId"></span></p>
                            <p><b>User:</b> <span id="mqttUser"></span></p>
                        </div>
                    </div>
                </div>
                <div class="mdl-grid">
                    <div class="mdl-cell mdl-cell--12-col">
                        <h4>Thermostat Data</h4>
                        <div id="thermostatData">
                            <p><b>Temperature:</b> <span id="temperatureSensor"></span>ºC</p>
                            <p><b>Humidity:</b> <span id="humiditySensor"></span>%</p>
                            <p><b>Hot tolerance:</b> <span id="hotToleranceData"></span>ºC</p>
                            <p><b>Cold tolerance:</b> <span id="coldToleranceData"></span>ºC</p>
                            <p><b>Temperature step:</b> <span id="temperatureStepData"></span>ºC</p>
                            <p><b>Target temperature:</b> <span id="targetTempData"></span>ºC</p>
                            <p><b>Action:</b> <span id="actionData"></span></p>
                            <p><b>Mode:</b> <span id="modeData"></span></p>
                            <p><b>Connectivity:</b> <span id="conectivityActiveData"></span></p>
                        </div>
                    </div>
                </div>
                <div class="mdl-grid">
                    <div class="mdl-cell mdl-cell--12-col">
                        <h4>Topics Data</h4>
                        <div id="topicsData">
                            <p><b>Topic prefix:</b> <span id="topicPrefix"></span></p>
                            <p><b>Temperature topic:</b> <span id="temperatureTopic"></span></p>
                            <p><b>Humidity topic:</b> <span id="humidityTopic"></span></p>
                            <p><b>Change mode topic:</b> <span id="changeModeTopic"></span></p>
                            <p><b>Change target temperature topic:</b> <span id="changeTargetTemperatureTopic"></span></p>
                            <p><b>Target temperature topic:</b> <span id="targetTemperatureTopic"></span></p>
                            <p><b>Availability topic:</b> <span id="availabilityTopic"></span></p>
                            <p><b>Mode topic:</b> <span id="modeTopic"></span></p>
                            <p><b>Action topic:</b> <span id="actionTopic"></span></p>
                        </div>
                    </div>
                </div>
            </div>
        </main>
    </div>
</body>

</html>
)=====";

const char FAVICON[1505] PROGMEM = {
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x08, 0x06, 0x00, 0x00, 0x00, 0x73, 0x7a, 0x7a, 0xf4, 0x00, 0x00, 0x05, 0xa8, 0x49, 0x44, 0x41, 0x54, 0x58, 0x47, 0xad, 0x97, 0x59, 0x6c, 0x54, 0x55, 0x18, 0xc7, 0x7f, 0xe7, 0xde, 0x29, 0x3b, 0x61, 0x91, 0x45, 0xd9, 0x44, 0x10, 0x2a, 0x10, 0x59, 0x12, 0xb8, 0x67, 0x58, 0x44, 0x88, 0x09, 0x61, 0x33, 0x88, 0x28, 0x42, 0x0c, 0xea, 0x1b, 0x91, 0x04, 0x83, 0x04, 0x0d, 0x91, 0x39, 0x65, 0xe8, 0x1d, 0x30, 0x20, 0x48, 0xe2, 0x0b, 0xca, 0x83, 0x51, 0x63, 0x0c, 0x10, 0x41, 0x31, 0x10, 0x21, 0x31, 0x20, 0x22, 0xa5, 0x77, 0x02, 0x12, 0x83, 0x12, 0x1b, 0xd6, 0xca, 0x26, 0xa1, 0x80, 0x10, 0x68, 0xe9, 0x74, 0xee, 0x1c, 0x73, 0xe6, 0x4e, 0xa7, 0x9d, 0xce, 0x50, 0x5a, 0xe2, 0xf7, 0x78, 0xce, 0xb7, 0xfc, 0xcf, 0xb7, 0x1f, 0xc1, 0xa3, 0x92, 0x1b, 0xff, 0x1c, 0xf4, 0x5b, 0x80, 0x00, 0xf6, 0xa1, 0xe4, 0x8c, 0x47, 0x51, 0x65, 0x84, 0x5b, 0x4f, 0xae, 0x77, 0x04, 0x18, 0x8f, 0x60, 0x1e, 0x29, 0x3a, 0x23, 0xf8, 0x02, 0x38, 0x86, 0x92, 0x4e, 0x6b, 0x95, 0xb5, 0x1e, 0x40, 0x54, 0x5b, 0xd8, 0x71, 0x1f, 0x78, 0x11, 0x25, 0xf7, 0xa4, 0x0d, 0xae, 0x2b, 0x1f, 0x8e, 0x2f, 0xfe, 0x24, 0xe2, 0x58, 0x08, 0xa1, 0x5b, 0x03, 0xe2, 0xc1, 0x00, 0xa2, 0xc7, 0x3a, 0x30, 0xfc, 0x5c, 0x2d, 0xf3, 0xe7, 0x1b, 0x63, 0x0d, 0xb4, 0x63, 0x87, 0x4d, 0xc5, 0x93, 0x49, 0x7c, 0x7f, 0x08, 0xd1, 0x09, 0x67, 0xd2, 0x17, 0xd1, 0xf8, 0xe3, 0xd8, 0xfa, 0x6a, 0x41, 0x00, 0x9f, 0x9c, 0x6e, 0x9b, 0xe6, 0x79, 0x67, 0x48, 0x6d, 0x21, 0x60, 0xf9, 0x00, 0xa2, 0x07, 0x3b, 0x61, 0x77, 0xa8, 0x02, 0x02, 0x41, 0xc1, 0x05, 0x56, 0x39, 0x83, 0x72, 0x5e, 0xe6, 0x7a, 0x17, 0x80, 0x1e, 0xf8, 0x75, 0x43, 0x09, 0x59, 0x02, 0x6d, 0xff, 0x05, 0xdc, 0x42, 0xc9, 0x01, 0x39, 0x46, 0x5c, 0xef, 0x0a, 0xf0, 0x44, 0xe6, 0xac, 0x9a, 0x22, 0xbb, 0x0f, 0x2b, 0xc7, 0xde, 0x6e, 0xcc, 0x93, 0x0f, 0xc0, 0xf5, 0xee, 0x03, 0xa7, 0x29, 0xae, 0x1c, 0xcd, 0xa9, 0x81, 0x3d, 0xb1, 0xf5, 0x65, 0xe0, 0x37, 0x94, 0x1c, 0x97, 0x15, 0xd4, 0x5a, 0x10, 0x8b, 0x57, 0x00, 0x43, 0x32, 0x67, 0x37, 0x28, 0xae, 0xec, 0x9d, 0xe3, 0x2d, 0xd7, 0xfb, 0x05, 0x70, 0xf0, 0xab, 0x7b, 0x40, 0xaf, 0x04, 0xf6, 0xdd, 0x38, 0x30, 0x02, 0x25, 0x8b, 0x1e, 0x0c, 0xe0, 0xe3, 0xb2, 0xf6, 0xdc, 0xb3, 0xab, 0xe9, 0xd2, 0xbd, 0x5d, 0xd6, 0x65, 0xb1, 0xf2, 0x39, 0x68, 0xf1, 0x3d, 0x4a, 0x16, 0x02, 0x7b, 0x0c, 0x48, 0xa2, 0x64, 0x38, 0xcf, 0xbd, 0xae, 0xa7, 0x41, 0xac, 0x40, 0x39, 0x9b, 0xd2, 0x77, 0x26, 0x14, 0xb7, 0x6f, 0xde, 0xc7, 0xaf, 0x6e, 0x4f, 0x74, 0xaa, 0x79, 0x64, 0xc6, 0xc1, 0x8d, 0x25, 0xa3, 0x07, 0xdb, 0x61, 0x77, 0xa8, 0xc1, 0x6f, 0xd3, 0x8d, 0xe8, 0x98, 0x7f, 0xd3, 0x57, 0xae, 0xf7, 0x2e, 0xb0, 0xa1, 0x29, 0xf2, 0xcc, 0x5d, 0x73, 0x00, 0xea, 0x80, 0x4d, 0x28, 0xb9, 0x32, 0xcd, 0xfb, 0xe1, 0xe1, 0x6e, 0x24, 0xdb, 0xdc, 0xc4, 0xef, 0xd4, 0x96, 0xe8, 0x88, 0x44, 0x61, 0x00, 0x81, 0xc1, 0xeb, 0x40, 0x47, 0x52, 0x7a, 0x16, 0x82, 0x69, 0x08, 0x61, 0x14, 0x7c, 0x89, 0x92, 0xa6, 0xe6, 0x73, 0xc9, 0xf5, 0x9a, 0x03, 0xb0, 0x01, 0x78, 0x0f, 0x58, 0x83, 0x10, 0xc7, 0xd1, 0x7a, 0x07, 0x70, 0x17, 0x25, 0x7b, 0x36, 0x9f, 0x03, 0x41, 0x7c, 0x83, 0x3a, 0x87, 0x3a, 0x10, 0x3b, 0x41, 0x2f, 0x40, 0xeb, 0xc5, 0x94, 0x84, 0xb7, 0xb2, 0xce, 0x7b, 0x8c, 0xa4, 0xf8, 0x0c, 0xa1, 0xc7, 0x02, 0x7d, 0x81, 0x0a, 0x8a, 0x2b, 0x47, 0xe5, 0xc6, 0x3f, 0xfe, 0x32, 0xe8, 0x9d, 0x80, 0x29, 0xd3, 0xe9, 0x40, 0x08, 0xf0, 0x88, 0x38, 0xe3, 0x9b, 0x96, 0x69, 0xcb, 0xfa, 0x40, 0xcc, 0x7b, 0x13, 0x9d, 0x6e, 0x36, 0x1e, 0x20, 0x81, 0x9b, 0xc0, 0x01, 0xa0, 0x17, 0x30, 0x09, 0xb0, 0xd0, 0x62, 0x0a, 0x25, 0xce, 0x21, 0x62, 0xde, 0x42, 0x34, 0xdf, 0x00, 0x6b, 0x51, 0x32, 0x52, 0xa8, 0xf4, 0x9a, 0xf7, 0xc0, 0x83, 0x24, 0x4a, 0xbd, 0x5d, 0x08, 0xe6, 0x62, 0x59, 0xcf, 0xb2, 0x6a, 0xdc, 0x1f, 0x39, 0x6c, 0xa5, 0xe5, 0x2e, 0x42, 0x18, 0x63, 0x6b, 0x80, 0xd5, 0xc0, 0x66, 0x94, 0x5c, 0xfe, 0x30, 0xe3, 0x41, 0x95, 0xe7, 0x24, 0xa1, 0xb6, 0x88, 0x8a, 0x54, 0x9e, 0x60, 0x10, 0x96, 0x14, 0x42, 0xbf, 0x42, 0x24, 0x6c, 0x5c, 0x9b, 0x4f, 0x31, 0xef, 0x00, 0x9a, 0xa9, 0x8d, 0x2e, 0xb6, 0xa0, 0xe4, 0x92, 0x82, 0xba, 0x1a, 0x75, 0xcb, 0x00, 0x80, 0xeb, 0xfd, 0x0c, 0x3c, 0x9f, 0x61, 0xae, 0x24, 0xe2, 0x3c, 0x95, 0xdb, 0x78, 0x8e, 0x4e, 0x01, 0xeb, 0x60, 0xc1, 0x52, 0x6c, 0x6c, 0xc1, 0x00, 0xdd, 0x7a, 0x3c, 0xc4, 0xf5, 0xe4, 0x02, 0xb4, 0xf8, 0x0a, 0x38, 0x8b, 0x92, 0x4f, 0xa7, 0x59, 0x82, 0x47, 0x54, 0x02, 0xfd, 0x33, 0x22, 0x07, 0x50, 0xf2, 0x05, 0x81, 0x1b, 0xdf, 0x0d, 0x7a, 0x36, 0x9a, 0x49, 0x84, 0xec, 0x5b, 0xf8, 0xfe, 0x51, 0xe0, 0x1a, 0x4a, 0x3e, 0x93, 0x66, 0x8c, 0x95, 0x2f, 0xca, 0x28, 0x4b, 0xa0, 0x64, 0xd0, 0x1d, 0x5b, 0x42, 0xd1, 0x13, 0x5d, 0xb1, 0x13, 0xb7, 0xb0, 0x98, 0xcd, 0x2a, 0xb9, 0x97, 0xa0, 0x7b, 0xf6, 0x42, 0x30, 0x19, 0x61, 0xdd, 0x27, 0x95, 0xfa, 0x1d, 0xf8, 0x49, 0x10, 0x34, 0x8c, 0x19, 0x28, 0x67, 0x5f, 0x60, 0xb0, 0xac, 0x2f, 0xda, 0xbe, 0x04, 0x18, 0x06, 0x43, 0xa3, 0x10, 0x7a, 0x35, 0x91, 0x70, 0x69, 0x4b, 0xec, 0xe6, 0xf0, 0xb8, 0xde, 0x21, 0x60, 0x0c, 0x70, 0x2e, 0xd0, 0x23, 0x06, 0x10, 0x71, 0x2e, 0x06, 0x76, 0xe2, 0xaf, 0xa1, 0xf5, 0x36, 0x03, 0x20, 0x05, 0x62, 0x66, 0x16, 0xc0, 0xda, 0xf8, 0x68, 0x52, 0xfa, 0x04, 0xe8, 0x23, 0x20, 0x4c, 0x6f, 0xef, 0x87, 0x92, 0x56, 0xab, 0x8d, 0x07, 0xde, 0x2b, 0x41, 0x8b, 0x28, 0xe8, 0x32, 0x10, 0x13, 0x41, 0x0f, 0x45, 0x85, 0x4f, 0x07, 0x00, 0xbc, 0x57, 0xd1, 0x6c, 0x37, 0x00, 0xbe, 0x03, 0xe6, 0x80, 0x35, 0x0c, 0x3f, 0x74, 0x0d, 0x3b, 0x71, 0x1e, 0xc1, 0x4d, 0x22, 0x72, 0x30, 0x6e, 0xf9, 0x4c, 0x10, 0x7b, 0x1f, 0x1a, 0xfb, 0x07, 0xa1, 0x73, 0xbd, 0x33, 0x68, 0x7c, 0x4a, 0x64, 0x31, 0xae, 0x67, 0xe2, 0xdf, 0x03, 0xdf, 0x7e, 0x92, 0x50, 0x6d, 0x47, 0x74, 0xe8, 0x2c, 0xf0, 0x63, 0x7d, 0x12, 0x9a, 0x41, 0x51, 0x3f, 0x6c, 0xae, 0xe1, 0x3b, 0x7d, 0xb2, 0xd5, 0xe0, 0x7a, 0x66, 0x1c, 0x5f, 0x46, 0x88, 0x05, 0xa4, 0x52, 0x05, 0x47, 0x6a, 0x9e, 0x7d, 0xcb, 0xb6, 0xd1, 0x29, 0x53, 0x92, 0xd3, 0xf1, 0xed, 0x9e, 0x44, 0xc7, 0x56, 0x11, 0xec, 0x11, 0x06, 0x44, 0xbf, 0x80, 0x5f, 0x9c, 0x44, 0x39, 0x23, 0x1b, 0xca, 0xd0, 0x64, 0xe9, 0x1a, 0x44, 0x5e, 0x19, 0x06, 0x43, 0xc4, 0x00, 0x1c, 0xd9, 0xca, 0x30, 0xdc, 0xc6, 0x4f, 0x8d, 0x26, 0x3a, 0xde, 0x24, 0x5f, 0x03, 0x19, 0x3b, 0x69, 0xfb, 0xc1, 0xe2, 0xd2, 0xb2, 0x4e, 0x18, 0xc4, 0x73, 0x19, 0x5a, 0x6c, 0x46, 0xb0, 0x8a, 0x88, 0x5c, 0x97, 0x56, 0x12, 0xcc, 0x82, 0x3a, 0x94, 0x34, 0x6d, 0x1b, 0xd6, 0x7a, 0xb3, 0x48, 0xb1, 0x07, 0xad, 0x17, 0x52, 0x12, 0xde, 0xd6, 0x12, 0xc0, 0x2d, 0x03, 0xe0, 0x7a, 0x8b, 0x81, 0x4f, 0x41, 0x2c, 0x41, 0x39, 0x5b, 0xb2, 0x8a, 0x03, 0x00, 0xb5, 0x28, 0x39, 0xb1, 0xe1, 0xac, 0x7c, 0x1a, 0x88, 0xfd, 0x08, 0xfd, 0x12, 0x91, 0xf0, 0xee, 0x87, 0x81, 0xc8, 0x07, 0xd0, 0x30, 0x8c, 0x4c, 0xcf, 0xaf, 0x01, 0x4c, 0x43, 0x79, 0x1b, 0x58, 0x8e, 0x92, 0x9b, 0x9b, 0x94, 0x99, 0x01, 0x50, 0x8d, 0x92, 0x93, 0x73, 0xce, 0x63, 0xe5, 0xf3, 0xd0, 0xe2, 0x5b, 0xe0, 0x23, 0x60, 0x19, 0x60, 0x03, 0x65, 0x28, 0xf9, 0x5c, 0x53, 0x40, 0x85, 0x96, 0x0c, 0x13, 0xb3, 0x7e, 0x08, 0xbd, 0x02, 0x2d, 0x06, 0x01, 0x4b, 0x41, 0xfc, 0x80, 0x72, 0xe6, 0xe4, 0xbd, 0x26, 0xf0, 0xc0, 0x6d, 0xd3, 0xd1, 0xf2, 0xee, 0x4a, 0xbd, 0xf5, 0x08, 0xde, 0x47, 0x8b, 0x8d, 0x58, 0x5c, 0x44, 0xeb, 0x8d, 0x40, 0x15, 0x4a, 0xf6, 0x69, 0xcc, 0x9b, 0x3f, 0x0b, 0xcc, 0xc6, 0x5b, 0x64, 0x77, 0xcd, 0xee, 0x6e, 0xa5, 0xde, 0x26, 0x04, 0x4b, 0x51, 0xb2, 0x4d, 0x41, 0x00, 0x82, 0x2a, 0x22, 0xd2, 0x8c, 0xdc, 0x5c, 0x72, 0xbd, 0x04, 0xe8, 0xed, 0xa8, 0xf0, 0xa2, 0xf4, 0xc5, 0xfa, 0x5f, 0x3b, 0x93, 0x28, 0xba, 0xd3, 0xfc, 0x42, 0x62, 0x36, 0x61, 0xdb, 0xbf, 0x97, 0xc3, 0x14, 0xf3, 0xe6, 0xa2, 0xd9, 0x55, 0x78, 0x25, 0x8b, 0x1f, 0x07, 0x7d, 0x2f, 0x2f, 0x04, 0x41, 0x82, 0xa6, 0xd0, 0xe2, 0x0d, 0x4a, 0x9c, 0xaf, 0xd3, 0x00, 0xb2, 0xba, 0x9b, 0x5b, 0xc9, 0x02, 0xc1, 0x3a, 0x04, 0x97, 0x28, 0xaa, 0x1b, 0x49, 0x4d, 0x47, 0x1b, 0x3b, 0x71, 0x15, 0x38, 0x81, 0x92, 0x13, 0xb2, 0x4f, 0x0c, 0xf2, 0xc4, 0x74, 0xb4, 0xc1, 0x99, 0xb3, 0x0a, 0x22, 0xce, 0xb0, 0x26, 0x9b, 0xf3, 0xe1, 0xf4, 0x52, 0x2a, 0xfc, 0x41, 0x24, 0xbb, 0x5c, 0xc7, 0xbe, 0x6b, 0x46, 0xf8, 0xc0, 0xa6, 0x9e, 0xcc, 0xcf, 0x81, 0x60, 0x77, 0xfb, 0x07, 0xa8, 0x77, 0xf9, 0xd5, 0xa6, 0x71, 0x23, 0xe6, 0x9d, 0x47, 0xd3, 0x07, 0xac, 0x91, 0x24, 0x45, 0x0d, 0x21, 0xff, 0x24, 0x70, 0x03, 0x25, 0x4d, 0xce, 0x04, 0x14, 0x80, 0x34, 0xe0, 0x7b, 0x67, 0x4e, 0x12, 0xf8, 0x6d, 0x7a, 0x67, 0x77, 0xcd, 0xcc, 0x61, 0x33, 0x1f, 0x93, 0xb2, 0xee, 0x60, 0x25, 0x89, 0x86, 0xef, 0xe4, 0x04, 0xb7, 0xfe, 0x63, 0x62, 0xeb, 0x11, 0x7c, 0x10, 0x3e, 0x95, 0xbe, 0x8b, 0xc5, 0xfb, 0xa3, 0xf5, 0xdf, 0xf8, 0x8e, 0x9d, 0xd7, 0xc8, 0xcc, 0xa2, 0x6b, 0x56, 0xb2, 0xe8, 0xd4, 0xbb, 0x85, 0x4a, 0xb2, 0x65, 0x7d, 0xa0, 0xb1, 0x64, 0xfd, 0xd7, 0x4c, 0x58, 0x92, 0xc8, 0x38, 0xd3, 0x21, 0xc1, 0x3d, 0x3a, 0x0c, 0xac, 0x53, 0xff, 0xef, 0xd7, 0xac, 0x10, 0xdc, 0xfa, 0xb3, 0xec, 0xe7, 0x54, 0x2c, 0xc2, 0x4f, 0x5d, 0xc1, 0x12, 0xfb, 0x33, 0x9f, 0x97, 0xfc, 0xff, 0x41, 0x73, 0x7a, 0x5a, 0xd5, 0x8a, 0xf3, 0xcb, 0xcc, 0x64, 0xf7, 0xeb, 0x99, 0x80, 0xef, 0x42, 0x85, 0xe7, 0x3d, 0xc4, 0x56, 0xc1, 0xeb, 0xff, 0x00, 0xee, 0x98, 0x40, 0xd8, 0xa0, 0x1e, 0x5d, 0xa5, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82};

const char CONFIG_MQTT_HTML[] PROGMEM = R"=====(
<!DOCTYPE html>
<html class="no-js" lang="">

<head>
    <title>ESP8266 Thermostat Config</title>
    <meta charset="utf-8">
    <meta http-equiv="x-ua-compatible" content="ie=edge">
    <meta name="description" content="">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="vendor/google-fonts.css">
    <link rel="stylesheet" href="vendor/material.css">
    <link rel="stylesheet" href="asset/espconfig.css">
    <script src="vendor/material.js"></script>
</head>

<body>
    <div class="mdl-layout mdl-js-layout mdl-layout--fixed-header">
        <header class="mdl-layout__header">
            <div class="mdl-layout__header-row">
                <span class="mdl-layout-title">MQTT Config</span>
            </div>
        </header>
        <div class="mdl-layout__drawer">
            <span class="mdl-layout-title">Thermostat Config</span>
            <nav class="mdl-navigation">
                <a class="mdl-navigation__link" href="/">Home</a>
                <a class="mdl-navigation__link" href="config-wifi.html">WiFi Config</a>
                <a class="mdl-navigation__link" href="config-mqtt.html">MQTT Config</a>
                <a class="mdl-navigation__link" href="config-thermostat.html">Thermostat Config</a>
                <a class="mdl-navigation__link" href="reboot.html">Reboot</a>
                <a class="mdl-navigation__link" href="reset.html">Reset</a>
            </nav>
        </div>
        <main class="mdl-layout__content">
            <div class="page-content">
                <form action="/setMqttConfig" method="post">
                    <div class="mdl-grid">
                        <div class="mdl-cell mdl-cell--12-col-desktop mdl-cell--8-col-tablet mdl-cell--4-col-phone">
                            <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
                                <input class="mdl-textfield__input" type="text" id="server" name="serverMqtt">
                                <label class="mdl-textfield__label" for="server">Server</label>
                            </div>
                        </div>
                    </div>
                    <div class="mdl-grid">
                        <div class="mdl-cell mdl-cell--12-col-desktop mdl-cell--8-col-tablet mdl-cell--4-col-phone">
                            <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
                                <input class="mdl-textfield__input" type="number" id="port" name="portMqtt" value="1883">
                                <label class="mdl-textfield__label" for="port">Port</label>
                            </div>
                        </div>
                    </div>
                    <div class="mdl-grid">
                        <div class="mdl-cell mdl-cell--12-col-desktop mdl-cell--8-col-tablet mdl-cell--4-col-phone">
                            <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
                                <input class="mdl-textfield__input" type="text" id="clientId" name="clientIdMqtt">
                                <label class="mdl-textfield__label" for="clientId">Client id</label>
                            </div>
                        </div>
                    </div>
                    <div class="mdl-grid">
                        <div class="mdl-cell mdl-cell--12-col-desktop mdl-cell--8-col-tablet mdl-cell--4-col-phone">
                            <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
                                <input class="mdl-textfield__input" type="text" id="user" name="userMqtt">
                                <label class="mdl-textfield__label" for="user">User</label>
                            </div>
                        </div>
                    </div>
                    <div class="mdl-grid">
                        <div class="mdl-cell mdl-cell--12-col-desktop mdl-cell--8-col-tablet mdl-cell--4-col-phone">
                            <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
                                <input class="mdl-textfield__input" type="password" id="password" name="passwordMqtt">
                                <label class="mdl-textfield__label" for="password">Password</label>
                            </div>
                        </div>
                    </div>
                    <div class="mdl-grid">
                        <div class="mdl-cell mdl-cell--12-col-desktop mdl-cell--8-col-tablet mdl-cell--4-col-phone">
                            <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
                                <input class="mdl-textfield__input" type="text" id="topicPrefix" name="topicPrefix">
                                <label class="mdl-textfield__label" for="topicPrefix">Topic prefix</label>
                            </div>
                        </div>
                    </div>
                    <div class="mdl-grid">
                        <div class="mdl-cell mdl-cell--12-col-desktop mdl-cell--8-col-tablet mdl-cell--4-col-phone">
                            <button class="mdl-button mdl-js-button mdl-button--raised mdl-button--colored" type="submit">Send</button>
                        </div>
                    </div>
                </form>
            </div>
        </main>
    </div>
</body>

</html>
)=====";

const char CONFIG_THERMOSTAT_HTML[] PROGMEM = R"=====(
<!DOCTYPE html>
<html class="no-js" lang="">

<head>
    <title>ESP8266 Thermostat Config</title>
    <meta charset="utf-8">
    <meta http-equiv="x-ua-compatible" content="ie=edge">
    <meta name="description" content="">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="vendor/google-fonts.css">
    <link rel="stylesheet" href="vendor/material.css">
    <link rel="stylesheet" href="asset/espconfig.css">
    <script src="vendor/material.js"></script>
</head>

<body>
    <div class="mdl-layout mdl-js-layout mdl-layout--fixed-header">
        <header class="mdl-layout__header">
            <div class="mdl-layout__header-row">
                <span class="mdl-layout-title">Thermostat Config</span>
            </div>
        </header>
        <div class="mdl-layout__drawer">
            <span class="mdl-layout-title">Thermostat Config</span>
            <nav class="mdl-navigation">
                <a class="mdl-navigation__link" href="/">Home</a>
                <a class="mdl-navigation__link" href="config-wifi.html">WiFi Config</a>
                <a class="mdl-navigation__link" href="config-mqtt.html">MQTT Config</a>
                <a class="mdl-navigation__link" href="config-thermostat.html">Thermostat Config</a>
                <a class="mdl-navigation__link" href="reboot.html">Reboot</a>
                <a class="mdl-navigation__link" href="reset.html">Reset</a>
            </nav>
        </div>
        <main class="mdl-layout__content">
            <div class="page-content">
                <form action="/setThermostatConfig" method="post">
                    <div class="mdl-grid">
                        <div class="mdl-cell mdl-cell--12-col-desktop mdl-cell--8-col-tablet mdl-cell--4-col-phone">
                            <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
                                <input class="mdl-textfield__input" type="number" id="hotTolerance" name="hotTolerance" step=".1" min="0.1" max="5">
                                <label class="mdl-textfield__label" for="hotTolerance">Hot tolerance</label>
                            </div>
                        </div>
                    </div>
                    <div class="mdl-grid">
                        <div class="mdl-cell mdl-cell--12-col-desktop mdl-cell--8-col-tablet mdl-cell--4-col-phone">
                            <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
                                <input class="mdl-textfield__input" type="number" id="coldTolerance" name="coldTolerance" step=".1" min="0.1" max="5">
                                <label class="mdl-textfield__label" for="coldTolerance">Cold Tolerance</label>
                            </div>
                        </div>
                    </div>
                    <div class="mdl-grid">
                        <div class="mdl-cell mdl-cell--12-col-desktop mdl-cell--8-col-tablet mdl-cell--4-col-phone">
                            <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
                                <input class="mdl-textfield__input" type="number" id="temperatureStep" name="temperatureStep" step=".1" min="0.1" max="5">
                                <label class="mdl-textfield__label" for="temperatureStep">Temperature step</label>
                            </div>
                        </div>
                    </div>
                    <div class="mdl-grid">
                        <div class="mdl-cell mdl-cell--12-col-desktop mdl-cell--8-col-tablet mdl-cell--4-col-phone">
                            <button class="mdl-button mdl-js-button mdl-button--raised mdl-button--colored" type="submit">Send</button>
                        </div>
                    </div>
                </form>
            </div>
        </main>
    </div>
</body>

</html>
)=====";

const char CONFIG_WIFI_HTML[] PROGMEM = R"=====(
<!DOCTYPE html>
<html class="no-js" lang="">

<head>
    <title>ESP8266 Thermostat Config</title>
    <meta charset="utf-8">
    <meta http-equiv="x-ua-compatible" content="ie=edge">
    <meta name="description" content="">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="vendor/google-fonts.css">
    <link rel="stylesheet" href="vendor/material.css">
    <link rel="stylesheet" href="asset/espconfig.css">
    <script src="vendor/material.js"></script>
</head>

<body>
    <div class="mdl-layout mdl-js-layout mdl-layout--fixed-header">
        <header class="mdl-layout__header">
            <div class="mdl-layout__header-row">
                <span class="mdl-layout-title">WiFi Config</span>
            </div>
        </header>
        <div class="mdl-layout__drawer">
            <span class="mdl-layout-title">Thermostat Config</span>
            <nav class="mdl-navigation">
                <a class="mdl-navigation__link" href="/">Home</a>
                <a class="mdl-navigation__link" href="config-wifi.html">WiFi Config</a>
                <a class="mdl-navigation__link" href="config-mqtt.html">MQTT Config</a>
                <a class="mdl-navigation__link" href="config-thermostat.html">Thermostat Config</a>
                <a class="mdl-navigation__link" href="reboot.html">Reboot</a>
                <a class="mdl-navigation__link" href="reset.html">Reset</a>
            </nav>
        </div>
        <main class="mdl-layout__content">
            <div class="page-content">
                <form action="/setWifiConfig" method="post">
                    <div class="mdl-grid">
                        <div class="mdl-cell mdl-cell--12-col-desktop mdl-cell--8-col-tablet mdl-cell--4-col-phone">
                            <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
                                <input class="mdl-textfield__input" type="text" id="ssid" name="ssid">
                                <label class="mdl-textfield__label" for="ssid">SSID</label>
                            </div>
                        </div>
                    </div>
                    <div class="mdl-grid">
                        <div class="mdl-cell mdl-cell--12-col-desktop mdl-cell--8-col-tablet mdl-cell--4-col-phone">
                            <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
                                <input class="mdl-textfield__input" type="password" id="password" name="password">
                                <label class="mdl-textfield__label" for="password">Password</label>
                            </div>
                        </div>
                    </div>
                    <div class="mdl-grid">
                        <div class="mdl-cell mdl-cell--12-col-desktop mdl-cell--8-col-tablet mdl-cell--4-col-phone">
                            <button class="mdl-button mdl-js-button mdl-button--raised mdl-button--colored" type="submit">Send</button>
                        </div>
                    </div>
                </form>
            </div>
        </main>
    </div>
</body>

</html>
)=====";

const char REBOOT_HTML[] PROGMEM = R"=====(
<!DOCTYPE html>
<html class="no-js" lang="">

<head>
    <title>ESP8266 Thermostat Config</title>
    <meta charset="utf-8">
    <meta http-equiv="x-ua-compatible" content="ie=edge">
    <meta name="description" content="">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="vendor/google-fonts.css">
    <link rel="stylesheet" href="vendor/material.css">
    <link rel="stylesheet" href="asset/espconfig.css">
    <script src="vendor/material.js"></script>
</head>

<body>
    <div class="mdl-layout mdl-js-layout mdl-layout--fixed-header">
        <header class="mdl-layout__header">
            <div class="mdl-layout__header-row">
                <span class="mdl-layout-title">Reboot</span>
            </div>
        </header>
        <div class="mdl-layout__drawer">
            <span class="mdl-layout-title">Thermostat Config</span>
            <nav class="mdl-navigation">
                <a class="mdl-navigation__link" href="/">Home</a>
                <a class="mdl-navigation__link" href="config-wifi.html">WiFi Config</a>
                <a class="mdl-navigation__link" href="config-mqtt.html">MQTT Config</a>
                <a class="mdl-navigation__link" href="config-thermostat.html">Thermostat Config</a>
                <a class="mdl-navigation__link" href="reboot.html">Reboot</a>
                <a class="mdl-navigation__link" href="reset.html">Reset</a>
            </nav>
        </div>
        <main class="mdl-layout__content">
            <div class="page-content">
                <form action="/reboot" method="post">
                    <div class="mdl-grid">
                        <div class="mdl-cell mdl-cell--12-col-desktop mdl-cell--8-col-tablet mdl-cell--4-col-phone">
                            <button class="mdl-button mdl-js-button mdl-button--raised mdl-button--colored" type="submit">Reboot</button>
                        </div>
                    </div>
                </form>
            </div>
        </main>
    </div>
</body>

</html>
)=====";

const char RESET_HTML[] PROGMEM = R"=====(
<!DOCTYPE html>
<html class="no-js" lang="">

<head>
    <title>ESP8266 Thermostat Config</title>
    <meta charset="utf-8">
    <meta http-equiv="x-ua-compatible" content="ie=edge">
    <meta name="description" content="">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="vendor/google-fonts.css">
    <link rel="stylesheet" href="vendor/material.css">
    <link rel="stylesheet" href="asset/espconfig.css">
    <script src="vendor/material.js"></script>
</head>

<body>
    <div class="mdl-layout mdl-js-layout mdl-layout--fixed-header">
        <header class="mdl-layout__header">
            <div class="mdl-layout__header-row">
                <span class="mdl-layout-title">Reset</span>
            </div>
        </header>
        <div class="mdl-layout__drawer">
            <span class="mdl-layout-title">Thermostat Config</span>
            <nav class="mdl-navigation">
                <a class="mdl-navigation__link" href="/">Home</a>
                <a class="mdl-navigation__link" href="config-wifi.html">WiFi Config</a>
                <a class="mdl-navigation__link" href="config-mqtt.html">MQTT Config</a>
                <a class="mdl-navigation__link" href="config-thermostat.html">Thermostat Config</a>
                <a class="mdl-navigation__link" href="reboot.html">Reboot</a>
                <a class="mdl-navigation__link" href="reset.html">Reset</a>
            </nav>
        </div>
        <main class="mdl-layout__content">
            <div class="page-content">
                <form action="/reset" method="post">
                    <div class="mdl-grid">
                        <div class="mdl-cell mdl-cell--12-col-desktop mdl-cell--8-col-tablet mdl-cell--4-col-phone">
                            <button class="mdl-button mdl-js-button mdl-button--raised mdl-button--colored" type="submit">Reset</button>
                        </div>
                    </div>
                </form>
            </div>
        </main>
    </div>
</body>

</html>
)=====";