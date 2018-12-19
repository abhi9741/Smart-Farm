#include <ESP8266WiFi.h>
 
const char* ssid = "MEC-Hostel";
const char* password = "Student@123$";
 
int ledPin = 13; // GPIO13---D7 of NodeMCU
const int trigPin = 5; 
const int echoPin = 4;
long duration;
float dist;

WiFiServer server(80);
 
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);
  delay(10);
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
   
  
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request

 
digitalWrite(trigPin, LOW);
 
delayMicroseconds(2);
 
// Sets the trigPin on HIGH state for 10 micro seconds
 
digitalWrite(trigPin, HIGH);
 
delayMicroseconds(10);
 
digitalWrite(trigPin, LOW);
 
// Reads the echoPin, returns the sound wave travel time in microseconds
 
duration = pulseIn(echoPin, HIGH);
 
// Calculating the distance

dist= (duration/2) / 29.1;
 
// Prints the distance on the Serial Monitor
 
Serial.print("Distance: ");
 dist=dist;
Serial.println(dist);
Serial.print("percentage filled :");
Serial.println((dist/5.0)*100);

  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, LOW);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, HIGH);
    value = LOW;
  }
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.println("Led is now: ");
 
  if(value == HIGH) {
    client.println("On");
  } else {
    client.println("Off");
  }
  client.println("distance");
  client.println(((7.01-dist)/7.01)*100.0);
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>On </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Off </button></a><br />");  
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
