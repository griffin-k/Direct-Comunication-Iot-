#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "hi";
const char* password = "00000000";

WebServer server(80);

void setup() {
    Serial.begin(115200);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    server.on("/sendString", HTTP_GET, [](){
        String dataReceived = server.arg("data");
        Serial.println("Received data: " + dataReceived);
        server.send(200, "text/plain", "Data received by ESP");
    });

    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient();
}
