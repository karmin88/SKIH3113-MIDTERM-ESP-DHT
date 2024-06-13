// Libraries
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// WiFi credentials
const char* ssid = "minnn";
const char* password = "0125658452minnn";

// Server name
const char* serverName = "http://192.168.200.123/sensor/writedata.php";

// DHT11
#define DHTPIN D4          // Define the DHT sensor pin
#define DHTTYPE DHT11      // Define the type of DHT sensor
DHT dht(DHTPIN, DHTTYPE);  // Create a DHT sensor object

void setup() {
  Serial.begin(115200);  // Initialize serial communication at 115200 baud
  while (!Serial)
    ;
  dht.begin();  // Initialize DHT11 sensor
  Serial.print("Connecting to WiFi...");
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
}

void loop() {
  // Read sensor data
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if sensor readings are valid
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor! Skipping data save.");  // Print error message if readings are invalid
    delay(10000);                                                           // Delay for 10 seconds before the next reading
    return;                                                                 // Skip the rest of the loop
  }

  // Print sensor readings
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Check WiFi connection
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    // Domain name with URL path or IP address with path
    http.begin(client, serverName);

    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String httpRequestData = "temperature=" + String(temperature) + "&humidity=" + String(humidity);  // Create the POST data
    int httpResponseCode = http.POST(httpRequestData);                                                // Send the POST request

    if (httpResponseCode > 0) {
      String response = http.getString();  // Get the response from the server
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(http.errorToString(httpResponseCode));  // Print the error message
    }

    http.end();  // End the HTTP connection
  } else {
    Serial.println("Error in WiFi connection");
  }

  // Delay for 10 seconds
  delay(10000);
}
