#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
#define PIN D1

// WiFi SETTINGS
ESP8266WebServer server(80); // Initialize web server


// CSS Colors
String color1 = "#fff"; // Accent
String color2 = "#000000"; // Background
String color3 = "#2f3136"; // Bar
String color4 = "#bfbfbb"; // Text
String color5 = "#ffe500"; // Important Bar


// Ticker Settings
String ticker_message = "Hello, World!";
bool run_display = true;
int width = 64;
int height = 8;


 // Matrix Settings
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(width, height, PIN,
  NEO_MATRIX_BOTTOM    + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);
 
const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(255, 255, 0),matrix.Color(0, 0, 255), matrix.Color(255, 0, 255), matrix.Color(0, 255, 255), matrix.Color(255, 255, 255)};





String GenSettingsHTML(bool doSome)
{
  String settings_html = "<title>Arduino Ticker</title>\n"
                      "<font face=\"Courier New\">\n"
                      "<style type=\"text/css\">\n"
                      "    #submit {\n"
                      "        background-color: " + color1 + ";\n"
                      "        padding: .5em;\n"
                      "        -moz-border-radius: 5px;\n"
                      "        -webkit-border-radius: 5px;\n"
                      "        border-radius: 6px;\n"
                      "        color: " + color2 + ";\n"
                      "        font-family: 'verdana';\n"
                      "        font-size: 20px;\n"
                      "        text-decoration: none;\n"
                      "        border: none;\n"
                      "    }\n"
                      "    #submit:hover {\n"
                      "        border: none;\n"
                      "        background: cyan;\n"
                      "        box-shadow: 0px 0px 1px #777;\n"
                      "        color: black;\n"
                      "    }\n"
                      "    body\n"
                      "    {\n"
                      "        color: " + color1 + ";\n"
                      "        background-color: " + color2 + ";\n"
                      "    }\n"
                      "    .topnav {\n"
                      "        background-color: " + color3 + ";\n"
                      "        border-left: solid " + color1 + " 5px;\n"
                      "        border-radius: 3px;\n"
                      "        overflow: hidden;\n"
                      "    }\n"
                      "    .topnav a {\n"
                      "        float: left;\n"
                      "        color: " + color4 + ";\n"
                      "        text-align: center;\n"
                      "        padding: 4px 10px;\n"
                      "        text-decoration: none;\n"
                      "        font-size: 17px;\n"
                      "        border-radius: 3px;\n"
                      "        margin-top: 0.5rem;\n"
                      "        margin-left: 0.5rem;\n"
                      "        margin-right: 0.5rem;\n"
                      "        margin-bottom: 0.5rem;\n"
                      "    }\n"
                      "    .topnav a:hover {\n"
                      "        background-color: " + color1 + ";\n"
                      "        color: black;\n"
                      "    }\n"
                      "    .topnav-right {\n"
                      "        float: right;\n"
                      "    }\n"
                      "    h1 {\n"
                      "        font-size: 1.7rem;\n"
                      "        margin-top: 1rem;\n"
                      "        margin-left: auto;\n"
                      "        margin-right: auto;\n"
                      "        background: " + color3 + ";\n"
                      "        color: " + color4 + ";\n"
                      "        padding: 0.2em 1em;\n"
                      "        border-radius: 3px;\n"
                      "        border-left: solid " + color1 + " 5px;\n"
                      "        font-weight: 100;\n"
                      "    }\n"
                      "    h2 {\n"
                      "        font-size: 1rem;\n"
                      "        margin-top: 1rem;\n"
                      "        margin-left: auto;\n"
                      "        margin-right: auto;\n"
                      "        background: " + color3 + ";\n"
                      "        color: " + color4 + ";\n"
                      "        padding: 0.2em 1em;\n"
                      "        border-radius: 3px;\n"
                      "        border-left: solid " + color1 + " 5px;\n"
                      "        font-weight: 100;\n"
                      "    }\n"
                      "    h3 {\n"
                      "        font-size: 1rem;\n"
                      "        margin-top: 1rem;\n"
                      "        margin-left: auto;\n"
                      "        margin-right: auto;\n"
                      "        background: " + color5 + ";\n"
                      "        color: " + color2 + ";\n"
                      "        padding: 0.2em 1em;\n"
                      "        border-radius: 3px;\n"
                      "        font-weight: 100;\n"
                      "    }\n"
                      "    .column {\n"
                      "        margin-left: 10rem;\n"
                      "        margin-right: 10rem;\n"
                      "    }\n"
                      "    .column input {\n"
                      "        float: right;\n"
                      "        margin-top: 0.5rem;\n"
                      "        background: transparent;\n"
                      "        color: " + color4 + ";\n"
                      "        outline: 0;\n"
                      "        border: 0;\n"
                      "        border-bottom: solid " + color1 + " 2px;\n"
                      "        font-size: 14px;\n"
                      "    }\n"
                      "    .column input {\n"
                      "        clear: both;\n"
                      "    }\n"
                      "    .column span {\n"
                      "        margin-top: 0.5rem;\n"
                      "        display: inline-block;\n"
                      "    }\n"
                      "    .column about {\n"
                      "      font-size: +12px;\n"
                      "    }\n"
                      "\n"    
                      "    .prefix {\n"
                      "      display: flex;\n"
                      "        justify-content: space-between;\n"
                      "    }\n"
                      "\n"    
                      "    hr {\n"
                      "      border-color: " + color3 + ";\n"
                      "        background-color: " + color3 + ";\n"
                      "        height: 2px;\n"
                      "        border: none;\n"
                      "    }\n"
                      "</style>\n"
                      "<br>"
                      "<html><body>\n"
                      "    <br><br><br><br>"
                      "    <div style='margin-left: 10rem; margin-right: 10rem' class=\"column\">\n"
                      "        <form name='frm' method='get'>\n"
                      "            <center><span style=\"font-size: +14px\"/>WiFi Ticker</span></center>"
                      "            <br><br>"
                      "            <center><textarea style='width: 100%' type='text' name='ticker_message' placeholder='Ticker Message' col=30 rows=5> </textarea></center><br>"
                      "            <input type='submit' id='submit' value='Apply'>\n"
                      "        </form>\n"
                      "        <form name='frm2' action='/on' method='get'>\n"
                      "            <input type='submit' id='submit' value='Turn Ticker On'>\n"
                      "        </form>"
                      "        <form name='frm3' action='/off' method='get'>\n"
                      "            <input type='submit' id='submit' value='Turn Ticker Off'>\n"
                      "        </form>"
                      "    </div>\n"
                      "</body></html>\n";

  return settings_html;
}





void SetServerBehavior()
{  
  server.on("/", HandleClient);

  server.on("/on", AdjustOn);

  server.on("/off", AdjustOff);
  
  server.begin();
}





void AdjustOn()
{
  //if (authenticated)
  //{
  if (server.args() > 0)
  {
    Serial.println("Server arguments received");
    
    for (uint8_t i = 0; i < server.args(); i++)
    {
      //Serial.println(server.argName(i));

      // BRANCH STATEMENTS TO CHANGE CONFIGURATION
      if (server.argName(i) == "ticker_message" && server.arg(i).length() > 0)
      {
        ticker_message = server.arg(i);
        Serial.print("New Ticker Message: ");
        Serial.println(server.arg(i));
      }
    }
  }
  
  run_display = true;

  String settings_html = GenSettingsHTML(true);
  Serial.print("settings_html.length() -> ");
  Serial.println(settings_html.length());
  
  server.send(200, "text/html", settings_html);
  Serial.println("-----------------------------------------");
}





void AdjustOff()
{
  //if (authenticated)
  //{
  if (server.args() > 0)
  {
    Serial.println("Server arguments received");
    
    for (uint8_t i = 0; i < server.args(); i++)
    {
      //Serial.println(server.argName(i));

      // BRANCH STATEMENTS TO CHANGE CONFIGURATION
      if (server.argName(i) == "ticker_message" && server.arg(i).length() > 0)
      {
        ticker_message = server.arg(i);
        Serial.print("New Ticker Message: ");
        Serial.println(server.arg(i));
      }
    }
  }
  
  run_display = false;

  String settings_html = GenSettingsHTML(true);
  Serial.print("settings_html.length() -> ");
  Serial.println(settings_html.length());
  
  server.send(200, "text/html", settings_html);
  Serial.println("-----------------------------------------");
}






// Function to handle client at /
// No Args
// No Return
void HandleClient()
{
  //if (authenticated)
  //{
  if (server.args() > 0)
  {
    Serial.println("Server arguments received");
    
    for (uint8_t i = 0; i < server.args(); i++)
    {
      //Serial.println(server.argName(i));

      // BRANCH STATEMENTS TO CHANGE CONFIGURATION
      if (server.argName(i) == "ticker_message" && server.arg(i).length() > 0)
      {
        ticker_message = server.arg(i);
        Serial.print("New Ticker Message: ");
        Serial.println(server.arg(i));
      }
    }
  }
  
  String settings_html = GenSettingsHTML(true);
  Serial.print("settings_html.length() -> ");
  Serial.println(settings_html.length());
  
  server.send(200, "text/html", settings_html);
  Serial.println("-----------------------------------------");
  
}





// Function to start an AP if it cant connect to one
// SSID and Password Args
// Return start AP bool
bool startAP()
{
  Serial.println("Configuring Access Point...");
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Ticker", "password");

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  SetServerBehavior();

  return true;
}


 
void setup() {
  Serial.begin(115200);
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(5);
  matrix.setTextColor(colors[6]);

  startAP();
}
 
int x = matrix.width();
int mess_len = 0;
 
void loop() {
  server.handleClient();

  if (run_display)
  {
    matrix.fillScreen(0);
    matrix.setCursor(x, 0);
    matrix.print(ticker_message);
  
    mess_len = ticker_message.length() * -6;
   
    if(--x < mess_len) {
      x = matrix.width();
    }
    matrix.show();
    delay(45);
  }
  else
  {
    matrix.fillScreen(0);
    matrix.show();
  }
}
