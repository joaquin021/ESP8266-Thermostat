const char HOME_JS[] PROGMEM = R"=====(
function getWifiConfig() {
    var xmlhttp = new XMLHttpRequest();

    xmlhttp.onreadystatechange = function() {
        if (xmlhttp.readyState == XMLHttpRequest.DONE) {
            if (xmlhttp.status == 200) {
                var response = JSON.parse(xmlhttp.responseText);
                document.getElementById("wifiSSID").innerHTML = response.ssid;
                document.getElementById("wifiIP").innerHTML = response.ip;
                document.getElementById("wifiConfig").style.display = "block";
                if(response.apIp == "(IP unset)") {
                    document.getElementById("softAPMessage").style.display = "none";
                } else {
                    document.getElementById("softAPMessage").style.display = "block";
                }
            } else {
                console.log('error', xmlhttp);
                document.getElementById("wifiConfig").style.display = "none";
            }
        }
    };

    xmlhttp.open("GET", "getWifiConfig", true);
    xmlhttp.send();
}

function getMqttConfig() {
    var xmlhttp = new XMLHttpRequest();

    xmlhttp.onreadystatechange = function() {
        if (xmlhttp.readyState == XMLHttpRequest.DONE) {
            if (xmlhttp.status == 200) {
                var response = JSON.parse(xmlhttp.responseText);
                document.getElementById("mqttServer").innerHTML = response.server;
                document.getElementById("mqttPort").innerHTML = response.port;
                document.getElementById("mqttClientId").innerHTML = response.clientId;
                document.getElementById("mqttUser").innerHTML = response.user;
                document.getElementById("mqttConfig").style.display = "block";
            } else {
                console.log('error', xmlhttp);
                document.getElementById("mqttConfig").style.display = "none";
            }
        }
    };

    xmlhttp.open("GET", "getMqttConfig", true);
    xmlhttp.send();
}

function getTopicsData() {
    var xmlhttp = new XMLHttpRequest();

    xmlhttp.onreadystatechange = function() {
        if (xmlhttp.readyState == XMLHttpRequest.DONE) {
            if (xmlhttp.status == 200) {
                var response = JSON.parse(xmlhttp.responseText);
                document.getElementById("topicPrefix").innerHTML = response.topicPrefix;
                document.getElementById("temperatureTopic").innerHTML = response.temperatureTopic;
                document.getElementById("humidityTopic").innerHTML = response.humidityTopic;
                document.getElementById("changeModeTopic").innerHTML = response.changeModeTopic;
                document.getElementById("changeTargetTemperatureTopic").innerHTML = response.changeTargetTemperatureTopic;
                document.getElementById("targetTemperatureTopic").innerHTML = response.targetTemperatureTopic;
                document.getElementById("availabilityTopic").innerHTML = response.availabilityTopic;
                document.getElementById("modeTopic").innerHTML = response.modeTopic;
                document.getElementById("actionTopic").innerHTML = response.actionTopic;
            } 
        }
    };

    xmlhttp.open("GET", "getTopicsData", true);
    xmlhttp.send();
}

function getThermostatData() {
    var xmlhttp = new XMLHttpRequest();

    xmlhttp.onreadystatechange = function() {
        if (xmlhttp.readyState == XMLHttpRequest.DONE) {
            if (xmlhttp.status == 200) {
                var response = JSON.parse(xmlhttp.responseText);
                document.getElementById("temperatureSensor").innerHTML = response.temperature;
                document.getElementById("humiditySensor").innerHTML = response.humidity;
                document.getElementById("hotToleranceData").innerHTML = response.hotTolerance;
                document.getElementById("coldToleranceData").innerHTML = response.coldTolerance;
                document.getElementById("temperatureStepData").innerHTML = response.temperatureStep;
                document.getElementById("targetTempData").innerHTML = response.targetTemp;
                document.getElementById("actionData").innerHTML = response.action;
                document.getElementById("modeData").innerHTML = response.mode;
                document.getElementById("conectivityActiveData").innerHTML = response.connectivityActive;
            } 
        }
    };

    xmlhttp.open("GET", "getThermostatData", true);
    xmlhttp.send();
}



function updateWifiStatusElement(wifiStatus) {
    document.getElementById('wifiStatus').innerHTML = wifiStatus;
    if (wifiStatus == "WL_CONNECTED") {
        getWifiConfig();
    } else {
        document.getElementById("wifiConfig").style.display = "none";
    }
}

function updateMqttStatusElement(mqttStatus) {
    document.getElementById('mqttStatus').innerHTML = mqttStatus;
    if (mqttStatus == "MQTT_CONNECTED") {
        getMqttConfig();
    } else {
        document.getElementById("mqttConfig").style.display = "none";
    }
}

(function scheduleAjax() {
    checkWifiStatus();
    checkMqttStatus();
    getTopicsData();
    getThermostatData();
    setTimeout(scheduleAjax, 60000);
})();
)=====";

const char ESP_CONFIG_JS[] PROGMEM = R"=====(
function checkWifiStatus() {
    var xmlhttp = new XMLHttpRequest();

    xmlhttp.onreadystatechange = function() {
        if (xmlhttp.readyState == XMLHttpRequest.DONE) {
            if (xmlhttp.status == 200) {
                updateWifiStatusElement(xmlhttp.responseText);
            } else {
                console.log('error', xmlhttp);
            }
        }
    };

    xmlhttp.open("GET", "checkWifiStatus", true);
    xmlhttp.send();
}

function checkMqttStatus() {
    var xmlhttp = new XMLHttpRequest();

    xmlhttp.onreadystatechange = function() {
        if (xmlhttp.readyState == XMLHttpRequest.DONE) {
            if (xmlhttp.status == 200) {
                updateMqttStatusElement(xmlhttp.responseText);
            } else {
                console.log('error', xmlhttp);
            }
        }
    };

    xmlhttp.open("GET", "checkMqttStatus", true);
    xmlhttp.send();
}
)=====";