#include <ESP8266WiFi.h>

// ======= Wi-Fi Configuration =======
const char* ssid = "YOUR_SSID";          // Replace with your Wi-Fi SSID
const char* password = "YOUR_WIFI_PASSWORD";  // Replace with your Wi-Fi password

// ======= Static IP Configuration =======
IPAddress local_IP(192, 168, 0, 132);   // Desired static IP address
IPAddress gateway(192, 168, 0, 1);      // Gateway IP (usually your router's IP)
IPAddress subnet(255, 255, 255, 0);     // Subnet mask
IPAddress dns1(8, 8, 8, 8);             // Primary DNS (optional)
IPAddress dns2(8, 8, 4, 4);             // Secondary DNS (optional)

// ======= Pin Definitions =======
const int light1 = 5; //D1
const int light2 = 4; //D2
const int light3 = 0; //D3
const int light4 = 2; //D4

// ======= Server Setup =======
WiFiServer server(80);

// ======= Light States =======
bool light1State = false;
bool light2State = false;
bool light3State = false;
bool light4State = false;

void setup() {
  Serial.begin(115200);
  
  // Initialize light pins as outputs and set them to LOW (off)
  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);
  pinMode(light3, OUTPUT);
  pinMode(light4, OUTPUT);
  
  digitalWrite(light1, LOW);
  digitalWrite(light2, LOW);
  digitalWrite(light3, LOW);
  digitalWrite(light4, LOW);
  
  // Configure static IP
  if (!WiFi.config(local_IP, gateway, subnet, dns1, dns2)) {
    Serial.println("STA Failed to configure");
  }
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.print("Connecting to Wi-Fi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("Connected to Wi-Fi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
  // Start the server
  server.begin();
}

void loop() {
  WiFiClient client = server.available();  // Listen for incoming clients

  if (client) {
    Serial.println("New client connected");
    String currentLine = "";
    String request = "";
    
    // Read the incoming request
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            break;  // End of headers
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
        
        request += c;
      }
    }
    
    // Handle the request
    if (request.indexOf("GET /toggle") != -1) {
      handleToggleRequest(client, request);
    } else if (request.indexOf("GET /") != -1) {
      serveHTML(client);
    }
    
    // Close the connection
    client.stop();
    Serial.println("Client disconnected");
  }
}

// Function to handle AJAX toggle requests
void handleToggleRequest(WiFiClient& client, String request) {
  int lightNumber = -1;
  
  // Parse the light number from the request
  int lightIndex = request.indexOf("light=");
  if (lightIndex != -1) {
    lightNumber = request.substring(lightIndex + 6).toInt();
  }
  
  if (lightNumber >= 1 && lightNumber <= 4) {
    toggleLight(lightNumber);
  }
  
  // Send JSON response with current states
  String jsonResponse = "{";
  jsonResponse += "\"light1\":" + String(light1State) + ",";
  jsonResponse += "\"light2\":" + String(light2State) + ",";
  jsonResponse += "\"light3\":" + String(light3State) + ",";
  jsonResponse += "\"light4\":" + String(light4State);
  jsonResponse += "}";
  
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println("Access-Control-Allow-Origin: *"); // Allow CORS
  client.println("Connection: close");
  client.println();
  client.println(jsonResponse);
}

// Function to toggle light states
void toggleLight(int lightNumber) {
  switch (lightNumber) {
    case 1:
      light1State = !light1State;
      digitalWrite(light1, light1State ? HIGH : LOW);
      Serial.println("Toggled Light 1 to " + String(light1State ? "ON" : "OFF"));
      break;
    case 2:
      light2State = !light2State;
      digitalWrite(light2, light2State ? HIGH : LOW);
      Serial.println("Toggled Light 2 to " + String(light2State ? "ON" : "OFF"));
      break;
    case 3:
      light3State = !light3State;
      digitalWrite(light3, light3State ? HIGH : LOW);
      Serial.println("Toggled Light 3 to " + String(light3State ? "ON" : "OFF"));
      break;
    case 4:
      light4State = !light4State;
      digitalWrite(light4, light4State ? HIGH : LOW);
      Serial.println("Toggled Light 4 to " + String(light4State ? "ON" : "OFF"));
      break;
    default:
      Serial.println("Invalid light number");
      break;
  }
}

// Function to serve the HTML page
void serveHTML(WiFiClient& client) {
  String html = "<!DOCTYPE html><html>";
  html += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  html += "<title>ESP8266 Light Control</title>";
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; }";
  html += "button { padding: 15px 25px; font-size: 16px; margin: 10px; }";
  html += "</style>";
  html += "<script>";
  
  html += "function toggleLight(light) {";
  html += "  var xhr = new XMLHttpRequest();";
  html += "  xhr.open('GET', '/toggle?light=' + light, true);";
  html += "  xhr.onreadystatechange = function() {";
  html += "    if (xhr.readyState == 4 && xhr.status == 200) {";
  html += "      var response = JSON.parse(xhr.responseText);";
  html += "      document.getElementById('light1').innerHTML = response.light1 ? 'ON' : 'OFF';";
  html += "      document.getElementById('light2').innerHTML = response.light2 ? 'ON' : 'OFF';";
  html += "      document.getElementById('light3').innerHTML = response.light3 ? 'ON' : 'OFF';";
  html += "      document.getElementById('light4').innerHTML = response.light4 ? 'ON' : 'OFF';";
  html += "    }";
  html += "  };";
  html += "  xhr.send();";
  html += "}";
  
  html += "</script>";
  html += "</head><body>";
  
  html += "<h1>ESP8266 Light Control</h1>";
  
  html += "<div>";
  html += "<p>Light 1: <span id=\"light1\">" + String(light1State ? "ON" : "OFF") + "</span></p>";
  html += "<button onclick=\"toggleLight(1)\">Toggle Light 1</button>";
  html += "</div>";
  
  html += "<div>";
  html += "<p>Light 2: <span id=\"light2\">" + String(light2State ? "ON" : "OFF") + "</span></p>";
  html += "<button onclick=\"toggleLight(2)\">Toggle Light 2</button>";
  html += "</div>";
  
  html += "<div>";
  html += "<p>Light 3: <span id=\"light3\">" + String(light3State ? "ON" : "OFF") + "</span></p>";
  html += "<button onclick=\"toggleLight(3)\">Toggle Light 3</button>";
  html += "</div>";
  
  html += "<div>";
  html += "<p>Light 4: <span id=\"light4\">" + String(light4State ? "ON" : "OFF") + "</span></p>";
  html += "<button onclick=\"toggleLight(4)\">Toggle Light 4</button>";
  html += "</div>";
  
  html += "</body></html>";
  
  // Send HTTP response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  client.println(html);
}
